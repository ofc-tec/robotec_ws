// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from rto_msgs:srv/SetEncoderPosition.idl
// generated code does not contain a copyright notice

#include "rto_msgs/srv/detail/set_encoder_position__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__srv__SetEncoderPosition__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf6, 0xc4, 0x99, 0x75, 0x63, 0xa0, 0xa0, 0x68,
      0xf1, 0xd4, 0x39, 0x39, 0xee, 0x76, 0xd3, 0xba,
      0x0e, 0x01, 0xf1, 0x90, 0x14, 0xcf, 0x79, 0xa2,
      0xd6, 0x83, 0x1d, 0xe4, 0xb9, 0xff, 0xeb, 0x23,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__srv__SetEncoderPosition_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x19, 0x11, 0x29, 0xf2, 0xcc, 0xed, 0x33, 0x74,
      0x69, 0xdf, 0xda, 0x7e, 0x8d, 0x5e, 0x1c, 0xf3,
      0xfd, 0x28, 0x63, 0x58, 0xe6, 0xec, 0x08, 0x36,
      0x8c, 0x30, 0x82, 0x76, 0x1e, 0xb4, 0xca, 0xce,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__srv__SetEncoderPosition_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x98, 0xc2, 0x35, 0x59, 0xee, 0x17, 0x9e, 0x66,
      0x9b, 0x1e, 0xad, 0xef, 0x99, 0xba, 0x52, 0xcc,
      0xca, 0xb2, 0x4d, 0x28, 0xb5, 0x0d, 0xf6, 0xf3,
      0xb2, 0xce, 0x49, 0x12, 0xc1, 0x1c, 0xab, 0x1b,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__srv__SetEncoderPosition_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x66, 0x45, 0x08, 0x3b, 0x70, 0x16, 0x4f, 0xba,
      0x12, 0x7e, 0xeb, 0xc5, 0xf0, 0x9f, 0x3d, 0x77,
      0xd6, 0x9a, 0xce, 0xac, 0x34, 0x06, 0xad, 0xa3,
      0xf9, 0xa7, 0xbd, 0x44, 0xee, 0x57, 0x0a, 0x4b,
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

static char rto_msgs__srv__SetEncoderPosition__TYPE_NAME[] = "rto_msgs/srv/SetEncoderPosition";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char rto_msgs__srv__SetEncoderPosition_Event__TYPE_NAME[] = "rto_msgs/srv/SetEncoderPosition_Event";
static char rto_msgs__srv__SetEncoderPosition_Request__TYPE_NAME[] = "rto_msgs/srv/SetEncoderPosition_Request";
static char rto_msgs__srv__SetEncoderPosition_Response__TYPE_NAME[] = "rto_msgs/srv/SetEncoderPosition_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char rto_msgs__srv__SetEncoderPosition__FIELD_NAME__request_message[] = "request_message";
static char rto_msgs__srv__SetEncoderPosition__FIELD_NAME__response_message[] = "response_message";
static char rto_msgs__srv__SetEncoderPosition__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field rto_msgs__srv__SetEncoderPosition__FIELDS[] = {
  {
    {rto_msgs__srv__SetEncoderPosition__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rto_msgs__srv__SetEncoderPosition_Request__TYPE_NAME, 39, 39},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rto_msgs__srv__SetEncoderPosition_Response__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {rto_msgs__srv__SetEncoderPosition_Event__TYPE_NAME, 37, 37},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rto_msgs__srv__SetEncoderPosition__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition_Event__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition_Request__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition_Response__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rto_msgs__srv__SetEncoderPosition__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__srv__SetEncoderPosition__TYPE_NAME, 31, 31},
      {rto_msgs__srv__SetEncoderPosition__FIELDS, 3, 3},
    },
    {rto_msgs__srv__SetEncoderPosition__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = rto_msgs__srv__SetEncoderPosition_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = rto_msgs__srv__SetEncoderPosition_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = rto_msgs__srv__SetEncoderPosition_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rto_msgs__srv__SetEncoderPosition_Request__FIELD_NAME__position[] = "position";
static char rto_msgs__srv__SetEncoderPosition_Request__FIELD_NAME__velocity[] = "velocity";

static rosidl_runtime_c__type_description__Field rto_msgs__srv__SetEncoderPosition_Request__FIELDS[] = {
  {
    {rto_msgs__srv__SetEncoderPosition_Request__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition_Request__FIELD_NAME__velocity, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rto_msgs__srv__SetEncoderPosition_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__srv__SetEncoderPosition_Request__TYPE_NAME, 39, 39},
      {rto_msgs__srv__SetEncoderPosition_Request__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rto_msgs__srv__SetEncoderPosition_Response__FIELD_NAME__structure_needs_at_least_one_member[] = "structure_needs_at_least_one_member";

static rosidl_runtime_c__type_description__Field rto_msgs__srv__SetEncoderPosition_Response__FIELDS[] = {
  {
    {rto_msgs__srv__SetEncoderPosition_Response__FIELD_NAME__structure_needs_at_least_one_member, 35, 35},
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
rto_msgs__srv__SetEncoderPosition_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__srv__SetEncoderPosition_Response__TYPE_NAME, 40, 40},
      {rto_msgs__srv__SetEncoderPosition_Response__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char rto_msgs__srv__SetEncoderPosition_Event__FIELD_NAME__info[] = "info";
static char rto_msgs__srv__SetEncoderPosition_Event__FIELD_NAME__request[] = "request";
static char rto_msgs__srv__SetEncoderPosition_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field rto_msgs__srv__SetEncoderPosition_Event__FIELDS[] = {
  {
    {rto_msgs__srv__SetEncoderPosition_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {rto_msgs__srv__SetEncoderPosition_Request__TYPE_NAME, 39, 39},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {rto_msgs__srv__SetEncoderPosition_Response__TYPE_NAME, 40, 40},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rto_msgs__srv__SetEncoderPosition_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition_Request__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {rto_msgs__srv__SetEncoderPosition_Response__TYPE_NAME, 40, 40},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rto_msgs__srv__SetEncoderPosition_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__srv__SetEncoderPosition_Event__TYPE_NAME, 37, 37},
      {rto_msgs__srv__SetEncoderPosition_Event__FIELDS, 3, 3},
    },
    {rto_msgs__srv__SetEncoderPosition_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = rto_msgs__srv__SetEncoderPosition_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = rto_msgs__srv__SetEncoderPosition_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint32 position\\t\\t# in encoder ticks\n"
  "uint32 velocity\\t\\t# in ticks/s\n"
  "---";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__srv__SetEncoderPosition__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__srv__SetEncoderPosition__TYPE_NAME, 31, 31},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 69, 69},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__srv__SetEncoderPosition_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__srv__SetEncoderPosition_Request__TYPE_NAME, 39, 39},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__srv__SetEncoderPosition_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__srv__SetEncoderPosition_Response__TYPE_NAME, 40, 40},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__srv__SetEncoderPosition_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__srv__SetEncoderPosition_Event__TYPE_NAME, 37, 37},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__srv__SetEncoderPosition__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__srv__SetEncoderPosition__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rto_msgs__srv__SetEncoderPosition_Event__get_individual_type_description_source(NULL);
    sources[3] = *rto_msgs__srv__SetEncoderPosition_Request__get_individual_type_description_source(NULL);
    sources[4] = *rto_msgs__srv__SetEncoderPosition_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__srv__SetEncoderPosition_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__srv__SetEncoderPosition_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__srv__SetEncoderPosition_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__srv__SetEncoderPosition_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__srv__SetEncoderPosition_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__srv__SetEncoderPosition_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rto_msgs__srv__SetEncoderPosition_Request__get_individual_type_description_source(NULL);
    sources[3] = *rto_msgs__srv__SetEncoderPosition_Response__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
