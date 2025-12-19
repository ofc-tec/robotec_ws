from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node


def generate_launch_description():
    # ---- Launch args ----
    model_path = LaunchConfiguration("model_path")
    audio_topic = LaunchConfiguration("audio_topic")

    # audio_capture params
    sample_rate = LaunchConfiguration("sample_rate")
    channels = LaunchConfiguration("channels")
    sample_format = LaunchConfiguration("sample_format")
    audio_format = LaunchConfiguration("audio_format")
    device = LaunchConfiguration("device")

    publish_partial = LaunchConfiguration("publish_partial")

    return LaunchDescription([
        DeclareLaunchArgument(
            "model_path",
            default_value="/home/oscar/.cache/vosk/vosk-model-small-en-us-0.15",
            description="Path to Vosk model directory"
        ),
        DeclareLaunchArgument(
            "audio_topic",
            default_value="/audio",
            description="Audio topic to subscribe/publish"
        ),
        DeclareLaunchArgument(
            "sample_rate",
            default_value="16000",
            description="Audio capture sample rate"
        ),
        DeclareLaunchArgument(
            "channels",
            default_value="1",
            description="Audio capture channels"
        ),
        DeclareLaunchArgument(
            "sample_format",
            default_value="S16LE",
            description="Audio sample format for capture (e.g., S16LE)"
        ),
        DeclareLaunchArgument(
            "audio_format",
            default_value="wave",
            description='audio_capture output format: MUST be "wave" or "mp3" in this build'
        ),
        DeclareLaunchArgument(
            "device",
            default_value="",
            description="Optional audio device string/index (leave empty for default)"
        ),
        DeclareLaunchArgument(
            "publish_partial",
            default_value="true",
            description="Publish partial recognition results"
        ),

        # ---- Audio Capture ----
        Node(
            package="audio_capture",
            executable="audio_capture_node",
            name="audio_capture_node",
            output="screen",
            parameters=[{
                "sample_rate": sample_rate,
                "channels": channels,
                "sample_format": sample_format,
                "format": audio_format,
                # Only set device if user passed something non-empty.
                # (audio_capture_node ignores unknown/empty, but we keep it explicit)
                "device": device,
            }]
        ),

        # ---- Vosk STT ----
        Node(
            package="robotino_audio",
            executable="vosk_node",
            name="vosk_stt_node",
            output="screen",
            parameters=[{
                "audio_topic": audio_topic,
                "model_path": model_path,
                "sample_rate": 16000,          # match capture
                "publish_partial": publish_partial,
            }]
        ),
    ])
