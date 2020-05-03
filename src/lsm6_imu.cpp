#include "minimu/lsm6_imu.h"

namespace minimu {

Lsm6_imu::Lsm6_imu(const uint8_t adapter_nr, const sa0_state device_mode)
    : Minimu_i2c_device<lsm6_regs_addr, lsm6_id>{adapter_nr, device_mode} {
    default_setup();
}

point3d Lsm6_imu::read_3d_burst(lsm6_regs_addr start_addr, double scale) {
    constexpr size_t num_of_bytes_in_3d_point = 6;
    auto bytes_block = read_bytes_block(start_addr, num_of_bytes_in_3d_point);

    return {scale * merge_bytes(bytes_block[1], bytes_block[0]),
            scale * merge_bytes(bytes_block[3], bytes_block[2]),
            scale * merge_bytes(bytes_block[5], bytes_block[4])};
}

static double mg_to_mps2(double acc_in_mg) {
    constexpr double earth_g = 9.80665;
    return acc_in_mg * earth_g / 1000.0;
}

static double mdps_to_dps(double gyro_in_mdps) { return gyro_in_mdps / 1000.0; }

point3d Lsm6_imu::read_gyro() {
    auto gyror = read_3d_burst(lsm6_regs_addr::outx_l_g, gyro_scale);
    return {mdps_to_dps(gyror.x), mdps_to_dps(gyror.y), mdps_to_dps(gyror.z)};
}

point3d Lsm6_imu::read_acc() {
    auto accr = read_3d_burst(lsm6_regs_addr::outx_l_xl, acc_scale);
    return {mg_to_mps2(accr.x), mg_to_mps2(accr.y), mg_to_mps2(accr.z)};
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
