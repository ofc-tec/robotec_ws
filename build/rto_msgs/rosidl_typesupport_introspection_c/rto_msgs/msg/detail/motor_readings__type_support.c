// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rto_msgs:msg/MotorReadings.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rto_msgs/msg/detail/motor_readings__rosidl_typesupport_introspection_c.h"
#include "rto_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rto_msgs/msg/detail/motor_readings__functions.h"
#include "rto_msgs/msg/detail/motor_readings__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `velocities`
// Member `positions`
// Member `currents`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rto_msgs__msg__MotorReadings__init(message_memory);
}

void rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_fini_function(void * message_memory)
{
  rto_msgs__msg__MotorReadings__fini(message_memory);
}

size_t rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__size_function__MotorReadings__velocities(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__velocities(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__velocities(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorReadings__velocities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__velocities(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__assign_function__MotorReadings__velocities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__velocities(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__resize_function__MotorReadings__velocities(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__size_function__MotorReadings__positions(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__positions(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__positions(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorReadings__positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__positions(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__assign_function__MotorReadings__positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__positions(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__resize_function__MotorReadings__positions(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

size_t rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__size_function__MotorReadings__currents(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__currents(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__currents(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorReadings__currents(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__currents(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__assign_function__MotorReadings__currents(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__currents(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__resize_function__MotorReadings__currents(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorReadings, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocities",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorReadings, velocities),  // bytes offset in struct
    NULL,  // default value
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__size_function__MotorReadings__velocities,  // size() function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__velocities,  // get_const(index) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__velocities,  // get(index) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorReadings__velocities,  // fetch(index, &value) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__assign_function__MotorReadings__velocities,  // assign(index, value) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__resize_function__MotorReadings__velocities  // resize(index) function pointer
  },
  {
    "positions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorReadings, positions),  // bytes offset in struct
    NULL,  // default value
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__size_function__MotorReadings__positions,  // size() function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__positions,  // get_const(index) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__positions,  // get(index) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorReadings__positions,  // fetch(index, &value) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__assign_function__MotorReadings__positions,  // assign(index, value) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__resize_function__MotorReadings__positions  // resize(index) function pointer
  },
  {
    "currents",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorReadings, currents),  // bytes offset in struct
    NULL,  // default value
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__size_function__MotorReadings__currents,  // size() function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorReadings__currents,  // get_const(index) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__get_function__MotorReadings__currents,  // get(index) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorReadings__currents,  // fetch(index, &value) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__assign_function__MotorReadings__currents,  // assign(index, value) function pointer
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__resize_function__MotorReadings__currents  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_members = {
  "rto_msgs__msg",  // message namespace
  "MotorReadings",  // message name
  4,  // number of fields
  sizeof(rto_msgs__msg__MotorReadings),
  false,  // has_any_key_member_
  rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_member_array,  // message members
  rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_init_function,  // function to initialize message memory (memory has to be allocated)
  rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_type_support_handle = {
  0,
  &rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_members,
  get_message_typesupport_handle_function,
  &rto_msgs__msg__MotorReadings__get_type_hash,
  &rto_msgs__msg__MotorReadings__get_type_description,
  &rto_msgs__msg__MotorReadings__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rto_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rto_msgs, msg, MotorReadings)() {
  rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_type_support_handle.typesupport_identifier) {
    rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rto_msgs__msg__MotorReadings__rosidl_typesupport_introspection_c__MotorReadings_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
