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
#include "goamdsmi.h"
/**
 *  @brief Go language stub to initialize the E-SMI library
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_esmi_init();

/**
 *  @brief Go stub to get the number of threads per core in the system
 *
 *  @param[in] ::uint32_t* Number of threads per core
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 */
goamdsmi_status_t go_shim_esmi_threads_per_core_get(uint32_t* threads_per_core);

/**
 *  @brief Go stub to get the number of threads available in the system
 *
 *  @param[in] ::uint32_t* Number of threads
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 */
goamdsmi_status_t go_shim_esmi_number_of_threads_get(uint32_t* number_of_threads);

/**
 *  @brief Go stub to get the total number of processor sockets
 *  available in the system
 *
 *  @param[in] ::uint32_t* value of num of cpu sockets
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 */
goamdsmi_status_t go_shim_esmi_number_of_sockets_get(uint32_t* number_of_sockets);

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
goamdsmi_status_t go_shim_esmi_core_energy_get(uint32_t num, uint64_t* core_energy);

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
goamdsmi_status_t go_shim_esmi_socket_energy_get(uint32_t socket_idx, uint64_t* socket_energy);

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
 *
 */
goamdsmi_status_t go_shim_esmi_prochot_status_get(uint32_t socket_idx, uint32_t* prochot);

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
goamdsmi_status_t go_shim_esmi_socket_power_get(uint32_t sock_ind, uint32_t* socket_power);

/**
 *  @brief Go language stub to get the current power cap value 
 *  for a given socket. 
 *
 *  @details This function will return the valid power cap @p pcap for a given
 *  socket @p sock_ind, this value will be used by the system to limit
 *  the power usage (in milliwatts).
 *
 *  @param[in] sock_ind a socket index
 *  @param[in] ::uint32_t* value of the socket power cap
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_esmi_socket_power_cap_get(uint32_t sock_ind, uint32_t* socket_power_cap);

/**
 *  @brief Go language stub to get the boostlimit value for a given core
 *
 *  @details This function will return the core's current boost limit
 *  @p boostlimit for a particular @p socket
 *
 *  @param[in] socket a socket index
 *  @param[in] ::uint32_t* value of the boostlimit
 *
 *  @retval GOAMDSMI_STATUS_SUCCESS is returned upon success.
 *  @retval GOAMDSMI_STATUS_FAILURE is returned upon failure.
 *
 */
goamdsmi_status_t go_shim_esmi_core_boostlimit_get(uint32_t socket, uint32_t* core_boostlimit);

