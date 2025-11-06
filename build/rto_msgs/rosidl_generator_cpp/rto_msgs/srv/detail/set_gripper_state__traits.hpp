// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rto_msgs:srv/SetGripperState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/set_gripper_state.hpp"


#ifndef RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__TRAITS_HPP_
#define RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rto_msgs/srv/detail/set_gripper_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rto_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetGripperState_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetGripperState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetGripperState_Request & msg, bool use_flow_style = false)
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
  const rto_msgs::srv::SetGripperState_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::srv::SetGripperState_Request & msg)
{
  return rto_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::srv::SetGripperState_Request>()
{
  return "rto_msgs::srv::SetGripperState_Request";
}

template<>
inline const char * name<rto_msgs::srv::SetGripperState_Request>()
{
  return "rto_msgs/srv/SetGripperState_Request";
}

template<>
struct has_fixed_size<rto_msgs::srv::SetGripperState_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rto_msgs::srv::SetGripperState_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rto_msgs::srv::SetGripperState_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rto_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetGripperState_Response & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetGripperState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetGripperState_Response & msg, bool use_flow_style = false)
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
  const rto_msgs::srv::SetGripperState_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::srv::SetGripperState_Response & msg)
{
  return rto_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::srv::SetGripperState_Response>()
{
  return "rto_msgs::srv::SetGripperState_Response";
}

template<>
inline const char * name<rto_msgs::srv::SetGripperState_Response>()
{
  return "rto_msgs/srv/SetGripperState_Response";
}

template<>
struct has_fixed_size<rto_msgs::srv::SetGripperState_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rto_msgs::srv::SetGripperState_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rto_msgs::srv::SetGripperState_Response>
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
  const SetGripperState_Event & msg,
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
  const SetGripperState_Event & msg,
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

inline std::string to_yaml(const SetGripperState_Event & msg, bool use_flow_style = false)
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
  const rto_msgs::srv::SetGripperState_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  rto_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rto_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const rto_msgs::srv::SetGripperState_Event & msg)
{
  return rto_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rto_msgs::srv::SetGripperState_Event>()
{
  return "rto_msgs::srv::SetGripperState_Event";
}

template<>
inline const char * name<rto_msgs::srv::SetGripperState_Event>()
{
  return "rto_msgs/srv/SetGripperState_Event";
}

template<>
struct has_fixed_size<rto_msgs::srv::SetGripperState_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<rto_msgs::srv::SetGripperState_Event>
  : std::integral_constant<bool, has_bounded_size<rto_msgs::srv::SetGripperState_Request>::value && has_bounded_size<rto_msgs::srv::SetGripperState_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<rto_msgs::srv::SetGripperState_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rto_msgs::srv::SetGripperState>()
{
  return "rto_msgs::srv::SetGripperState";
}

template<>
inline const char * name<rto_msgs::srv::SetGripperState>()
{
  return "rto_msgs/srv/SetGripperState";
}

template<>
struct has_fixed_size<rto_msgs::srv::SetGripperState>
  : std::integral_constant<
    bool,
    has_fixed_size<rto_msgs::srv::SetGripperState_Request>::value &&
    has_fixed_size<rto_msgs::srv::SetGripperState_Response>::value
  >
{
};

template<>
struct has_bounded_size<rto_msgs::srv::SetGripperState>
  : std::integral_constant<
    bool,
    has_bounded_size<rto_msgs::srv::SetGripperState_Request>::value &&
    has_bounded_size<rto_msgs::srv::SetGripperState_Response>::value
  >
{
};

template<>
struct is_service<rto_msgs::srv::SetGripperState>
  : std::true_type
{
};

template<>
struct is_service_request<rto_msgs::srv::SetGripperState_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rto_msgs::srv::SetGripperState_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__TRAITS_HPP_
