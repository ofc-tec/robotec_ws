// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:srv/SetEncoderPosition.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/set_encoder_position.hpp"


#ifndef RTO_MSGS__SRV__DETAIL__SET_ENCODER_POSITION__BUILDER_HPP_
#define RTO_MSGS__SRV__DETAIL__SET_ENCODER_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/srv/detail/set_encoder_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetEncoderPosition_Request_velocity
{
public:
  explicit Init_SetEncoderPosition_Request_velocity(::rto_msgs::srv::SetEncoderPosition_Request & msg)
  : msg_(msg)
  {}
  ::rto_msgs::srv::SetEncoderPosition_Request velocity(::rto_msgs::srv::SetEncoderPosition_Request::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetEncoderPosition_Request msg_;
};

class Init_SetEncoderPosition_Request_position
{
public:
  Init_SetEncoderPosition_Request_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetEncoderPosition_Request_velocity position(::rto_msgs::srv::SetEncoderPosition_Request::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_SetEncoderPosition_Request_velocity(msg_);
  }

private:
  ::rto_msgs::srv::SetEncoderPosition_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetEncoderPosition_Request>()
{
  return rto_msgs::srv::builder::Init_SetEncoderPosition_Request_position();
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
auto build<::rto_msgs::srv::SetEncoderPosition_Response>()
{
  return ::rto_msgs::srv::SetEncoderPosition_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace rto_msgs


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetEncoderPosition_Event_response
{
public:
  explicit Init_SetEncoderPosition_Event_response(::rto_msgs::srv::SetEncoderPosition_Event & msg)
  : msg_(msg)
  {}
  ::rto_msgs::srv::SetEncoderPosition_Event response(::rto_msgs::srv::SetEncoderPosition_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetEncoderPosition_Event msg_;
};

class Init_SetEncoderPosition_Event_request
{
public:
  explicit Init_SetEncoderPosition_Event_request(::rto_msgs::srv::SetEncoderPosition_Event & msg)
  : msg_(msg)
  {}
  Init_SetEncoderPosition_Event_response request(::rto_msgs::srv::SetEncoderPosition_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetEncoderPosition_Event_response(msg_);
  }

private:
  ::rto_msgs::srv::SetEncoderPosition_Event msg_;
};

class Init_SetEncoderPosition_Event_info
{
public:
  Init_SetEncoderPosition_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetEncoderPosition_Event_request info(::rto_msgs::srv::SetEncoderPosition_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetEncoderPosition_Event_request(msg_);
  }

private:
  ::rto_msgs::srv::SetEncoderPosition_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetEncoderPosition_Event>()
{
  return rto_msgs::srv::builder::Init_SetEncoderPosition_Event_info();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__SRV__DETAIL__SET_ENCODER_POSITION__BUILDER_HPP_
