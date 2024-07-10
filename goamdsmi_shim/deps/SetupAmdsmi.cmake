# SPDX-License-Identifier: MIT
set(AMDSMI_DIR "/opt/rocm")

# First check for user-specified AMDSMI_DIR
if(AMDSMI_DIR)
    message(STATUS "Looking for Amd_smi using AMDSMI_DIR = ${AMDSMI_DIR}")

    set(AMDSMI_FOUND TRUE CACHE INTERNAL "")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    set(AMDSMI_DIR ${AMDSMI_DIR} CACHE PATH "" FORCE)
    set(AMDSMI_INCLUDE_DIRS ${AMDSMI_DIR}/include CACHE PATH "" FORCE)
    set(AMDSMI_LIBRARY ${AMDSMI_DIR}/lib CACHE PATH "" FORCE)
	set(AMDSMI_LIBRARY ${AMDSMI_DIR}/lib64 CACHE PATH "" FORCE)
    include_directories(${AMDSMI_INCLUDE_DIRS})

    message(STATUS "FOUND amdsmi")
    message(STATUS " [*] AMDSMI_DIR = ${AMDSMI_DIR}")
    message(STATUS " [*] AMDSMI_INCLUDE_DIRS = ${AMDSMI_INCLUDE_DIRS}")
    message(STATUS " [*] AMDSMI_LIBRARY = ${AMDSMI_LIBRARY}")
endif()

# Abort if all methods fail
if(NOT AMDSMI_FOUND)
    message(FATAL_ERROR "AMD SMI library support needs explict AMDSMI_DIR")
endif()

