// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rto_msgs:msg/EncoderReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/encoder_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__TRAITS_HPP_
#define RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rto_msgs/msg/detail/encoder_readings__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rto_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const EncoderReadings & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: velocity
  {
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << ", ";
  }

  // member: current
  {
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const EncoderReadings & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << "\n";
  }

  // member: current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const EncoderReadings & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace rto_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rto_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rto_msgs::msg::EncoderReadings & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::msg::EncoderReadings & msg)
{
  return rto_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::msg::EncoderReadings>()
{
  return "rto_msgs::msg::EncoderReadings";
}

template<>
inline const char * name<rto_msgs::msg::EncoderReadings>()
{
  return "rto_msgs/msg/EncoderReadings";
}

template<>
struct has_fixed_size<rto_msgs::msg::EncoderReadings>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<rto_msgs::msg::EncoderReadings>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<rto_msgs::msg::EncoderReadings>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__TRAITS_HPP_
