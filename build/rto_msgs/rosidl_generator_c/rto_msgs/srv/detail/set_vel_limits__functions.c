// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rto_msgs:srv/SetVelLimits.idl
// generated code does not contain a copyright notice
#include "rto_msgs/srv/detail/set_vel_limits__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
rto_msgs__srv__SetVelLimits_Request__init(rto_msgs__srv__SetVelLimits_Request * msg)
{
  if (!msg) {
    return false;
  }
  // max_linear_vel
  // min_linear_vel
  // max_angular_vel
  // min_angular_vel
  return true;
}

void
rto_msgs__srv__SetVelLimits_Request__fini(rto_msgs__srv__SetVelLimits_Request * msg)
{
  if (!msg) {
    return;
  }
  // max_linear_vel
  // min_linear_vel
  // max_angular_vel
  // min_angular_vel
}

bool
rto_msgs__srv__SetVelLimits_Request__are_equal(const rto_msgs__srv__SetVelLimits_Request * lhs, const rto_msgs__srv__SetVelLimits_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // max_linear_vel
  if (lhs->max_linear_vel != rhs->max_linear_vel) {
    return false;
  }
  // min_linear_vel
  if (lhs->min_linear_vel != rhs->min_linear_vel) {
    return false;
  }
  // max_angular_vel
  if (lhs->max_angular_vel != rhs->max_angular_vel) {
    return false;
  }
  // min_angular_vel
  if (lhs->min_angular_vel != rhs->min_angular_vel) {
    return false;
  }
  return true;
}

bool
rto_msgs__srv__SetVelLimits_Request__copy(
  const rto_msgs__srv__SetVelLimits_Request * input,
  rto_msgs__srv__SetVelLimits_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // max_linear_vel
  output->max_linear_vel = input->max_linear_vel;
  // min_linear_vel
  output->min_linear_vel = input->min_linear_vel;
  // max_angular_vel
  output->max_angular_vel = input->max_angular_vel;
  // min_angular_vel
  output->min_angular_vel = input->min_angular_vel;
  return true;
}

rto_msgs__srv__SetVelLimits_Request *
rto_msgs__srv__SetVelLimits_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Request * msg = (rto_msgs__srv__SetVelLimits_Request *)allocator.allocate(sizeof(rto_msgs__srv__SetVelLimits_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__srv__SetVelLimits_Request));
  bool success = rto_msgs__srv__SetVelLimits_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__srv__SetVelLimits_Request__destroy(rto_msgs__srv__SetVelLimits_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__srv__SetVelLimits_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__srv__SetVelLimits_Request__Sequence__init(rto_msgs__srv__SetVelLimits_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Request * data = NULL;

  if (size) {
    data = (rto_msgs__srv__SetVelLimits_Request *)allocator.zero_allocate(size, sizeof(rto_msgs__srv__SetVelLimits_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__srv__SetVelLimits_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__srv__SetVelLimits_Request__fini(&data[i - 1]);
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
rto_msgs__srv__SetVelLimits_Request__Sequence__fini(rto_msgs__srv__SetVelLimits_Request__Sequence * array)
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
      rto_msgs__srv__SetVelLimits_Request__fini(&array->data[i]);
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

rto_msgs__srv__SetVelLimits_Request__Sequence *
rto_msgs__srv__SetVelLimits_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Request__Sequence * array = (rto_msgs__srv__SetVelLimits_Request__Sequence *)allocator.allocate(sizeof(rto_msgs__srv__SetVelLimits_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__srv__SetVelLimits_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__srv__SetVelLimits_Request__Sequence__destroy(rto_msgs__srv__SetVelLimits_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__srv__SetVelLimits_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__srv__SetVelLimits_Request__Sequence__are_equal(const rto_msgs__srv__SetVelLimits_Request__Sequence * lhs, const rto_msgs__srv__SetVelLimits_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__srv__SetVelLimits_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__srv__SetVelLimits_Request__Sequence__copy(
  const rto_msgs__srv__SetVelLimits_Request__Sequence * input,
  rto_msgs__srv__SetVelLimits_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__srv__SetVelLimits_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__srv__SetVelLimits_Request * data =
      (rto_msgs__srv__SetVelLimits_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__srv__SetVelLimits_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__srv__SetVelLimits_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__srv__SetVelLimits_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
rto_msgs__srv__SetVelLimits_Response__init(rto_msgs__srv__SetVelLimits_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
rto_msgs__srv__SetVelLimits_Response__fini(rto_msgs__srv__SetVelLimits_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
rto_msgs__srv__SetVelLimits_Response__are_equal(const rto_msgs__srv__SetVelLimits_Response * lhs, const rto_msgs__srv__SetVelLimits_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
rto_msgs__srv__SetVelLimits_Response__copy(
  const rto_msgs__srv__SetVelLimits_Response * input,
  rto_msgs__srv__SetVelLimits_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

rto_msgs__srv__SetVelLimits_Response *
rto_msgs__srv__SetVelLimits_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Response * msg = (rto_msgs__srv__SetVelLimits_Response *)allocator.allocate(sizeof(rto_msgs__srv__SetVelLimits_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__srv__SetVelLimits_Response));
  bool success = rto_msgs__srv__SetVelLimits_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__srv__SetVelLimits_Response__destroy(rto_msgs__srv__SetVelLimits_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__srv__SetVelLimits_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__srv__SetVelLimits_Response__Sequence__init(rto_msgs__srv__SetVelLimits_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Response * data = NULL;

  if (size) {
    data = (rto_msgs__srv__SetVelLimits_Response *)allocator.zero_allocate(size, sizeof(rto_msgs__srv__SetVelLimits_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__srv__SetVelLimits_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__srv__SetVelLimits_Response__fini(&data[i - 1]);
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
rto_msgs__srv__SetVelLimits_Response__Sequence__fini(rto_msgs__srv__SetVelLimits_Response__Sequence * array)
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
      rto_msgs__srv__SetVelLimits_Response__fini(&array->data[i]);
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

rto_msgs__srv__SetVelLimits_Response__Sequence *
rto_msgs__srv__SetVelLimits_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Response__Sequence * array = (rto_msgs__srv__SetVelLimits_Response__Sequence *)allocator.allocate(sizeof(rto_msgs__srv__SetVelLimits_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__srv__SetVelLimits_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__srv__SetVelLimits_Response__Sequence__destroy(rto_msgs__srv__SetVelLimits_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__srv__SetVelLimits_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__srv__SetVelLimits_Response__Sequence__are_equal(const rto_msgs__srv__SetVelLimits_Response__Sequence * lhs, const rto_msgs__srv__SetVelLimits_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__srv__SetVelLimits_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__srv__SetVelLimits_Response__Sequence__copy(
  const rto_msgs__srv__SetVelLimits_Response__Sequence * input,
  rto_msgs__srv__SetVelLimits_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__srv__SetVelLimits_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__srv__SetVelLimits_Response * data =
      (rto_msgs__srv__SetVelLimits_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__srv__SetVelLimits_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__srv__SetVelLimits_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__srv__SetVelLimits_Response__copy(
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
// #include "rto_msgs/srv/detail/set_vel_limits__functions.h"

bool
rto_msgs__srv__SetVelLimits_Event__init(rto_msgs__srv__SetVelLimits_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    rto_msgs__srv__SetVelLimits_Event__fini(msg);
    return false;
  }
  // request
  if (!rto_msgs__srv__SetVelLimits_Request__Sequence__init(&msg->request, 0)) {
    rto_msgs__srv__SetVelLimits_Event__fini(msg);
    return false;
  }
  // response
  if (!rto_msgs__srv__SetVelLimits_Response__Sequence__init(&msg->response, 0)) {
    rto_msgs__srv__SetVelLimits_Event__fini(msg);
    return false;
  }
  return true;
}

void
rto_msgs__srv__SetVelLimits_Event__fini(rto_msgs__srv__SetVelLimits_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  rto_msgs__srv__SetVelLimits_Request__Sequence__fini(&msg->request);
  // response
  rto_msgs__srv__SetVelLimits_Response__Sequence__fini(&msg->response);
}

bool
rto_msgs__srv__SetVelLimits_Event__are_equal(const rto_msgs__srv__SetVelLimits_Event * lhs, const rto_msgs__srv__SetVelLimits_Event * rhs)
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
  if (!rto_msgs__srv__SetVelLimits_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!rto_msgs__srv__SetVelLimits_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
rto_msgs__srv__SetVelLimits_Event__copy(
  const rto_msgs__srv__SetVelLimits_Event * input,
  rto_msgs__srv__SetVelLimits_Event * output)
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
  if (!rto_msgs__srv__SetVelLimits_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!rto_msgs__srv__SetVelLimits_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

rto_msgs__srv__SetVelLimits_Event *
rto_msgs__srv__SetVelLimits_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Event * msg = (rto_msgs__srv__SetVelLimits_Event *)allocator.allocate(sizeof(rto_msgs__srv__SetVelLimits_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rto_msgs__srv__SetVelLimits_Event));
  bool success = rto_msgs__srv__SetVelLimits_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rto_msgs__srv__SetVelLimits_Event__destroy(rto_msgs__srv__SetVelLimits_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rto_msgs__srv__SetVelLimits_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rto_msgs__srv__SetVelLimits_Event__Sequence__init(rto_msgs__srv__SetVelLimits_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Event * data = NULL;

  if (size) {
    data = (rto_msgs__srv__SetVelLimits_Event *)allocator.zero_allocate(size, sizeof(rto_msgs__srv__SetVelLimits_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rto_msgs__srv__SetVelLimits_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rto_msgs__srv__SetVelLimits_Event__fini(&data[i - 1]);
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
rto_msgs__srv__SetVelLimits_Event__Sequence__fini(rto_msgs__srv__SetVelLimits_Event__Sequence * array)
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
      rto_msgs__srv__SetVelLimits_Event__fini(&array->data[i]);
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

rto_msgs__srv__SetVelLimits_Event__Sequence *
rto_msgs__srv__SetVelLimits_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rto_msgs__srv__SetVelLimits_Event__Sequence * array = (rto_msgs__srv__SetVelLimits_Event__Sequence *)allocator.allocate(sizeof(rto_msgs__srv__SetVelLimits_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rto_msgs__srv__SetVelLimits_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rto_msgs__srv__SetVelLimits_Event__Sequence__destroy(rto_msgs__srv__SetVelLimits_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rto_msgs__srv__SetVelLimits_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rto_msgs__srv__SetVelLimits_Event__Sequence__are_equal(const rto_msgs__srv__SetVelLimits_Event__Sequence * lhs, const rto_msgs__srv__SetVelLimits_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rto_msgs__srv__SetVelLimits_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rto_msgs__srv__SetVelLimits_Event__Sequence__copy(
  const rto_msgs__srv__SetVelLimits_Event__Sequence * input,
  rto_msgs__srv__SetVelLimits_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rto_msgs__srv__SetVelLimits_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rto_msgs__srv__SetVelLimits_Event * data =
      (rto_msgs__srv__SetVelLimits_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rto_msgs__srv__SetVelLimits_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rto_msgs__srv__SetVelLimits_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rto_msgs__srv__SetVelLimits_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
