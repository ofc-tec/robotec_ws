// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rto_msgs:msg/MotorErrorReadings.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "rto_msgs/msg/motor_error_readings.hpp"


#ifndef RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__STRUCT_HPP_
#define RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__STRUCT_HPP_

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
# define DEPRECATED__rto_msgs__msg__MotorErrorReadings __attribute__((deprecated))
#else
# define DEPRECATED__rto_msgs__msg__MotorErrorReadings __declspec(deprecated)
#endif

namespace rto_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorErrorReadings_
{
  using Type = MotorErrorReadings_<ContainerAllocator>;

  explicit MotorErrorReadings_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit MotorErrorReadings_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _name_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _name_type name;
  using _error_status_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _error_status_type error_status;
  using _error_code_type =
    std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>>;
  _error_code_type error_code;
  using _error_msg_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _error_msg_type error_msg;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__name(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__error_status(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->error_status = _arg;
    return *this;
  }
  Type & set__error_code(
    const std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> & _arg)
  {
    this->error_code = _arg;
    return *this;
  }
  Type & set__error_msg(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->error_msg = _arg;
    return *this;
  }

  // constant declarations
  // guard against 'NO_ERROR' being predefined by MSVC by temporarily undefining it
#if defined(_WIN32)
#  if defined(NO_ERROR)
#    pragma push_macro("NO_ERROR")
#    undef NO_ERROR
#  endif
#endif
  static constexpr uint8_t NO_ERROR =
    0u;
#if defined(_WIN32)
#  pragma warning(suppress : 4602)
#  pragma pop_macro("NO_ERROR")
#endif
  static constexpr uint8_t ENCODER_FAILURE =
    1u;
  static constexpr uint8_t DRIVE_FAILURE =
    2u;
  static constexpr uint8_t LOW_VOLTAGE =
    3u;
  static constexpr uint8_t UNKNOWN_ERROR =
    255u;

  // pointer types
  using RawPtr =
    rto_msgs::msg::MotorErrorReadings_<ContainerAllocator> *;
  using ConstRawPtr =
    const rto_msgs::msg::MotorErrorReadings_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rto_msgs::msg::MotorErrorReadings_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rto_msgs::msg::MotorErrorReadings_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rto_msgs::msg::MotorErrorReadings_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rto_msgs::msg::MotorErrorReadings_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rto_msgs::msg::MotorErrorReadings_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rto_msgs::msg::MotorErrorReadings_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rto_msgs::msg::MotorErrorReadings_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rto_msgs::msg::MotorErrorReadings_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rto_msgs__msg__MotorErrorReadings
    std::shared_ptr<rto_msgs::msg::MotorErrorReadings_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rto_msgs__msg__MotorErrorReadings
    std::shared_ptr<rto_msgs::msg::MotorErrorReadings_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorErrorReadings_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->name != other.name) {
      return false;
    }
    if (this->error_status != other.error_status) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->error_msg != other.error_msg) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorErrorReadings_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorErrorReadings_

// alias to use template instance with default allocator
using MotorErrorReadings =
  rto_msgs::msg::MotorErrorReadings_<std::allocator<void>>;

// constant definitions
// guard against 'NO_ERROR' being predefined by MSVC by temporarily undefining it
#if defined(_WIN32)
#  if defined(NO_ERROR)
#    pragma push_macro("NO_ERROR")
#    undef NO_ERROR
#  endif
#endif
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MotorErrorReadings_<ContainerAllocator>::NO_ERROR;
#endif  // __cplusplus < 201703L
#if defined(_WIN32)
#  pragma warning(suppress : 4602)
#  pragma pop_macro("NO_ERROR")
#endif
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MotorErrorReadings_<ContainerAllocator>::ENCODER_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MotorErrorReadings_<ContainerAllocator>::DRIVE_FAILURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MotorErrorReadings_<ContainerAllocator>::LOW_VOLTAGE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t MotorErrorReadings_<ContainerAllocator>::UNKNOWN_ERROR;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace rto_msgs

#endif  // RTO_MSGS__MSG__DETAIL__MOTOR_ERROR_READINGS__STRUCT_HPP_
