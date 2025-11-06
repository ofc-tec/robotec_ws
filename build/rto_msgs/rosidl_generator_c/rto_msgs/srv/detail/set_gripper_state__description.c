// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from rto_msgs:srv/SetGripperState.idl
// generated code does not contain a copyright notice

#include "rto_msgs/srv/detail/set_gripper_state__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__srv__SetGripperState__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x22, 0xd3, 0x4f, 0x7f, 0xf9, 0x52, 0x4c, 0x20,
      0xf3, 0x9f, 0xb7, 0x68, 0x5c, 0x1a, 0xfd, 0x76,
      0xb1, 0xd2, 0xcd, 0xd5, 0x2e, 0x47, 0x82, 0xab,
      0x1d, 0x18, 0xde, 0xb5, 0x20, 0x0f, 0xd2, 0x01,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__srv__SetGripperState_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xde, 0x7b, 0xca, 0xe0, 0x0f, 0x7f, 0xd7, 0x5a,
      0xbe, 0x0f, 0x65, 0x43, 0x78, 0x7f, 0xf1, 0xdf,
      0x61, 0x09, 0xcc, 0x23, 0xb1, 0x78, 0xd9, 0xfe,
      0x5a, 0xb6, 0x4a, 0xa1, 0x21, 0xf5, 0x2b, 0xcf,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__srv__SetGripperState_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xdf, 0x6a, 0x88, 0x76, 0x21, 0x82, 0x19, 0x83,
      0x19, 0x8a, 0xbf, 0x13, 0xc4, 0xee, 0xba, 0x22,
      0x00, 0x03, 0x4a, 0xb7, 0xf3, 0x01, 0x80, 0x4b,
      0x74, 0x47, 0x84, 0xce, 0xce, 0x91, 0x06, 0xbb,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__srv__SetGripperState_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xae, 0xfe, 0xe5, 0xf8, 0x41, 0xbc, 0x9f, 0x8d,
      0x52, 0xc8, 0x07, 0x0a, 0xcb, 0xdd, 0x06, 0x43,
      0xe6, 0x72, 0xec, 0xe2, 0xd0, 0x3f, 0x9f, 0x8d,
      0x89, 0xd5, 0x74, 0xe2, 0x04, 0x63, 0x1c, 0x76,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char rto_msgs__srv__SetGripperState__TYPE_NAME[] = "rto_msgs/srv/SetGripperState";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char rto_msgs__srv__SetGripperState_Event__TYPE_NAME[] = "rto_msgs/srv/SetGripperState_Event";
static char rto_msgs__srv__SetGripperState_Request__TYPE_NAME[] = "rto_msgs/srv/SetGripperState_Request";
static char rto_msgs__srv__SetGripperState_Response__TYPE_NAME[] = "rto_msgs/srv/SetGripperState_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char rto_msgs__srv__SetGripperState__FIELD_NAME__request_message[] = "request_message";
static char rto_msgs__srv__SetGripperState__FIELD_NAME__response_message[] = "response_message";
static char rto_msgs__srv__SetGripperState__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field rto_msgs__srv__SetGripperState__FIELDS[] = {
  {
    {rto_msgs__srv__SetGripperState__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rto_msgs__srv__SetGripperState_Request__TYPE_NAME, 36, 36},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rto_msgs__srv__SetGripperState_Response__TYPE_NAME, 37, 37},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rto_msgs__srv__SetGripperState_Event__TYPE_NAME, 34, 34},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rto_msgs__srv__SetGripperState__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState_Event__TYPE_NAME, 34, 34},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState_Request__TYPE_NAME, 36, 36},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState_Response__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rto_msgs__srv__SetGripperState__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__srv__SetGripperState__TYPE_NAME, 28, 28},
      {rto_msgs__srv__SetGripperState__FIELDS, 3, 3},
    },
    {rto_msgs__srv__SetGripperState__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = rto_msgs__srv__SetGripperState_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = rto_msgs__srv__SetGripperState_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = rto_msgs__srv__SetGripperState_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rto_msgs__srv__SetGripperState_Request__FIELD_NAME__state[] = "state";

static rosidl_runtime_c__type_description__Field rto_msgs__srv__SetGripperState_Request__FIELDS[] = {
  {
    {rto_msgs__srv__SetGripperState_Request__FIELD_NAME__state, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rto_msgs__srv__SetGripperState_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__srv__SetGripperState_Request__TYPE_NAME, 36, 36},
      {rto_msgs__srv__SetGripperState_Request__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rto_msgs__srv__SetGripperState_Response__FIELD_NAME__structure_needs_at_least_one_member[] = "structure_needs_at_least_one_member";

static rosidl_runtime_c__type_description__Field rto_msgs__srv__SetGripperState_Response__FIELDS[] = {
  {
    {rto_msgs__srv__SetGripperState_Response__FIELD_NAME__structure_needs_at_least_one_member, 35, 35},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rto_msgs__srv__SetGripperState_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__srv__SetGripperState_Response__TYPE_NAME, 37, 37},
      {rto_msgs__srv__SetGripperState_Response__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rto_msgs__srv__SetGripperState_Event__FIELD_NAME__info[] = "info";
static char rto_msgs__srv__SetGripperState_Event__FIELD_NAME__request[] = "request";
static char rto_msgs__srv__SetGripperState_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field rto_msgs__srv__SetGripperState_Event__FIELDS[] = {
  {
    {rto_msgs__srv__SetGripperState_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {rto_msgs__srv__SetGripperState_Request__TYPE_NAME, 36, 36},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {rto_msgs__srv__SetGripperState_Response__TYPE_NAME, 37, 37},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rto_msgs__srv__SetGripperState_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState_Request__TYPE_NAME, 36, 36},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetGripperState_Response__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rto_msgs__srv__SetGripperState_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__srv__SetGripperState_Event__TYPE_NAME, 34, 34},
      {rto_msgs__srv__SetGripperState_Event__FIELDS, 3, 3},
    },
    {rto_msgs__srv__SetGripperState_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = rto_msgs__srv__SetGripperState_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = rto_msgs__srv__SetGripperState_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool state \\t# set true to open else false to close\n"
  "---";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__srv__SetGripperState__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__srv__SetGripperState__TYPE_NAME, 28, 28},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 54, 54},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__srv__SetGripperState_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__srv__SetGripperState_Request__TYPE_NAME, 36, 36},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__srv__SetGripperState_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__srv__SetGripperState_Response__TYPE_NAME, 37, 37},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__srv__SetGripperState_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__srv__SetGripperState_Event__TYPE_NAME, 34, 34},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__srv__SetGripperState__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__srv__SetGripperState__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rto_msgs__srv__SetGripperState_Event__get_individual_type_description_source(NULL);
    sources[3] = *rto_msgs__srv__SetGripperState_Request__get_individual_type_description_source(NULL);
    sources[4] = *rto_msgs__srv__SetGripperState_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__srv__SetGripperState_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__srv__SetGripperState_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__srv__SetGripperState_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__srv__SetGripperState_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__srv__SetGripperState_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__srv__SetGripperState_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rto_msgs__srv__SetGripperState_Request__get_individual_type_description_source(NULL);
    sources[3] = *rto_msgs__srv__SetGripperState_Response__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
