// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rto_msgs:srv/SetEncoderPosition.idl
// generated code does not contain a copyright notice
#include "rto_msgs/srv/detail/set_encoder_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
rto_msgs__srv__SetEncoderPosition_Request__init(rto_msgs__srv__SetEncoderPosition_Request * msg)
{
  if (!msg) {
    return false;
  }
  // position
  // velocity
  return true;
}

void
rto_msgs__srv__SetEncoderPosition_Request__fini(rto_msgs__srv__SetEncoderPosition_Request * msg)
{
  if (!msg) {
    return;
  }
  // position
  // velocity
}

bool
rto_msgs__srv__SetEncoderPosition_Request__are_equal(const rto_msgs__srv__SetEncoderPosition_Request * lhs, const rto_msgs__srv__SetEncoderPosition_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  return true;
}

bool
rto_msgs__srv__SetEncoderPosition_Request__copy(
  const rto_msgs__srv__SetEncoderPosition_Request * input,
  rto_msgs__srv__SetEncoderPosition_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // position
  output->position = input->position;
  // velocity
  output->velocity = input->velocity;
  return true;
}

rto_msgs__srv__SetEncoderPosition_Request *
rto_msgs__srv__SetEncoderPosition_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Request * msg = (rto_msgs__srv__SetEncoderPosition_Request *)allocator.allocate(sizeof(rto_msgs__srv__SetEncoderPosition_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__srv__SetEncoderPosition_Request));
  bool success = rto_msgs__srv__SetEncoderPosition_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__srv__SetEncoderPosition_Request__destroy(rto_msgs__srv__SetEncoderPosition_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__srv__SetEncoderPosition_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__srv__SetEncoderPosition_Request__Sequence__init(rto_msgs__srv__SetEncoderPosition_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Request * data = NULL;

  if (size) {
    data = (rto_msgs__srv__SetEncoderPosition_Request *)allocator.zero_allocate(size, sizeof(rto_msgs__srv__SetEncoderPosition_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__srv__SetEncoderPosition_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__srv__SetEncoderPosition_Request__fini(&data[i - 1]);
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
rto_msgs__srv__SetEncoderPosition_Request__Sequence__fini(rto_msgs__srv__SetEncoderPosition_Request__Sequence * array)
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
      rto_msgs__srv__SetEncoderPosition_Request__fini(&array->data[i]);
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

rto_msgs__srv__SetEncoderPosition_Request__Sequence *
rto_msgs__srv__SetEncoderPosition_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Request__Sequence * array = (rto_msgs__srv__SetEncoderPosition_Request__Sequence *)allocator.allocate(sizeof(rto_msgs__srv__SetEncoderPosition_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__srv__SetEncoderPosition_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__srv__SetEncoderPosition_Request__Sequence__destroy(rto_msgs__srv__SetEncoderPosition_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__srv__SetEncoderPosition_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__srv__SetEncoderPosition_Request__Sequence__are_equal(const rto_msgs__srv__SetEncoderPosition_Request__Sequence * lhs, const rto_msgs__srv__SetEncoderPosition_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__srv__SetEncoderPosition_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__srv__SetEncoderPosition_Request__Sequence__copy(
  const rto_msgs__srv__SetEncoderPosition_Request__Sequence * input,
  rto_msgs__srv__SetEncoderPosition_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__srv__SetEncoderPosition_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__srv__SetEncoderPosition_Request * data =
      (rto_msgs__srv__SetEncoderPosition_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__srv__SetEncoderPosition_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__srv__SetEncoderPosition_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__srv__SetEncoderPosition_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
rto_msgs__srv__SetEncoderPosition_Response__init(rto_msgs__srv__SetEncoderPosition_Response * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
rto_msgs__srv__SetEncoderPosition_Response__fini(rto_msgs__srv__SetEncoderPosition_Response * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
rto_msgs__srv__SetEncoderPosition_Response__are_equal(const rto_msgs__srv__SetEncoderPosition_Response * lhs, const rto_msgs__srv__SetEncoderPosition_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
rto_msgs__srv__SetEncoderPosition_Response__copy(
  const rto_msgs__srv__SetEncoderPosition_Response * input,
  rto_msgs__srv__SetEncoderPosition_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

rto_msgs__srv__SetEncoderPosition_Response *
rto_msgs__srv__SetEncoderPosition_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Response * msg = (rto_msgs__srv__SetEncoderPosition_Response *)allocator.allocate(sizeof(rto_msgs__srv__SetEncoderPosition_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__srv__SetEncoderPosition_Response));
  bool success = rto_msgs__srv__SetEncoderPosition_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__srv__SetEncoderPosition_Response__destroy(rto_msgs__srv__SetEncoderPosition_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__srv__SetEncoderPosition_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__srv__SetEncoderPosition_Response__Sequence__init(rto_msgs__srv__SetEncoderPosition_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Response * data = NULL;

  if (size) {
    data = (rto_msgs__srv__SetEncoderPosition_Response *)allocator.zero_allocate(size, sizeof(rto_msgs__srv__SetEncoderPosition_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__srv__SetEncoderPosition_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__srv__SetEncoderPosition_Response__fini(&data[i - 1]);
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
rto_msgs__srv__SetEncoderPosition_Response__Sequence__fini(rto_msgs__srv__SetEncoderPosition_Response__Sequence * array)
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
      rto_msgs__srv__SetEncoderPosition_Response__fini(&array->data[i]);
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

rto_msgs__srv__SetEncoderPosition_Response__Sequence *
rto_msgs__srv__SetEncoderPosition_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Response__Sequence * array = (rto_msgs__srv__SetEncoderPosition_Response__Sequence *)allocator.allocate(sizeof(rto_msgs__srv__SetEncoderPosition_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__srv__SetEncoderPosition_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__srv__SetEncoderPosition_Response__Sequence__destroy(rto_msgs__srv__SetEncoderPosition_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__srv__SetEncoderPosition_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__srv__SetEncoderPosition_Response__Sequence__are_equal(const rto_msgs__srv__SetEncoderPosition_Response__Sequence * lhs, const rto_msgs__srv__SetEncoderPosition_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__srv__SetEncoderPosition_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__srv__SetEncoderPosition_Response__Sequence__copy(
  const rto_msgs__srv__SetEncoderPosition_Response__Sequence * input,
  rto_msgs__srv__SetEncoderPosition_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__srv__SetEncoderPosition_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__srv__SetEncoderPosition_Response * data =
      (rto_msgs__srv__SetEncoderPosition_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__srv__SetEncoderPosition_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__srv__SetEncoderPosition_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__srv__SetEncoderPosition_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "rto_msgs/srv/detail/set_encoder_position__functions.h"

bool
rto_msgs__srv__SetEncoderPosition_Event__init(rto_msgs__srv__SetEncoderPosition_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    rto_msgs__srv__SetEncoderPosition_Event__fini(msg);
    return false;
  }
  // request
  if (!rto_msgs__srv__SetEncoderPosition_Request__Sequence__init(&msg->request, 0)) {
    rto_msgs__srv__SetEncoderPosition_Event__fini(msg);
    return false;
  }
  // response
  if (!rto_msgs__srv__SetEncoderPosition_Response__Sequence__init(&msg->response, 0)) {
    rto_msgs__srv__SetEncoderPosition_Event__fini(msg);
    return false;
  }
  return true;
}

void
rto_msgs__srv__SetEncoderPosition_Event__fini(rto_msgs__srv__SetEncoderPosition_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  rto_msgs__srv__SetEncoderPosition_Request__Sequence__fini(&msg->request);
  // response
  rto_msgs__srv__SetEncoderPosition_Response__Sequence__fini(&msg->response);
}

bool
rto_msgs__srv__SetEncoderPosition_Event__are_equal(const rto_msgs__srv__SetEncoderPosition_Event * lhs, const rto_msgs__srv__SetEncoderPosition_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!rto_msgs__srv__SetEncoderPosition_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!rto_msgs__srv__SetEncoderPosition_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
rto_msgs__srv__SetEncoderPosition_Event__copy(
  const rto_msgs__srv__SetEncoderPosition_Event * input,
  rto_msgs__srv__SetEncoderPosition_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!rto_msgs__srv__SetEncoderPosition_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!rto_msgs__srv__SetEncoderPosition_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

rto_msgs__srv__SetEncoderPosition_Event *
rto_msgs__srv__SetEncoderPosition_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Event * msg = (rto_msgs__srv__SetEncoderPosition_Event *)allocator.allocate(sizeof(rto_msgs__srv__SetEncoderPosition_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__srv__SetEncoderPosition_Event));
  bool success = rto_msgs__srv__SetEncoderPosition_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__srv__SetEncoderPosition_Event__destroy(rto_msgs__srv__SetEncoderPosition_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__srv__SetEncoderPosition_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__srv__SetEncoderPosition_Event__Sequence__init(rto_msgs__srv__SetEncoderPosition_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Event * data = NULL;

  if (size) {
    data = (rto_msgs__srv__SetEncoderPosition_Event *)allocator.zero_allocate(size, sizeof(rto_msgs__srv__SetEncoderPosition_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__srv__SetEncoderPosition_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__srv__SetEncoderPosition_Event__fini(&data[i - 1]);
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
rto_msgs__srv__SetEncoderPosition_Event__Sequence__fini(rto_msgs__srv__SetEncoderPosition_Event__Sequence * array)
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
      rto_msgs__srv__SetEncoderPosition_Event__fini(&array->data[i]);
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

rto_msgs__srv__SetEncoderPosition_Event__Sequence *
rto_msgs__srv__SetEncoderPosition_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetEncoderPosition_Event__Sequence * array = (rto_msgs__srv__SetEncoderPosition_Event__Sequence *)allocator.allocate(sizeof(rto_msgs__srv__SetEncoderPosition_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__srv__SetEncoderPosition_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__srv__SetEncoderPosition_Event__Sequence__destroy(rto_msgs__srv__SetEncoderPosition_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__srv__SetEncoderPosition_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__srv__SetEncoderPosition_Event__Sequence__are_equal(const rto_msgs__srv__SetEncoderPosition_Event__Sequence * lhs, const rto_msgs__srv__SetEncoderPosition_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__srv__SetEncoderPosition_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__srv__SetEncoderPosition_Event__Sequence__copy(
  const rto_msgs__srv__SetEncoderPosition_Event__Sequence * input,
  rto_msgs__srv__SetEncoderPosition_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__srv__SetEncoderPosition_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__srv__SetEncoderPosition_Event * data =
      (rto_msgs__srv__SetEncoderPosition_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__srv__SetEncoderPosition_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__srv__SetEncoderPosition_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__srv__SetEncoderPosition_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
