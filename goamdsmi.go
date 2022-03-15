package goamdsmi

/*
#cgo CFLAGS: -Wall
#cgo LDFLAGS: -L/opt/goamdsmi/lib -lgoamdsmi_shim64 -Wl,--unresolved-symbols=ignore-in-object-files
#include <stdint.h>
#include "smi_go_shim.h"
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

