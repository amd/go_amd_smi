# SPDX-License-Identifier: MIT

# First check for user-specified ROCM_SMI_DIR
if(ROCM_SMI_DIR)
    message(STATUS "Looking for Rocm_smi using ROCM_SMI_DIR = ${ROCM_SMI_DIR}")

    set(ROCM_SMI_FOUND TRUE CACHE INTERNAL "")
    set(VARIORUM_ROCM_SMI_DIR ${ROCM_SMI_DIR} CACHE INTERNAL "")
    set(ROCM_SMI_DIR ${ROCM_SMI_DIR} CACHE PATH "" FORCE)
    set(ROCM_SMI_INCLUDE_DIRS ${ROCM_SMI_DIR}/include CACHE PATH "" FORCE)
    set(ROCM_SMI_LIBRARY ${ROCM_SMI_DIR}/lib/librocm_smi64.so CACHE PATH "" FORCE)
    include_directories(${ROCM_SMI_INCLUDE_DIRS})

    message(STATUS "FOUND rocm_smi")
    message(STATUS " [*] ROCM_SMI_DIR = ${ROCM_SMI_DIR}")
    message(STATUS " [*] ROCM_SMI_INCLUDE_DIRS = ${ROCM_SMI_INCLUDE_DIRS}")
    message(STATUS " [*] ROCM_SMI_LIBRARY = ${ROCM_SMI_LIBRARY}")
# If ROCM_SMI_DIR not specified, then try to automatically find the ROCM_SMI header
# and library
elseif(NOT ROCM_SMI_FOUND)
    find_path(ROCM_SMI_INCLUDE_DIRS
        NAMES rocm_smi.h
    )

    find_library(ROCM_SMI_LIBRARY
        NAMES librocm_smi64.so
    )

    if(ROCM_SMI_INCLUDE_DIRS AND ROCM_SMI_LIBRARY)
        set(ROCM_SMI_FOUND TRUE CACHE INTERNAL "")
        set(VARIORUM_ROCM_SMI_DIR ${ROCM_SMI_DIR} CACHE INTERNAL "")
        set(ROCM_SMI_DIR ${ROCM_SMI_DIR} CACHE PATH "" FORCE)
        set(ROCM_SMI_INCLUDE_DIRS ${ROCM_SMI_INCLUDE_DIRS} CACHE PATH "" FORCE)
        set(ROCM_SMI_LIBRARY ${ROCM_SMI_LIBRARY} CACHE PATH "" FORCE)
        include_directories(${ROCM_SMI_INCLUDE_DIRS})

        message(STATUS "FOUND rocm_smi using find_library()")
        message(STATUS " [*] ROCM_SMI_INCLUDE_DIRS = ${ROCM_SMI_INCLUDE_DIRS}")
        message(STATUS " [*] ROCM_SMI_LIBRARY = ${ROCM_SMI_LIBRARY}")
    endif()
endif()

# Abort if all methods fail
if(NOT ROCM_SMI_FOUND)
    message(FATAL_ERROR "Rocm SMI library support needs explict ROCM_SMI_DIR")
endif()
