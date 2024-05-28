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
#include <rocm_smi/rocm_smi.h>
#include "rocm_smi_go_shim.h"

int32_t go_shim_rsmi_init()
{
	return (RSMI_STATUS_SUCCESS == rsmi_init(0)) ? 1 : 0;
}

int32_t go_shim_rsmi_shutdown()
{
        return (RSMI_STATUS_SUCCESS == rsmi_shut_down()) ? 1 : 0;
}

int32_t go_shim_rsmi_num_monitor_devices()
{
	uint32_t num_monitor_devs = 0;

	if(RSMI_STATUS_SUCCESS == rsmi_num_monitor_devices(&num_monitor_devs))
		return num_monitor_devs;

	return 0;
}

char* go_shim_rsmi_dev_name_get(uint32_t dv_ind)
{
        uint32_t len = 256;
        char *dev_name = (char*)malloc(sizeof(char)*len);
        dev_name[0] = '\0';

        if(RSMI_STATUS_SUCCESS == rsmi_dev_name_get(dv_ind, dev_name, &len))
        {
                return dev_name;
        }

        return NULL;
}

uint16_t go_shim_rsmi_dev_id_get(uint32_t dv_ind)
{
	uint16_t id = 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_id_get(dv_ind, &id))
		return id;

	return 0;
}

uint64_t go_shim_rsmi_dev_pci_id_get(uint32_t dv_ind)
{
        uint64_t id = 0;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_pci_id_get(dv_ind, &id))
                return id;

        return 0;
}

char* go_shim_rsmi_dev_vendor_name_get(uint32_t dv_ind)
{
        uint32_t len = 256;
        char *vendor_name = (char*)malloc(sizeof(char)*len);
        vendor_name[0] = '\0';

        if(RSMI_STATUS_SUCCESS == rsmi_dev_vendor_name_get(dv_ind, vendor_name, &len))
                return vendor_name;

        return NULL;
}

char* go_shim_rsmi_dev_vbios_version_get(uint32_t dv_ind)
{
        uint32_t len = 256;
        char *vbios_ver = (char*)malloc(sizeof(char)*len);
        vbios_ver[0] = '\0';

        if(RSMI_STATUS_SUCCESS == rsmi_dev_vbios_version_get(dv_ind, vbios_ver, &len))
        {
                return vbios_ver;
        }

        return NULL;
}

uint64_t go_shim_rsmi_dev_power_cap_get(uint32_t dv_ind)
{
	uint64_t power_cap = 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_power_cap_get(dv_ind, 0, &power_cap))
		return power_cap;

	return 0;
}

uint64_t go_shim_rsmi_dev_power_ave_get(uint32_t dv_ind)
{
	uint64_t power_ave = 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_power_ave_get(dv_ind, 0, &power_ave))
		return power_ave;

	return 0;
}

uint64_t go_shim_rsmi_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric)
{
	uint64_t temperature = 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_temp_metric_get(dv_ind, sensor, metric, &temperature))
		return temperature;

	return 0;
}

uint32_t go_shim_rsmi_dev_overdrive_level_get(uint32_t dv_ind)
{
        uint32_t od;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_overdrive_level_get(dv_ind, &od))
                return od;

        return 0;
}

uint32_t go_shim_rsmi_dev_mem_overdrive_level_get(uint32_t dv_ind)
{
        uint32_t od;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_mem_overdrive_level_get(dv_ind, &od))
                return od;

        return 0;
}

uint32_t go_shim_rsmi_dev_perf_level_get(uint32_t dv_ind)
{
        rsmi_dev_perf_level_t perf;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_perf_level_get(dv_ind, &perf))
                return perf;

        return 0;
}

uint64_t go_shim_rsmi_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind)
{
	rsmi_frequencies_t freq;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_gpu_clk_freq_get(dv_ind, RSMI_CLK_TYPE_SYS, &freq))
		return freq.frequency[freq.current];

	return 0;
}

uint64_t go_shim_rsmi_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind)
{
	rsmi_frequencies_t freq;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_gpu_clk_freq_get(dv_ind, RSMI_CLK_TYPE_MEM, &freq))
		return freq.frequency[freq.current];

	return 0;
}

uint64_t go_shim_rsmi_od_volt_freq_range_min_get_sclk(uint32_t dv_ind)
{
        rsmi_od_volt_freq_data_t odv;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
                return odv.curr_sclk_range.lower_bound;

        return 0;
}

uint64_t go_shim_rsmi_od_volt_freq_range_min_get_mclk(uint32_t dv_ind)
{
        rsmi_od_volt_freq_data_t odv;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
                return odv.curr_mclk_range.lower_bound;

        return 0;
}

uint64_t go_shim_rsmi_od_volt_freq_range_max_get_sclk(uint32_t dv_ind)
{
        rsmi_od_volt_freq_data_t odv;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
                return odv.curr_sclk_range.upper_bound;

        return 0;
}

uint64_t go_shim_rsmi_od_volt_freq_range_max_get_mclk(uint32_t dv_ind)
{
        rsmi_od_volt_freq_data_t odv;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_od_volt_info_get(dv_ind, &odv))
                return odv.curr_mclk_range.upper_bound;

        return 0;
}

uint64_t go_shim_rsmi_dev_gpu_busy_percent_get(uint32_t dv_ind)
{
	 uint64_t usage = 0;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_busy_percent_get(dv_ind, &usage))
                return usage;

        return 0;
}


uint64_t go_shim_rsmi_dev_gpu_memory_busy_percent_get(uint32_t dv_ind)
{
         uint64_t usage = 0;
	 uint64_t total = 0;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_memory_usage_get(dv_ind, RSMI_MEM_TYPE_VRAM, &usage) && 
	   RSMI_STATUS_SUCCESS == rsmi_dev_memory_total_get(dv_ind, RSMI_MEM_TYPE_VRAM, &total))
		return (uint64_t)(usage*100)/total;

	return 0;
}

uint64_t go_shim_rsmi_dev_gpu_memory_usage_get(uint32_t dv_ind)
{
        uint64_t usage = 0;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_memory_usage_get(dv_ind, RSMI_MEM_TYPE_VRAM, &usage))
                return (uint64_t)usage;

        return 0;
}

uint64_t go_shim_rsmi_dev_gpu_memory_total_get(uint32_t dv_ind)
{
        uint64_t total = 0;

        if(RSMI_STATUS_SUCCESS == rsmi_dev_memory_total_get(dv_ind, RSMI_MEM_TYPE_VRAM, &total))
                return (uint64_t)total;

        return 0;
}

