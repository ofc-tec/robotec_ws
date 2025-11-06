// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:msg/MotorErrorReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/motor_error_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__BUILDER_HPP_
#define RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/msg/detail/motor_error_readings__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace msg
{

namespace builder
{

class Init_MotorErrorReadings_error_msg
{
public:
  explicit Init_MotorErrorReadings_error_msg(::rto_msgs::msg::MotorErrorReadings & msg)
  : msg_(msg)
  {}
  ::rto_msgs::msg::MotorErrorReadings error_msg(::rto_msgs::msg::MotorErrorReadings::_error_msg_type arg)
  {
    msg_.error_msg = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::msg::MotorErrorReadings msg_;
};

class Init_MotorErrorReadings_error_code
{
public:
  explicit Init_MotorErrorReadings_error_code(::rto_msgs::msg::MotorErrorReadings & msg)
  : msg_(msg)
  {}
  Init_MotorErrorReadings_error_msg error_code(::rto_msgs::msg::MotorErrorReadings::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_MotorErrorReadings_error_msg(msg_);
  }

private:
  ::rto_msgs::msg::MotorErrorReadings msg_;
};

class Init_MotorErrorReadings_error_status
{
public:
  explicit Init_MotorErrorReadings_error_status(::rto_msgs::msg::MotorErrorReadings & msg)
  : msg_(msg)
  {}
  Init_MotorErrorReadings_error_code error_status(::rto_msgs::msg::MotorErrorReadings::_error_status_type arg)
  {
    msg_.error_status = std::move(arg);
    return Init_MotorErrorReadings_error_code(msg_);
  }

private:
  ::rto_msgs::msg::MotorErrorReadings msg_;
};

class Init_MotorErrorReadings_name
{
public:
  explicit Init_MotorErrorReadings_name(::rto_msgs::msg::MotorErrorReadings & msg)
  : msg_(msg)
  {}
  Init_MotorErrorReadings_error_status name(::rto_msgs::msg::MotorErrorReadings::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_MotorErrorReadings_error_status(msg_);
  }

private:
  ::rto_msgs::msg::MotorErrorReadings msg_;
};

class Init_MotorErrorReadings_header
{
public:
  Init_MotorErrorReadings_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorErrorReadings_name header(::rto_msgs::msg::MotorErrorReadings::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MotorErrorReadings_name(msg_);
  }

private:
  ::rto_msgs::msg::MotorErrorReadings msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::msg::MotorErrorReadings>()
{
  return rto_msgs::msg::builder::Init_MotorErrorReadings_header();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__BUILDER_HPP_
