// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from rto_msgs:srv/SetOmniDriveEnabled.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rto_msgs/srv/detail/set_omni_drive_enabled__functions.h"
#include "rto_msgs/srv/detail/set_omni_drive_enabled__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace rto_msgs
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SetOmniDriveEnabled_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetOmniDriveEnabled_Request_type_support_ids_t;

static const _SetOmniDriveEnabled_Request_type_support_ids_t _SetOmniDriveEnabled_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SetOmniDriveEnabled_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetOmniDriveEnabled_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetOmniDriveEnabled_Request_type_support_symbol_names_t _SetOmniDriveEnabled_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, rto_msgs, srv, SetOmniDriveEnabled_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rto_msgs, srv, SetOmniDriveEnabled_Request)),
  }
};

typedef struct _SetOmniDriveEnabled_Request_type_support_data_t
{
  void * data[2];
} _SetOmniDriveEnabled_Request_type_support_data_t;

static _SetOmniDriveEnabled_Request_type_support_data_t _SetOmniDriveEnabled_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetOmniDriveEnabled_Request_message_typesupport_map = {
  2,
  "rto_msgs",
  &_SetOmniDriveEnabled_Request_message_typesupport_ids.typesupport_identifier[0],
  &_SetOmniDriveEnabled_Request_message_typesupport_symbol_names.symbol_name[0],
  &_SetOmniDriveEnabled_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetOmniDriveEnabled_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetOmniDriveEnabled_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &rto_msgs__srv__SetOmniDriveEnabled_Request__get_type_hash,
  &rto_msgs__srv__SetOmniDriveEnabled_Request__get_type_description,
  &rto_msgs__srv__SetOmniDriveEnabled_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace rto_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Request>()
{
  return &::rto_msgs::srv::rosidl_typesupport_cpp::SetOmniDriveEnabled_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, rto_msgs, srv, SetOmniDriveEnabled_Request)() {
  return get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rto_msgs/srv/detail/set_omni_drive_enabled__functions.h"
// already included above
// #include "rto_msgs/srv/detail/set_omni_drive_enabled__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace rto_msgs
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SetOmniDriveEnabled_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetOmniDriveEnabled_Response_type_support_ids_t;

static const _SetOmniDriveEnabled_Response_type_support_ids_t _SetOmniDriveEnabled_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SetOmniDriveEnabled_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetOmniDriveEnabled_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetOmniDriveEnabled_Response_type_support_symbol_names_t _SetOmniDriveEnabled_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, rto_msgs, srv, SetOmniDriveEnabled_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rto_msgs, srv, SetOmniDriveEnabled_Response)),
  }
};

typedef struct _SetOmniDriveEnabled_Response_type_support_data_t
{
  void * data[2];
} _SetOmniDriveEnabled_Response_type_support_data_t;

static _SetOmniDriveEnabled_Response_type_support_data_t _SetOmniDriveEnabled_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetOmniDriveEnabled_Response_message_typesupport_map = {
  2,
  "rto_msgs",
  &_SetOmniDriveEnabled_Response_message_typesupport_ids.typesupport_identifier[0],
  &_SetOmniDriveEnabled_Response_message_typesupport_symbol_names.symbol_name[0],
  &_SetOmniDriveEnabled_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetOmniDriveEnabled_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetOmniDriveEnabled_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &rto_msgs__srv__SetOmniDriveEnabled_Response__get_type_hash,
  &rto_msgs__srv__SetOmniDriveEnabled_Response__get_type_description,
  &rto_msgs__srv__SetOmniDriveEnabled_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace rto_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Response>()
{
  return &::rto_msgs::srv::rosidl_typesupport_cpp::SetOmniDriveEnabled_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, rto_msgs, srv, SetOmniDriveEnabled_Response)() {
  return get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rto_msgs/srv/detail/set_omni_drive_enabled__functions.h"
// already included above
// #include "rto_msgs/srv/detail/set_omni_drive_enabled__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace rto_msgs
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SetOmniDriveEnabled_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetOmniDriveEnabled_Event_type_support_ids_t;

static const _SetOmniDriveEnabled_Event_type_support_ids_t _SetOmniDriveEnabled_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SetOmniDriveEnabled_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetOmniDriveEnabled_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetOmniDriveEnabled_Event_type_support_symbol_names_t _SetOmniDriveEnabled_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, rto_msgs, srv, SetOmniDriveEnabled_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rto_msgs, srv, SetOmniDriveEnabled_Event)),
  }
};

typedef struct _SetOmniDriveEnabled_Event_type_support_data_t
{
  void * data[2];
} _SetOmniDriveEnabled_Event_type_support_data_t;

static _SetOmniDriveEnabled_Event_type_support_data_t _SetOmniDriveEnabled_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetOmniDriveEnabled_Event_message_typesupport_map = {
  2,
  "rto_msgs",
  &_SetOmniDriveEnabled_Event_message_typesupport_ids.typesupport_identifier[0],
  &_SetOmniDriveEnabled_Event_message_typesupport_symbol_names.symbol_name[0],
  &_SetOmniDriveEnabled_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t SetOmniDriveEnabled_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetOmniDriveEnabled_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &rto_msgs__srv__SetOmniDriveEnabled_Event__get_type_hash,
  &rto_msgs__srv__SetOmniDriveEnabled_Event__get_type_description,
  &rto_msgs__srv__SetOmniDriveEnabled_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace rto_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Event>()
{
  return &::rto_msgs::srv::rosidl_typesupport_cpp::SetOmniDriveEnabled_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, rto_msgs, srv, SetOmniDriveEnabled_Event)() {
  return get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rto_msgs/srv/detail/set_omni_drive_enabled__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace rto_msgs
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _SetOmniDriveEnabled_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _SetOmniDriveEnabled_type_support_ids_t;

static const _SetOmniDriveEnabled_type_support_ids_t _SetOmniDriveEnabled_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _SetOmniDriveEnabled_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _SetOmniDriveEnabled_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _SetOmniDriveEnabled_type_support_symbol_names_t _SetOmniDriveEnabled_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, rto_msgs, srv, SetOmniDriveEnabled)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, rto_msgs, srv, SetOmniDriveEnabled)),
  }
};

typedef struct _SetOmniDriveEnabled_type_support_data_t
{
  void * data[2];
} _SetOmniDriveEnabled_type_support_data_t;

static _SetOmniDriveEnabled_type_support_data_t _SetOmniDriveEnabled_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _SetOmniDriveEnabled_service_typesupport_map = {
  2,
  "rto_msgs",
  &_SetOmniDriveEnabled_service_typesupport_ids.typesupport_identifier[0],
  &_SetOmniDriveEnabled_service_typesupport_symbol_names.symbol_name[0],
  &_SetOmniDriveEnabled_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t SetOmniDriveEnabled_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_SetOmniDriveEnabled_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<rto_msgs::srv::SetOmniDriveEnabled>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<rto_msgs::srv::SetOmniDriveEnabled>,
  &rto_msgs__srv__SetOmniDriveEnabled__get_type_hash,
  &rto_msgs__srv__SetOmniDriveEnabled__get_type_description,
  &rto_msgs__srv__SetOmniDriveEnabled__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace rto_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled>()
{
  return &::rto_msgs::srv::rosidl_typesupport_cpp::SetOmniDriveEnabled_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, rto_msgs, srv, SetOmniDriveEnabled)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<rto_msgs::srv::SetOmniDriveEnabled>();
}

#ifdef __cplusplus
}
#endif
