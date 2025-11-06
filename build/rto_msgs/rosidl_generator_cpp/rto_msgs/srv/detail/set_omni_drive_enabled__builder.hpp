// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:srv/SetOmniDriveEnabled.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/set_omni_drive_enabled.hpp"


#ifndef RTO_MSGS__SRV__DETAIL__SET_OMNI_DRIVE_ENABLED__BUILDER_HPP_
#define RTO_MSGS__SRV__DETAIL__SET_OMNI_DRIVE_ENABLED__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/srv/detail/set_omni_drive_enabled__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetOmniDriveEnabled_Request_enable
{
public:
  Init_SetOmniDriveEnabled_Request_enable()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rto_msgs::srv::SetOmniDriveEnabled_Request enable(::rto_msgs::srv::SetOmniDriveEnabled_Request::_enable_type arg)
  {
    msg_.enable = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetOmniDriveEnabled_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetOmniDriveEnabled_Request>()
{
  return rto_msgs::srv::builder::Init_SetOmniDriveEnabled_Request_enable();
}

}  // namespace rto_msgs


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetOmniDriveEnabled_Response_success
{
public:
  Init_SetOmniDriveEnabled_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rto_msgs::srv::SetOmniDriveEnabled_Response success(::rto_msgs::srv::SetOmniDriveEnabled_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetOmniDriveEnabled_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetOmniDriveEnabled_Response>()
{
  return rto_msgs::srv::builder::Init_SetOmniDriveEnabled_Response_success();
}

}  // namespace rto_msgs


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetOmniDriveEnabled_Event_response
{
public:
  explicit Init_SetOmniDriveEnabled_Event_response(::rto_msgs::srv::SetOmniDriveEnabled_Event & msg)
  : msg_(msg)
  {}
  ::rto_msgs::srv::SetOmniDriveEnabled_Event response(::rto_msgs::srv::SetOmniDriveEnabled_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetOmniDriveEnabled_Event msg_;
};

class Init_SetOmniDriveEnabled_Event_request
{
public:
  explicit Init_SetOmniDriveEnabled_Event_request(::rto_msgs::srv::SetOmniDriveEnabled_Event & msg)
  : msg_(msg)
  {}
  Init_SetOmniDriveEnabled_Event_response request(::rto_msgs::srv::SetOmniDriveEnabled_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetOmniDriveEnabled_Event_response(msg_);
  }

private:
  ::rto_msgs::srv::SetOmniDriveEnabled_Event msg_;
};

class Init_SetOmniDriveEnabled_Event_info
{
public:
  Init_SetOmniDriveEnabled_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetOmniDriveEnabled_Event_request info(::rto_msgs::srv::SetOmniDriveEnabled_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetOmniDriveEnabled_Event_request(msg_);
  }

private:
  ::rto_msgs::srv::SetOmniDriveEnabled_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetOmniDriveEnabled_Event>()
{
  return rto_msgs::srv::builder::Init_SetOmniDriveEnabled_Event_info();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__SRV__DETAIL__SET_OMNI_DRIVE_ENABLED__BUILDER_HPP_
