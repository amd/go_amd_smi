// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2024, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Developed by:
 *
 *                 AMD Research and AMD Software Development
 *
 *                 Advanced Micro Devices, Inc.
 *
 *                 www.amd.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sellcopies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *  - The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the Advanced Micro Devices,
 * Inc. shall not be used in advertising or otherwise to promote the sale, use
 * or other dealings in this Software without prior written authorization from
 * the Advanced Micro Devices, Inc.
 *
 */

#include <stdint.h>
#include "amdsmi_go_shim.h"
#ifdef AMDSMI_BUILD
#include <amd_smi/amdsmi.h>
#endif
#include <unistd.h>
#define nullptr ((void*)0)

#ifdef AMDSMI_BUILD
#define MAX_SOCKET_ACROSS_SYSTEM         4
#define CPU_0                            0
#define GPU_SENSOR_0                     0
#define MAX_CPU_PER_SOCKET               4
#define MAX_PHYSICALCORE_ACROSS_SYSTEM 384
#define MAX_LOGICALCORE_ACROSS_SYSTEM  768
#define MAX_GPU_DEVICE_ACROSS_SYSTEM    24
#define MAX_GPU_POWER_FROM_DRIVER      0xFFFF

#define AMDSMI_DRIVER_NAME     "AMDSMI"
#define AMDSMI_LIB_FILE        "/opt/rocm/lib/libamd_smi.so"
#define AMDSMI_LIB64_FILE      "/opt/rocm/lib64/libamd_smi.so"

#define AMDGPU_DRIVER_NAME     "AMDGPUDriver"
#define AMDGPU_INITSTATE_FILE  "/sys/module/amdgpu/initstate"

#define AMDHSMP_DRIVER_NAME    "AMDHSMPDriver"
#define AMDHSMP_INITSTATE_FILE "/sys/module/amd_hsmp/initstate"

static uint32_t num_apuSockets              = 0;
static uint32_t num_cpuSockets              = 0;
static uint32_t num_gpuSockets              = 0;
static uint32_t cpuInitCompleted            = false;
static uint32_t gpuInitCompleted            = false;
static uint32_t apuInitCompleted            = false;

static uint32_t num_cpu_inAllSocket                = 0;
static uint32_t num_cpu_physicalCore_inAllSocket   = 0;
static uint32_t num_gpu_devices_inAllSocket        = 0;

static amdsmi_socket_handle     amdsmi_apusocket_handle_all_socket[MAX_SOCKET_ACROSS_SYSTEM+MAX_GPU_DEVICE_ACROSS_SYSTEM]    = {0};
static amdsmi_socket_handle     amdsmi_cpusocket_handle_all_socket[MAX_SOCKET_ACROSS_SYSTEM]                                 = {0};
static amdsmi_socket_handle     amdsmi_gpusocket_handle_all_socket[MAX_GPU_DEVICE_ACROSS_SYSTEM]                             = {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_cpu_across_socket[MAX_SOCKET_ACROSS_SYSTEM*MAX_CPU_PER_SOCKET]   = {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_cpu_physicalCore_across_socket[MAX_PHYSICALCORE_ACROSS_SYSTEM]   = {0};
static amdsmi_processor_handle  amdsmi_processor_handle_all_gpu_device_across_socket[MAX_GPU_DEVICE_ACROSS_SYSTEM]           = {0};

goamdsmi_status_t is_file_present(const char* driver_name, const char* file_name)
{
    if(0 == access(file_name, F_OK)) 
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, %s found \"%s\" and returns:%d\n", driver_name, file_name, GOAMDSMI_STATUS_SUCCESS);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_2)) {printf("AMDSMI, Status, %s not found, missing \"%s\" and returns:%d\n", driver_name, file_name, GOAMDSMI_STATUS_FAILURE);}
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmi_present()
{
    if((GOAMDSMI_STATUS_SUCCESS == is_file_present(AMDSMI_DRIVER_NAME, AMDSMI_LIB_FILE)) || (GOAMDSMI_STATUS_SUCCESS == is_file_present(AMDSMI_DRIVER_NAME, AMDSMI_LIB64_FILE)))
    {
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t check_amdgpu_driver()
{
    return is_file_present(AMDGPU_DRIVER_NAME, AMDGPU_INITSTATE_FILE);
}

goamdsmi_status_t check_hsmp_driver()
{
    return  is_file_present(AMDHSMP_DRIVER_NAME, AMDHSMP_INITSTATE_FILE);
}

goamdsmi_status_t go_shim_amdsmiapu_init(goamdsmi_Init_t goamdsmi_Init)
{
    if((GOAMDSMI_CPU_INIT == goamdsmi_Init) && (true == cpuInitCompleted))
    {
        if((0 == num_cpuSockets)||(0 == num_cpu_inAllSocket)||(0 == num_cpu_physicalCore_inAllSocket))
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Failed, Returns previous enumurated AMDSMICPUInit:%d, CpuSocketCount:%d, CpuCount:%d, CpuPhysicalCoreCount:%d\n", GOAMDSMI_STATUS_FAILURE, num_cpuSockets, num_cpu_inAllSocket, num_cpu_physicalCore_inAllSocket);}
            return GOAMDSMI_STATUS_FAILURE;
        }
        else 
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, Returns previous enumurated AMDSMICPUInit:%d, CpuSocketCount:%d, CpuCount:%d, CpuPhysicalCoreCount:%d\n", GOAMDSMI_STATUS_SUCCESS, num_cpuSockets, num_cpu_inAllSocket, num_cpu_physicalCore_inAllSocket);}
            return GOAMDSMI_STATUS_SUCCESS;
        }
    }
    
    if((GOAMDSMI_GPU_INIT == goamdsmi_Init) && (true == gpuInitCompleted))
    {
        if((0 == num_gpuSockets)||(0 == num_gpu_devices_inAllSocket))
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Failed, Returns previous enumurated AMDSMIGPUInit:%d, GpuSocketCount:%d, GpuCount:%d\n", GOAMDSMI_STATUS_FAILURE, num_gpuSockets, num_gpu_devices_inAllSocket);}
            return GOAMDSMI_STATUS_FAILURE;
        }
        else
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, Returns previous enumurated AMDSMIGPUInit:%d, GpuSocketCount:%d, GpuCount:%d\n", GOAMDSMI_STATUS_SUCCESS, num_gpuSockets, num_gpu_devices_inAllSocket);}
            return GOAMDSMI_STATUS_SUCCESS;
        }
    }

#if 0
    if(GOAMDSMI_STATUS_FAILURE == go_shim_amdsmi_present())
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Failed, AMDSMI not present in the System, missing \"%s\" (or) \"%s\"\n", AMDSMI_LIB_FILE, AMDSMI_LIB64_FILE);}
        return GOAMDSMI_STATUS_FAILURE;
    }
#endif

    if ((GOAMDSMI_STATUS_SUCCESS == check_amdgpu_driver()) && (GOAMDSMI_STATUS_SUCCESS == check_hsmp_driver())) 
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_2)) {printf("AMDSMI, Status, Identified APU machine and going to enumurate APU\n");}

        if( (AMDSMI_STATUS_SUCCESS == amdsmi_init(AMDSMI_INIT_AMD_APUS)) &&
            (AMDSMI_STATUS_SUCCESS == amdsmi_get_socket_handles(&num_apuSockets, nullptr)) &&
            (AMDSMI_STATUS_SUCCESS == amdsmi_get_socket_handles(&num_apuSockets, &amdsmi_apusocket_handle_all_socket[0])) &&
            (0 != num_apuSockets))
        {
            cpuInitCompleted = true;
            gpuInitCompleted = true;
            apuInitCompleted = true;
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, Identified APU machine ApuNumSockets=%d\n",num_apuSockets);}
            for(uint32_t socket_counter = 0; socket_counter < num_apuSockets; socket_counter++)
            {
                uint32_t num_cpu               = 0;
                uint32_t num_cpu_physicalCores = 0;
                uint32_t num_gpu_devices       = 0;

                //CPU
                processor_type_t cpu_processor_type         = AMDSMI_PROCESSOR_TYPE_AMD_CPU;
                processor_type_t cpu_core_processor_type    = AMDSMI_PROCESSOR_TYPE_AMD_CPU_CORE;
                if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], cpu_processor_type, nullptr, &num_cpu)) &&
                    (0 != num_cpu) &&
                    (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], cpu_processor_type, &amdsmi_processor_handle_all_cpu_across_socket[num_cpu_inAllSocket], &num_cpu)))
                {
                    if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], cpu_core_processor_type, nullptr, &num_cpu_physicalCores)) &&
                        (0 != num_cpu_physicalCores) &&
                        (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], cpu_core_processor_type, &amdsmi_processor_handle_all_cpu_physicalCore_across_socket[num_cpu_physicalCore_inAllSocket], &num_cpu_physicalCores)))
                    {
                        num_cpu_physicalCore_inAllSocket = num_cpu_physicalCore_inAllSocket+num_cpu_physicalCores;
                    }
                    num_cpu_inAllSocket = num_cpu_inAllSocket+num_cpu;
                    num_cpuSockets = num_cpuSockets+1;
                }

                //GPU
                processor_type_t gpu_device_processor_type    = AMDSMI_PROCESSOR_TYPE_AMD_GPU;
                if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], gpu_device_processor_type, nullptr, &num_gpu_devices)) &&
                    (0 != num_gpu_devices) &&
                    (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_apusocket_handle_all_socket[socket_counter], gpu_device_processor_type, &amdsmi_processor_handle_all_gpu_device_across_socket[num_gpu_devices_inAllSocket], &num_gpu_devices)))
                {
                     num_gpu_devices_inAllSocket = num_gpu_devices_inAllSocket+num_gpu_devices;
                     num_gpuSockets = num_gpuSockets+1;
                }
            }
        }
    }
    else if(GOAMDSMI_CPU_INIT == goamdsmi_Init)
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_2)) {printf("AMDSMI, Status, Going to enumurate only CPU\n");}
        cpuInitCompleted = true;
        
        if (GOAMDSMI_STATUS_SUCCESS == check_hsmp_driver()) 
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_2)) {printf("AMDSMI, Status, Identified CPU Driver and going to enumurate only CPU\n");}

            if( (AMDSMI_STATUS_SUCCESS != amdsmi_init(AMDSMI_INIT_AMD_CPUS)) ||
                (AMDSMI_STATUS_SUCCESS != amdsmi_get_socket_handles(&num_cpuSockets, nullptr)) || 
                (AMDSMI_STATUS_SUCCESS != amdsmi_get_socket_handles(&num_cpuSockets, &amdsmi_cpusocket_handle_all_socket[0])) ||
                (0 == num_cpuSockets))
            {
                if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Failed, AMDSMICPUInit:0, CpuNumSockets=0\n");}
                return GOAMDSMI_STATUS_FAILURE;
            }        
        }
        else
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_3)) {printf("AMDSMI, Status, Missing CPU Driver and not going to enumurate only CPU\n");}
        }
        //CPU
        for(uint32_t cpu_socket_counter = 0; cpu_socket_counter < num_cpuSockets; cpu_socket_counter++)
        {
            uint32_t num_cpu               = 0;
            uint32_t num_cpu_physicalCores = 0;

            processor_type_t cpu_processor_type         = AMDSMI_PROCESSOR_TYPE_AMD_CPU;
            processor_type_t cpu_core_processor_type    = AMDSMI_PROCESSOR_TYPE_AMD_CPU_CORE;
            if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_cpusocket_handle_all_socket[cpu_socket_counter], cpu_processor_type, nullptr, &num_cpu)) &&
                (0 != num_cpu) &&
                (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_cpusocket_handle_all_socket[cpu_socket_counter], cpu_processor_type, &amdsmi_processor_handle_all_cpu_across_socket[num_cpu_inAllSocket], &num_cpu)))
            {
                if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_cpusocket_handle_all_socket[cpu_socket_counter], cpu_core_processor_type, nullptr, &num_cpu_physicalCores)) &&
                    (0 != num_cpu_physicalCores) &&
                    (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_cpusocket_handle_all_socket[cpu_socket_counter], cpu_core_processor_type, &amdsmi_processor_handle_all_cpu_physicalCore_across_socket[num_cpu_physicalCore_inAllSocket], &num_cpu_physicalCores)))
                {
                    num_cpu_physicalCore_inAllSocket = num_cpu_physicalCore_inAllSocket+num_cpu_physicalCores;
                }
                num_cpu_inAllSocket = num_cpu_inAllSocket+num_cpu;
            }
        }
    }
    else if(GOAMDSMI_GPU_INIT == goamdsmi_Init)    
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_2)) {printf("AMDSMI, Status, Going to enumurate only GPU\n");}
        gpuInitCompleted = true;
        
        if (GOAMDSMI_STATUS_SUCCESS == check_amdgpu_driver()) 
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_2)) {printf("AMDSMI, Status, Identified GPU Driver and going to enumurate only GPU\n");}

            if( (AMDSMI_STATUS_SUCCESS != amdsmi_init(AMDSMI_INIT_AMD_GPUS)) ||
                (AMDSMI_STATUS_SUCCESS != amdsmi_get_socket_handles(&num_gpuSockets, nullptr)) || 
                (AMDSMI_STATUS_SUCCESS != amdsmi_get_socket_handles(&num_gpuSockets, &amdsmi_gpusocket_handle_all_socket[0])) ||
                (0 == num_gpuSockets))
            {
                if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Failed, AMDSMIGPUInit:0, GpuNumSockets=0\n");}
                return GOAMDSMI_STATUS_FAILURE;
            }
        }
        else
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_3)) {printf("AMDSMI, Status, Missing GPU Driver and not going to enumurate only GPU\n");}
        }
        
        //GPU
        for(uint32_t gpu_socket_counter = 0; gpu_socket_counter < num_gpuSockets; gpu_socket_counter++)
        {
            uint32_t num_gpu_devices       = 0;
            
            processor_type_t gpu_device_processor_type    = AMDSMI_PROCESSOR_TYPE_AMD_GPU;
            if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_gpusocket_handle_all_socket[gpu_socket_counter], gpu_device_processor_type, nullptr, &num_gpu_devices)) &&
                (0 != num_gpu_devices) &&
                (AMDSMI_STATUS_SUCCESS == amdsmi_get_processor_handles_by_type(amdsmi_gpusocket_handle_all_socket[gpu_socket_counter], gpu_device_processor_type, &amdsmi_processor_handle_all_gpu_device_across_socket[num_gpu_devices_inAllSocket], &num_gpu_devices)))
            {
                num_gpu_devices_inAllSocket = num_gpu_devices_inAllSocket+num_gpu_devices;
            }
        }
    }
    
    //CPU
    if((GOAMDSMI_CPU_INIT == goamdsmi_Init) && ((0 == num_cpuSockets)||(0 == num_cpu_inAllSocket)||(0 == num_cpu_physicalCore_inAllSocket)))
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Failed, CPU Enumuration Failed AMDSMICPUInit:%d, CpuSocketCount:%d, CpuCount:%d, CpuPhysicalCoreCount:%d,\n", GOAMDSMI_STATUS_FAILURE, num_cpuSockets, num_cpu_inAllSocket, num_cpu_physicalCore_inAllSocket);}
        return GOAMDSMI_STATUS_FAILURE;
    }
    
    //GPU
    if((GOAMDSMI_GPU_INIT == goamdsmi_Init) && ((0 == num_gpuSockets)||(0 == num_gpu_devices_inAllSocket)))
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Failed, GPU Enumuration Failed AMDSMIGPUInit:%d, GpuSocketCount:%d, GpuCount:%d\n", GOAMDSMI_STATUS_FAILURE, num_gpuSockets, num_gpu_devices_inAllSocket);}
        return GOAMDSMI_STATUS_FAILURE;
    }

    if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) 
    {
        if((GOAMDSMI_CPU_INIT == goamdsmi_Init) || apuInitCompleted)    printf("AMDSMI, Status, AMDSMICPUInit:%d, CpuSocketCount:%d, CpuCount:%d, CpuPhysicalCoreCount:%d,\n", GOAMDSMI_STATUS_SUCCESS, num_cpuSockets, num_cpu_inAllSocket, num_cpu_physicalCore_inAllSocket);
        if((GOAMDSMI_GPU_INIT == goamdsmi_Init) || apuInitCompleted)    printf("AMDSMI, Status, AMDSMIGPUInit:%d, GpuSocketCount:%d, GpuCount:%d\n", GOAMDSMI_STATUS_SUCCESS, num_gpuSockets, num_gpu_devices_inAllSocket);
    }
    
    return GOAMDSMI_STATUS_SUCCESS;
}
////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
goamdsmi_status_t go_shim_amdsmicpu_init()    
{
    if(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmiapu_init(GOAMDSMI_CPU_INIT))
    {
        if((num_cpu_inAllSocket) && (num_cpu_physicalCore_inAllSocket))
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, InitAMDSMICPUInit:%d, CpuSocketCount:%d, CpuCount:%d, CpuPhysicalCoreCount:%d,\n", GOAMDSMI_STATUS_SUCCESS, num_cpuSockets, num_cpu_inAllSocket, num_cpu_physicalCore_inAllSocket);}
            return GOAMDSMI_STATUS_SUCCESS;
        }
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_threads_per_core_get(uint32_t* threads_per_core)
{
    *threads_per_core               = 0;
    uint32_t threads_per_core_temp  = 0;

    if((AMDSMI_STATUS_SUCCESS == amdsmi_get_threads_per_core(&threads_per_core_temp)))
    {
        *threads_per_core = threads_per_core_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, CpuThreadsPerCore:%d\n", *threads_per_core);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_number_of_threads_get(uint32_t* number_of_threads)
{
    *number_of_threads            = 0;
    uint32_t num_threads_per_core = 0;
    if(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmicpu_threads_per_core_get(&num_threads_per_core))
    {
        *number_of_threads = num_cpu_physicalCore_inAllSocket*num_threads_per_core;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, CpuNumThreads:%d\n", *number_of_threads);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_number_of_sockets_get(uint32_t* number_of_sockets)
{
    *number_of_sockets = num_cpuSockets;
    if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, CpuNumSockets:%d\n", *number_of_sockets);}
    return GOAMDSMI_STATUS_SUCCESS;
}

goamdsmi_status_t go_shim_amdsmicpu_core_energy_get(uint32_t thread_index, uint64_t* core_energy)
{
    *core_energy                 = 0;
    uint64_t core_energy_temp    = 0;
    uint32_t physicalCore_index  = thread_index%num_cpu_physicalCore_inAllSocket;

    if(AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_core_energy(amdsmi_processor_handle_all_cpu_physicalCore_across_socket[physicalCore_index], &core_energy_temp))
    {
        *core_energy = core_energy_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Thread:%d PC:%d, CpuCoreEnergy:%d, CpuCoreEnergyJoules:%.6f\n", thread_index, physicalCore_index, (int)(*core_energy), ((double)(*core_energy))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_socket_energy_get(uint32_t socket_index, uint64_t* socket_energy)
{
    *socket_energy              = 0;
    uint64_t socket_energy_temp = 0;
    if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_energy(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &socket_energy_temp)))
    {
        *socket_energy = socket_energy_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Socket:%d, CpuSocketEnergy:%d, CpuSocketEnergyJoules:%.6f\n", socket_index, (int)(*socket_energy), ((double)(*socket_energy))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_prochot_status_get(uint32_t socket_index, uint32_t* prochot)
{
    *prochot               = 0;
    uint32_t prochot_temp  = 0;
    if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_prochot_status(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &prochot_temp)))
    {
        *prochot = prochot_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Socket:%d, CpuProchotStatus:%d\n", socket_index, *prochot);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_socket_power_get(uint32_t socket_index, uint32_t* socket_power)
{
    *socket_power              = 0;
    uint32_t socket_power_temp = 0;
    if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_power(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &socket_power_temp)))
    {
        *socket_power = socket_power_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Socket:%d, CpuSocketPower:%d, CpuSocketPowerWatt:%.3f\n", socket_index, *socket_power, ((double)(*socket_power))/1000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_socket_power_cap_get(uint32_t socket_index, uint32_t* socket_power_cap)
{
    *socket_power_cap              = 0;
    uint32_t socket_power_cap_temp = 0;
    if((AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_socket_power_cap(amdsmi_processor_handle_all_cpu_across_socket[socket_index], &socket_power_cap_temp)))
    {
        *socket_power_cap = socket_power_cap_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Socket:%d, CpuSocketPowerCap:%d, CpuSocketPowerCapWatt:%.3f\n", socket_index, *socket_power_cap, ((double)(*socket_power_cap))/1000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmicpu_core_boostlimit_get(uint32_t thread_index, uint32_t* core_boostlimit)
{
    *core_boostlimit               = 0;
    uint32_t core_boostlimit_temp  = 0;
    uint32_t physicalCore_index    = thread_index%num_cpu_physicalCore_inAllSocket;

    if(AMDSMI_STATUS_SUCCESS == amdsmi_get_cpu_core_boostlimit(amdsmi_processor_handle_all_cpu_physicalCore_across_socket[physicalCore_index], &core_boostlimit_temp))
    {
        *core_boostlimit = core_boostlimit_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Thread:%d PC:%d, CpuCoreBoostLimit:%d\n", thread_index, physicalCore_index, *core_boostlimit);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
goamdsmi_status_t go_shim_amdsmigpu_init()
{
    if(GOAMDSMI_STATUS_SUCCESS == go_shim_amdsmiapu_init(GOAMDSMI_GPU_INIT))
    {
        if((num_gpu_devices_inAllSocket))
        {
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, InitAMDSMIGPUInit:%d, GpuSocketCount:%d, GpuCount:%d\n", GOAMDSMI_STATUS_SUCCESS, num_gpuSockets, num_gpu_devices_inAllSocket);}
            return GOAMDSMI_STATUS_SUCCESS;
        }
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_shutdown()
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_num_monitor_devices(uint32_t* gpu_num_monitor_devices)
{
    *gpu_num_monitor_devices = num_gpu_devices_inAllSocket;
    if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success, GpuNumMonitorDevices:%d\n", *gpu_num_monitor_devices);}
    return GOAMDSMI_STATUS_SUCCESS;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_name_get(uint32_t dv_ind, char** gpu_dev_name)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id)
{
    *gpu_dev_id              = 0;
    uint16_t gpu_dev_id_temp = 0;
    
    if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_id(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], &gpu_dev_id_temp)))
    {
        *gpu_dev_id = gpu_dev_id_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuDevId:%d\n", dv_ind, *gpu_dev_id);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap)
{
    *gpu_power_cap                                      = 0;
    amdsmi_power_cap_info_t amdsmi_power_cap_info_temp  = {0};

    if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_power_cap_info(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], GPU_SENSOR_0, &amdsmi_power_cap_info_temp)))
    {
        *gpu_power_cap = amdsmi_power_cap_info_temp.power_cap;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuPowerCap:%d, GpuPowerCapInWatt:%.6f\n", dv_ind, (int)(*gpu_power_cap), ((double)(*gpu_power_cap))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_power_get(uint32_t dv_ind, uint64_t* gpu_power)
{
    *gpu_power                                  = 0;
    uint64_t gpu_power_temp                     = 0;
    amdsmi_power_info_t amdsmi_power_info_temp  = {0};

    if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_power_info(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], &amdsmi_power_info_temp)))
    {
        gpu_power_temp = amdsmi_power_info_temp.average_socket_power;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_2)) {printf("AMDSMI, Success for Gpu:%d, GpuPowerAverage:%d, GpuPowerAverageinWatt:%.6f\n", dv_ind, (int)(gpu_power_temp), ((double)(gpu_power_temp))/1000000);}

        if(MAX_GPU_POWER_FROM_DRIVER == gpu_power_temp)
        {
            gpu_power_temp = amdsmi_power_info_temp.current_socket_power;
            if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_2)) {printf("AMDSMI, Success for Gpu:%d, GpuPowerCurrent:%d, GpuPowerCurrentinWatt:%.6f\n", dv_ind, (int)(gpu_power_temp), ((double)(gpu_power_temp))/1000000);}
        }
        *gpu_power = gpu_power_temp;
        *gpu_power = (*gpu_power)*1000000;//to maintain backward compatibity with old ROCM SMI
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuPower:%d, GpuPowerinWatt:%.6f\n", dv_ind, (int)(*gpu_power), ((double)(*gpu_power))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature)
{
    *gpu_temperature              = 0;
    uint64_t gpu_temperature_temp = 0;

    if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_temp_metric(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], sensor, metric, &gpu_temperature_temp)))
    {
        *gpu_temperature = gpu_temperature_temp;
        *gpu_temperature = (*gpu_temperature)*1000;//to maintain backward compatibity with old ROCM SMI
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d Sensor:%d Metric:%d, GpuTemperature:%d, GpuTemperatureInDegree:%.3f\n", dv_ind, sensor, metric, (int)(*gpu_temperature), ((double)(*gpu_temperature))/1000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq)
{
    *gpu_sclk_freq            = 0;
    amdsmi_frequencies_t freq = {0};

    if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_clk_freq(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], AMDSMI_CLK_TYPE_SYS, &freq)))
    {
        *gpu_sclk_freq = freq.frequency[freq.current];
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuSclkFreq:%d, GpuSclkFreqMhz:%.6f\n", dv_ind, (int)(*gpu_sclk_freq), ((double)(*gpu_sclk_freq))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq)
{
    *gpu_memclk_freq          = 0;
    amdsmi_frequencies_t freq = {0};

    if((dv_ind < num_gpu_devices_inAllSocket) && (AMDSMI_STATUS_SUCCESS == amdsmi_get_clk_freq(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], AMDSMI_CLK_TYPE_MEM, &freq)))
    {
        *gpu_memclk_freq = freq.frequency[freq.current];
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuMclkFreq:%d, GpuMclkFreqMhz:%.6f\n", dv_ind, (int)(*gpu_memclk_freq), ((double)(*gpu_memclk_freq))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk)
{
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_busy_percent_get(uint32_t dv_ind, uint32_t* gpu_busy_percent)
{
    *gpu_busy_percent       = 0;
     amdsmi_engine_usage_t amdsmi_engine_usage_temp;

    if(AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_activity(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], &amdsmi_engine_usage_temp))
    {
        *gpu_busy_percent = amdsmi_engine_usage_temp.gfx_activity;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuBusyPerc:%d\n", dv_ind, *gpu_busy_percent);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_3)) {printf("AMDSMI, Failed for Gpu:%d, GpuBusyPerc:%d\n", dv_ind, *gpu_busy_percent);}
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent)
{
    *gpu_memory_busy_percent       = 0;
    uint64_t gpu_memory_usage_temp = 0;
    uint64_t gpu_memory_total_temp = 0;

    if( (AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_memory_usage(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], AMDSMI_MEM_TYPE_VRAM, &gpu_memory_usage_temp))&&
        (AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_memory_total(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], AMDSMI_MEM_TYPE_VRAM, &gpu_memory_total_temp)))
    {
        *gpu_memory_busy_percent = (uint64_t)(gpu_memory_usage_temp*100)/gpu_memory_total_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuMemoryBusyPerc:%ld\n", dv_ind, (*gpu_memory_busy_percent));}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_3)) {printf("AMDSMI, Failed for Gpu:%d, GpuMemoryBusyPerc:%ld\n", dv_ind, (*gpu_memory_busy_percent));}
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage)
{
    *gpu_memory_usage               = 0;
     uint64_t gpu_memory_usage_temp = 0;

    if(AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_memory_usage(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], AMDSMI_MEM_TYPE_VRAM, &gpu_memory_usage_temp))
    {
        *gpu_memory_usage = (uint64_t)gpu_memory_usage_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuMemoryUsage:%ld\n", dv_ind, (*gpu_memory_usage));}
        return GOAMDSMI_STATUS_SUCCESS;
    }
        
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total)
{
    *gpu_memory_total        = 0;
    uint64_t gpu_memory_total_temp    = 0;

    if(AMDSMI_STATUS_SUCCESS == amdsmi_get_gpu_memory_total(amdsmi_processor_handle_all_gpu_device_across_socket[dv_ind], AMDSMI_MEM_TYPE_VRAM, &gpu_memory_total_temp))
    {
        *gpu_memory_total = (uint64_t)gpu_memory_total_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("AMDSMI, Success for Gpu:%d, GpuMemoryTotal:%ld\n", dv_ind, (*gpu_memory_total));}
        return GOAMDSMI_STATUS_SUCCESS;
    }
        
    return GOAMDSMI_STATUS_FAILURE;
}
#else
////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
goamdsmi_status_t go_shim_amdsmicpu_init()                                                                 {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_threads_per_core_get(uint32_t* threads_per_core)                       {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_number_of_threads_get(uint32_t* number_of_threads)                     {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_number_of_sockets_get(uint32_t* number_of_sockets)                     {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_core_energy_get(uint32_t thread_index, uint64_t* core_energy)          {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_socket_energy_get(uint32_t socket_index, uint64_t* socket_energy)      {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_prochot_status_get(uint32_t socket_index, uint32_t* prochot)           {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_socket_power_get(uint32_t socket_index, uint32_t* socket_power)        {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_socket_power_cap_get(uint32_t socket_index, uint32_t* socket_power_cap){return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmicpu_core_boostlimit_get(uint32_t thread_index, uint32_t* core_boostlimit)  {return GOAMDSMI_STATUS_FAILURE;}

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
goamdsmi_status_t go_shim_amdsmigpu_init()                                                        {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_shutdown()                                                    {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_num_monitor_devices(uint32_t* gpu_num_monitor_devices)        {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_name_get(uint32_t dv_ind, char** gpu_dev_name)            {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id)             {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id)         {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name)  {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version)  {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap)   {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_power_get(uint32_t dv_ind, uint64_t* gpu_power)           {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature)    {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level)            {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level)    {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf)                            {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq)                {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq)              {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk)           {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk)         {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk)           {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk)         {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_busy_percent_get(uint32_t dv_ind, uint32_t* gpu_busy_percent)              {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent)                    {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage)              {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total)              {return GOAMDSMI_STATUS_FAILURE;}
#endif
