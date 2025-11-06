// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rto_msgs:msg/EncoderReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/encoder_readings.h"


#ifndef RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__STRUCT_H_
#define RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/EncoderReadings in the package rto_msgs.
typedef struct rto_msgs__msg__EncoderReadings
{
  std_msgs__msg__Header header;
  /// actual velocity in ticks/s
  uint32_t velocity;
  /// actual position in ticks
  uint32_t position;
  /// in A
  uint32_t current;
} rto_msgs__msg__EncoderReadings;

// Struct for a sequence of rto_msgs__msg__EncoderReadings.
typedef struct rto_msgs__msg__EncoderReadings__Sequence
{
  rto_msgs__msg__EncoderReadings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__msg__EncoderReadings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__STRUCT_H_
