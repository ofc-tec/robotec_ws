// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rto_msgs:msg/AnalogReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/analog_readings.h"


#ifndef RTO_MSGS__MSG__DETAIL__ANALOG_READINGS__STRUCT_H_
#define RTO_MSGS__MSG__DETAIL__ANALOG_READINGS__STRUCT_H_

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
// Member 'values'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/AnalogReadings in the package rto_msgs.
typedef struct rto_msgs__msg__AnalogReadings
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__float__Sequence values;
} rto_msgs__msg__AnalogReadings;

// Struct for a sequence of rto_msgs__msg__AnalogReadings.
typedef struct rto_msgs__msg__AnalogReadings__Sequence
{
  rto_msgs__msg__AnalogReadings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__msg__AnalogReadings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RTO_MSGS__MSG__DETAIL__ANALOG_READINGS__STRUCT_H_
