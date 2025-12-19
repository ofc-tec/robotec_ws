#!/usr/bin/env python3
# robotino_audio/vosk_node.py
#
# Subscribes to audio_common_msgs/AudioData (raw PCM bytes) and publishes:
#   - /speech/text     (final results)
#   - /speech/partial  (partial results, optional)
#
# Parameters:
#   audio_topic      (string) : default "/audio"
#   model_path       (string) : default "/home/oscar/.cache/vosk/vosk-model-small-en-us-0.15"
#   sample_rate      (int)    : default 16000
#   publish_partial  (bool)   : default true
#
# Notes:
# - audio_capture_node must be publishing PCM at 16kHz mono (you already set format=pcm).
# - Vosk expects PCM 16-bit little endian; AudioData is uint8[] bytes.

import json
import os

import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from audio_common_msgs.msg import AudioData

from vosk import Model, KaldiRecognizer


class VoskNode(Node):
    def __init__(self):
        super().__init__("vosk_stt_node")

        # -------------------- Parameters --------------------
        self.declare_parameter("audio_topic", "/audio")
        self.declare_parameter("model_path", "/home/oscar/.cache/vosk/vosk-model-small-en-us-0.15")
        self.declare_parameter("sample_rate", 16000)
        self.declare_parameter("publish_partial", True)

        self.audio_topic = self.get_parameter("audio_topic").value
        self.model_path = self.get_parameter("model_path").value
        self.sample_rate = int(self.get_parameter("sample_rate").value)
        self.publish_partial = bool(self.get_parameter("publish_partial").value)

        # Basic validation
        if not self.model_path:
            raise RuntimeError("Parameter 'model_path' is empty.")
        if not os.path.isdir(self.model_path):
            raise RuntimeError(f"Vosk model_path does not exist or is not a directory: {self.model_path}")
        if self.sample_rate <= 0:
            raise RuntimeError(f"Invalid sample_rate: {self.sample_rate}")

        self.get_logger().info(f"[vosk] audio_topic: {self.audio_topic}")
        self.get_logger().info(f"[vosk] sample_rate: {self.sample_rate}")
        self.get_logger().info(f"[vosk] model_path: {self.model_path}")
        self.get_logger().info(f"[vosk] publish_partial: {self.publish_partial}")

        # -------------------- Vosk init --------------------
        # If model fails to load, this will throw before "Ready".
        self.model = Model(self.model_path)
        self.rec = KaldiRecognizer(self.model, self.sample_rate)
        self.rec.SetWords(True)

        # -------------------- ROS I/O --------------------
        self.pub_text = self.create_publisher(String, "/speech/text", 10)
        self.pub_partial = self.create_publisher(String, "/speech/partial", 10)

        self.sub_audio = self.create_subscription(
            AudioData,
            self.audio_topic,
            self._audio_cb,
            50,
        )

        self.get_logger().info("[vosk] Ready.")

        # Optional: track last partial to avoid spamming identical messages
        self._last_partial = ""

    def _publish_final(self, text: str):
        msg = String()
        msg.data = text
        self.pub_text.publish(msg)
        self.get_logger().info(f"[vosk] FINAL: {text}")

    def _publish_partial(self, partial: str):
        if not self.publish_partial:
            return
        # avoid repeating the same partial constantly
        if partial and partial != self._last_partial:
            self._last_partial = partial
            msg = String()
            msg.data = partial
            self.pub_partial.publish(msg)

    def _audio_cb(self, msg: AudioData):
        # AudioData.data is uint8[] → convert to bytes
        chunk = bytes(msg.data)

        # AcceptWaveform returns True when it thinks an utterance ended (pause/silence)
        if self.rec.AcceptWaveform(chunk):
            try:
                result = json.loads(self.rec.Result())
            except json.JSONDecodeError:
                return

            text = (result.get("text") or "").strip()
            if text:
                self._publish_final(text)

            # reset last partial after a final result
            self._last_partial = ""
        else:
            # Partial results while speaking
            try:
                pres = json.loads(self.rec.PartialResult())
            except json.JSONDecodeError:
                return
            partial = (pres.get("partial") or "").strip()
            self._publish_partial(partial)


def main():
    rclpy.init()
    node = VoskNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
