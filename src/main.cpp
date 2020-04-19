#include <iostream>

#include "minimu/text_frame_builder.h"

int main(int argc, char *argv[]) {
    /* agv: /dev adapter nr, use i2c tools to find it
     * cli may need polishing
     */
    minimu::Lsm6_imu imu{std::stoi(argv[1]), minimu::sa0_state::sa0_high};
    minimu::Lis3mdl_magmeter mag{std::stoi(argv[1]), minimu::sa0_state::sa0_high};
    minimu::TextFrameBuilder tfb{imu, mag};

    while (true) {
        std::cout << tfb.make_text_frame();
    }

    return 0;
}
