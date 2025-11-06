// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from rto_msgs:msg/MotorReadings.idl
// generated code does not contain a copyright notice
#ifndef RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "rto_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "rto_msgs/msg/detail/motor_readings__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rto_msgs
bool cdr_serialize_rto_msgs__msg__MotorReadings(
  const rto_msgs__msg__MotorReadings * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rto_msgs
bool cdr_deserialize_rto_msgs__msg__MotorReadings(
  eprosima::fastcdr::Cdr &,
  rto_msgs__msg__MotorReadings * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rto_msgs
size_t get_serialized_size_rto_msgs__msg__MotorReadings(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rto_msgs
size_t max_serialized_size_rto_msgs__msg__MotorReadings(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rto_msgs
bool cdr_serialize_key_rto_msgs__msg__MotorReadings(
  const rto_msgs__msg__MotorReadings * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rto_msgs
size_t get_serialized_size_key_rto_msgs__msg__MotorReadings(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rto_msgs
size_t max_serialized_size_key_rto_msgs__msg__MotorReadings(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_rto_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rto_msgs, msg, MotorReadings)();

#ifdef __cplusplus
}
#endif

#endif  // RTO_MSGS__MSG__DETAIL__MOTOR_READINGS__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
