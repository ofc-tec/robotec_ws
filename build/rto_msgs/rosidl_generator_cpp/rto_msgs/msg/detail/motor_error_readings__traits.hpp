// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rto_msgs:msg/MotorErrorReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/motor_error_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__TRAITS_HPP_
#define RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rto_msgs/msg/detail/motor_error_readings__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rto_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorErrorReadings & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: name
  {
    if (msg.name.size() == 0) {
      out << "name: []";
    } else {
      out << "name: [";
      size_t pending_items = msg.name.size();
      for (auto item : msg.name) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: error_status
  {
    if (msg.error_status.size() == 0) {
      out << "error_status: []";
    } else {
      out << "error_status: [";
      size_t pending_items = msg.error_status.size();
      for (auto item : msg.error_status) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: error_code
  {
    if (msg.error_code.size() == 0) {
      out << "error_code: []";
    } else {
      out << "error_code: [";
      size_t pending_items = msg.error_code.size();
      for (auto item : msg.error_code) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: error_msg
  {
    if (msg.error_msg.size() == 0) {
      out << "error_msg: []";
    } else {
      out << "error_msg: [";
      size_t pending_items = msg.error_msg.size();
      for (auto item : msg.error_msg) {
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
  const MotorErrorReadings & msg,
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

  // member: name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.name.size() == 0) {
      out << "name: []\n";
    } else {
      out << "name:\n";
      for (auto item : msg.name) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: error_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.error_status.size() == 0) {
      out << "error_status: []\n";
    } else {
      out << "error_status:\n";
      for (auto item : msg.error_status) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: error_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.error_code.size() == 0) {
      out << "error_code: []\n";
    } else {
      out << "error_code:\n";
      for (auto item : msg.error_code) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: error_msg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.error_msg.size() == 0) {
      out << "error_msg: []\n";
    } else {
      out << "error_msg:\n";
      for (auto item : msg.error_msg) {
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

inline std::string to_yaml(const MotorErrorReadings & msg, bool use_flow_style = false)
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
  const rto_msgs::msg::MotorErrorReadings & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::msg::MotorErrorReadings & msg)
{
  return rto_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::msg::MotorErrorReadings>()
{
  return "rto_msgs::msg::MotorErrorReadings";
}

template<>
inline const char * name<rto_msgs::msg::MotorErrorReadings>()
{
  return "rto_msgs/msg/MotorErrorReadings";
}

template<>
struct has_fixed_size<rto_msgs::msg::MotorErrorReadings>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rto_msgs::msg::MotorErrorReadings>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<rto_msgs::msg::MotorErrorReadings>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__TRAITS_HPP_
