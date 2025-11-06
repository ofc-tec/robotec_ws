// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rto_msgs:srv/SetGripperState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/set_gripper_state.h"


#ifndef RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__STRUCT_H_
#define RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SetGripperState in the package rto_msgs.
typedef struct rto_msgs__srv__SetGripperState_Request
{
  /// set true to open else false to close
  bool state;
} rto_msgs__srv__SetGripperState_Request;

// Struct for a sequence of rto_msgs__srv__SetGripperState_Request.
typedef struct rto_msgs__srv__SetGripperState_Request__Sequence
{
  rto_msgs__srv__SetGripperState_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__srv__SetGripperState_Request__Sequence;

// Constants defined in the message

/// Struct defined in srv/SetGripperState in the package rto_msgs.
typedef struct rto_msgs__srv__SetGripperState_Response
{
  uint8_t structure_needs_at_least_one_member;
} rto_msgs__srv__SetGripperState_Response;

// Struct for a sequence of rto_msgs__srv__SetGripperState_Response.
typedef struct rto_msgs__srv__SetGripperState_Response__Sequence
{
  rto_msgs__srv__SetGripperState_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__srv__SetGripperState_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  rto_msgs__srv__SetGripperState_Event__request__MAX_SIZE = 1
};
// response
enum
{
  rto_msgs__srv__SetGripperState_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SetGripperState in the package rto_msgs.
typedef struct rto_msgs__srv__SetGripperState_Event
{
  service_msgs__msg__ServiceEventInfo info;
  rto_msgs__srv__SetGripperState_Request__Sequence request;
  rto_msgs__srv__SetGripperState_Response__Sequence response;
} rto_msgs__srv__SetGripperState_Event;

// Struct for a sequence of rto_msgs__srv__SetGripperState_Event.
typedef struct rto_msgs__srv__SetGripperState_Event__Sequence
{
  rto_msgs__srv__SetGripperState_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__srv__SetGripperState_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__STRUCT_H_
