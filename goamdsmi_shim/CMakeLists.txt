# SPDX-License-Identifier: MIT

#
# Minimum version of cmake required
#
cmake_minimum_required(VERSION 3.5.0)

#
#   cmake command line options:
#
#   1) Set CMAKE_BUILD_TYPE to either "Debug" or "Release".
#      If not set, the default value is "Debug"
#
#      example #cmake -DCMAKE_BUILD_TYPE=Release ..
#
#   2) Set ENABLE_GTEST to either "ON" or "OFF".
#      If not set, the default value is "OFF"
#
#      example #cmake -DENABLE_GTEST=ON ..
#
#   3) Set ENABLE_CODE_COV to either "ON" or "OFF".
#      If not set, the default value is "OFF"
#      Code Coverage is not preferred in "Release" build type.
#
#      example #cmake -DENABLE_CODE_COV=ON ..
#
#   4) Set ENABLE_STATIC_LIB to either "1" or "0".
#      If not set, the default value is "disbaled"
#
#      example #cmake -DENABLE_STATIC_LIB=1 ..
#
#   3) Set -DWITH_ESMI and -DWITH_ROCM_SMI to either "ON" or "OFF".
#      If not set, the default value is "OFF" for WITH_ESMI, "OFF" for WITH_ROCM_SMI and "ON" for WITH_AMDSMI.
#      This cmake options builds required library APIs as per user need.
#
#      example #Below possible combinations.
#	       #cmake -DWITH_ESMI=ON   -DWITH_ROCM_SMI=ON  -DWITH_AMDSMI=OFF ../amd_smi.cmake ../
#	       #cmake -DWITH_ESMI=OFF  -DWITH_ROCM_SMI=ON  -DWITH_AMDSMI=OFF ../amd_smi.cmake ../
#	       #cmake -DWITH_ESMI=ON   -DWITH_ROCM_SMI=OFF -DWITH_AMDSMI=OFF ../amd_smi.cmake ../
#	       #cmake -DWITH_ESMI=OFF  -DWITH_ROCM_SMI=OFF -DWITH_AMDSMI=ON  ../amd_smi.cmake ../
#	       #cmake -DWITH_ESMI=ON   -DWITH_ROCM_SMI=OFF -DWITH_AMDSMI=ON  ../amd_smi.cmake ../
#	       #cmake -DWITH_ESMI=OFF  -DWITH_ROCM_SMI=ON  -DWITH_AMDSMI=ON  ../amd_smi.cmake ../
#	       #cmake -DWITH_ESMI=ON   -DWITH_ROCM_SMI=ON  -DWITH_AMDSMI=ON  ../amd_smi.cmake ../
#
#   Build Steps:
#   1) #mkdir build
#   2) #cd build
#   3) #cmake ../amd_smi.cmake ../
#      The above command will pick default -DWITH_ESMI=OFF -DWITH_ROCM_SMI=OFF -DWITH_AMDSMI=ON
#      (or)
#      #cmake -C ../amd_smi.cmake ../
#      The above '-C' option will pick default -DWITH_ESMI=ON -DWITH_ROCM_SMI=ON -DWITH_AMDSMI=ON
#   4) #make
#   5) #make install


option(WITH_ESMI         "Support cpu family"			OFF)
option(WITH_ROCM_SMI     "Support gpu family"			OFF)
option(WITH_AMDSMI       "Support unified cpu and gpu"		ON)

set(ESMI_DIR "" CACHE PATH "path to e_smi installation")
set(ROCM_SMI_DIR "" CACHE PATH "path to rocm_smi installation")
set(AMDSMI_DIR "" CACHE PATH "path to amdsmi installation")

if(WITH_ESMI)
add_definitions(-DESMI_BUILD)
include(deps/SetupEsmi.cmake)
endif()

if(WITH_ROCM_SMI)
add_definitions(-DROCM_BUILD)
include(deps/SetupRocmsmi.cmake)
endif()

if(WITH_AMDSMI)
add_definitions(-DAMDSMI_BUILD)
add_definitions(-DENABLE_ESMI_LIB)
include(deps/SetupAmdsmi.cmake)
endif()

if(ENABLE_DEBUG_LEVEL)
add_definitions(-DENABLE_DEBUG_LEVEL=${ENABLE_DEBUG_LEVEL})
message("**** Enabling Debug Level=${ENABLE_DEBUG_LEVEL} ****")
else()
add_definitions(-DENABLE_DEBUG_LEVEL=0)
endif()

set(GOAMDSMI_SHIM "goamdsmi_shim")
set(GOAMDSMI_SHIM_LIB "goamdsmi")
set(GOAMDSMI_SHIM_COMPONENT "lib${GOAMDSMI_SHIM}")
set(GOAMDSMI_SHIM_TARGET "${GOAMDSMI_SHIM}64")

# The following default version values should be updated as appropriate for
# ABI breaks (update MAJOR and MINOR), and ABI/API additions (update MINOR).
# Until ABI stabilizes VERSION_MAJOR will be 0. This should be over-ridden
# by git tags (through "git describe") when they are present.
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_NUM_COMMIT 0)

set(SO_VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}")

set(${GOAMDSMI_SHIM}_VERSION_MAJOR "${VERSION_MAJOR}")
set(${GOAMDSMI_SHIM}_VERSION_MINOR "${VERSION_MINOR}")
set(${GOAMDSMI_SHIM}_VERSION_PATCH "0")
set(${GOAMDSMI_SHIM}_VERSION_BUILD "0")
message("SOVERSION: ${SO_VERSION_STRING}")

## Define default variable and variables for the optional build target
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
	CACHE STRING "Location of goamdsmi_shim source code.")
set(CMAKE_INSTALL_PREFIX "/opt/goamdsmi"
                                CACHE STRING "Default installation directory.")
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/goamdsmi"
                                      CACHE STRING "Default packaging prefix.")

project(${GOAMDSMI_SHIM_TARGET})

# Create a configure file to get version info from within library
configure_file(
	"${PROJECT_SOURCE_DIR}/${GOAMDSMI_SHIM_TARGET}Config.in"
	"${PROJECT_SOURCE_DIR}/include/${GOAMDSMI_SHIM_TARGET}Config.h")

if (NOT DEFINED CPACK_PACKAGE_VENDOR)
    set(CPACK_PACKAGE_VENDOR "AMD")
endif()

if (NOT DEFINED CPACK_PACKAGE_CONTACT)
    set(CPACK_PACKAGE_CONTACT "Advanced Micro Devices Inc.")
endif()

if (NOT DEFINED CPACK_PACKAGE_DESCRIPTION_SUMMARY)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
	"AMD CGO wrapper")
endif()

if (NOT GOAMDSMI_SHIM_PACKAGE)
	set(GOAMDSMI_SHIM_PACKAGE goamdsmi_shim_lib64)
endif()

set(CPACK_PACKAGE_FILE_NAME "${GOAMDSMI_SHIM_PACKAGE}-${SO_VERSION_STRING}")
## Verbose output.
set(CMAKE_VERBOSE_MAKEFILE on)

## Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fpic -fno-rtti -m64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse -msse2 -std=c++11 ")
# Use this instead of above for 32 bit
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")

if ("${CMAKE_BUILD_TYPE}" STREQUAL Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -O0 -DDEBUG")
endif ()

set(go_amd_smi_headers)

set(go_amd_smi_sources)

set(go_amd_smi_includes)


add_subdirectory(goamdsmi)
list(APPEND go_amd_smi_headers goamdsmi/goamdsmi.h ${go_amd_smi_headers})
list(APPEND go_amd_smi_headers goamdsmi/goamdsmi_shim.h ${go_amd_smi_headers})
list(APPEND go_amd_smi_sources goamdsmi/goamdsmi_shim.c)
list(APPEND go_amd_smi_includes ${CMAKE_CURRENT_SOURCE_DIR}/goamdsmi)

list(APPEND go_amd_smi_headers esmi/esmi_go_shim.h ${go_amd_smi_headers})
list(APPEND go_amd_smi_sources esmi/esmi_go_shim.c)
list(APPEND go_amd_smi_includes ${CMAKE_CURRENT_SOURCE_DIR}/esmi)

list(APPEND go_amd_smi_headers rsmi/rocm_smi_go_shim.h ${go_amd_smi_headers})
list(APPEND go_amd_smi_sources rsmi/rocm_smi_go_shim.c)
list(APPEND go_amd_smi_includes ${CMAKE_CURRENT_SOURCE_DIR}/rsmi)

list(APPEND go_amd_smi_headers amdsmi/amdsmi_go_shim.h ${go_amd_smi_headers})
list(APPEND go_amd_smi_sources amdsmi/amdsmi_go_shim.c)
list(APPEND go_amd_smi_includes ${CMAKE_CURRENT_SOURCE_DIR}/amdsmi)

add_library(${GOAMDSMI_SHIM_TARGET} SHARED
	    ${go_amd_smi_sources}
	    ${go_amd_smi_headers}
	    ${go_amd_smi_includes})

target_link_libraries(${GOAMDSMI_SHIM_TARGET} pthread rt m)

if(WITH_ROCM_SMI)
	target_link_libraries(${GOAMDSMI_SHIM_TARGET} rocm_smi64)
	target_link_libraries(${GOAMDSMI_SHIM_TARGET} -L${ROCM_SMI_DIR}/lib)
endif()

if(WITH_ESMI)
	target_link_libraries(${GOAMDSMI_SHIM_TARGET} e_smi64)
	target_link_libraries(${GOAMDSMI_SHIM_TARGET} -L${ESMI_DIR}/lib)
endif()

if(WITH_AMDSMI)
    target_link_libraries(${GOAMDSMI_SHIM_TARGET} amd_smi)
    target_link_libraries(${GOAMDSMI_SHIM_TARGET} -L${AMDSMI_DIR}/lib)
    target_link_libraries(${GOAMDSMI_SHIM_TARGET} -L${AMDSMI_DIR}/lib64)
endif()

## Set the VERSION and SOVERSION values
set_property(TARGET ${GOAMDSMI_SHIM_TARGET} PROPERTY
                SOVERSION "${VERSION_MAJOR}")
set_property(TARGET ${GOAMDSMI_SHIM_TARGET} PROPERTY
                VERSION "${SO_VERSION_STRING}")

## If the library is a release, strip the target library
if ("${CMAKE_BUILD_TYPE}" STREQUAL Release)
    add_custom_command(
	  TARGET ${GOAMDSMI_SHIM_TARGET}
	  POST_BUILD COMMAND ${CMAKE_STRIP} lib${GOAMDSMI_SHIM_TARGET}.so)
endif ()

set(go_amd_smi_install_headers
    goamdsmi/goamdsmi.h
    goamdsmi/goamdsmi_shim.h
    esmi/esmi_go_shim.h
    rsmi/rocm_smi_go_shim.h
    amdsmi/amdsmi_go_shim.h
)

## Add the install directives for the runtime library.
install(TARGETS ${GOAMDSMI_SHIM_TARGET}
	LIBRARY DESTINATION lib COMPONENT ${GOAMDSMI_SHIM_COMPONENT})
install(FILES ${go_amd_smi_install_headers} 
	DESTINATION include)

include_directories(${go_amd_smi_includes})
