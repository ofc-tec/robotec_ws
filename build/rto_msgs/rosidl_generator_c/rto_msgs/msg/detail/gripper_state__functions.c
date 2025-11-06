// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rto_msgs:msg/GripperState.idl
// generated code does not contain a copyright notice
#include "rto_msgs/msg/detail/gripper_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
rto_msgs__msg__GripperState__init(rto_msgs__msg__GripperState * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    rto_msgs__msg__GripperState__fini(msg);
    return false;
  }
  // state
  return true;
}

void
rto_msgs__msg__GripperState__fini(rto_msgs__msg__GripperState * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // state
}

bool
rto_msgs__msg__GripperState__are_equal(const rto_msgs__msg__GripperState * lhs, const rto_msgs__msg__GripperState * rhs)
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
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  return true;
}

bool
rto_msgs__msg__GripperState__copy(
  const rto_msgs__msg__GripperState * input,
  rto_msgs__msg__GripperState * output)
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
  // state
  output->state = input->state;
  return true;
}

rto_msgs__msg__GripperState *
rto_msgs__msg__GripperState__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__GripperState * msg = (rto_msgs__msg__GripperState *)allocator.allocate(sizeof(rto_msgs__msg__GripperState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__msg__GripperState));
  bool success = rto_msgs__msg__GripperState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__msg__GripperState__destroy(rto_msgs__msg__GripperState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__msg__GripperState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__msg__GripperState__Sequence__init(rto_msgs__msg__GripperState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__GripperState * data = NULL;

  if (size) {
    data = (rto_msgs__msg__GripperState *)allocator.zero_allocate(size, sizeof(rto_msgs__msg__GripperState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__msg__GripperState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__msg__GripperState__fini(&data[i - 1]);
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
rto_msgs__msg__GripperState__Sequence__fini(rto_msgs__msg__GripperState__Sequence * array)
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
      rto_msgs__msg__GripperState__fini(&array->data[i]);
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

rto_msgs__msg__GripperState__Sequence *
rto_msgs__msg__GripperState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__GripperState__Sequence * array = (rto_msgs__msg__GripperState__Sequence *)allocator.allocate(sizeof(rto_msgs__msg__GripperState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__msg__GripperState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__msg__GripperState__Sequence__destroy(rto_msgs__msg__GripperState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__msg__GripperState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__msg__GripperState__Sequence__are_equal(const rto_msgs__msg__GripperState__Sequence * lhs, const rto_msgs__msg__GripperState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__msg__GripperState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__msg__GripperState__Sequence__copy(
  const rto_msgs__msg__GripperState__Sequence * input,
  rto_msgs__msg__GripperState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__msg__GripperState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__msg__GripperState * data =
      (rto_msgs__msg__GripperState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__msg__GripperState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__msg__GripperState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__msg__GripperState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
