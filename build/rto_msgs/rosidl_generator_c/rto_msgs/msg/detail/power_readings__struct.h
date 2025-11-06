// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rto_msgs:msg/PowerReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/power_readings.h"


#ifndef RTO_MSGS__MSG__DETAIL__POWER_READINGS__STRUCT_H_
#define RTO_MSGS__MSG__DETAIL__POWER_READINGS__STRUCT_H_

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

/// Struct defined in msg/PowerReadings in the package rto_msgs.
typedef struct rto_msgs__msg__PowerReadings
{
  /// time-stamp
  std_msgs__msg__Header header;
  /// current in A
  float current;
  /// voltage in V
  float voltage;
  /// bool for low battery
  bool battery_low;
} rto_msgs__msg__PowerReadings;

// Struct for a sequence of rto_msgs__msg__PowerReadings.
typedef struct rto_msgs__msg__PowerReadings__Sequence
{
  rto_msgs__msg__PowerReadings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__msg__PowerReadings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RTO_MSGS__MSG__DETAIL__POWER_READINGS__STRUCT_H_
