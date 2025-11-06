// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from rto_msgs:msg/MotorReadings.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "rto_msgs/msg/detail/motor_readings__functions.h"
#include "rto_msgs/msg/detail/motor_readings__struct.hpp"
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

void MotorReadings_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) rto_msgs::msg::MotorReadings(_init);
}

void MotorReadings_fini_function(void * message_memory)
{
  auto typed_message = static_cast<rto_msgs::msg::MotorReadings *>(message_memory);
  typed_message->~MotorReadings();
}

size_t size_function__MotorReadings__velocities(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MotorReadings__velocities(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__MotorReadings__velocities(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__MotorReadings__velocities(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MotorReadings__velocities(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MotorReadings__velocities(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MotorReadings__velocities(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__MotorReadings__velocities(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__MotorReadings__positions(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MotorReadings__positions(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__MotorReadings__positions(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__MotorReadings__positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int32_t *>(
    get_const_function__MotorReadings__positions(untyped_member, index));
  auto & value = *reinterpret_cast<int32_t *>(untyped_value);
  value = item;
}

void assign_function__MotorReadings__positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int32_t *>(
    get_function__MotorReadings__positions(untyped_member, index));
  const auto & value = *reinterpret_cast<const int32_t *>(untyped_value);
  item = value;
}

void resize_function__MotorReadings__positions(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__MotorReadings__currents(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MotorReadings__currents(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__MotorReadings__currents(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__MotorReadings__currents(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__MotorReadings__currents(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__MotorReadings__currents(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__MotorReadings__currents(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__MotorReadings__currents(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MotorReadings_message_member_array[4] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::MotorReadings, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "velocities",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::MotorReadings, velocities),  // bytes offset in struct
    nullptr,  // default value
    size_function__MotorReadings__velocities,  // size() function pointer
    get_const_function__MotorReadings__velocities,  // get_const(index) function pointer
    get_function__MotorReadings__velocities,  // get(index) function pointer
    fetch_function__MotorReadings__velocities,  // fetch(index, &value) function pointer
    assign_function__MotorReadings__velocities,  // assign(index, value) function pointer
    resize_function__MotorReadings__velocities  // resize(index) function pointer
  },
  {
    "positions",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::MotorReadings, positions),  // bytes offset in struct
    nullptr,  // default value
    size_function__MotorReadings__positions,  // size() function pointer
    get_const_function__MotorReadings__positions,  // get_const(index) function pointer
    get_function__MotorReadings__positions,  // get(index) function pointer
    fetch_function__MotorReadings__positions,  // fetch(index, &value) function pointer
    assign_function__MotorReadings__positions,  // assign(index, value) function pointer
    resize_function__MotorReadings__positions  // resize(index) function pointer
  },
  {
    "currents",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(rto_msgs::msg::MotorReadings, currents),  // bytes offset in struct
    nullptr,  // default value
    size_function__MotorReadings__currents,  // size() function pointer
    get_const_function__MotorReadings__currents,  // get_const(index) function pointer
    get_function__MotorReadings__currents,  // get(index) function pointer
    fetch_function__MotorReadings__currents,  // fetch(index, &value) function pointer
    assign_function__MotorReadings__currents,  // assign(index, value) function pointer
    resize_function__MotorReadings__currents  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MotorReadings_message_members = {
  "rto_msgs::msg",  // message namespace
  "MotorReadings",  // message name
  4,  // number of fields
  sizeof(rto_msgs::msg::MotorReadings),
  false,  // has_any_key_member_
  MotorReadings_message_member_array,  // message members
  MotorReadings_init_function,  // function to initialize message memory (memory has to be allocated)
  MotorReadings_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MotorReadings_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MotorReadings_message_members,
  get_message_typesupport_handle_function,
  &rto_msgs__msg__MotorReadings__get_type_hash,
  &rto_msgs__msg__MotorReadings__get_type_description,
  &rto_msgs__msg__MotorReadings__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace rto_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rto_msgs::msg::MotorReadings>()
{
  return &::rto_msgs::msg::rosidl_typesupport_introspection_cpp::MotorReadings_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rto_msgs, msg, MotorReadings)() {
  return &::rto_msgs::msg::rosidl_typesupport_introspection_cpp::MotorReadings_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
