#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <fcntl.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cstdint>
#include <cstdlib>
#include <stdexcept>

namespace minimu {

using std::string_literals::operator""s;

struct point3d {
    double x;
    double y;
    double z;
};

enum class sa0_state { sa0_low, sa0_high, sa0_auto };

template <typename regmap_type>
class I2c_device {
   public:
    void write(const uint8_t value) const;
    void write(const regmap_type address, const uint8_t value) const;
    uint8_t read() const;
    uint8_t read(const regmap_type address) const;

   protected:
    void open_dev(const uint8_t adapter_nr);
    bool try_connect(const regmap_type i2c_address) noexcept;
    void connect(const regmap_type i2c_address);
    void detect_device_mode();

    int device_handle;
};

template <typename regmap_type>
class Minimu_i2c_device : public I2c_device<regmap_type> {
   protected:
    void connect(const sa0_state device_mode = sa0_state::sa0_auto);
    void detect_device_mode();
    bool who_id_matches() const;

    const uint8_t who_id;
};

template <typename regmap_type>
void I2c_device<regmap_type>::open_dev(const uint8_t adapter_nr) {
    const std::string path{"/dev/i2c-" + std::to_string(adapter_nr)};
    device_handle = open(path.c_str(), O_RDWR);
    if (device_handle < 0) {
        throw std::runtime_error{"Could not open i2c device at: "s + path};
    }
}

template <typename regmap_type>
bool I2c_device<regmap_type>::try_connect(
    const regmap_type i2c_address) noexcept {
    return ioctl(device_handle, I2C_SLAVE, i2c_address) > -1;
}

template <typename regmap_type>
void I2c_device<regmap_type>::connect(const regmap_type i2c_address) {
    if (!try_connect(i2c_address)) {
        throw std::runtime_error{"Could not connect to i2c device"s};
    }
}

template <typename regmap_type>
void I2c_device<regmap_type>::write(const uint8_t value) const {
    auto dev_status = i2c_smbus_write_byte(device_handle, value);
    if (dev_status < 0) {
        throw std::runtime_error{"Could not write to i2c device"s};
    }
}

template <typename regmap_type>
void I2c_device<regmap_type>::write(const regmap_type address,
                                    const uint8_t value) const {
    auto dev_status = i2c_smbus_write_byte_data(device_handle, address, value);
    if (dev_status < 0) {
        throw std::runtime_error{"Could not read from i2c device at: "s +
                                 std::to_string(address)};
    }
}

template <typename regmap_type>
uint8_t I2c_device<regmap_type>::read() const {
    uint8_t ret = i2c_smbus_read_byte(device_handle);
    if (ret < 0) {
        throw std::runtime_error{"Could not read from i2c device"s};
    }
    return ret;
}

template <typename regmap_type>
uint8_t I2c_device<regmap_type>::read(const regmap_type address) const {
    auto ret = i2c_smbus_read_byte_data(device_handle, address);
    if (ret < 0) {
        throw std::runtime_error{"Could not read from i2c device at: "s +
                                 std::to_string(address)};
    }
    return ret;
}

template <typename regmap_type>
bool Minimu_i2c_device<regmap_type>::who_id_matches() const {
    return read(regmap_type::who_am_i) == who_id;
}

/* TODO: maybe some refactor, more elegant logic here */
template <typename regmap_type>
void Minimu_i2c_device<regmap_type>::connect(const sa0_state device_mode) {
    switch (device_mode) {
        case sa0_state::sa0_low:
            connect(regmap_type::sa0_low_addr);

            if (!who_id_matches()) {
                throw std::runtime_error{
                    "Connected i2c device id did not match"s};
            }
            break;

        case sa0_state::sa0_high:
            connect(regmap_type::sa0_high_addr);

            if (!who_id_matches()) {
                throw std::runtime_error{
                    "Connected i2c device id did not match"s};
            }
            break;

        default:
            detect_device_mode();
            break;
    }
}

template <typename regmap_type>
void Minimu_i2c_device<regmap_type>::detect_device_mode() {
    if (try_connect(regmap_type::sa0_low_addr) && who_id_matches()) {
        return;
    }
    if (try_connect(regmap_type::sa0_low_addr) && who_id_matches()) {
        return;
    } else {
        throw std::runtime_error{
            "Could not find matching i2c device using auto-detect mode"s};
    }
}

}  // namespace minimu

#endif
