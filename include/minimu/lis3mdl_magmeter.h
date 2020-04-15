#ifndef LIS3MDL_MAGNETOMETR_H
#define LIS3MDL_MAGNETOMETR_H

#include "minimu/i2c_device.h"

namespace minimu {

struct lis3mdl_magmeter_regs : public minimu_regs {};

class Lis3mdl_magmeter : public I2c_device {
   public:
    point3d read();

    void default_setup();
    void set_rate();
    void set_auto_increment();
    void set_continuous_mode();
    void set_default_xy_axes_rate();
    void set_default_z_axis_rate();
    void set_default_scale();
};

}  // namespace minimu

#endif
