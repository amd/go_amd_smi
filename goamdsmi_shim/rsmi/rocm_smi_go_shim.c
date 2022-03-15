// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <rocm_smi.h>
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

