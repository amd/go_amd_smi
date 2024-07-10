# SPDX-License-Identifier: MIT

# c compiler
set(CMAKE_C_COMPILER "gcc" CACHE PATH "")

# cpp compiler
set(CMAKE_CXX_COMPILER "g++" CACHE PATH "")

set(WITH_ESMI ON CACHE BOOL "")
set(WITH_ROCM_SMI ON CACHE BOOL "")
set(WITH_AMDSMI ON CACHE BOOL "")

# path to global esmi, rocm_smi and amdsmi install
set(ESMI_DIR "/opt/e-sms/e_smi" CACHE PATH "")
set(ROCM_SMI_DIR "/opt/rocm" CACHE PATH "")
set(AMDSMI_DIR "/opt/rocm" CACHE PATH "")
