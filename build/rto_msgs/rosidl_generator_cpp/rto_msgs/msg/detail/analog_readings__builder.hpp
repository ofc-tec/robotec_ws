// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:msg/AnalogReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/analog_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__ANALOG_READINGS__BUILDER_HPP_
#define RTO_MSGS__MSG__DETAIL__ANALOG_READINGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/msg/detail/analog_readings__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace msg
{

namespace builder
{

class Init_AnalogReadings_values
{
public:
  explicit Init_AnalogReadings_values(::rto_msgs::msg::AnalogReadings & msg)
  : msg_(msg)
  {}
  ::rto_msgs::msg::AnalogReadings values(::rto_msgs::msg::AnalogReadings::_values_type arg)
  {
    msg_.values = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::msg::AnalogReadings msg_;
};

class Init_AnalogReadings_header
{
public:
  Init_AnalogReadings_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AnalogReadings_values header(::rto_msgs::msg::AnalogReadings::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_AnalogReadings_values(msg_);
  }

private:
  ::rto_msgs::msg::AnalogReadings msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::msg::AnalogReadings>()
{
  return rto_msgs::msg::builder::Init_AnalogReadings_header();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__ANALOG_READINGS__BUILDER_HPP_
