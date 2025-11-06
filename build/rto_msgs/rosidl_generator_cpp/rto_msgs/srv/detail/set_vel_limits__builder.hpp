// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:srv/SetVelLimits.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/set_vel_limits.hpp"


#ifndef RTO_MSGS__SRV__DETAIL__SET_VEL_LIMITS__BUILDER_HPP_
#define RTO_MSGS__SRV__DETAIL__SET_VEL_LIMITS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/srv/detail/set_vel_limits__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetVelLimits_Request_min_angular_vel
{
public:
  explicit Init_SetVelLimits_Request_min_angular_vel(::rto_msgs::srv::SetVelLimits_Request & msg)
  : msg_(msg)
  {}
  ::rto_msgs::srv::SetVelLimits_Request min_angular_vel(::rto_msgs::srv::SetVelLimits_Request::_min_angular_vel_type arg)
  {
    msg_.min_angular_vel = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetVelLimits_Request msg_;
};

class Init_SetVelLimits_Request_max_angular_vel
{
public:
  explicit Init_SetVelLimits_Request_max_angular_vel(::rto_msgs::srv::SetVelLimits_Request & msg)
  : msg_(msg)
  {}
  Init_SetVelLimits_Request_min_angular_vel max_angular_vel(::rto_msgs::srv::SetVelLimits_Request::_max_angular_vel_type arg)
  {
    msg_.max_angular_vel = std::move(arg);
    return Init_SetVelLimits_Request_min_angular_vel(msg_);
  }

private:
  ::rto_msgs::srv::SetVelLimits_Request msg_;
};

class Init_SetVelLimits_Request_min_linear_vel
{
public:
  explicit Init_SetVelLimits_Request_min_linear_vel(::rto_msgs::srv::SetVelLimits_Request & msg)
  : msg_(msg)
  {}
  Init_SetVelLimits_Request_max_angular_vel min_linear_vel(::rto_msgs::srv::SetVelLimits_Request::_min_linear_vel_type arg)
  {
    msg_.min_linear_vel = std::move(arg);
    return Init_SetVelLimits_Request_max_angular_vel(msg_);
  }

private:
  ::rto_msgs::srv::SetVelLimits_Request msg_;
};

class Init_SetVelLimits_Request_max_linear_vel
{
public:
  Init_SetVelLimits_Request_max_linear_vel()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetVelLimits_Request_min_linear_vel max_linear_vel(::rto_msgs::srv::SetVelLimits_Request::_max_linear_vel_type arg)
  {
    msg_.max_linear_vel = std::move(arg);
    return Init_SetVelLimits_Request_min_linear_vel(msg_);
  }

private:
  ::rto_msgs::srv::SetVelLimits_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetVelLimits_Request>()
{
  return rto_msgs::srv::builder::Init_SetVelLimits_Request_max_linear_vel();
}

}  // namespace rto_msgs


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetVelLimits_Response_success
{
public:
  Init_SetVelLimits_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rto_msgs::srv::SetVelLimits_Response success(::rto_msgs::srv::SetVelLimits_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetVelLimits_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetVelLimits_Response>()
{
  return rto_msgs::srv::builder::Init_SetVelLimits_Response_success();
}

}  // namespace rto_msgs


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetVelLimits_Event_response
{
public:
  explicit Init_SetVelLimits_Event_response(::rto_msgs::srv::SetVelLimits_Event & msg)
  : msg_(msg)
  {}
  ::rto_msgs::srv::SetVelLimits_Event response(::rto_msgs::srv::SetVelLimits_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetVelLimits_Event msg_;
};

class Init_SetVelLimits_Event_request
{
public:
  explicit Init_SetVelLimits_Event_request(::rto_msgs::srv::SetVelLimits_Event & msg)
  : msg_(msg)
  {}
  Init_SetVelLimits_Event_response request(::rto_msgs::srv::SetVelLimits_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetVelLimits_Event_response(msg_);
  }

private:
  ::rto_msgs::srv::SetVelLimits_Event msg_;
};

class Init_SetVelLimits_Event_info
{
public:
  Init_SetVelLimits_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetVelLimits_Event_request info(::rto_msgs::srv::SetVelLimits_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetVelLimits_Event_request(msg_);
  }

private:
  ::rto_msgs::srv::SetVelLimits_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetVelLimits_Event>()
{
  return rto_msgs::srv::builder::Init_SetVelLimits_Event_info();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__SRV__DETAIL__SET_VEL_LIMITS__BUILDER_HPP_
