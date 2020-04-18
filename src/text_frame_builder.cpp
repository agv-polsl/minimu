#include "minimu/text_frame_builder.h"

#include <sstream>
#include <chrono>

namespace minimu {

std::string TextFrameBuilder::make_text_frame() {
	return make_time_string() + make_readouts_string();
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

std::string TextFrameBuilder::make_time_string() {
    auto now = std::chrono::system_clock::now();
    return std::to_string(std::chrono::system_clock::to_time_t(now));
}

}  // namespace minimu
