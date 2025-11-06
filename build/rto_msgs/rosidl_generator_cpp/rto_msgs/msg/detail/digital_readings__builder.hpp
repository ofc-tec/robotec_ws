// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rto_msgs:msg/DigitalReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/digital_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__DIGITAL_READINGS__BUILDER_HPP_
#define RTO_MSGS__MSG__DETAIL__DIGITAL_READINGS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rto_msgs/msg/detail/digital_readings__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rto_msgs
{

namespace msg
{

namespace builder
{

class Init_DigitalReadings_values
{
public:
  explicit Init_DigitalReadings_values(::rto_msgs::msg::DigitalReadings & msg)
  : msg_(msg)
  {}
  ::rto_msgs::msg::DigitalReadings values(::rto_msgs::msg::DigitalReadings::_values_type arg)
  {
    msg_.values = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rto_msgs::msg::DigitalReadings msg_;
};

class Init_DigitalReadings_header
{
public:
  Init_DigitalReadings_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DigitalReadings_values header(::rto_msgs::msg::DigitalReadings::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DigitalReadings_values(msg_);
  }

private:
  ::rto_msgs::msg::DigitalReadings msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::rto_msgs::msg::DigitalReadings>()
{
  return rto_msgs::msg::builder::Init_DigitalReadings_header();
}

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__DIGITAL_READINGS__BUILDER_HPP_
