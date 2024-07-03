# SPDX-License-Identifier: MIT

set(ROCM_SMI_DIR "/opt/rocm")
# First check for user-specified ROCM_SMI_DIR
if(ROCM_SMI_DIR)
    message(STATUS "Looking for Rocm_smi using ROCM_SMI_DIR = ${ROCM_SMI_DIR}")

    set(ROCM_SMI_FOUND TRUE CACHE INTERNAL "")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    set(ROCM_SMI_DIR ${ROCM_SMI_DIR} CACHE PATH "" FORCE)
    set(ROCM_SMI_INCLUDE_DIRS ${ROCM_SMI_DIR}/include CACHE PATH "" FORCE)
    set(ROCM_SMI_LIBRARY ${ROCM_SMI_DIR}/lib CACHE PATH "" FORCE)
    include_directories(${ROCM_SMI_INCLUDE_DIRS})

    message(STATUS "FOUND rocm_smi")
    message(STATUS " [*] ROCM_SMI_DIR = ${ROCM_SMI_DIR}")
    message(STATUS " [*] ROCM_SMI_INCLUDE_DIRS = ${ROCM_SMI_INCLUDE_DIRS}")
    message(STATUS " [*] ROCM_SMI_LIBRARY = ${ROCM_SMI_LIBRARY}")
endif()

# Abort if all methods fail
if(NOT ROCM_SMI_FOUND)
    message(FATAL_ERROR "Rocm SMI library support needs explict ROCM_SMI_DIR")
endif()
