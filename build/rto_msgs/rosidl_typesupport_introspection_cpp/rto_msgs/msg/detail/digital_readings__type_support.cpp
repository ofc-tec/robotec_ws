// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rto_msgs:msg/DigitalReadings.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rto_msgs/msg/detail/digital_readings__functions.h"
#include "rto_msgs/msg/detail/digital_readings__struct.hpp"
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

void DigitalReadings_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rto_msgs::msg::DigitalReadings(_init);
}

void DigitalReadings_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rto_msgs::msg::DigitalReadings *>(message_memory);
  typed_message->~DigitalReadings();
}

size_t size_function__DigitalReadings__values(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<bool> *>(untyped_member);
  return member->size();
}

void fetch_function__DigitalReadings__values(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & member = *reinterpret_cast<const std::vector<bool> *>(untyped_member);
  auto & value = *reinterpret_cast<bool *>(untyped_value);
  value = member[index];
}

void assign_function__DigitalReadings__values(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & member = *reinterpret_cast<std::vector<bool> *>(untyped_member);
  const auto & value = *reinterpret_cast<const bool *>(untyped_value);
  member[index] = value;
}

void resize_function__DigitalReadings__values(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<bool> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember DigitalReadings_message_member_array[2] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::DigitalReadings, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "values",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::DigitalReadings, values),  // bytes offset in struct
    nullptr,  // default value
    size_function__DigitalReadings__values,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    fetch_function__DigitalReadings__values,  // fetch(index, &value) function pointer
    assign_function__DigitalReadings__values,  // assign(index, value) function pointer
    resize_function__DigitalReadings__values  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers DigitalReadings_message_members = {
  "rto_msgs::msg",  // message namespace
  "DigitalReadings",  // message name
  2,  // number of fields
  sizeof(rto_msgs::msg::DigitalReadings),
  false,  // has_any_key_member_
  DigitalReadings_message_member_array,  // message members
  DigitalReadings_init_function,  // function to initialize message memory (memory has to be allocated)
  DigitalReadings_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t DigitalReadings_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &DigitalReadings_message_members,
  get_message_typesupport_handle_function,
  &rto_msgs__msg__DigitalReadings__get_type_hash,
  &rto_msgs__msg__DigitalReadings__get_type_description,
  &rto_msgs__msg__DigitalReadings__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rto_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rto_msgs::msg::DigitalReadings>()
{
  return &::rto_msgs::msg::rosidl_typesupport_introspection_cpp::DigitalReadings_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rto_msgs, msg, DigitalReadings)() {
  return &::rto_msgs::msg::rosidl_typesupport_introspection_cpp::DigitalReadings_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
