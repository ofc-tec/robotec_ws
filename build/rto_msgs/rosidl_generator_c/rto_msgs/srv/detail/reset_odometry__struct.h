// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rto_msgs:srv/ResetOdometry.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/reset_odometry.h"


#ifndef RTO_MSGS__SRV__DETAIL__RESET_ODOMETRY__STRUCT_H_
#define RTO_MSGS__SRV__DETAIL__RESET_ODOMETRY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/ResetOdometry in the package rto_msgs.
typedef struct rto_msgs__srv__ResetOdometry_Request
{
  /// in meters
  float x;
  /// in meters
  float y;
  /// in rad
  float phi;
} rto_msgs__srv__ResetOdometry_Request;

// Struct for a sequence of rto_msgs__srv__ResetOdometry_Request.
typedef struct rto_msgs__srv__ResetOdometry_Request__Sequence
{
  rto_msgs__srv__ResetOdometry_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__srv__ResetOdometry_Request__Sequence;

// Constants defined in the message

/// Struct defined in srv/ResetOdometry in the package rto_msgs.
typedef struct rto_msgs__srv__ResetOdometry_Response
{
  uint8_t structure_needs_at_least_one_member;
} rto_msgs__srv__ResetOdometry_Response;

// Struct for a sequence of rto_msgs__srv__ResetOdometry_Response.
typedef struct rto_msgs__srv__ResetOdometry_Response__Sequence
{
  rto_msgs__srv__ResetOdometry_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__srv__ResetOdometry_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  rto_msgs__srv__ResetOdometry_Event__request__MAX_SIZE = 1
};
// response
enum
{
  rto_msgs__srv__ResetOdometry_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/ResetOdometry in the package rto_msgs.
typedef struct rto_msgs__srv__ResetOdometry_Event
{
  service_msgs__msg__ServiceEventInfo info;
  rto_msgs__srv__ResetOdometry_Request__Sequence request;
  rto_msgs__srv__ResetOdometry_Response__Sequence response;
} rto_msgs__srv__ResetOdometry_Event;

// Struct for a sequence of rto_msgs__srv__ResetOdometry_Event.
typedef struct rto_msgs__srv__ResetOdometry_Event__Sequence
{
  rto_msgs__srv__ResetOdometry_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rto_msgs__srv__ResetOdometry_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RTO_MSGS__SRV__DETAIL__RESET_ODOMETRY__STRUCT_H_
