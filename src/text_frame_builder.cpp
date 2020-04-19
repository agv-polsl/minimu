#include "minimu/text_frame_builder.h"

#include <chrono>
#include <sstream>

namespace minimu {

std::string TextFrameBuilder::make_text_frame() {
    return make_dt_string() + "," + make_readouts_string();
}

std::string TextFrameBuilder::make_readouts_string() {
    auto gyror = imu.read_gyro();
    auto accr = imu.read_acc();
    auto magr = mag.read();

    std::stringstream ss;
    ss << gyror.x << ',' << gyror.y << ',' << gyror.z << ',' << accr.x << ','
       << accr.y << ',' << accr.z << ',' << magr.x << ',' << magr.y << ','
       << magr.z << ',';
    return ss.str();
}

std::string TextFrameBuilder::make_dt_string() {
    return std::to_string(yield_dt());
}

double TextFrameBuilder::yield_dt() {
    static auto oldt = std::chrono::high_resolution_clock::now();

    auto newt = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> ms = (newt - oldt);
    oldt = newt;

    return ms.count();
}

}  // namespace minimu
