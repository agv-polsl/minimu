#ifndef LSM6_REGS_ADDR_H
#define LSM6_REGS_ADDR_H

#include <cstdint>

namespace minimu {

enum class lsm6_regs_addr : uint8_t {
    /* Device i2c addresses */
    sa0_high_addr = 0b1101011,
    sa0_low_addr = 0b1101010,

    /* Device registers */
    func_cfg_access = 0x01,

    fifo_ctrl1 = 0x06,
    fifo_ctrl2 = 0x07,
    fifo_ctrl3 = 0x08,
    fifo_ctrl4 = 0x09,
    fifo_ctrl5 = 0x0a,
    orient_cfg_g = 0x0b,

    int1_ctrl = 0x0d,
    int2_ctrl = 0x0e,
    who_am_i = 0x0f,
    ctrl1_xl = 0x10,
    ctrl2_g = 0x11,
    ctrl3_c = 0x12,
    ctrl4_c = 0x13,
    ctrl5_c = 0x14,
    ctrl6_c = 0x15,
    ctrl7_g = 0x16,
    ctrl8_xl = 0x17,
    ctrl9_xl = 0x18,
    ctrl10_c = 0x19,

    wake_up_src = 0x1b,
    tap_src = 0x1c,
    d6d_src = 0x1d,
    status_reg = 0x1e,

    out_temp_l = 0x20,
    out_temp_h = 0x21,
    outx_l_g = 0x22,
    outx_h_g = 0x23,
    outy_l_g = 0x24,
    outy_h_g = 0x25,
    outz_l_g = 0x26,
    outz_h_g = 0x27,
    outx_l_xl = 0x28,
    outx_h_xl = 0x29,
    outy_l_xl = 0x2a,
    outy_h_xl = 0x2b,
    outz_l_xl = 0x2c,
    outz_h_xl = 0x2d,

    fifo_status1 = 0x3a,
    fifo_status2 = 0x3b,
    fifo_status3 = 0x3c,
    fifo_status4 = 0x3d,
    fifo_data_out_l = 0x3e,
    fifo_data_out_h = 0x3f,
    timestamp0_reg = 0x40,
    timestamp1_reg = 0x41,
    timestamp2_reg = 0x42,

    step_timestamp_l = 0x49,
    step_timestamp_h = 0x4a,
    step_counter_l = 0x4b,
    step_counter_h = 0x4c,

    func_src = 0x53,

    tap_cfg = 0x58,
    tap_ths_6d = 0x59,
    int_dur2 = 0x5a,
    wake_up_ths = 0x5b,
    wake_up_dur = 0x5c,
    free_fall = 0x5d,
    md1_cfg = 0x5e,
    md2_cfg = 0x5f,
};

}  // namespace minimu

#endif
