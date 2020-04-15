#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <cstdint>

namespace minimu {

struct point3d {
	double x;
	double y;
	double z;
};

struct minimu_regs {
    const uint8_t who_am_i;
};

struct device_addr {
    const uint8_t sa0_high_addr;
    const uint8_t a0_low_addr;
};

enum class sa0_state { sa0_low, sa0_high, sa0_auto };

class I2c_device {
   public:
    void write(uint8_t value);
    void write_reg(int reg, uint8_t value);
    uint8_t read();
    uint8_t read_reg(int reg);
	void detect_device_mode();

   protected:
    uint8_t device_handle;
};

}  // namespace minimu

#endif
