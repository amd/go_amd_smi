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

#include "goamdsmi.h"
////////////////////////////////////////////////------------CPU------------////////////////////////////////////////////////
/**
 *  @brief Go language stub to initialize the AMDSMI library
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmicpu_init();

/**
 *  @brief Go language stub to get the core energy for a given core
 *
 *  @details Given a core index @p num, this function will call the
 *  esmi_core_energy_get() function to update the @p penergy in micro Joules.
 *  This value is then passed as a uint64_t val to the Go routine that called it.
 *
 *  @param[in] num is the core index
 *  @param[in] ::uint64_t* value of the penergy in micro Joules.
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmicpu_core_energy_get(uint32_t num, uint64_t* core_energy);

/**
 *  @brief Go language stub to get the socket energy for a given socket
 *
 *  @details Given a socket index @p socket_idx, this function will call the
 *  esmi_socket_energy_get() function to get the socket energy counter of an
 *  online cpu in that socket. This value is then passed as a uint64_t val to 
 *  the Go routine that called it.
 *
 *  @param[in] socket_idx is the socket index
 *  @param[in] ::uint64_t* value of the socket energy counter
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmicpu_socket_energy_get(uint32_t socket_idx, uint64_t* socket_energy);

/**
 *  @brief Go language stub to get normalized status of 
 *  the processor's PROCHOT status.
 *  1 - PROCHOT active, 0 - PROCHOT inactive
 *
 *  @details Given a socket index @p socket_idx and this function will get
 *  PROCHOT at @p prochot.
 *
 *  @param[in] socket_idx a socket index
 *  @param[in] ::uint32_t* value of the prochot status
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmicpu_prochot_status_get(uint32_t socket_idx, uint32_t* prochot);

/**
 *  @brief Go language stub to get the instantaneous power 
 *  consumption of the provided socket.
 *
 *  @details Given a socket index @p sock_ind this function will 
 *  get the current power consumption (in milliwatts).
 *
 *  @param[in] sock_ind a socket index
 *  @param[in] ::uint32_t* value of the socket power
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmicpu_socket_power_get(uint32_t sock_ind, uint32_t* socket_power);

/**
 *  @brief Go language stub to get the current power cap value 
 *  for a given socket. 
 *
 *  @details This function will return the valid power cap @p pcap for a given
 *  socket @p sock_ind, this value will be used by the system to limit
 *  the power usage (in milliwatts).
 *
 *  @param[in] socket index
 *  @param[in] ::uint32_t* value of the socket power cap
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmicpu_socket_power_cap_get(uint32_t sock_ind, uint32_t* socket_power_cap);

/**
 *  @brief Go language stub to get the boostlimit value for a given core
 *
 *  @details This function will return the core's current boost limit
 *  @p boostlimit for a particular @p socket
 *
 *  @param[in] socket index
 *  @param[in] ::uint32_t* value of the boostlimit
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmicpu_core_boostlimit_get(uint32_t socket, uint32_t* core_boostlimit);

/**
 *  @brief Go stub to get the number of threads per core in the system
 *
 *  @param[in] ::uint32_t* Number of threads per core
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 */
goamdsmi_status_t go_shim_amdsmicpu_threads_per_core_get(uint32_t* threads_per_core);

/**
 *  @brief Go stub to get the number of threads available in the system
 *
 *  @param[in] ::uint32_t* Number of threads
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 */
goamdsmi_status_t go_shim_amdsmicpu_number_of_threads_get(uint32_t* number_of_threads);

/**
 *  @brief Go stub to get the total number of processor sockets 
 *  available in the system
 *
 *  @param[in] ::uint32_t* value of num of cpu sockets
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 */
goamdsmi_status_t go_shim_amdsmicpu_number_of_sockets_get(uint32_t* number_of_sockets);

////////////////////////////////////////////////------------GPU------------////////////////////////////////////////////////
/**
 *  @brief Go language stub to initialize the ROCm-SMI library
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_init();

/**
 *  @brief Go language stub to shut down the ROCm-SMI library
 *  and do necessary clean up
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_shutdown();

/**
 *  @brief Go language stub to get the number of GPU devices
 *
 *  @details This function will call the rsmi_num_monitor_devices()
 *  function to return the number of GPU devices to be monitored.
 *  This value is then passed as a uint val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t* value of num GPUs
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_num_monitor_devices(uint32_t* gpu_num_monitor_devices);

/**
 *  @brief Go language stub to get the gpu device name string
 *
 *  @details This function will call the rsmi_dev_name_get()
 *  function to write the gpu device name string (up to len characters)
 *  for device dv_ind and return a char pointer. This value is then
 *  passed as char * to the Go routine that called it. The caller of this
 *  function must free the allocated buffer for the device name.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::char** value of gpu device name
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_name_get(uint32_t dv_ind, char** gpu_dev_name);

/**
 *  @brief Go language stub to get the GPU device id
 *
 *  @details This function will call the rsmi_dev_id_get()
 *  function to return the GPU device id. This value is then
 *  passed as a uint16_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint16_t* value of gpu deviceID
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_id_get(uint32_t dv_ind, uint16_t* gpu_dev_id);

/**
 *  @brief Go language stub to get the GPU unique pci id
 *
 *  @details This function will call the rsmi_dev_pci_id_get()
 *  function to return the unique PCI device identifier
 *  associated for a device. This value is then passed as
 *  a uint64_t val to the Go routine that called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint64_t* value of pci id
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_pci_id_get(uint32_t dv_ind, uint64_t* gpu_pci_id);

/**
 *  @brief Go language stub to get the VBIOS identifier string
 *
 *  @details This function will call the rsmi_dev_vbios_ver_get()
 *  function to write the VBIOS char array (up to len characters)
 *  for device dv_ind and return a char pointer. This value is then
 *  passed as char pointer to the Go routine that called it. The caller
 *  of this funcion must free the allocated buffer for the vbios
 *  identifier
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::char** GPU vendor name
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_vbios_version_get(uint32_t dv_ind, char** vbios_version);

/**
 *  @brief Go language stub to get the vendor
 *
 *  @details This function will call the rsmi_dev_vendor_name_get()
 *  function to write the name of the vendor char array (up to len
 *  characters) for a device dv_ind and return a char pointer. This
 *  value is then passed as a char pointer to the Go routine that
 *  called it. The caller of this funcion must free the allocated
 *  buffer for the vbios identifier
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::char** GPU vendor name
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_vendor_name_get(uint32_t dv_ind, char** gpu_vendor_name);

/**
 *  @brief Go language stub to get the GPU power cap
 *
 *  @details This function will call the rsmi_dev_power_cap_get()
 *  function to return the gpu power cap. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint64_t* GPU power cap
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_power_cap_get(uint32_t dv_ind, uint64_t* gpu_power_cap);

/**
 *  @brief Go language stub to get the GPU power
 *
 *  @details This function will call the rsmi_dev_power_get()
 *  function to return the gpu power. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint64_t* GPU power
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_power_get(uint32_t dv_ind, uint64_t* gpu_power);

/**
 *  @brief Go language stub to get the GPU current temperature
 *
 *  @details This function will call the rsmi_dev_temp_metric_get()
 *  function to return the gpu current temperature. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, uint32_t sensor, uint32_t metric
 *  @param[in] ::uint64_t* GPU current temperature
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric, uint64_t* gpu_temperature);

/**
 *  @brief Go language stub to get the overdrive level of the device
 *
 *  @details This function will call the rsmi_dev_overdrive_level_get()
 *  function to return the overdrive percentage. This value is then
 *  passed as a uint32_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint32_t* overdrive level
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_overdrive_level);

/**
 *  @brief Go language stub to get the memory overdrive level of the device
 *
 *  @details This function will call the rsmi_dev_mem_overdrive_level_get()
 *  function to return the memory overdrive percentage. This value is then
 *  passed as a uint32_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint32_t* memory overdrive level
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_mem_overdrive_level_get(uint32_t dv_ind, uint32_t* gpu_mem_overdrive_level);

/**
 *  @brief Go language stub to get the performance level of the device
 *
 *  @details This function will call the rsmi_dev_perf_level_get()
 *  function to return the  rsmi_dev_perf_level_t. This value is then
 *  passed as a uint32_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint32_t* performance level (rsmi_dev_perf_level_t)
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_perf_level_get(uint32_t dv_ind, uint32_t *gpu_perf);

/**
 *  @brief Go language stub to get the GPU SCLK limit
 *
 *  @details This function will call the rsmi_dev_gpu_clk_freq_get()
 *  function to return the gpu SCLK Limit. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *  @param[in] ::uint64_t* GPU SCLK Limit
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind, uint64_t* gpu_sclk_freq);

/**
 *  @brief Go language stub to get the GPU MCLK limit
 *
 *  @details This function will call the rsmi_dev_gpu_clk_freq_get()
 *  function to return the gpu MCLK Limit. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *  @param[in] ::uint64_t* GPU MCLK Limit
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind, uint64_t* gpu_memclk_freq);

/**
 *  @brief Go language stub to get the minimum supported SCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the minium supported SCLK frequency.
 *  This value is then passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint64_t* mimimum supported sclk frequency
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_sclk(uint32_t dv_ind, uint64_t* gpu_min_sclk);

/**
 *  @brief Go language stub to get the minimum supported MCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the minium supported MCLK frequency.
 *  This value is then passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint64_t* mimimum supported mclk sfrequency
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_min_get_mclk(uint32_t dv_ind, uint64_t* gpu_min_memclk);

/**
 *  @brief Go language stub to get the maximum supported SCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the maxium supported SCLK frequency.
 *  This value is then passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint64_t* maximum supported sclk frequency
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_sclk(uint32_t dv_ind, uint64_t* gpu_max_sclk);

/**
 *  @brief Go language stub to get the maximum supported MCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the maxium supported MCLK frequency.
 *  This value is then passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *  @param[in] ::uint64_t* maximum supported mclk sfrequency
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_od_volt_freq_range_max_get_mclk(uint32_t dv_ind, uint64_t* gpu_max_memclk);

/**
 *  @brief Go language stub to get the GPU Activity
 *
 *  @details This function will call the rsmi_dev_gpu_activity_get()
 *  function to return the current GPU use. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *  @param[in] ::uint64_t* GPU Activity use
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_busy_percent_get(uint32_t dv_ind, uint32_t* gpu_busy_percent);

/**
 *  @brief Go language stub to get the GPU Memory Use percent
 *
 *  @details This function will call the rsmi_dev_memory_busy_percent_get()
 *  function to return the current device memory use percent. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *  @param[in] ::uint64_t* GPU memory use percent
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_busy_percent_get(uint32_t dv_ind, uint64_t* gpu_memory_busy_percent);

/**
 *  @brief Go language stub to get the GPU Memory Usage
 *
 *  @details This function will call the rsmi_dev_memory_usage_get()
 *  function to return the amount of memory currently being used. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t  device index, flag, ptr to rsmi_frequencies_t
 *  @param[in] ::uint64_t* GPU memory usage
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_usage_get(uint32_t dv_ind, uint64_t* gpu_memory_usage);

/**
 *  @brief Go language stub to get the Total amount of GPU Memory
 *
 *  @details This function will call the rsmi_dev_memory_total_get()
 *  function to return the total amount of memory. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *  @param[in] ::uint64_t* Total GPU memory
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_amdsmigpu_dev_gpu_memory_total_get(uint32_t dv_ind, uint64_t* gpu_memory_total);
