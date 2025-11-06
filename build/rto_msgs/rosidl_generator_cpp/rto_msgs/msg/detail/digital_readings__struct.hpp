// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rto_msgs:msg/DigitalReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/digital_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__DIGITAL_READINGS__STRUCT_HPP_
#define RTO_MSGS__MSG__DETAIL__DIGITAL_READINGS__STRUCT_HPP_

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
# define DEPRECATED__rto_msgs__msg__DigitalReadings __attribute__((deprecated))
#else
# define DEPRECATED__rto_msgs__msg__DigitalReadings __declspec(deprecated)
#endif

namespace rto_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DigitalReadings_
{
  using Type = DigitalReadings_<ContainerAllocator>;

  explicit DigitalReadings_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit DigitalReadings_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _values_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _values_type values;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__values(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->values = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    rto_msgs::msg::DigitalReadings_<ContainerAllocator> *;
  using ConstRawPtr =
    const rto_msgs::msg::DigitalReadings_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rto_msgs::msg::DigitalReadings_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rto_msgs::msg::DigitalReadings_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rto_msgs::msg::DigitalReadings_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rto_msgs::msg::DigitalReadings_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rto_msgs::msg::DigitalReadings_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rto_msgs::msg::DigitalReadings_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rto_msgs::msg::DigitalReadings_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rto_msgs::msg::DigitalReadings_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rto_msgs__msg__DigitalReadings
    std::shared_ptr<rto_msgs::msg::DigitalReadings_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rto_msgs__msg__DigitalReadings
    std::shared_ptr<rto_msgs::msg::DigitalReadings_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DigitalReadings_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->values != other.values) {
      return false;
    }
    return true;
  }
  bool operator!=(const DigitalReadings_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DigitalReadings_

// alias to use template instance with default allocator
using DigitalReadings =
  rto_msgs::msg::DigitalReadings_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__DIGITAL_READINGS__STRUCT_HPP_
