#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <cstdint>

namespace minimu {

struct point3d {
    double x;
    double y;
    double z;
};

enum class sa0_state { sa0_low, sa0_high, sa0_auto };

template <typename regmap_type>
class I2c_device {
   public:
    void connect(uint8_t adapter_nr);
    void write(uint8_t value);
    void write_reg(regmap_type address, uint8_t value);
    uint8_t read();
    uint8_t read_reg(regmap_type address);

   protected:
    void detect_device_mode();

    uint8_t device_handle;
};

template <typename regmap_type>
void I2c_device<regmap_type>::detect_device_mode() {
   
}

}  // namespace minimu

#endif
