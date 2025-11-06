// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from rto_msgs:msg/MotorErrorReadings.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "rto_msgs/msg/detail/motor_error_readings__rosidl_typesupport_introspection_c.h"
#include "rto_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "rto_msgs/msg/detail/motor_error_readings__functions.h"
#include "rto_msgs/msg/detail/motor_error_readings__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `name`
// Member `error_msg`
#include "rosidl_runtime_c/string_functions.h"
// Member `error_status`
// Member `error_code`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  rto_msgs__msg__MotorErrorReadings__init(message_memory);
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_fini_function(void * message_memory)
{
  rto_msgs__msg__MotorErrorReadings__fini(message_memory);
}

size_t rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__size_function__MotorErrorReadings__name(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__name(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__name(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorErrorReadings__name(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__name(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__assign_function__MotorErrorReadings__name(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__name(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__resize_function__MotorErrorReadings__name(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__size_function__MotorErrorReadings__error_status(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_status(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_status(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorErrorReadings__error_status(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_status(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__assign_function__MotorErrorReadings__error_status(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_status(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__resize_function__MotorErrorReadings__error_status(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

size_t rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__size_function__MotorErrorReadings__error_code(
  const void * untyped_member)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return member->size;
}

const void * rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_code(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__uint8__Sequence * member =
    (const rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_code(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  return &member->data[index];
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorErrorReadings__error_code(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uint8_t * item =
    ((const uint8_t *)
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_code(untyped_member, index));
  uint8_t * value =
    (uint8_t *)(untyped_value);
  *value = *item;
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__assign_function__MotorErrorReadings__error_code(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uint8_t * item =
    ((uint8_t *)
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_code(untyped_member, index));
  const uint8_t * value =
    (const uint8_t *)(untyped_value);
  *item = *value;
}

bool rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__resize_function__MotorErrorReadings__error_code(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__uint8__Sequence * member =
    (rosidl_runtime_c__uint8__Sequence *)(untyped_member);
  rosidl_runtime_c__uint8__Sequence__fini(member);
  return rosidl_runtime_c__uint8__Sequence__init(member, size);
}

size_t rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__size_function__MotorErrorReadings__error_msg(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_msg(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_msg(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorErrorReadings__error_msg(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_msg(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__assign_function__MotorErrorReadings__error_msg(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_msg(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__resize_function__MotorErrorReadings__error_msg(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_member_array[5] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorErrorReadings, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorErrorReadings, name),  // bytes offset in struct
    NULL,  // default value
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__size_function__MotorErrorReadings__name,  // size() function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__name,  // get_const(index) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__name,  // get(index) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorErrorReadings__name,  // fetch(index, &value) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__assign_function__MotorErrorReadings__name,  // assign(index, value) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__resize_function__MotorErrorReadings__name  // resize(index) function pointer
  },
  {
    "error_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorErrorReadings, error_status),  // bytes offset in struct
    NULL,  // default value
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__size_function__MotorErrorReadings__error_status,  // size() function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_status,  // get_const(index) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_status,  // get(index) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorErrorReadings__error_status,  // fetch(index, &value) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__assign_function__MotorErrorReadings__error_status,  // assign(index, value) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__resize_function__MotorErrorReadings__error_status  // resize(index) function pointer
  },
  {
    "error_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorErrorReadings, error_code),  // bytes offset in struct
    NULL,  // default value
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__size_function__MotorErrorReadings__error_code,  // size() function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_code,  // get_const(index) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_code,  // get(index) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorErrorReadings__error_code,  // fetch(index, &value) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__assign_function__MotorErrorReadings__error_code,  // assign(index, value) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__resize_function__MotorErrorReadings__error_code  // resize(index) function pointer
  },
  {
    "error_msg",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs__msg__MotorErrorReadings, error_msg),  // bytes offset in struct
    NULL,  // default value
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__size_function__MotorErrorReadings__error_msg,  // size() function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_const_function__MotorErrorReadings__error_msg,  // get_const(index) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__get_function__MotorErrorReadings__error_msg,  // get(index) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__fetch_function__MotorErrorReadings__error_msg,  // fetch(index, &value) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__assign_function__MotorErrorReadings__error_msg,  // assign(index, value) function pointer
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__resize_function__MotorErrorReadings__error_msg  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_members = {
  "rto_msgs__msg",  // message namespace
  "MotorErrorReadings",  // message name
  5,  // number of fields
  sizeof(rto_msgs__msg__MotorErrorReadings),
  false,  // has_any_key_member_
  rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_member_array,  // message members
  rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_init_function,  // function to initialize message memory (memory has to be allocated)
  rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_type_support_handle = {
  0,
  &rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_members,
  get_message_typesupport_handle_function,
  &rto_msgs__msg__MotorErrorReadings__get_type_hash,
  &rto_msgs__msg__MotorErrorReadings__get_type_description,
  &rto_msgs__msg__MotorErrorReadings__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_rto_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rto_msgs, msg, MotorErrorReadings)() {
  rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_type_support_handle.typesupport_identifier) {
    rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &rto_msgs__msg__MotorErrorReadings__rosidl_typesupport_introspection_c__MotorErrorReadings_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
