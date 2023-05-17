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

