# SPDX-License-Identifier: MIT

set(go_amd_smi_esmi_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/esmi_go_shim.h
  CACHE INTERNAL "")

set(go_amd_smi_esmi_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/esmi_go_shim.c
    CACHE INTERNAL "")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${go_amd_smi_esmi_includes})

add_library(go_amd_smi_esmi OBJECT
            ${go_amd_smi_esmi_sources}
            ${go_amd_smi_esmi_headers})

### Shared libraries need PIC
set_property(TARGET ${go_amd_smi_esmi} PROPERTY POSITION_INDEPENDENT_CODE 1)
