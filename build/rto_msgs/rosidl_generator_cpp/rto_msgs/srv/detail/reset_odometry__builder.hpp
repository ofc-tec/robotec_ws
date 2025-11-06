// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:srv/ResetOdometry.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/reset_odometry.hpp"


#ifndef RTO_MSGS__SRV__DETAIL__RESET_ODOMETRY__BUILDER_HPP_
#define RTO_MSGS__SRV__DETAIL__RESET_ODOMETRY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/srv/detail/reset_odometry__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_ResetOdometry_Request_phi
{
public:
  explicit Init_ResetOdometry_Request_phi(::rto_msgs::srv::ResetOdometry_Request & msg)
  : msg_(msg)
  {}
  ::rto_msgs::srv::ResetOdometry_Request phi(::rto_msgs::srv::ResetOdometry_Request::_phi_type arg)
  {
    msg_.phi = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::ResetOdometry_Request msg_;
};

class Init_ResetOdometry_Request_y
{
public:
  explicit Init_ResetOdometry_Request_y(::rto_msgs::srv::ResetOdometry_Request & msg)
  : msg_(msg)
  {}
  Init_ResetOdometry_Request_phi y(::rto_msgs::srv::ResetOdometry_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_ResetOdometry_Request_phi(msg_);
  }

private:
  ::rto_msgs::srv::ResetOdometry_Request msg_;
};

class Init_ResetOdometry_Request_x
{
public:
  Init_ResetOdometry_Request_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ResetOdometry_Request_y x(::rto_msgs::srv::ResetOdometry_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_ResetOdometry_Request_y(msg_);
  }

private:
  ::rto_msgs::srv::ResetOdometry_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::ResetOdometry_Request>()
{
  return rto_msgs::srv::builder::Init_ResetOdometry_Request_x();
}

}  // namespace rto_msgs


namespace rto_msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::ResetOdometry_Response>()
{
  return ::rto_msgs::srv::ResetOdometry_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace rto_msgs


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_ResetOdometry_Event_response
{
public:
  explicit Init_ResetOdometry_Event_response(::rto_msgs::srv::ResetOdometry_Event & msg)
  : msg_(msg)
  {}
  ::rto_msgs::srv::ResetOdometry_Event response(::rto_msgs::srv::ResetOdometry_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::ResetOdometry_Event msg_;
};

class Init_ResetOdometry_Event_request
{
public:
  explicit Init_ResetOdometry_Event_request(::rto_msgs::srv::ResetOdometry_Event & msg)
  : msg_(msg)
  {}
  Init_ResetOdometry_Event_response request(::rto_msgs::srv::ResetOdometry_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_ResetOdometry_Event_response(msg_);
  }

private:
  ::rto_msgs::srv::ResetOdometry_Event msg_;
};

class Init_ResetOdometry_Event_info
{
public:
  Init_ResetOdometry_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ResetOdometry_Event_request info(::rto_msgs::srv::ResetOdometry_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_ResetOdometry_Event_request(msg_);
  }

private:
  ::rto_msgs::srv::ResetOdometry_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::ResetOdometry_Event>()
{
  return rto_msgs::srv::builder::Init_ResetOdometry_Event_info();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__SRV__DETAIL__RESET_ODOMETRY__BUILDER_HPP_
