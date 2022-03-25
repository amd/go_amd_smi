# SPDX-License-Identifier: MIT

# First check for user-specified ESMI_DIR
if(ESMI_DIR)
    message(STATUS "Looking for esmi using ESMI_DIR = ${ESMI_DIR}")

    set(ESMI_FOUND TRUE CACHE INTERNAL "")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    set(ESMI_DIR ${ESMI_DIR} CACHE PATH "" FORCE)
    set(ESMI_INCLUDE_DIRS ${ESMI_DIR}/include/e_smi CACHE PATH "" FORCE)
    set(ESMI_LIBRARY ${ESMI_DIR}/lib CACHE PATH "" FORCE)
    include_directories(${ESMI_INCLUDE_DIRS})

    message(STATUS "FOUND esmi")
    message(STATUS " [*] ESMI_DIR = ${ESMI_DIR}")
    message(STATUS " [*] ESMI_INCLUDE_DIRS = ${ESMI_INCLUDE_DIRS}")
    message(STATUS " [*] ESMI_LIBRARY = ${ESMI_LIBRARY}")
endif()

# Abort if all methods fail
if(NOT ESMI_FOUND)
    message(FATAL_ERROR "E-SMI library support needs explict ESMI_DIR")
endif()
