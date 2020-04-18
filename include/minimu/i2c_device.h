#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
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
    I2c_device() = default;
    explicit I2c_device(const uint8_t adapter_nr) { open_dev(adapter_nr); }
    I2c_device(const uint8_t adapter_nr, const regmap_type i2c_address) {
        open_dev(adapter_nr);
        connect(i2c_address);
    }
    void open_dev(const uint8_t adapter_nr);
    bool try_connect(const regmap_type i2c_address) noexcept;
    void connect(const regmap_type i2c_address);
    void write(const std::byte value) const;
    void write(const regmap_type address, const std::byte value) const;
    std::byte read() const;
    std::byte read(const regmap_type address) const;

   protected:
    int device_handle;
};

template <typename regmap_type, std::byte device_id>
class Minimu_i2c_device : public I2c_device<regmap_type> {
   public:
    Minimu_i2c_device() = delete;
    Minimu_i2c_device(const uint8_t adapter_nr,
                      const sa0_state device_mode = sa0_state::sa0_auto)
        : I2c_device<regmap_type>{adapter_nr} {
        connect(device_mode);
    }

   protected:
    void connect(const sa0_state device_mode = sa0_state::sa0_auto);
    void detect_device_mode();
    bool who_id_matches() const;
};

inline uint16_t merge_bytes(const std::byte high, const std::byte low) {
    return static_cast<uint16_t>(high << 8 | low);
}

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
void I2c_device<regmap_type>::write(const std::byte value) const {
    auto v = static_cast<uint8_t>(value);

    auto dev_status = ::write(device_handle, &v, 1);
    if (dev_status < 0) {
        throw std::runtime_error{"Could not write to i2c device; "s +
                                 std::strerror(errno)};
    }
}

template <typename address_map>
void I2c_device<address_map>::write(const address_map address,
                                    const std::byte value) const {
    constexpr size_t bytes_to_write = 2;
    uint8_t buffer[bytes_to_write] = {static_cast<uint8_t>(address),
                                      static_cast<uint8_t>(value)};

    if (::write(device_handle, buffer, bytes_to_write) != bytes_to_write) {
        throw std::runtime_error{"Could not read from i2c device"};
    }
}

template <typename regmap_type>
std::byte I2c_device<regmap_type>::read() const {
    uint8_t ret;
    constexpr size_t bytes_to_read = 1;

    if (::read(device_handle, &ret, bytes_to_read) != bytes_to_read) {
        throw std::runtime_error{"Could not read from i2c device"s};
    }
    return std::byte{ret};
}

template <typename regmap_type>
std::byte I2c_device<regmap_type>::read(const regmap_type address) const {
    write(static_cast<std::byte>(address));
    return read();
}

template <typename regmap_type, std::byte device_id>
bool Minimu_i2c_device<regmap_type, device_id>::who_id_matches() const {
    return I2c_device<regmap_type>::read(regmap_type::who_am_i) == device_id;
}

/* TODO: maybe some refactor, more elegant logic here */
template <typename regmap_type, std::byte device_id>
void Minimu_i2c_device<regmap_type, device_id>::connect(
    const sa0_state device_mode) {
    switch (device_mode) {
        case sa0_state::sa0_low:
            I2c_device<regmap_type>::connect(regmap_type::sa0_low_addr);
            if (!who_id_matches()) {
                throw std::runtime_error{
                    "Connected i2c device id did not match"s};
            }
            break;

        case sa0_state::sa0_high:
            I2c_device<regmap_type>::connect(regmap_type::sa0_high_addr);
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

template <typename regmap_type, std::byte device_id>
void Minimu_i2c_device<regmap_type, device_id>::detect_device_mode() {
    if (I2c_device<regmap_type>::try_connect(regmap_type::sa0_low_addr) &&
        who_id_matches()) {
        return;
    }
    if (I2c_device<regmap_type>::try_connect(regmap_type::sa0_low_addr) &&
        who_id_matches()) {
        return;
    } else {
        throw std::runtime_error{
            "Could not find matching i2c device using auto-detect mode"s};
    }
}

}  // namespace minimu

#endif
