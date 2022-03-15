// SPDX-License-Identifier: MIT

/**
 *  @brief Go language stub to initialize the E-SMI library
 *
 *  @retval ::int32_t value of 1 upon success
 *  @retval Zero is returned upon failure.
 *
 */
int32_t go_shim_esmi_init();

/**
 *  @brief Go language stub to get the core energy for a given core
 *
 *  @details Given a core index @p num, this function will call the
 *  esmi_core_energy_get() function to update the @p penergy in micro Joules.
 *  This value is then passed as a uint64_t val to the Go routine that called it.
 *
 *  @param[in] num is the core index
 *
 *  @retval ::uint64_t value of the penergy in micro Joules.
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_esmi_core_energy_get(uint32_t num);

/**
 *  @brief Go language stub to get the socket energy for a given socket
 *
 *  @details Given a socket index @p socket_idx, this function will call the
 *  esmi_socket_energy_get() function to get the socket energy counter of an
 *  online cpu in that socket. This value is then passed as a uint64_t val to 
 *  the Go routine that called it.
 *
 *  @param[in] socket_idx is the socket index
 *
 *  @retval ::uint64_t value of the socket energy counter
 *  @retval zero is returned upon failure.
 *
 */
uint64_t go_shim_esmi_socket_energy_get(uint32_t socket_idx);

/**
 *  @brief Go language stub to get normalized status of 
 *  the processor's PROCHOT status.
 *  1 - PROCHOT active, 0 - PROCHOT inactive
 *
 *  @details Given a socket index @p socket_idx and this function will get
 *  PROCHOT at @p prochot.
 *
 *  @param[in] socket_idx a socket index
 *
 *  @retval ::uint32_t value of the prochot status
 *  @retval Zero is returned upon failure or if status is inactive.
 *
 */
uint32_t go_shim_esmi_prochot_status_get(uint32_t socket_idx);

/**
 *  @brief Go language stub to get the instantaneous power 
 *  consumption of the provided socket.
 *
 *  @details Given a socket index @p sock_ind this function will 
 *  get the current power consumption (in milliwatts).
 *
 *  @param[in] sock_ind a socket index
 *
 *  @retval ::uint32_t value of the socket power
 *  @retval Zero is returned upon failure.
 *
 */
uint32_t go_shim_esmi_socket_power_get(uint32_t sock_ind);

/**
 *  @brief Go language stub to get the current power cap value 
 *  for a given socket. 
 *
 *  @details This function will return the valid power cap @p pcap for a given
 *  socket @p sock_ind, this value will be used by the system to limit
 *  the power usage (in milliwatts).
 *
 *  @param[in] sock_ind a socket index
 *
 *  @retval ::uint32_t value of the socket power cap
 *  @retval Zero is returned upon failure.
 *
 */
uint32_t go_shim_esmi_socket_power_cap_get(uint32_t sock_ind);

/**
 *  @brief Go language stub to get the boostlimit value for a given core
 *
 *  @details This function will return the core's current boost limit
 *  @p boostlimit for a particular @p socket
 *
 *  @param[in] socket a socket index
 *
 *  @retval ::uint32_t value of the boostlimit
 *  @retval Zero is returned upon failure.
 *
 */
uint32_t go_shim_esmi_core_boostlimit_get(uint32_t socket);

/**
 *  @brief Go stub to get the number of threads per core in the system
 *
 *  @retval ::Number of threads per core
 *  @retval Zero is returned upon failure.
 */
int32_t go_shim_esmi_threads_per_core_get();

/**
 *  @brief Go stub to get the number of threads available in the system
 *
 *  @retval ::Number of threads
 *  @retval Zero is returned upon failure.
 */
int32_t go_shim_esmi_number_of_threads_get();

/**
 *  @brief Go stub to get the total number of processor sockets 
 *  available in the system
 *
 *  @retval ::int32_t value of the socket number
 *  @retval Zero is returned upon failure.
 */
int32_t go_shim_esmi_number_of_sockets_get();

