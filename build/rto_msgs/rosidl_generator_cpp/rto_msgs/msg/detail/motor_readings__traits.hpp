// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rto_msgs:msg/MotorReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/motor_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__TRAITS_HPP_
#define RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rto_msgs/msg/detail/motor_readings__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rto_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorReadings & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: velocities
  {
    if (msg.velocities.size() == 0) {
      out << "velocities: []";
    } else {
      out << "velocities: [";
      size_t pending_items = msg.velocities.size();
      for (auto item : msg.velocities) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: positions
  {
    if (msg.positions.size() == 0) {
      out << "positions: []";
    } else {
      out << "positions: [";
      size_t pending_items = msg.positions.size();
      for (auto item : msg.positions) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: currents
  {
    if (msg.currents.size() == 0) {
      out << "currents: []";
    } else {
      out << "currents: [";
      size_t pending_items = msg.currents.size();
      for (auto item : msg.currents) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorReadings & msg,
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

  // member: velocities
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.velocities.size() == 0) {
      out << "velocities: []\n";
    } else {
      out << "velocities:\n";
      for (auto item : msg.velocities) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: positions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.positions.size() == 0) {
      out << "positions: []\n";
    } else {
      out << "positions:\n";
      for (auto item : msg.positions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: currents
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.currents.size() == 0) {
      out << "currents: []\n";
    } else {
      out << "currents:\n";
      for (auto item : msg.currents) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorReadings & msg, bool use_flow_style = false)
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
  const rto_msgs::msg::MotorReadings & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::msg::MotorReadings & msg)
{
  return rto_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::msg::MotorReadings>()
{
  return "rto_msgs::msg::MotorReadings";
}

template<>
inline const char * name<rto_msgs::msg::MotorReadings>()
{
  return "rto_msgs/msg/MotorReadings";
}

template<>
struct has_fixed_size<rto_msgs::msg::MotorReadings>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rto_msgs::msg::MotorReadings>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rto_msgs::msg::MotorReadings>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__TRAITS_HPP_
