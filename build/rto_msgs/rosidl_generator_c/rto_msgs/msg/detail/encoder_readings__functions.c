// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rto_msgs:msg/EncoderReadings.idl
// generated code does not contain a copyright notice
#include "rto_msgs/msg/detail/encoder_readings__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
rto_msgs__msg__EncoderReadings__init(rto_msgs__msg__EncoderReadings * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    rto_msgs__msg__EncoderReadings__fini(msg);
    return false;
  }
  // velocity
  // position
  // current
  return true;
}

void
rto_msgs__msg__EncoderReadings__fini(rto_msgs__msg__EncoderReadings * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // velocity
  // position
  // current
}

bool
rto_msgs__msg__EncoderReadings__are_equal(const rto_msgs__msg__EncoderReadings * lhs, const rto_msgs__msg__EncoderReadings * rhs)
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
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // current
  if (lhs->current != rhs->current) {
    return false;
  }
  return true;
}

bool
rto_msgs__msg__EncoderReadings__copy(
  const rto_msgs__msg__EncoderReadings * input,
  rto_msgs__msg__EncoderReadings * output)
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
  // velocity
  output->velocity = input->velocity;
  // position
  output->position = input->position;
  // current
  output->current = input->current;
  return true;
}

rto_msgs__msg__EncoderReadings *
rto_msgs__msg__EncoderReadings__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__EncoderReadings * msg = (rto_msgs__msg__EncoderReadings *)allocator.allocate(sizeof(rto_msgs__msg__EncoderReadings), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__msg__EncoderReadings));
  bool success = rto_msgs__msg__EncoderReadings__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__msg__EncoderReadings__destroy(rto_msgs__msg__EncoderReadings * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__msg__EncoderReadings__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__msg__EncoderReadings__Sequence__init(rto_msgs__msg__EncoderReadings__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__EncoderReadings * data = NULL;

  if (size) {
    data = (rto_msgs__msg__EncoderReadings *)allocator.zero_allocate(size, sizeof(rto_msgs__msg__EncoderReadings), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__msg__EncoderReadings__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__msg__EncoderReadings__fini(&data[i - 1]);
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
rto_msgs__msg__EncoderReadings__Sequence__fini(rto_msgs__msg__EncoderReadings__Sequence * array)
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
      rto_msgs__msg__EncoderReadings__fini(&array->data[i]);
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

rto_msgs__msg__EncoderReadings__Sequence *
rto_msgs__msg__EncoderReadings__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__msg__EncoderReadings__Sequence * array = (rto_msgs__msg__EncoderReadings__Sequence *)allocator.allocate(sizeof(rto_msgs__msg__EncoderReadings__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__msg__EncoderReadings__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__msg__EncoderReadings__Sequence__destroy(rto_msgs__msg__EncoderReadings__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__msg__EncoderReadings__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__msg__EncoderReadings__Sequence__are_equal(const rto_msgs__msg__EncoderReadings__Sequence * lhs, const rto_msgs__msg__EncoderReadings__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__msg__EncoderReadings__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__msg__EncoderReadings__Sequence__copy(
  const rto_msgs__msg__EncoderReadings__Sequence * input,
  rto_msgs__msg__EncoderReadings__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__msg__EncoderReadings);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__msg__EncoderReadings * data =
      (rto_msgs__msg__EncoderReadings *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__msg__EncoderReadings__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__msg__EncoderReadings__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__msg__EncoderReadings__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
