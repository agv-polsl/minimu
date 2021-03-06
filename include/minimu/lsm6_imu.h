#ifndef LSM6_IMU_REGS_H
#define LSM6_IMU_REGS_H

#include "minimu/i2c_device.h"
#include "minimu/lsm6_regs_addr.h"

namespace minimu {

constexpr std::byte lsm6_id{0x69};

class Lsm6_imu : public Minimu_i2c_device<lsm6_regs_addr, lsm6_id> {
   public:
    Lsm6_imu() = delete;
    Lsm6_imu(const uint8_t adapter_nr, const sa0_state device_mode);
    /**
     * Returns gyroscope readout in degrees per second.
     */
    point3d read_gyro();
    /**
     * Returns accelerometer readout in meters per second squared.
     */
    point3d read_acc();

    void default_setup();
    void set_gyro_rate_and_scale();
    void set_acc_rate_and_scale();
    void set_auto_increment();

   private:
    point3d read_3d_burst(lsm6_regs_addr start_addr, double scale);
    double acc_scale;
    double gyro_scale;
};

}  // namespace minimu

#endif
