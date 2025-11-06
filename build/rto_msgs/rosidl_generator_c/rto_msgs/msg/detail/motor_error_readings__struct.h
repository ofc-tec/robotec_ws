// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rto_msgs:msg/MotorErrorReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/motor_error_readings.h"


#ifndef RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__STRUCT_H_
#define RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'NO_ERROR'.
enum
{
  rto_msgs__msg__MotorErrorReadings__NO_ERROR = 0
};

/// Constant 'ENCODER_FAILURE'.
enum
{
  rto_msgs__msg__MotorErrorReadings__ENCODER_FAILURE = 1
};

/// Constant 'DRIVE_FAILURE'.
enum
{
  rto_msgs__msg__MotorErrorReadings__DRIVE_FAILURE = 2
};

/// Constant 'LOW_VOLTAGE'.
enum
{
  rto_msgs__msg__MotorErrorReadings__LOW_VOLTAGE = 3
};

/// Constant 'UNKNOWN_ERROR'.
enum
{
  rto_msgs__msg__MotorErrorReadings__UNKNOWN_ERROR = 255
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'name'
// Member 'error_msg'
#include "rosidl_runtime_c/string.h"
// Member 'error_status'
// Member 'error_code'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/MotorErrorReadings in the package rto_msgs.
typedef struct rto_msgs__msg__MotorErrorReadings
{
  /// MotorError.msg
  std_msgs__msg__Header header;
  /// Arrays to represent each wheel's state
  /// Wheel identifier
  rosidl_runtime_c__String__Sequence name;
  /// True if the corresponding wheel has an error
  rosidl_runtime_c__boolean__Sequence error_status;
  /// Error code for each wheel
  rosidl_runtime_c__uint8__Sequence error_code;
  /// Error message for each wheel
  rosidl_runtime_c__String__Sequence error_msg;
} rto_msgs__msg__MotorErrorReadings;

// Struct for a sequence of rto_msgs__msg__MotorErrorReadings.
typedef struct rto_msgs__msg__MotorErrorReadings__Sequence
{
  rto_msgs__msg__MotorErrorReadings * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__msg__MotorErrorReadings__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__STRUCT_H_
