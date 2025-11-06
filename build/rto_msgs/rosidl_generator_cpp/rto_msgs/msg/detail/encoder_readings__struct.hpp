// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rto_msgs:msg/EncoderReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/encoder_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__STRUCT_HPP_
#define RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__STRUCT_HPP_

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
# define DEPRECATED__rto_msgs__msg__EncoderReadings __attribute__((deprecated))
#else
# define DEPRECATED__rto_msgs__msg__EncoderReadings __declspec(deprecated)
#endif

namespace rto_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EncoderReadings_
{
  using Type = EncoderReadings_<ContainerAllocator>;

  explicit EncoderReadings_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity = 0ul;
      this->position = 0ul;
      this->current = 0ul;
    }
  }

  explicit EncoderReadings_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity = 0ul;
      this->position = 0ul;
      this->current = 0ul;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _velocity_type =
    uint32_t;
  _velocity_type velocity;
  using _position_type =
    uint32_t;
  _position_type position;
  using _current_type =
    uint32_t;
  _current_type current;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__velocity(
    const uint32_t & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__position(
    const uint32_t & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__current(
    const uint32_t & _arg)
  {
    this->current = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rto_msgs::msg::EncoderReadings_<ContainerAllocator> *;
  using ConstRawPtr =
    const rto_msgs::msg::EncoderReadings_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rto_msgs::msg::EncoderReadings_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rto_msgs::msg::EncoderReadings_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rto_msgs::msg::EncoderReadings_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rto_msgs::msg::EncoderReadings_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rto_msgs::msg::EncoderReadings_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rto_msgs::msg::EncoderReadings_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rto_msgs::msg::EncoderReadings_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rto_msgs::msg::EncoderReadings_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rto_msgs__msg__EncoderReadings
    std::shared_ptr<rto_msgs::msg::EncoderReadings_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rto_msgs__msg__EncoderReadings
    std::shared_ptr<rto_msgs::msg::EncoderReadings_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EncoderReadings_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    return true;
  }
  bool operator!=(const EncoderReadings_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EncoderReadings_

// alias to use template instance with default allocator
using EncoderReadings =
  rto_msgs::msg::EncoderReadings_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__ENCODER_READINGS__STRUCT_HPP_
