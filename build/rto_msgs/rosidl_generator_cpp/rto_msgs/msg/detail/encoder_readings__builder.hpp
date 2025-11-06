// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:msg/EncoderReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/encoder_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__BUILDER_HPP_
#define RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/msg/detail/encoder_readings__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace msg
{

namespace builder
{

class Init_EncoderReadings_current
{
public:
  explicit Init_EncoderReadings_current(::rto_msgs::msg::EncoderReadings & msg)
  : msg_(msg)
  {}
  ::rto_msgs::msg::EncoderReadings current(::rto_msgs::msg::EncoderReadings::_current_type arg)
  {
    msg_.current = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::msg::EncoderReadings msg_;
};

class Init_EncoderReadings_position
{
public:
  explicit Init_EncoderReadings_position(::rto_msgs::msg::EncoderReadings & msg)
  : msg_(msg)
  {}
  Init_EncoderReadings_current position(::rto_msgs::msg::EncoderReadings::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_EncoderReadings_current(msg_);
  }

private:
  ::rto_msgs::msg::EncoderReadings msg_;
};

class Init_EncoderReadings_velocity
{
public:
  explicit Init_EncoderReadings_velocity(::rto_msgs::msg::EncoderReadings & msg)
  : msg_(msg)
  {}
  Init_EncoderReadings_position velocity(::rto_msgs::msg::EncoderReadings::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_EncoderReadings_position(msg_);
  }

private:
  ::rto_msgs::msg::EncoderReadings msg_;
};

class Init_EncoderReadings_header
{
public:
  Init_EncoderReadings_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_EncoderReadings_velocity header(::rto_msgs::msg::EncoderReadings::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_EncoderReadings_velocity(msg_);
  }

private:
  ::rto_msgs::msg::EncoderReadings msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::msg::EncoderReadings>()
{
  return rto_msgs::msg::builder::Init_EncoderReadings_header();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__BUILDER_HPP_
