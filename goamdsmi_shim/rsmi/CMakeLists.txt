# SPDX-License-Identifier: MIT

set(go_amd_smi_rocm_smi_headers
  ${CMAKE_CURRENT_SOURCE_DIR}/rocm_smi_go_shim.h
  CACHE INTERNAL "")

set(go_amd_smi_rocm_smi_sources
  ${CMAKE_CURRENT_SOURCE_DIR}/rocm_smi_go_shim.c
    CACHE INTERNAL "")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${go_amd_smi_rocm_smi_includes})

add_library(go_amd_smi_rocm_smi OBJECT
            ${go_amd_smi_rocm_smi_sources}
            ${go_amd_smi_rocm_smi_headers})

### Shared libraries need PIC
set_property(TARGET ${go_amd_smi_rocm_smi} PROPERTY POSITION_INDEPENDENT_CODE 1)
