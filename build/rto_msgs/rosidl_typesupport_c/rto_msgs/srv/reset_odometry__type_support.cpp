// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from rto_msgs:srv/ResetOdometry.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rto_msgs/srv/detail/reset_odometry__struct.h"
#include "rto_msgs/srv/detail/reset_odometry__type_support.h"
#include "rto_msgs/srv/detail/reset_odometry__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace rto_msgs
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _ResetOdometry_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ResetOdometry_Request_type_support_ids_t;

static const _ResetOdometry_Request_type_support_ids_t _ResetOdometry_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ResetOdometry_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ResetOdometry_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ResetOdometry_Request_type_support_symbol_names_t _ResetOdometry_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rto_msgs, srv, ResetOdometry_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rto_msgs, srv, ResetOdometry_Request)),
  }
};

typedef struct _ResetOdometry_Request_type_support_data_t
{
  void * data[2];
} _ResetOdometry_Request_type_support_data_t;

static _ResetOdometry_Request_type_support_data_t _ResetOdometry_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ResetOdometry_Request_message_typesupport_map = {
  2,
  "rto_msgs",
  &_ResetOdometry_Request_message_typesupport_ids.typesupport_identifier[0],
  &_ResetOdometry_Request_message_typesupport_symbol_names.symbol_name[0],
  &_ResetOdometry_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ResetOdometry_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ResetOdometry_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &rto_msgs__srv__ResetOdometry_Request__get_type_hash,
  &rto_msgs__srv__ResetOdometry_Request__get_type_description,
  &rto_msgs__srv__ResetOdometry_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace rto_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, rto_msgs, srv, ResetOdometry_Request)() {
  return &::rto_msgs::srv::rosidl_typesupport_c::ResetOdometry_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rto_msgs/srv/detail/reset_odometry__struct.h"
// already included above
// #include "rto_msgs/srv/detail/reset_odometry__type_support.h"
// already included above
// #include "rto_msgs/srv/detail/reset_odometry__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace rto_msgs
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _ResetOdometry_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ResetOdometry_Response_type_support_ids_t;

static const _ResetOdometry_Response_type_support_ids_t _ResetOdometry_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ResetOdometry_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ResetOdometry_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ResetOdometry_Response_type_support_symbol_names_t _ResetOdometry_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rto_msgs, srv, ResetOdometry_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rto_msgs, srv, ResetOdometry_Response)),
  }
};

typedef struct _ResetOdometry_Response_type_support_data_t
{
  void * data[2];
} _ResetOdometry_Response_type_support_data_t;

static _ResetOdometry_Response_type_support_data_t _ResetOdometry_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ResetOdometry_Response_message_typesupport_map = {
  2,
  "rto_msgs",
  &_ResetOdometry_Response_message_typesupport_ids.typesupport_identifier[0],
  &_ResetOdometry_Response_message_typesupport_symbol_names.symbol_name[0],
  &_ResetOdometry_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ResetOdometry_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ResetOdometry_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &rto_msgs__srv__ResetOdometry_Response__get_type_hash,
  &rto_msgs__srv__ResetOdometry_Response__get_type_description,
  &rto_msgs__srv__ResetOdometry_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace rto_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, rto_msgs, srv, ResetOdometry_Response)() {
  return &::rto_msgs::srv::rosidl_typesupport_c::ResetOdometry_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rto_msgs/srv/detail/reset_odometry__struct.h"
// already included above
// #include "rto_msgs/srv/detail/reset_odometry__type_support.h"
// already included above
// #include "rto_msgs/srv/detail/reset_odometry__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace rto_msgs
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _ResetOdometry_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ResetOdometry_Event_type_support_ids_t;

static const _ResetOdometry_Event_type_support_ids_t _ResetOdometry_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ResetOdometry_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ResetOdometry_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ResetOdometry_Event_type_support_symbol_names_t _ResetOdometry_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rto_msgs, srv, ResetOdometry_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rto_msgs, srv, ResetOdometry_Event)),
  }
};

typedef struct _ResetOdometry_Event_type_support_data_t
{
  void * data[2];
} _ResetOdometry_Event_type_support_data_t;

static _ResetOdometry_Event_type_support_data_t _ResetOdometry_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ResetOdometry_Event_message_typesupport_map = {
  2,
  "rto_msgs",
  &_ResetOdometry_Event_message_typesupport_ids.typesupport_identifier[0],
  &_ResetOdometry_Event_message_typesupport_symbol_names.symbol_name[0],
  &_ResetOdometry_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t ResetOdometry_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ResetOdometry_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &rto_msgs__srv__ResetOdometry_Event__get_type_hash,
  &rto_msgs__srv__ResetOdometry_Event__get_type_description,
  &rto_msgs__srv__ResetOdometry_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace rto_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, rto_msgs, srv, ResetOdometry_Event)() {
  return &::rto_msgs::srv::rosidl_typesupport_c::ResetOdometry_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rto_msgs/srv/detail/reset_odometry__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace rto_msgs
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _ResetOdometry_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _ResetOdometry_type_support_ids_t;

static const _ResetOdometry_type_support_ids_t _ResetOdometry_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _ResetOdometry_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _ResetOdometry_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _ResetOdometry_type_support_symbol_names_t _ResetOdometry_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, rto_msgs, srv, ResetOdometry)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, rto_msgs, srv, ResetOdometry)),
  }
};

typedef struct _ResetOdometry_type_support_data_t
{
  void * data[2];
} _ResetOdometry_type_support_data_t;

static _ResetOdometry_type_support_data_t _ResetOdometry_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _ResetOdometry_service_typesupport_map = {
  2,
  "rto_msgs",
  &_ResetOdometry_service_typesupport_ids.typesupport_identifier[0],
  &_ResetOdometry_service_typesupport_symbol_names.symbol_name[0],
  &_ResetOdometry_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t ResetOdometry_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_ResetOdometry_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &ResetOdometry_Request_message_type_support_handle,
  &ResetOdometry_Response_message_type_support_handle,
  &ResetOdometry_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    rto_msgs,
    srv,
    ResetOdometry
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    rto_msgs,
    srv,
    ResetOdometry
  ),
  &rto_msgs__srv__ResetOdometry__get_type_hash,
  &rto_msgs__srv__ResetOdometry__get_type_description,
  &rto_msgs__srv__ResetOdometry__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace rto_msgs

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, rto_msgs, srv, ResetOdometry)() {
  return &::rto_msgs::srv::rosidl_typesupport_c::ResetOdometry_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
