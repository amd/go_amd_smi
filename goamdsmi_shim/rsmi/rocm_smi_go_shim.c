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

int32_t go_shim_rsmi_num_monitor_devices()
{
	uint32_t num_monitor_devs = 0;

	if(RSMI_STATUS_SUCCESS == rsmi_num_monitor_devices(&num_monitor_devs))
		return num_monitor_devs;

	return 0;
}

uint16_t go_shim_rsmi_dev_id_get(uint32_t dv_ind)
{
	uint16_t id = 0;

	if(RSMI_STATUS_SUCCESS == rsmi_dev_id_get(dv_ind, &id))
		return id;

	return 0;
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
