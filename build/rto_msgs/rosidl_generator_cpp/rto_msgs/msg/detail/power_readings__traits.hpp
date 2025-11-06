// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rto_msgs:msg/PowerReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/power_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__POWER_READINGS__TRAITS_HPP_
#define RTO_MSGS__MSG__DETAIL__POWER_READINGS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rto_msgs/msg/detail/power_readings__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rto_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PowerReadings & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: current
  {
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << ", ";
  }

  // member: voltage
  {
    out << "voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.voltage, out);
    out << ", ";
  }

  // member: battery_low
  {
    out << "battery_low: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_low, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PowerReadings & msg,
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

  // member: current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current: ";
    rosidl_generator_traits::value_to_yaml(msg.current, out);
    out << "\n";
  }

  // member: voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.voltage, out);
    out << "\n";
  }

  // member: battery_low
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_low: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_low, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PowerReadings & msg, bool use_flow_style = false)
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
  const rto_msgs::msg::PowerReadings & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::msg::PowerReadings & msg)
{
  return rto_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::msg::PowerReadings>()
{
  return "rto_msgs::msg::PowerReadings";
}

template<>
inline const char * name<rto_msgs::msg::PowerReadings>()
{
  return "rto_msgs/msg/PowerReadings";
}

template<>
struct has_fixed_size<rto_msgs::msg::PowerReadings>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<rto_msgs::msg::PowerReadings>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<rto_msgs::msg::PowerReadings>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RTO_MSGS__MSG__DETAIL__POWER_READINGS__TRAITS_HPP_
