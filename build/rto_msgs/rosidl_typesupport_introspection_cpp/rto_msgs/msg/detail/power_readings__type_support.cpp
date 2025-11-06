// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rto_msgs:msg/PowerReadings.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rto_msgs/msg/detail/power_readings__functions.h"
#include "rto_msgs/msg/detail/power_readings__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace rto_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void PowerReadings_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rto_msgs::msg::PowerReadings(_init);
}

void PowerReadings_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rto_msgs::msg::PowerReadings *>(message_memory);
  typed_message->~PowerReadings();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember PowerReadings_message_member_array[4] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::PowerReadings, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "current",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::PowerReadings, current),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "voltage",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::PowerReadings, voltage),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "battery_low",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::PowerReadings, battery_low),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers PowerReadings_message_members = {
  "rto_msgs::msg",  // message namespace
  "PowerReadings",  // message name
  4,  // number of fields
  sizeof(rto_msgs::msg::PowerReadings),
  false,  // has_any_key_member_
  PowerReadings_message_member_array,  // message members
  PowerReadings_init_function,  // function to initialize message memory (memory has to be allocated)
  PowerReadings_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t PowerReadings_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &PowerReadings_message_members,
  get_message_typesupport_handle_function,
  &rto_msgs__msg__PowerReadings__get_type_hash,
  &rto_msgs__msg__PowerReadings__get_type_description,
  &rto_msgs__msg__PowerReadings__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rto_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rto_msgs::msg::PowerReadings>()
{
  return &::rto_msgs::msg::rosidl_typesupport_introspection_cpp::PowerReadings_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rto_msgs, msg, PowerReadings)() {
  return &::rto_msgs::msg::rosidl_typesupport_introspection_cpp::PowerReadings_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
