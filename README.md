![Build](https://github.com/agv-polsl/minimu/workflows/Build/badge.svg)

# Minimu

Pololu Minimu-9 v5 gyroscope, accelerometer and magnetometer combo reader over I2C bus for Linux devices.
Tested on RaspberryPi, should work on all I2C enabled Linux devices.
Available as C++ library and simple CLI demo.

## Build

This depends on Linux kernel I2C driver via userspace access library.
On Debian that is `libi2c-dev` package.

You can run build in Docker.
For example to map project directory as Docker volume run:
```docker run -v `pwd`:/proj -it agvpolsl/minimu-i2c-builder```.

Build follows standard CMake procedure; in project directory run:

```sh
mkdir build && cd build
cmake ..
cmake --build .
```

## Usage

### CLI

The CLI is app takes one argument of active I2C adapter.
It assumes `sa0` pin to be high (which is also the default hardware state).
To find adapter number and examine your devices use `i2cdetect` tool.

### C++ library

The library is available via CMake build.
It doesn't feature system wide installation, instead it is best to place the source code
inside your project and use it with `add_subdirectory(lib/minimu)` and `target_link_libraries(target minimu::minimu-lib)`.

Init your devices with:

```cpp
minimu::Lsm6_imu imu{adapter_num, minimu::sa0_state::sa0_high};
minimu::Lis3mdl_magmeter mag{adapter_num, minimu::sa0_state::sa0_high};
```

Data can be read with: `read_gyro()`, `read_acc()`  for IMU and `read()` for magnetometer.

If you need direct communication with I2C devices you can use underlying `I2C_device` class.
You can read and write bytes from registers that can be found in `lsm6_regs_addr.h` and `lis3mdl_regs_addr.h` headers.
For example it is possible to write to register `fifo_ctrl1` with:

```cpp
imu.write(minimu::lsm6_regs_addr::fifo_ctrl1, std::byte{0b11001100});
```

The Linux C `errno` system is mapped to C++ exceptions inside the library.
For more information relate to the datasheets.
