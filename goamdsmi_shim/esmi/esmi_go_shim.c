// SPDX-License-Identifier: MIT
/*
 * Copyright (c) 2022, Advanced Micro Devices, Inc.
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
#include "esmi_go_shim.h"
#ifdef ESMI_BUILD
#include <e_smi.h>
#endif

#ifdef ESMI_BUILD
goamdsmi_status_t go_shim_esmi_init()
{
    if(ESMI_SUCCESS == esmi_init())
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success, CpuInit:%d\n", GOAMDSMI_STATUS_SUCCESS);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_threads_per_core_get(uint32_t* threads_per_core)
{
    *threads_per_core              = 0;
    uint32_t threads_per_core_temp = 0;

    if(ESMI_SUCCESS == esmi_threads_per_core_get(&threads_per_core_temp))
    {
        *threads_per_core = threads_per_core_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success, CpuThreadsPerCore:%lu\n", (unsigned long)(*threads_per_core));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_number_of_threads_get(uint32_t* number_of_threads)
{
    *number_of_threads                 = 0;
    uint32_t number_of_threads_temp    = 0;

    if(ESMI_SUCCESS ==  esmi_number_of_cpus_get(&number_of_threads_temp))
    {
        *number_of_threads = number_of_threads_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success, CpuNumThreads:%lu\n", (unsigned long)(*number_of_threads));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_number_of_sockets_get(uint32_t* number_of_sockets)
{
    *number_of_sockets              = 0;
    uint32_t number_of_sockets_temp = 0;

    if (ESMI_SUCCESS == esmi_number_of_sockets_get(&number_of_sockets_temp))
    {
        *number_of_sockets = number_of_sockets_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success, CpuNumSockets:%lu\n", (unsigned long)(*number_of_sockets));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_core_energy_get(uint32_t thread_index, uint64_t* core_energy)
{
    *core_energy              = 0;
    uint64_t core_energy_temp = 0;

    if(ESMI_SUCCESS == esmi_core_energy_get(thread_index, &core_energy_temp))
    {
        *core_energy = core_energy_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success for Thread:%d, CpuCoreEnergy:%llu, CpuCoreEnergyJoules:%.6f, CpuCoreEnergyKJoules:%.9f\n", thread_index, (unsigned long long)(*core_energy), ((double)(*core_energy))/1000000, ((double)(*core_energy))/1000000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_socket_energy_get(uint32_t socket_index, uint64_t* socket_energy)
{
    *socket_energy              = 0;
    uint64_t socket_energy_temp = 0;

    if(ESMI_SUCCESS == esmi_socket_energy_get(socket_index, &socket_energy_temp))
    {
        *socket_energy = socket_energy_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success for Socket:%d, CpuSocketEnergy:%llu, CpuSocketEnergyJoules:%.6f, CpuSocketEnergyKJoules:%.9f\n", socket_index, (unsigned long long)(*socket_energy), ((double)(*socket_energy))/1000000, ((double)(*socket_energy))/1000000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_prochot_status_get(uint32_t socket_index, uint32_t* prochot)
{
    *prochot               = 0;
    uint32_t prochot_temp  = 0;

    if(ESMI_SUCCESS == esmi_prochot_status_get(socket_index, &prochot_temp))
    {
        *prochot = prochot_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success for Socket:%d, CpuProchotStatus:%lu\n", socket_index, (unsigned long)(*prochot));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_socket_power_get(uint32_t socket_index, uint32_t* socket_power)
{
    *socket_power              = 0;
    uint32_t socket_power_temp = 0;

    if(ESMI_SUCCESS == esmi_socket_power_get(socket_index, &socket_power_temp))
    {
        *socket_power = socket_power_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success for Socket:%d, CpuSocketPower:%lu, CpuSocketPowerWatt:%.3f\n", socket_index, (unsigned long)(*socket_power), ((double)(*socket_power))/1000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_socket_power_cap_get(uint32_t socket_index, uint32_t* socket_power_cap)
{
    *socket_power_cap              = 0;
    uint32_t socket_power_cap_temp = 0;

    if(ESMI_SUCCESS == esmi_socket_power_cap_get(socket_index, &socket_power_cap_temp))
    {
        *socket_power_cap = socket_power_cap_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success for Socket:%d, CpuSocketPowerCap:%lu, CpuSocketPowerCapWatt:%.3f\n", socket_index, (unsigned long)(*socket_power_cap), ((double)(*socket_power_cap))/1000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_esmi_core_boostlimit_get(uint32_t thread_index, uint32_t* core_boostlimit)
{
    *core_boostlimit              = 0;
    uint32_t core_boostlimit_temp = 0;

    if(ESMI_SUCCESS == esmi_core_boostlimit_get(thread_index, &core_boostlimit_temp))
    {
        *core_boostlimit = core_boostlimit_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ESMI, Success for Thread:%d, CpuCoreBoostLimit:%lu\n", thread_index, (unsigned long)(*core_boostlimit));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}
#else
goamdsmi_status_t go_shim_esmi_init()									{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_threads_per_core_get(uint32_t* threads_per_core)				{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_number_of_threads_get(uint32_t* number_of_threads)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_number_of_sockets_get(uint32_t* number_of_sockets)			{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_core_energy_get(uint32_t thread_index, uint64_t* core_energy)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_socket_energy_get(uint32_t socket_index, uint64_t* socket_energy)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_prochot_status_get(uint32_t socket_index, uint32_t* prochot)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_socket_power_get(uint32_t socket_index, uint32_t* socket_power)		{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_socket_power_cap_get(uint32_t socket_index, uint32_t* socket_power_cap)	{return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_esmi_core_boostlimit_get(uint32_t thread_index, uint32_t* core_boostlimit)	{return GOAMDSMI_STATUS_FAILURE;}
#endif
