#include "minimu/lsm6_imu.h"

namespace minimu {

Lsm6_imu::Lsm6_imu(const uint8_t adapter_nr, const sa0_state device_mode)
    : Minimu_i2c_device<lsm6_regs_addr, lsm6_id>{adapter_nr, device_mode} {
    default_setup();
}

point3d Lsm6_imu::read_3d_burst(lsm6_regs_addr start_addr, double scale) {
    write(static_cast<std::byte>(start_addr));

    std::byte x_low = read();
    std::byte x_high = read();
    std::byte y_low = read();
    std::byte y_high = read();
    std::byte z_low = read();
    std::byte z_high = read();

    return {scale * merge_bytes(x_high, x_low),
            scale * merge_bytes(y_high, y_low),
            scale * merge_bytes(z_high, z_low)};
}

point3d Lsm6_imu::read_gyro() {
    return read_3d_burst(lsm6_regs_addr::outx_l_g, gyro_scale);
}

point3d Lsm6_imu::read_acc() {
    return read_3d_burst(lsm6_regs_addr::outx_l_xl, acc_scale);
}

void Lsm6_imu::default_setup() {
    set_acc_rate_and_scale();
    set_gyro_rate_and_scale();
    set_auto_increment();
}

void Lsm6_imu::set_acc_rate_and_scale() {
    const std::byte set_default_rate{0b10000000};
    const double default_scale = 0.061;

    write(lsm6_regs_addr::ctrl1_xl, set_default_rate);
    acc_scale = default_scale;
}

void Lsm6_imu::set_gyro_rate_and_scale() {
    const std::byte set_default_rate{0b10000000};
    const double default_scale = 8.75;

    write(lsm6_regs_addr::ctrl2_g, set_default_rate);
    gyro_scale = default_scale;
}

void Lsm6_imu::set_auto_increment() {
    const std::byte set_auto_inc{0b00000100};
    write(lsm6_regs_addr::ctrl3_c, set_auto_inc);
}

}  // namespace minimu
