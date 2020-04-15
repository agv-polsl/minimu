#ifndef LSM6_IMU_REGS_H
#define LSM6_IMU_REGS_H

#include "minimu/i2c_device.h"

namespace minimu {

struct lsm6_imu_regs : public minimu_regs {};

class Lsm6_imu : public I2c_device {
   public:
    point3d read_gyro();
    point3d read_acc();

    void default_setup();
    void set_acc_rate();
    void set_auto_increment();
    void set_continuous_mode();
};

}  // namespace minimu

#endif
