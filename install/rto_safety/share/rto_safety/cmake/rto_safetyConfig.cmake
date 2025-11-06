# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_rto_safety_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED rto_safety_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(rto_safety_FOUND FALSE)
  elseif(NOT rto_safety_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(rto_safety_FOUND FALSE)
  endif()
  return()
endif()
set(_rto_safety_CONFIG_INCLUDED TRUE)

# output package information
if(NOT rto_safety_FIND_QUIETLY)
  message(STATUS "Found rto_safety: 0.0.0 (${rto_safety_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'rto_safety' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT rto_safety_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(rto_safety_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${rto_safety_DIR}/${_extra}")
endforeach()
