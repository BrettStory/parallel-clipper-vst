#pragma once

#include "IPlug_include_in_plug_hdr.h"

const int NUMBER_OF_PROGRAMS = 3;
const IColor COLOR_FONT_PRIMARY(255, 254, 167, 117);
const IColor COLOR_FONT_SECONDARY(255, 212, 96, 89);
const IColor COLOR_LIGHT(255, 128, 43, 91);
const IColor COLOR_MEDIUM(255, 86, 25, 79);
const IColor COLOR_DARK(255, 38, 11, 44);
const IColor COLOR_DARKEST(255, 1, 0, 2);

enum EParams {
	SOFTNESS = 0,
	THRESHOLD = 1,
	SOFT_PRE_GAIN = 2,
	HARD_PRE_GAIN = 3,
	POST_GAIN = 4,
	NUMBER_OF_PARAMETERS
};

class ParallelClipper : public IPlug {
public:
	ParallelClipper(IPlugInstanceInfo instanceInfo);

#if IPLUG_DSP // All DSP methods and member variables should be within an IPLUG_DSP guard, should you want distributed UI
	void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
#endif
};
