// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from rto_msgs:msg/PowerReadings.idl
// generated code does not contain a copyright notice

#include "rto_msgs/msg/detail/power_readings__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_rto_msgs
const rosidl_type_hash_t *
rto_msgs__msg__PowerReadings__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6f, 0xab, 0x5c, 0x05, 0x3b, 0xa5, 0x9f, 0x17,
      0x81, 0x2a, 0x6d, 0x9e, 0x9c, 0x16, 0xaa, 0xd9,
      0xb7, 0xe7, 0x78, 0x24, 0xe1, 0x81, 0x70, 0x09,
      0x84, 0x40, 0x4d, 0x39, 0xdf, 0x5c, 0x5d, 0x35,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "std_msgs/msg/detail/header__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char rto_msgs__msg__PowerReadings__TYPE_NAME[] = "rto_msgs/msg/PowerReadings";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char rto_msgs__msg__PowerReadings__FIELD_NAME__header[] = "header";
static char rto_msgs__msg__PowerReadings__FIELD_NAME__current[] = "current";
static char rto_msgs__msg__PowerReadings__FIELD_NAME__voltage[] = "voltage";
static char rto_msgs__msg__PowerReadings__FIELD_NAME__battery_low[] = "battery_low";

static rosidl_runtime_c__type_description__Field rto_msgs__msg__PowerReadings__FIELDS[] = {
  {
    {rto_msgs__msg__PowerReadings__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__msg__PowerReadings__FIELD_NAME__current, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__msg__PowerReadings__FIELD_NAME__voltage, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {rto_msgs__msg__PowerReadings__FIELD_NAME__battery_low, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription rto_msgs__msg__PowerReadings__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
rto_msgs__msg__PowerReadings__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {rto_msgs__msg__PowerReadings__TYPE_NAME, 26, 26},
      {rto_msgs__msg__PowerReadings__FIELDS, 4, 4},
    },
    {rto_msgs__msg__PowerReadings__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "std_msgs/Header header\\t# time-stamp\n"
  "float32 current\\t        # current in A\n"
  "float32 voltage\\t        # voltage in V\n"
  "bool battery_low        # bool for low battery";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
rto_msgs__msg__PowerReadings__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {rto_msgs__msg__PowerReadings__TYPE_NAME, 26, 26},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 160, 160},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
rto_msgs__msg__PowerReadings__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *rto_msgs__msg__PowerReadings__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
