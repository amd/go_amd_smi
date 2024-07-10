# SPDX-License-Identifier: MIT

set(goamdsmi_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/goamdsmi.h
  ${CMAKE_CURRENT_SOURCE_DIR}/goamdsmi_shim.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../amdsmi/amdsmi_go_shim.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../esmi/esmi_go_shim.h
  ${CMAKE_CURRENT_SOURCE_DIR}/../rsmi/rocm_smi_go_shim.h
  CACHE INTERNAL "")

set(goamdsmi_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/goamdsmi_shim.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../amdsmi/amdsmi_go_shim.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../esmi/esmi_go_shim.c
  ${CMAKE_CURRENT_SOURCE_DIR}/../rsmi/rocm_smi_go_shim.c
    CACHE INTERNAL "")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${goamdsmi_includes})

add_library(goamdsmi_ OBJECT
            ${goamdsmi_sources}
            ${goamdsmi_headers})

### Shared libraries need PIC
set_property(TARGET ${goamdsmi_} PROPERTY POSITION_INDEPENDENT_CODE 1)

