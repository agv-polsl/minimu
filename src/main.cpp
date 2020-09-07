#include <exception>
#include <iostream>

#include "minimu/text_frame_builder.h"

int main(int argc, char* argv[]) {
    /**
     * CLI takes one argument of I2C device adapter number, this note that this
     * demo defaults to sa0 pin on minimu being high (which is also hardware
     * default).
     */
    if (argc != 2) {
        throw std::invalid_argument{
            "One argument of I2C device adapter number is required."};
    }

    try {
        auto adapter_num = std::stoi(argv[1]);
    } catch (std::invalid_argument& ie) {
        throw std::invalid_argument{
            "Given I2C adapter number is invalid; could not convert it to "
            "number."
        }
    }
    minimu::Lsm6_imu imu{adapter_num, minimu::sa0_state::sa0_high};
    minimu::Lis3mdl_magmeter mag{adapter_num, minimu::sa0_state::sa0_high};

    minimu::TextFrameBuilder tfb{imu, mag};

    while (true) {
        std::cout << tfb.make_text_frame();
    }
    return 0;
}
