// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rto_msgs:msg/DigitalReadings.idl
// generated code does not contain a copyright notice
#include "rto_msgs/msg/detail/digital_readings__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `values`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
rto_msgs__msg__DigitalReadings__init(rto_msgs__msg__DigitalReadings * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    rto_msgs__msg__DigitalReadings__fini(msg);
    return false;
  }
  // values
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->values, 0)) {
    rto_msgs__msg__DigitalReadings__fini(msg);
    return false;
  }
  return true;
}

void
rto_msgs__msg__DigitalReadings__fini(rto_msgs__msg__DigitalReadings * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // values
  rosidl_runtime_c__boolean__Sequence__fini(&msg->values);
}

bool
rto_msgs__msg__DigitalReadings__are_equal(const rto_msgs__msg__DigitalReadings * lhs, const rto_msgs__msg__DigitalReadings * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // values
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->values), &(rhs->values)))
  {
    return false;
  }
  return true;
}

bool
rto_msgs__msg__DigitalReadings__copy(
  const rto_msgs__msg__DigitalReadings * input,
  rto_msgs__msg__DigitalReadings * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // values
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->values), &(output->values)))
  {
    return false;
  }
  return true;
}

rto_msgs__msg__DigitalReadings *
rto_msgs__msg__DigitalReadings__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__DigitalReadings * msg = (rto_msgs__msg__DigitalReadings *)allocator.allocate(sizeof(rto_msgs__msg__DigitalReadings), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__msg__DigitalReadings));
  bool success = rto_msgs__msg__DigitalReadings__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__msg__DigitalReadings__destroy(rto_msgs__msg__DigitalReadings * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__msg__DigitalReadings__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__msg__DigitalReadings__Sequence__init(rto_msgs__msg__DigitalReadings__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__DigitalReadings * data = NULL;

  if (size) {
    data = (rto_msgs__msg__DigitalReadings *)allocator.zero_allocate(size, sizeof(rto_msgs__msg__DigitalReadings), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__msg__DigitalReadings__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__msg__DigitalReadings__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rto_msgs__msg__DigitalReadings__Sequence__fini(rto_msgs__msg__DigitalReadings__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rto_msgs__msg__DigitalReadings__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rto_msgs__msg__DigitalReadings__Sequence *
rto_msgs__msg__DigitalReadings__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__DigitalReadings__Sequence * array = (rto_msgs__msg__DigitalReadings__Sequence *)allocator.allocate(sizeof(rto_msgs__msg__DigitalReadings__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__msg__DigitalReadings__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__msg__DigitalReadings__Sequence__destroy(rto_msgs__msg__DigitalReadings__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__msg__DigitalReadings__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__msg__DigitalReadings__Sequence__are_equal(const rto_msgs__msg__DigitalReadings__Sequence * lhs, const rto_msgs__msg__DigitalReadings__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__msg__DigitalReadings__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__msg__DigitalReadings__Sequence__copy(
  const rto_msgs__msg__DigitalReadings__Sequence * input,
  rto_msgs__msg__DigitalReadings__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__msg__DigitalReadings);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__msg__DigitalReadings * data =
      (rto_msgs__msg__DigitalReadings *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__msg__DigitalReadings__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__msg__DigitalReadings__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__msg__DigitalReadings__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
