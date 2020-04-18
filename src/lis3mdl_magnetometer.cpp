#include <cstddef>

#include "minimu/lis3mdl_magmeter.h"

namespace minimu {

point3d Lis3mdl_magmeter::read() const {
    std::byte enable_subaddress_updating{0x80};

	auto addr_as_byte = static_cast<std::byte>(lis3mdl_regs_addr::out_x_l); 
	write(addr_as_byte | enable_subaddress_updating);

    std::byte x_low = Minimu_i2c_device::read();
    std::byte x_high = Minimu_i2c_device::read();
    std::byte y_low = Minimu_i2c_device::read();
    std::byte y_high = Minimu_i2c_device::read();
    std::byte z_low = Minimu_i2c_device::read();
    std::byte z_high = Minimu_i2c_device::read();

    return {scale * merge_bytes(x_high, x_low),
            scale * merge_bytes(y_high, y_low),
            scale * merge_bytes(z_high, z_low)};
}

void Lis3mdl_magmeter::default_setup() {}

void Lis3mdl_magmeter::set_rate() {}

void Lis3mdl_magmeter::set_auto_increment() {}

void Lis3mdl_magmeter::set_continuous_mode() {}

void Lis3mdl_magmeter::set_default_xy_axes_rate() {}

void Lis3mdl_magmeter::set_default_z_axis_rate() {}

void Lis3mdl_magmeter::set_default_scale() {}

}  // namespace minimu
