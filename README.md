1. [GO AMD SMI Binding](#desc)
2. [Importing the GO SMI Binding](#import)
3. [GO APIs exported by the GO SMI Binding](#api)
4. [The goamdsmi_shmi library](#shim)
5. [Building the goamdsmi_shim library](#build_shim)
6. [Example Code](#example)

<a name="desc"></a>
# GO AMD SMI (WIP)

GO AMD SMI provides GO binding for [E-SMI In-Band C library](https://github.com/amd/esmi_ib_library.git),
[ROCm SMI Library](https://github.com/RadeonOpenCompute/rocm_smi_lib.git), and any
GO language application that needs to link with these libraries and call the APIs
from the GO application. The GO binding are imported in the
[AMD SMI Exporter](https://github.com/amd/amd_smi_exporter.git) to export information
provided by the AMD E-SMI inband library and the ROCm SMI GPU library to the Prometheus server.

## Important note about Versioning and Backward Compatibility
The GO AMD SMI Binding follows the E-SMI In-band library and the ROCm library in its releases,
as it is dependent on the underlying libraries for its data. The binding is currently under
development, and therefore subject to change.

While every effort will be made to ensure stable backward compatibility in software releases with
a major version greater than 0, any code/interface may be subject to rivision/change while the
major version remains 0.

## Downloading the code

The GO SMI Binding code may be downloaded from:

	<https://github.com/amd/go_amd_smi.git>

This repository contains the go binding and the goamdsmi_shim library code requires the dependent
libraries esmi in-band and rocm_smi libraries to be installed on the system.

<a name="import"></a>
# Importing the GO SMI Binding in your code

The GO SMI binding may be imported into go code by adding the following import line:

	```import "github.com/amd/goamdsmi"```

** NOTE: ** The GO SMI binding depends on the following libraries:

	- E-SMI inband library ("https://github.com/amd/esmi_ib_library")
	- ROCm SMI library("https://github.com/RadeonOpenCompute/rocm_smi_lib")
	- goamdsmi_shim library ("https://github.com/amd/goamdsmi/goamdsmi_shim")

for linkage, and the libraries are expected to be installed in the 
**"/opt/e-sms/e_smi/lib",
  "/opt/rocm/lib", and
  "/opt/goamdsmi/lib"**
directories respectively by default, or subject to config changes applied to the library path.
Please refer to the README.md of the E-SMI and ROCm SMI repositories for build and installation
 instructions. The following header file(s) are included in this repository:

	* ```esmi_go_shim.h```
	* ```rocm_smi_go_shim.h```

<a name="shim"></a>
# The goamdsmi_shim library

The goamdsmi_shim is the wrapper library over the AMD E_SMI and ROCm library APIs. This shim
library provides entry points to the goamdsmi GO language binding. This library code is built
independently into a shared library that has a dependency on the E-SMI and ROCm libraries.

<a name="build_shim"></a>
# Building the goamdsmi_shim library

## Additional Required software for building
In order to build the goamdsmi_shim library, the following components are required. Note that the
software versions listed are what is being used in development. Earlier versions are not guaranteed
to work:
* CMake (v3.5.0)

Building the library is achieved by following the typical CMake build sequence, as follows.
#### ```$ cd goamdsmi_shim```
#### ```$ mkdir -p build```
#### ```$ cd build```
#### ```$ cmake -C ../amd_smi.cmake ../```
#### ```$ make```
The built library will appear in the `build` folder.

#### ```# Install library file and header; default location is /opt/goamdsmi/```
#### ```$ sudo make install```

** NOTE: ** The below combinations useful for compilation as per user requirement:
#### ```$ cmake -C ../amd_smi.cmake ../```
#### ```# The '-C' option will pick default -DWITH_ESMI=ON -DWITH_ROCM_SMI=ON```
#### ```(or)```
#### ```$ cmake ../amd_smi.cmake ../```
#### ```# The above command will pick default -DWITH_ESMI=OFF -DWITH_ROCM_SMI=ON```
#### ```(or)```
#### ```$ cmake -DWITH_ESMI=ON  -DWITH_ROCM_SMI=OFF ../amd_smi.cmake ../```
#### ```The command useful if user needs to build as per the requirement```

<a name="api"></a>
# GO APIs exported by the GO SMI Binding

## GO_rsmi_init()
	### Input: none
	### Return: uint status where ZERO is a failure

## GO_rsmi_num_monitor_devices()
	### Input: none
	### Return: uint value of number of GPU devices. ZERO is a failure

## GO_rsmi_dev_id_get()
	### Input: none
	### Return: uint value of GPU dev id.  ZERO is a failure

## GO_rsmi_dev_power_cap_get()
	### Input: int value of dev index
	### Return: uint64_t value of power cap. ZERO is a failure

## GO_rsmi_dev_power_ave_get()
	### Input: int value of dev index
	### Return: uint64_t value of power avg. ZERO is a failure

## GO_rsmi_dev_temp_metric_get()
	### Input: int value of dev index, sensor and metric
	### Return: uint64_t value of current temperature. ZERO is a failure

## GO_rsmi_dev_gpu_clk_freq_get_sclk()
	### Input: int value of dev index
	### Return: uint64_t value of system frequency

## GO_rsmi_dev_gpu_clk_freq_get_mclk()
	### Input: int value of dev index
	### Return: uint64_t value of memory frequency

## GO_rsmi_dev_gpu_busy_percent_get()
        ### Input: int value of dev index
        ### Return: uint64_t value of GPU Use percent

## GO_rsmi_dev_gpu_memory_busy_percent_get()
        ### Input: int value of dev index
        ### Return: uint64_t value of GPU memory busy percent


## GO_esmi_init()
	### Input: none
	### Return: uint status where ZERO is a failure

## GO_esmi_number_of_sockets_get()
	### Input: none
	### Return: uint value of the number of sockets. ZERO indicates failure.

## GO_esmi_number_of_threads_get()
	### Input: none
	### Return: uint value of the number of threads (1 indexed). ZERO indicates failure

## GO_esmi_threads_per_core_get()
	### Input: none
	### Return: uint value of the number of threads per core. ZERO indicates failure.

## GO_esmi_core_energy_get()
	### Input: int value of the core number
	### Return: uint value of the energy counter for the thread/core. ZERO indicates failure.

## GO_esmi_core_boostlimit_get()
	### Input: int value of the core number
	### Return: uint value of the boost limit of the core. ZERO indicates failure.

## GO_esmi_socket_energy_get()
	### Input: int value of the socket number
	### Return: uint value of the socket energy counter. ZERO indicates failure.

## GO_esmi_socket_power_get()
	### Input: int value of the socket number
	### Return: uint value of the socket power consumed. ZERO indicates failure.

## GO_esmi_socket_power_cap_get()
	### Input: int value of the socket number
	### Return: C.uint32_t value of the power cap for the socket. ZERO indicates failure.

## GO_esmi_prochot_status_get()
	### Input: int value of the socket number
	### Return: C.uint32_t value. 1 indicates an asserted PROC_HOT status, 0 indicates a de-asserted state or failure.


<a name="example"></a>
# Example Code

	```
	package collect

	import "https://github.com/amd/goamdsmi"

	type AMDParams struct {
		CoreEnergy [256]float64
		SocketEnergy [2]float64
		CoreBoost [256]float64
		SocketPower [2]float64
		PowerLimit [2]float64
		ProchotStatus [2]float64
		Sockets uint
		Threads uint
		ThreadsPerCore uint
	}

	func Scan() (AMDParams) {

		var stat AMDParams
		value64 := uint64(0)
		value32 := uint32(0)

		if 1 == goamdsmi.GO_esmi_init() {
			num_sockets := int(goamdsmi.GO_esmi_number_of_sockets_get())
			num_threads := int(goamdsmi.GO_esmi_number_of_threads_get())
			num_threads_per_core := int(goamdsmi.GO_esmi_threads_per_core_get())

			stat.Sockets = uint(num_sockets)
			stat.Threads = uint(num_threads)
			stat.ThreadsPerCore = uint(num_threads_per_core)

			for i := 0; i < num_threads ; i++ {
				value64 = uint64(goamdsmi.GO_esmi_core_energy_get(i))
				stat.CoreEnergy[i] = float64(value64)
				value64 = 0

				value32 = uint32(goamdsmi.GO_esmi_core_boostlimit_get(i))
				stat.CoreBoost[i] = float64(value32)
				value32 = 0
			}

			for i := 0; i < num_sockets ; i++ {
				value64 = uint64(goamdsmi.GO_esmi_socket_energy_get(i))
				stat.SocketEnergy[i] = float64(value64)
				value64 = 0

				value32 = uint32(goamdsmi.GO_esmi_socket_power_get(i))
				stat.SocketPower[i] = float64(value32)
				value32 = 0

				value32 = uint32(goamdsmi.GO_esmi_socket_power_cap_get(i))
				stat.PowerLimit[i] = float64(value32)
				value32 = 0

				value32 = uint32(goamdsmi.GO_esmi_prochot_status_get(i))
				stat.ProchotStatus[i] = float64(value32)
				value32 = 0
			}
		}

		return stat
	}
	```
