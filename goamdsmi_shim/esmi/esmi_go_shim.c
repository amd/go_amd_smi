// SPDX-License-Identifier: MIT

#include <stdint.h>
#include <e_smi.h>
#include "esmi_go_shim.h"

int32_t go_shim_esmi_init()
{
	return (ESMI_SUCCESS == esmi_init()) ? 1 : 0;
}

int32_t go_shim_esmi_threads_per_core_get()
{
	uint32_t num_threads_per_core;

	if(ESMI_SUCCESS == esmi_threads_per_core_get(&num_threads_per_core))
		return num_threads_per_core;

	return 0;
}

int32_t go_shim_esmi_number_of_threads_get()
{
	uint32_t total_num_threads;

	if(ESMI_SUCCESS ==  esmi_number_of_cpus_get(&total_num_threads))
		return total_num_threads;

	return 0;
}

int32_t go_shim_esmi_number_of_sockets_get()
{
	uint32_t num_sockets;

	if (ESMI_SUCCESS == esmi_number_of_sockets_get(&num_sockets))
		return num_sockets;

       	 return 0;
}

uint64_t go_shim_esmi_core_energy_get(uint32_t thread_index)
{
	uint64_t core_penergy = 0;

	if(ESMI_SUCCESS == esmi_core_energy_get(thread_index, &core_penergy))
		return core_penergy;

	return 0;
}

uint64_t go_shim_esmi_socket_energy_get(uint32_t socket_index)
{
	uint64_t socket_penergy = 0;

	if(ESMI_SUCCESS == esmi_socket_energy_get(socket_index, &socket_penergy))
		return socket_penergy;

	return 0;
}

uint32_t go_shim_esmi_prochot_status_get(uint32_t socket_index)
{
	uint32_t prochot;

	if(ESMI_SUCCESS == esmi_prochot_status_get(socket_index, &prochot))
		return prochot;

 	return 0;
}

uint32_t go_shim_esmi_socket_power_get(uint32_t socket_index)
{
	uint32_t ppower;

	if(ESMI_SUCCESS == esmi_socket_power_get(socket_index, &ppower))
		return ppower;

	return 0;
}

uint32_t go_shim_esmi_socket_power_cap_get(uint32_t socket_index)
{
	uint32_t pcap;

	if(ESMI_SUCCESS == esmi_socket_power_cap_get(socket_index, &pcap))
		return pcap;

	return 0;
}

uint32_t go_shim_esmi_core_boostlimit_get(uint32_t thread_index)
{
	uint32_t boostlimit = 0;

	if(ESMI_SUCCESS == esmi_core_boostlimit_get(thread_index, &boostlimit))
		return boostlimit;

	return 0;
}

