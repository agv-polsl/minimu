#ifndef LIS3MDL_REGS_ADDR_H
#define LIS3MDL_REGS_ADDR_H

#include <cstdint>

namespace minimu {

enum class lis3mdl_regs_addr : uint8_t {
    /* Device i2c addresses */
    sa0_high_addr = 0b0011110,
    sa0_low_addr = 0b0011100,

    /* Device registers */
    ctrl_reg1 = 0x20,
    ctrl_reg2 = 0x21,
    ctrl_reg3 = 0x22,
    ctrl_reg4 = 0x23,
    ctrl_reg5 = 0x24,

    status_reg = 0x27,
    out_x_l = 0x28,
    out_x_h = 0x29,
    out_y_l = 0x2a,
    out_y_h = 0x2b,
    out_z_l = 0x2c,
    out_z_h = 0x2d,
    temp_out_l = 0x2e,
    who_am_i = 0x0f,
    temp_out_h = 0x2f,
    int_cfg = 0x30,
    int_src = 0x31,
    int_ths_l = 0x32,
    int_ths_h = 0x33,
};

}  // namespace lis3mdl

#endif
