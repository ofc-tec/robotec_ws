// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:msg/PowerReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/power_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__POWER_READINGS__BUILDER_HPP_
#define RTO_MSGS__MSG__DETAIL__POWER_READINGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/msg/detail/power_readings__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace msg
{

namespace builder
{

class Init_PowerReadings_battery_low
{
public:
  explicit Init_PowerReadings_battery_low(::rto_msgs::msg::PowerReadings & msg)
  : msg_(msg)
  {}
  ::rto_msgs::msg::PowerReadings battery_low(::rto_msgs::msg::PowerReadings::_battery_low_type arg)
  {
    msg_.battery_low = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::msg::PowerReadings msg_;
};

class Init_PowerReadings_voltage
{
public:
  explicit Init_PowerReadings_voltage(::rto_msgs::msg::PowerReadings & msg)
  : msg_(msg)
  {}
  Init_PowerReadings_battery_low voltage(::rto_msgs::msg::PowerReadings::_voltage_type arg)
  {
    msg_.voltage = std::move(arg);
    return Init_PowerReadings_battery_low(msg_);
  }

private:
  ::rto_msgs::msg::PowerReadings msg_;
};

class Init_PowerReadings_current
{
public:
  explicit Init_PowerReadings_current(::rto_msgs::msg::PowerReadings & msg)
  : msg_(msg)
  {}
  Init_PowerReadings_voltage current(::rto_msgs::msg::PowerReadings::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_PowerReadings_voltage(msg_);
  }

private:
  ::rto_msgs::msg::PowerReadings msg_;
};

class Init_PowerReadings_header
{
public:
  Init_PowerReadings_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PowerReadings_current header(::rto_msgs::msg::PowerReadings::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PowerReadings_current(msg_);
  }

private:
  ::rto_msgs::msg::PowerReadings msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::msg::PowerReadings>()
{
  return rto_msgs::msg::builder::Init_PowerReadings_header();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__POWER_READINGS__BUILDER_HPP_
