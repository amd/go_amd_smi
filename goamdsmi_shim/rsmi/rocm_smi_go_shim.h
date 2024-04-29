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

/**
 *  @brief Go language stub to initialize the ROCm-SMI library
 *
 *  @retval ::int32_t value of 1 upon success
 *  @retval Zero is returned upon failure.
 *
 */
int32_t go_shim_rsmi_init();

/**
 *  @brief Go language stub to shut down the ROCm-SMI library
 *  and do necessary clean up
 *
 *  @retval ::int32_t value of 1 upon success
 *  @retval Zero is returned upon failure.
 *
 */
int32_t go_shim_rsmi_shutdown();

/**
 *  @brief Go language stub to get the number of GPU devices
 *
 *  @details This function will call the rsmi_num_monitor_devices()
 *  function to return the number of GPU devices to be monitored.
 *  This value is then passed as a uint val to the Go routine that
 *  called it.
 *
 *  @param[in] ::
 *
 *  @retval ::uint value of num GPUs
 *  @retval zero is returned upon failure.
 *
 */
int32_t go_shim_rsmi_num_monitor_devices();

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
 *
 *  @retval ::char* VBIOS identifier
 *  @retval NULL is returned upon failure.
 *
 */
char* go_shim_rsmi_dev_name_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU device id
 *
 *  @details This function will call the rsmi_dev_id_get()
 *  function to return the GPU device id. This value is then
 *  passed as a uint16_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint16_t value of num GPUs
 *  @retval zero is returned upon failure.
 *
 */
uint16_t go_shim_rsmi_dev_id_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU unique pci id
 *
 *  @details This function will call the rsmi_dev_pci_id_get()
 *  function to return the unique PCI device identifier
 *  associated for a device. This value is then passed as
 *  a uint64_t val to the Go routine that called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint64_t value of pci id
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_pci_id_get(uint32_t dv_ind);

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
 *  @param[in] ::char* vbios buffer of length
 *
 *  @retval ::char* VBIOS identifier
 *  @retval NULL is returned upon failure
 *
 */
char* go_shim_rsmi_dev_vbios_version_get(uint32_t dv_ind);

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
 *
 *  @retval ::uint16_t value of subsystem id
 *  @retval NULL is returned upon failure.
 *
 */
char* go_shim_rsmi_dev_vendor_name_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU power cap
 *
 *  @details This function will call the rsmi_dev_power_cap_get()
 *  function to return the gpu power cap. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint64_t GPU power cap
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_power_cap_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU power average
 *
 *  @details This function will call the rsmi_dev_power_ave_get()
 *  function to return the gpu power average. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint64_t GPU power average
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_power_ave_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU current temperature
 *
 *  @details This function will call the rsmi_dev_temp_metric_get()
 *  function to return the gpu current temperature. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, uint32_t sensor, uint32_t metric
 *
 *  @retval ::uint64_t GPU current temperature
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_temp_metric_get(uint32_t dv_ind, uint32_t sensor, uint32_t metric);

/**
 *  @brief Go language stub to get the overdrive level of the device
 *
 *  @details This function will call the rsmi_dev_overdrive_level_get()
 *  function to return the overdrive percentage. This value is then
 *  passed as a uint32_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint32_t overdrive level
 *  @retval zero is returned upon failure.
 *
 */
uint32_t go_shim_rsmi_dev_overdrive_level_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the memory overdrive level of the device
 *
 *  @details This function will call the rsmi_dev_mem_overdrive_level_get()
 *  function to return the memory overdrive percentage. This value is then
 *  passed as a uint32_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint32_t memory overdrive level
 *  @retval zero is returned upon failure.
 *
 */
uint32_t go_shim_rsmi_dev_mem_overdrive_level_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the performance level of the device
 *
 *  @details This function will call the rsmi_dev_perf_level_get()
 *  function to return the  rsmi_dev_perf_level_t. This value is then
 *  passed as a uint32_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint32_t performance level (rsmi_dev_perf_level_t)
 *  @retval zero is returned upon failure.
 *
 */
uint32_t go_shim_rsmi_dev_perf_level_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU SCLK limit
 *
 *  @details This function will call the rsmi_dev_gpu_clk_freq_get()
 *  function to return the gpu SCLK Limit. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::uint64_t GPU SCLK Limit
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_gpu_clk_freq_get_sclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU MCLK limit
 *
 *  @details This function will call the rsmi_dev_gpu_clk_freq_get()
 *  function to return the gpu MCLK Limit. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::uint64_t GPU MCLK Limit
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_gpu_clk_freq_get_mclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the minimum supported SCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the minium supported SCLK frequency.
 *  This value is then passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint64_t mimimum supported sclk frequency
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_od_volt_freq_range_min_get_sclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the minimum supported MCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the minium supported MCLK frequency.
 *  This value is then passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint64_t mimimum supported mclk sfrequency
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_od_volt_freq_range_min_get_mclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the maximum supported SCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the maxium supported SCLK frequency.
 *  This value is then passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint64_t maximum supported sclk frequency
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_od_volt_freq_range_max_get_sclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the maximum supported MCLK frequency
 *
 *  @details This function will call the rsmi_od_volt_freq_data_get()
 *  function to return the maxium supported MCLK frequency.
 *  This value is then passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index
 *
 *  @retval ::uint64_t maximum supported mclk sfrequency
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_od_volt_freq_range_max_get_mclk(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU Activity
 *
 *  @details This function will call the rsmi_dev_gpu_activity_get()
 *  function to return the current GPU use. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::uint64_t GPU Activity use
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_gpu_busy_percent_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU Memory Use percent
 *
 *  @details This function will call the rsmi_dev_memory_busy_percent_get()
 *  function to return the current device memory use percent. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::uint64_t GPU memory use percent
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_gpu_memory_busy_percent_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the GPU Memory Usage
 *
 *  @details This function will call the rsmi_dev_memory_usage_get()
 *  function to return the amount of memory currently being used. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::uint64_t GPU memory usage
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_gpu_memory_usage_get(uint32_t dv_ind);

/**
 *  @brief Go language stub to get the Total amount of GPU Memory
 *
 *  @details This function will call the rsmi_dev_memory_total_get()
 *  function to return the total amount of memory. This value is then
 *  passed as a uint64_t val to the Go routine that
 *  called it.
 *
 *  @param[in] ::uint32_t device index, flag, ptr to rsmi_frequencies_t
 *
 *  @retval ::uint64_t Total GPU memory
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_rsmi_dev_gpu_memory_total_get(uint32_t dv_ind);


