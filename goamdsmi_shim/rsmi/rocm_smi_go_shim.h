// SPDX-License-Identifier: MIT

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

