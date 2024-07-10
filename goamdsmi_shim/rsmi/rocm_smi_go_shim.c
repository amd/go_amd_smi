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
#include "rocm_smi_go_shim.h"
#ifdef ROCM_BUILD
#include <rocm_smi/rocm_smi.h>
#endif
#include <stdlib.h>
#define GPU_SENSOR_0 0
char powerTypesToString[3][30] = {"RSMI_AVERAGE_POWER", "RSMI_CURRENT_POWER", "RSMI_INVALID_POWER"};

#ifdef ROCM_BUILD
goamdsmi_status_t go_shim_rsmi_init()
{
    if(RSMI_STATUS_SUCCESS == rsmi_init(0))
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success, GpuInit:%d\n", GOAMDSMI_STATUS_SUCCESS);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_shutdown()
{
    if (RSMI_STATUS_SUCCESS == rsmi_shut_down())
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success, GpuShutdown:%d\n", GOAMDSMI_STATUS_SUCCESS);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_num_monitor_devices(uint32_t* gpu_num_monitor_devices)
{
    *gpu_num_monitor_devices              = 0;
    uint32_t gpu_num_monitor_devices_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_num_monitor_devices(&gpu_num_monitor_devices_temp))
    {
        *gpu_num_monitor_devices = gpu_num_monitor_devices_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success, GpuNumMonitorDevices:%d\n", *gpu_num_monitor_devices);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_name_get(uint32_t dv_ind, char** gpu_dev_name)
{
    uint32_t len = 256;
    char *dev_name = (char*)malloc(sizeof(char)*len);
    dev_name[0] = '\0';

    if(RSMI_STATUS_SUCCESS == rsmi_dev_name_get(dv_ind, dev_name, len))
    {
        *gpu_dev_name = dev_name;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuDevName:%s\n", dv_ind, *gpu_dev_name);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    free(dev_name);

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id)
{
    *gpu_dev_id              = 0;
    uint16_t gpu_dev_id_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_id_get(dv_ind, &gpu_dev_id_temp))
    {
        *gpu_dev_id = gpu_dev_id_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuDevId:%d\n", dv_ind, *gpu_dev_id);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id)
{
    *gpu_pci_id              = 0;
    uint64_t gpu_pci_id_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_pci_id_get(dv_ind, &gpu_pci_id_temp))
    {
        *gpu_pci_id = gpu_pci_id_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuPciId:%ld\n", dv_ind, (*gpu_pci_id));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;;
}

goamdsmi_status_t go_shim_rsmi_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name)
{
    uint32_t len = 256;
    char *vendor_name = (char*)malloc(sizeof(char)*len);
    vendor_name[0] = '\0';

    if(RSMI_STATUS_SUCCESS == rsmi_dev_vendor_name_get(dv_ind, vendor_name, len))
    {
        *gpu_vendor_name = vendor_name;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuVendorName:%s\n", dv_ind, *gpu_vendor_name);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    free(vendor_name);

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version)
{
    uint32_t len = 256;
    char *vbios_ver = (char*)malloc(sizeof(char)*len);
    vbios_ver[0] = '\0';

    if(RSMI_STATUS_SUCCESS == rsmi_dev_vbios_version_get(dv_ind, vbios_ver, len))
    {
        *vbios_version = vbios_ver;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuVbiosVersion:%s\n", dv_ind, *vbios_version);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    free(vbios_ver);

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap)
{
    *gpu_power_cap              = 0;
    uint64_t gpu_power_cap_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_power_cap_get(dv_ind, GPU_SENSOR_0, &gpu_power_cap_temp))
    {
        *gpu_power_cap = gpu_power_cap_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuPowerCap:%ld, GpuPowerCapInWatt:%.6f\n", dv_ind, (*gpu_power_cap), ((double)(*gpu_power_cap))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_power_get(uint32_t dv_ind, uint64_t* gpu_power)
{
    *gpu_power              = 0;
    uint64_t gpu_power_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_power_ave_get(dv_ind, GPU_SENSOR_0, &gpu_power_temp))
    {
        *gpu_power = gpu_power_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuPowerAverage:%ld, GpuPowerAverageinWatt:%.6f\n", dv_ind, (*gpu_power), ((double)(*gpu_power))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    RSMI_POWER_TYPE power_type = RSMI_INVALID_POWER;
    if(RSMI_STATUS_SUCCESS == rsmi_dev_power_get(dv_ind, &gpu_power_temp, &power_type))
    {
        *gpu_power = gpu_power_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d PowerType:%d, PowerTypeStr:%s, GpuPower:%ld, GpuPowerinWatt:%.6f\n", dv_ind, (int)power_type, powerTypesToString[power_type], (*gpu_power), ((double)(*gpu_power))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }
    else
    {
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Failed for Gpu:%d PowerType:%d, PowerTypeStr:%s, GpuPower:%ld, GpuPowerinWatt:%.6f\n", dv_ind, (int)power_type, powerTypesToString[power_type], (*gpu_power), ((double)(*gpu_power))/1000000);}
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature)
{
    *gpu_temperature              = 0;
    uint64_t gpu_temperature_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_temp_metric_get(dv_ind, sensor, metric, &gpu_temperature_temp))
    {
        *gpu_temperature = gpu_temperature_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d Sensor:%d Metric:%d, GpuTemperature:%ld, GpuTemperatureInDegree:%.3f\n", dv_ind, sensor, metric, (*gpu_temperature), ((double)(*gpu_temperature))/1000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level)
{
    *gpu_overdrive_level              = 0;
    uint32_t gpu_overdrive_level_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_overdrive_level_get(dv_ind, &gpu_overdrive_level_temp))
    {
        *gpu_overdrive_level = gpu_overdrive_level_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuOverdriveLevel:%d\n", dv_ind, *gpu_overdrive_level);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level)
{
    *gpu_mem_overdrive_level              = 0;
    uint32_t gpu_mem_overdrive_level_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_mem_overdrive_level_get(dv_ind, &gpu_mem_overdrive_level_temp))
    {
        *gpu_mem_overdrive_level = gpu_mem_overdrive_level_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuMemoryOverdriveLevel:%d\n", dv_ind, *gpu_mem_overdrive_level);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf)
{
    *gpu_perf                  = 0;
    rsmi_dev_perf_level_t perf = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_perf_level_get(dv_ind, &perf))
    {
        *gpu_perf = perf;                //Conversion from rsmi_dev_perf_level_t to uint32_t
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuPerfLevel:%d\n", dv_ind, *gpu_perf);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq)
{
    *gpu_sclk_freq           = 0;
    rsmi_frequencies_t freq  = {0};

    if(RSMI_STATUS_SUCCESS == rsmi_dev_gpu_clk_freq_get(dv_ind, RSMI_CLK_TYPE_SYS, &freq))
    {
        *gpu_sclk_freq = freq.frequency[freq.current];
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuSclkFreq:%ld, GpuSclkFreqMhz:%.6f\n", dv_ind, (*gpu_sclk_freq), ((double)(*gpu_sclk_freq))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq)
{
    *gpu_memclk_freq        = 0;
    rsmi_frequencies_t freq = {0};

    if(RSMI_STATUS_SUCCESS == rsmi_dev_gpu_clk_freq_get(dv_ind, RSMI_CLK_TYPE_MEM, &freq))
    {
        *gpu_memclk_freq = freq.frequency[freq.current];
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuMclkFreq:%ld, GpuMclkFreqMhz:%.6f\n", dv_ind, (*gpu_memclk_freq), ((double)(*gpu_memclk_freq))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk)
{
    *gpu_min_sclk            = 0;
    rsmi_od_volt_freq_data_t odv;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
    {
        *gpu_min_sclk = odv.curr_sclk_range.lower_bound;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuSclkMinfreq:%ld, GpuSclkMinfreqMhz:%.6f\n", dv_ind, (*gpu_min_sclk), ((double)(*gpu_min_sclk))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk)
{
    *gpu_min_memclk            = 0;
    rsmi_od_volt_freq_data_t odv;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
    {
        *gpu_min_memclk = odv.curr_mclk_range.lower_bound;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuMemclkMinfreq:%ld, GpuMemclkMinfreqMhz:%.6f\n", dv_ind, (*gpu_min_memclk), ((double)(*gpu_min_memclk))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk)
{
    *gpu_max_sclk            = 0;
    rsmi_od_volt_freq_data_t odv;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
    {
        *gpu_max_sclk = odv.curr_sclk_range.upper_bound;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuSclkMaxfreq:%ld, GpuSclkMaxfreqMhz:%.6f\n", dv_ind, (*gpu_max_sclk), ((double)(*gpu_max_sclk))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk)
{
    *gpu_max_memclk            = 0;
    rsmi_od_volt_freq_data_t odv;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
    {
        *gpu_max_memclk = odv.curr_mclk_range.upper_bound;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuMemclkMaxfreq:%ld, GpuMemclkMaxfreqMhz:%.6f\n", dv_ind, (*gpu_max_memclk), ((double)(*gpu_max_memclk))/1000000);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_busy_percent_get(uint32_t dv_ind, uint32_t* gpu_busy_percent)
{
    *gpu_busy_percent              = 0;
    uint32_t gpu_busy_percent_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_busy_percent_get(dv_ind, &gpu_busy_percent_temp))
    {
        *gpu_busy_percent = gpu_busy_percent_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuBusyPerc:%d\n", dv_ind, *gpu_busy_percent);}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent)
{
    *gpu_memory_busy_percent        = 0;
     uint64_t gpu_memory_usage_temp = 0;
     uint64_t gpu_memory_total_temp = 0;

    if( (RSMI_STATUS_SUCCESS == rsmi_dev_memory_usage_get(dv_ind, RSMI_MEM_TYPE_VRAM, &gpu_memory_usage_temp))&&
        (RSMI_STATUS_SUCCESS == rsmi_dev_memory_total_get(dv_ind, RSMI_MEM_TYPE_VRAM, &gpu_memory_total_temp)))
    {
        *gpu_memory_busy_percent = (uint64_t)(gpu_memory_usage_temp*100)/gpu_memory_total_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuMemoryBusyPerc:%ld\n", dv_ind, (*gpu_memory_busy_percent));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage)
{
    *gpu_memory_usage              = 0;
    uint64_t gpu_memory_usage_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_memory_usage_get(dv_ind, RSMI_MEM_TYPE_VRAM, &gpu_memory_usage_temp))
    {
        *gpu_memory_usage = (uint64_t)gpu_memory_usage_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuMemoryUsage:%ld\n", dv_ind, (*gpu_memory_usage));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}

goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total)
{
    *gpu_memory_total              = 0;
    uint64_t gpu_memory_total_temp = 0;

    if(RSMI_STATUS_SUCCESS == rsmi_dev_memory_total_get(dv_ind, RSMI_MEM_TYPE_VRAM, &gpu_memory_total_temp))
    {
        *gpu_memory_total = (uint64_t)gpu_memory_total_temp;
        if (enable_debug_level(GOAMDSMI_DEBUG_LEVEL_1)) {printf("ROCMSMI, Success for Gpu:%d, GpuMemoryTotal:%ld\n", dv_ind, (*gpu_memory_total));}
        return GOAMDSMI_STATUS_SUCCESS;
    }

    return GOAMDSMI_STATUS_FAILURE;
}
#else
goamdsmi_status_t go_shim_rsmi_init()                                                        {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_shutdown()                                                    {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_num_monitor_devices(uint32_t* gpu_num_monitor_devices)        {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_name_get(uint32_t dv_ind, char** gpu_dev_name)            {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id)             {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id)         {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name)  {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version)  {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap)   {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_power_get(uint32_t dv_ind, uint64_t* gpu_power)           {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature)    {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level)            {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level)    {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf)                            {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq)                {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq)              {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk)           {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk)         {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk)           {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk)         {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_busy_percent_get(uint32_t dv_ind, uint32_t* gpu_busy_percent)              {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent){return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage)              {return GOAMDSMI_STATUS_FAILURE;}
goamdsmi_status_t go_shim_rsmi_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total)              {return GOAMDSMI_STATUS_FAILURE;}
#endif
