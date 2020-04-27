#include <cstddef>

#include "minimu/lis3mdl_magmeter.h"

namespace minimu {

Lis3mdl_magmeter::Lis3mdl_magmeter(const uint8_t adapter_nr,
                                   const sa0_state device_mode)
    : Minimu_i2c_device<lis3mdl_regs_addr, lis3mdl_id>{adapter_nr,
                                                       device_mode} {
    default_setup();
}

point3d Lis3mdl_magmeter::read() const {
    std::byte enable_subaddress_updating{0b10000000};

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

void Lis3mdl_magmeter::default_setup() {
    set_default_rate();
    set_default_scale();
    set_continuous_mode();
}

void Lis3mdl_magmeter::set_default_rate() {
    const std::byte set_10hz_rate{0b00010000};
    const std::byte xy_axes_ultra_mode{0b01100000};
    const std::byte z_axis_ultra_mode{0b00001100};

    write(lis3mdl_regs_addr::ctrl_reg1, set_10hz_rate | xy_axes_ultra_mode);
    write(lis3mdl_regs_addr::ctrl_reg4, z_axis_ultra_mode);
}

void Lis3mdl_magmeter::set_default_scale() {
    const double default_scale = 0.1888;
    const std::byte enable_default_scale{0x00};
    write(lis3mdl_regs_addr::ctrl_reg2, enable_default_scale);
    scale = default_scale;
}

void Lis3mdl_magmeter::set_continuous_mode() {
    const std::byte enable_continuous_mode{0x00};
    write(lis3mdl_regs_addr::ctrl_reg3, enable_continuous_mode);
}

}  // namespace minimu
