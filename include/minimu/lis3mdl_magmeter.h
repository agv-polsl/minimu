#ifndef LIS3MDL_MAGNETOMETR_H
#define LIS3MDL_MAGNETOMETR_H

#include "minimu/i2c_device.h"
#include "minimu/lis3mdl_regs_addr.h"

namespace minimu {

class Lis3mdl_magmeter : public Minimu_i2c_device<lis3mdl_regs_addr> {
   public:
    point3d read() const;
    void default_setup();
    void set_rate();
    void set_auto_increment();
    void set_continuous_mode();
    void set_default_xy_axes_rate();
    void set_default_z_axis_rate();
    void set_default_scale();

   private:
    double scale;
};

}  // namespace minimu

#endif
