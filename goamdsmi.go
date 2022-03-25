/*
 * MIT-X11 Open Source License
 *
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
package goamdsmi

/*
#cgo CFLAGS: -Wall -I/opt/goamdsmi/include
#cgo LDFLAGS: -L/opt/goamdsmi/lib -lgoamdsmi_shim64 -Wl,--unresolved-symbols=ignore-in-object-files
#include <stdint.h>
#include <esmi_go_shim.h>
#include <rocm_smi_go_shim.h>
*/
import "C"

func GO_rsmi_init() (uint) {
	return uint(C.go_shim_rsmi_init())
}

func GO_rsmi_num_monitor_devices() (uint) {
	return uint(C.go_shim_rsmi_num_monitor_devices())
}

func GO_rsmi_dev_id_get(i int) (C.uint16_t) {
	return C.uint16_t(C.go_shim_rsmi_dev_id_get(C.uint(i)))
}

func GO_rsmi_dev_power_cap_get(i int) (C.uint64_t) {
	return C.go_shim_rsmi_dev_power_cap_get(C.uint(i))
}

func GO_rsmi_dev_power_ave_get(i int) (C.uint64_t) {
	return C.go_shim_rsmi_dev_power_ave_get(C.uint(i))
}

func GO_rsmi_dev_temp_metric_get(i int, sensor int, metric int) (C.uint64_t) {
	return C.go_shim_rsmi_dev_temp_metric_get(C.uint(i), C.uint(sensor), C.uint(metric))
}

func GO_esmi_init() (uint) {
	return uint(C.go_shim_esmi_init())
}

func GO_esmi_number_of_sockets_get() (uint) {
	return uint(C.go_shim_esmi_number_of_sockets_get())
}

func GO_esmi_number_of_threads_get() (uint) {
	return uint(C.go_shim_esmi_number_of_threads_get())
}

func GO_esmi_threads_per_core_get() (uint) {
	return uint(C.go_shim_esmi_threads_per_core_get())
}

func GO_esmi_core_energy_get(i int) (C.uint64_t) {
	return C.go_shim_esmi_core_energy_get(C.uint(i))
}

func GO_esmi_core_boostlimit_get(i int) (C.uint32_t) {
	return C.go_shim_esmi_core_boostlimit_get(C.uint(i))
}

func GO_esmi_socket_energy_get(i int) (C.uint64_t) {
	return C.go_shim_esmi_socket_energy_get(C.uint(i))
}

func GO_esmi_socket_power_get(i int) (C.uint32_t) {
	return C.go_shim_esmi_socket_power_get(C.uint(i))
}

func GO_esmi_socket_power_cap_get(i int) (C.uint32_t) {
	return C.go_shim_esmi_socket_power_cap_get(C.uint(i))
}

func GO_esmi_prochot_status_get(i int) (C.uint32_t) {
	return C.go_shim_esmi_prochot_status_get(C.uint(i))
}

