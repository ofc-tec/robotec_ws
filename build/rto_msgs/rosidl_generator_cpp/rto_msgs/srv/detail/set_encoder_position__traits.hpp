// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rto_msgs:srv/SetEncoderPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/set_encoder_position.hpp"


#ifndef RTO_MSGS__SRV__DETAIL__SET_ENCODER_POSITION__TRAITS_HPP_
#define RTO_MSGS__SRV__DETAIL__SET_ENCODER_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rto_msgs/srv/detail/set_encoder_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rto_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetEncoderPosition_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: position
  {
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << ", ";
  }

  // member: velocity
  {
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetEncoderPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << "\n";
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetEncoderPosition_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rto_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rto_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rto_msgs::srv::SetEncoderPosition_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::srv::SetEncoderPosition_Request & msg)
{
  return rto_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::srv::SetEncoderPosition_Request>()
{
  return "rto_msgs::srv::SetEncoderPosition_Request";
}

template<>
inline const char * name<rto_msgs::srv::SetEncoderPosition_Request>()
{
  return "rto_msgs/srv/SetEncoderPosition_Request";
}

template<>
struct has_fixed_size<rto_msgs::srv::SetEncoderPosition_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rto_msgs::srv::SetEncoderPosition_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rto_msgs::srv::SetEncoderPosition_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rto_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetEncoderPosition_Response & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetEncoderPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetEncoderPosition_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rto_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rto_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rto_msgs::srv::SetEncoderPosition_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::srv::SetEncoderPosition_Response & msg)
{
  return rto_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::srv::SetEncoderPosition_Response>()
{
  return "rto_msgs::srv::SetEncoderPosition_Response";
}

template<>
inline const char * name<rto_msgs::srv::SetEncoderPosition_Response>()
{
  return "rto_msgs/srv/SetEncoderPosition_Response";
}

template<>
struct has_fixed_size<rto_msgs::srv::SetEncoderPosition_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rto_msgs::srv::SetEncoderPosition_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rto_msgs::srv::SetEncoderPosition_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace rto_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetEncoderPosition_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
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
  const SetEncoderPosition_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetEncoderPosition_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rto_msgs

namespace rosidl_generator_traits
{

[[deprecated("use rto_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rto_msgs::srv::SetEncoderPosition_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::srv::SetEncoderPosition_Event & msg)
{
  return rto_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::srv::SetEncoderPosition_Event>()
{
  return "rto_msgs::srv::SetEncoderPosition_Event";
}

template<>
inline const char * name<rto_msgs::srv::SetEncoderPosition_Event>()
{
  return "rto_msgs/srv/SetEncoderPosition_Event";
}

template<>
struct has_fixed_size<rto_msgs::srv::SetEncoderPosition_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rto_msgs::srv::SetEncoderPosition_Event>
  : std::integral_constant<bool, has_bounded_size<rto_msgs::srv::SetEncoderPosition_Request>::value && has_bounded_size<rto_msgs::srv::SetEncoderPosition_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<rto_msgs::srv::SetEncoderPosition_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rto_msgs::srv::SetEncoderPosition>()
{
  return "rto_msgs::srv::SetEncoderPosition";
}

template<>
inline const char * name<rto_msgs::srv::SetEncoderPosition>()
{
  return "rto_msgs/srv/SetEncoderPosition";
}

template<>
struct has_fixed_size<rto_msgs::srv::SetEncoderPosition>
  : std::integral_constant<
    bool,
    has_fixed_size<rto_msgs::srv::SetEncoderPosition_Request>::value &&
    has_fixed_size<rto_msgs::srv::SetEncoderPosition_Response>::value
  >
{
};

template<>
struct has_bounded_size<rto_msgs::srv::SetEncoderPosition>
  : std::integral_constant<
    bool,
    has_bounded_size<rto_msgs::srv::SetEncoderPosition_Request>::value &&
    has_bounded_size<rto_msgs::srv::SetEncoderPosition_Response>::value
  >
{
};

template<>
struct is_service<rto_msgs::srv::SetEncoderPosition>
  : std::true_type
{
};

template<>
struct is_service_request<rto_msgs::srv::SetEncoderPosition_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rto_msgs::srv::SetEncoderPosition_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RTO_MSGS__SRV__DETAIL__SET_ENCODER_POSITION__TRAITS_HPP_
