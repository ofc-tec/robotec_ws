// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:srv/SetGripperState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/srv/set_gripper_state.hpp"


#ifndef RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__BUILDER_HPP_
#define RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/srv/detail/set_gripper_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetGripperState_Request_state
{
public:
  Init_SetGripperState_Request_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rto_msgs::srv::SetGripperState_Request state(::rto_msgs::srv::SetGripperState_Request::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetGripperState_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetGripperState_Request>()
{
  return rto_msgs::srv::builder::Init_SetGripperState_Request_state();
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
auto build<::rto_msgs::srv::SetGripperState_Response>()
{
  return ::rto_msgs::srv::SetGripperState_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace rto_msgs


namespace rto_msgs
{

namespace srv
{

namespace builder
{

class Init_SetGripperState_Event_response
{
public:
  explicit Init_SetGripperState_Event_response(::rto_msgs::srv::SetGripperState_Event & msg)
  : msg_(msg)
  {}
  ::rto_msgs::srv::SetGripperState_Event response(::rto_msgs::srv::SetGripperState_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::srv::SetGripperState_Event msg_;
};

class Init_SetGripperState_Event_request
{
public:
  explicit Init_SetGripperState_Event_request(::rto_msgs::srv::SetGripperState_Event & msg)
  : msg_(msg)
  {}
  Init_SetGripperState_Event_response request(::rto_msgs::srv::SetGripperState_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetGripperState_Event_response(msg_);
  }

private:
  ::rto_msgs::srv::SetGripperState_Event msg_;
};

class Init_SetGripperState_Event_info
{
public:
  Init_SetGripperState_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetGripperState_Event_request info(::rto_msgs::srv::SetGripperState_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetGripperState_Event_request(msg_);
  }

private:
  ::rto_msgs::srv::SetGripperState_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::srv::SetGripperState_Event>()
{
  return rto_msgs::srv::builder::Init_SetGripperState_Event_info();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__SRV__DETAIL__SET_GRIPPER_STATE__BUILDER_HPP_
