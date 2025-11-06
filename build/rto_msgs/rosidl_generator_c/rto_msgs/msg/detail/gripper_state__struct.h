// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rto_msgs:msg/GripperState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/gripper_state.h"


#ifndef RTO_MSGS__MSG__DETAIL__GRIPPER_STATE__STRUCT_H_
#define RTO_MSGS__MSG__DETAIL__GRIPPER_STATE__STRUCT_H_

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

/// Struct defined in msg/GripperState in the package rto_msgs.
typedef struct rto_msgs__msg__GripperState
{
  std_msgs__msg__Header header;
  /// true if open else false if closed
  bool state;
} rto_msgs__msg__GripperState;

// Struct for a sequence of rto_msgs__msg__GripperState.
typedef struct rto_msgs__msg__GripperState__Sequence
{
  rto_msgs__msg__GripperState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__msg__GripperState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RTO_MSGS__MSG__DETAIL__GRIPPER_STATE__STRUCT_H_
