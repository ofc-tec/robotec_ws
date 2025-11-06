// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rto_msgs:msg/PowerReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/power_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__POWER_READINGS__STRUCT_HPP_
#define RTO_MSGS__MSG__DETAIL__POWER_READINGS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rto_msgs__msg__PowerReadings __attribute__((deprecated))
#else
# define DEPRECATED__rto_msgs__msg__PowerReadings __declspec(deprecated)
#endif

namespace rto_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PowerReadings_
{
  using Type = PowerReadings_<ContainerAllocator>;

  explicit PowerReadings_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current = 0.0f;
      this->voltage = 0.0f;
      this->battery_low = false;
    }
  }

  explicit PowerReadings_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current = 0.0f;
      this->voltage = 0.0f;
      this->battery_low = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _current_type =
    float;
  _current_type current;
  using _voltage_type =
    float;
  _voltage_type voltage;
  using _battery_low_type =
    bool;
  _battery_low_type battery_low;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__current(
    const float & _arg)
  {
    this->current = _arg;
    return *this;
  }
  Type & set__voltage(
    const float & _arg)
  {
    this->voltage = _arg;
    return *this;
  }
  Type & set__battery_low(
    const bool & _arg)
  {
    this->battery_low = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rto_msgs::msg::PowerReadings_<ContainerAllocator> *;
  using ConstRawPtr =
    const rto_msgs::msg::PowerReadings_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rto_msgs::msg::PowerReadings_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rto_msgs::msg::PowerReadings_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rto_msgs::msg::PowerReadings_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rto_msgs::msg::PowerReadings_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rto_msgs::msg::PowerReadings_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rto_msgs::msg::PowerReadings_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rto_msgs::msg::PowerReadings_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rto_msgs::msg::PowerReadings_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rto_msgs__msg__PowerReadings
    std::shared_ptr<rto_msgs::msg::PowerReadings_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rto_msgs__msg__PowerReadings
    std::shared_ptr<rto_msgs::msg::PowerReadings_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PowerReadings_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    if (this->voltage != other.voltage) {
      return false;
    }
    if (this->battery_low != other.battery_low) {
      return false;
    }
    return true;
  }
  bool operator!=(const PowerReadings_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PowerReadings_

// alias to use template instance with default allocator
using PowerReadings =
  rto_msgs::msg::PowerReadings_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__POWER_READINGS__STRUCT_HPP_
