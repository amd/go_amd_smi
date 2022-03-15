# SPDX-License-Identifier: MIT

# First check for user-specified ESMI_DIR
if(ESMI_DIR)
    message(STATUS "Looking for esmi using ESMI_DIR = ${ESMI_DIR}")

    set(ESMI_FOUND TRUE CACHE INTERNAL "")
#    set(VARIORUM_ESMI_DIR ${ESMI_DIR} CACHE INTERNAL "")
    set(ESMI_DIR ${ESMI_DIR} CACHE PATH "" FORCE)
    set(ESMI_INCLUDE_DIRS ${ESMI_DIR}/include/e_smi CACHE PATH "" FORCE)
    set(ESMI_LIBRARY ${ESMI_DIR}/lib/libe_smi64.so CACHE PATH "" FORCE)
    include_directories(${ESMI_INCLUDE_DIRS})

    message(STATUS "FOUND esmi")
    message(STATUS " [*] ESMI_DIR = ${ESMI_DIR}")
    message(STATUS " [*] ESMI_INCLUDE_DIRS = ${ESMI_INCLUDE_DIRS}")
    message(STATUS " [*] ESMI_LIBRARY = ${ESMI_LIBRARY}")
# If ESMI_DIR not specified, then try to automatically find the ESMI header
# and library
elseif(NOT ESMI_FOUND)
    find_path(ESMI_INCLUDE_DIRS
        NAMES e_smi.h
    )

    find_library(ESMI_LIBRARY
        NAMES libe_smi64.so
    )

    if(ESMI_INCLUDE_DIRS AND ESMI_LIBRARY)
        set(ESMI_FOUND TRUE CACHE INTERNAL "")
        set(VARIORUM_ESMI_DIR ${ESMI_DIR} CACHE INTERNAL "")
        set(ESMI_DIR ${ESMI_DIR} CACHE PATH "" FORCE)
        set(ESMI_INCLUDE_DIRS ${ESMI_INCLUDE_DIRS} CACHE PATH "" FORCE)
        set(ESMI_LIBRARY ${ESMI_LIBRARY} CACHE PATH "" FORCE)
        include_directories(${ESMI_INCLUDE_DIRS})

        message(STATUS "FOUND rocm_smi using find_library()")
        message(STATUS " [*] ESMI_INCLUDE_DIRS = ${ESMI_INCLUDE_DIRS}")
        message(STATUS " [*] ESMI_LIBRARY = ${ESMI_LIBRARY}")
    endif()
endif()

# Abort if all methods fail
if(NOT ESMI_FOUND)
    message(FATAL_ERROR "E-SMI library support needs explict ESMI_DIR")
endif()
