// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:msg/MotorReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/motor_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__BUILDER_HPP_
#define RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/msg/detail/motor_readings__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace msg
{

namespace builder
{

class Init_MotorReadings_currents
{
public:
  explicit Init_MotorReadings_currents(::rto_msgs::msg::MotorReadings & msg)
  : msg_(msg)
  {}
  ::rto_msgs::msg::MotorReadings currents(::rto_msgs::msg::MotorReadings::_currents_type arg)
  {
    msg_.currents = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::msg::MotorReadings msg_;
};

class Init_MotorReadings_positions
{
public:
  explicit Init_MotorReadings_positions(::rto_msgs::msg::MotorReadings & msg)
  : msg_(msg)
  {}
  Init_MotorReadings_currents positions(::rto_msgs::msg::MotorReadings::_positions_type arg)
  {
    msg_.positions = std::move(arg);
    return Init_MotorReadings_currents(msg_);
  }

private:
  ::rto_msgs::msg::MotorReadings msg_;
};

class Init_MotorReadings_velocities
{
public:
  explicit Init_MotorReadings_velocities(::rto_msgs::msg::MotorReadings & msg)
  : msg_(msg)
  {}
  Init_MotorReadings_positions velocities(::rto_msgs::msg::MotorReadings::_velocities_type arg)
  {
    msg_.velocities = std::move(arg);
    return Init_MotorReadings_positions(msg_);
  }

private:
  ::rto_msgs::msg::MotorReadings msg_;
};

class Init_MotorReadings_header
{
public:
  Init_MotorReadings_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorReadings_velocities header(::rto_msgs::msg::MotorReadings::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_MotorReadings_velocities(msg_);
  }

private:
  ::rto_msgs::msg::MotorReadings msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::msg::MotorReadings>()
{
  return rto_msgs::msg::builder::Init_MotorReadings_header();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__BUILDER_HPP_
