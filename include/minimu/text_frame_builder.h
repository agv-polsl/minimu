#ifndef TEXT_FRAME_BUILDER_H
#define TEXT_FRAME_BUILDER_H

#include <string>

#include "minimu/i2c_device.h"
#include "minimu/lsm6_imu.h"
#include "minimu/lis3mdl_magmeter.h"

namespace minimu {

class TextFrameBuilder {
   public:
    TextFrameBuilder(Lsm6_imu& imu, Lis3mdl_magmeter& mag)
        : imu{imu}, mag{mag} {}
	std::string make_text_frame();

   private:
    Lsm6_imu& imu;
    Lis3mdl_magmeter& mag;
};

}  // namespace minimu

#endif
