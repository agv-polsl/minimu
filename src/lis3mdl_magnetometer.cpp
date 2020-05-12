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
    constexpr size_t num_of_bytes_in_3d_point = 6;
    constexpr auto start_addr = lis3mdl_regs_addr::out_x_l;
    auto bytes_block = read_bytes_block(start_addr, num_of_bytes_in_3d_point);

    return {scale * merge_bytes(bytes_block[1], bytes_block[0]),
            scale * merge_bytes(bytes_block[3], bytes_block[2]),
            scale * merge_bytes(bytes_block[5], bytes_block[4])};
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
    constexpr double default_scale = 1.0 / 6842.0;
    const std::byte enable_default_scale{0x00};
    write(lis3mdl_regs_addr::ctrl_reg2, enable_default_scale);
    scale = default_scale;
}

void Lis3mdl_magmeter::set_continuous_mode() {
    const std::byte enable_continuous_mode{0x00};
    write(lis3mdl_regs_addr::ctrl_reg3, enable_continuous_mode);
}

}  // namespace minimu
