// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:msg/GripperState.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/gripper_state.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__GRIPPER_STATE__BUILDER_HPP_
#define RTO_MSGS__MSG__DETAIL__GRIPPER_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/msg/detail/gripper_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace msg
{

namespace builder
{

class Init_GripperState_state
{
public:
  explicit Init_GripperState_state(::rto_msgs::msg::GripperState & msg)
  : msg_(msg)
  {}
  ::rto_msgs::msg::GripperState state(::rto_msgs::msg::GripperState::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::msg::GripperState msg_;
};

class Init_GripperState_header
{
public:
  Init_GripperState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperState_state header(::rto_msgs::msg::GripperState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GripperState_state(msg_);
  }

private:
  ::rto_msgs::msg::GripperState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::msg::GripperState>()
{
  return rto_msgs::msg::builder::Init_GripperState_header();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__GRIPPER_STATE__BUILDER_HPP_
