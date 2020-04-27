#ifndef LIS3MDL_MAGNETOMETR_H
#define LIS3MDL_MAGNETOMETR_H

#include "minimu/i2c_device.h"
#include "minimu/lis3mdl_regs_addr.h"

namespace minimu {

constexpr std::byte lis3mdl_id{0x3D};

class Lis3mdl_magmeter
    : public Minimu_i2c_device<lis3mdl_regs_addr, lis3mdl_id> {
   public:
    Lis3mdl_magmeter() = delete;
    Lis3mdl_magmeter(const uint8_t adapter_nr, const sa0_state device_mode);
    point3d read() const;

   private:
    double scale;

    void default_setup();
    void set_default_rate();
    void set_default_scale();
    void set_continuous_mode();
};  // namespace minimu

}  // namespace minimu

#endif
