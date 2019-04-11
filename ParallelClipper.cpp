#include "ParallelClipper.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "audio-clipping/SoftClipArctan.hpp"
#include "audio-clipping/HardClip.hpp"
namespace clipping = brettstory::audio::clipping;

ParallelClipper::ParallelClipper(IPlugInstanceInfo instanceInfo) : IPLUG_CTOR(NUMBER_OF_PARAMETERS, NUMBER_OF_PROGRAMS, instanceInfo) {
	GetParam(SOFTNESS)->InitDouble("Softness", 50, 0, 100, 1, "%");
	GetParam(THRESHOLD)->InitDouble("Threshold", 50, 1, 100, 0.1, "%");
	GetParam(SOFT_PRE_GAIN)->InitDouble("Soft Pre Gain", 1, 0, 100, 0.1, "x");
	GetParam(HARD_PRE_GAIN)->InitDouble("Hard Pre Gain", 1, 0, 100, 0.1, "x");
	GetParam(POST_GAIN)->InitDouble("Post Gain", 100, 0, 200, 1, "%");

#if IPLUG_EDITOR // All UI methods and member variables should be within an IPLUG_EDITOR guard, should you want distributed UI
	mMakeGraphicsFunc = [&]() {
		return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, 1.);
	};

	mLayoutFunc = [&](IGraphics * pGraphics) {
		pGraphics->AttachCornerResizer(kUIResizerScale, false);
		pGraphics->AttachPanelBackground(COLOR_TRANSPARENT);
		pGraphics->LoadFont(ROBOTTO_FN);

		const IRECT bounds = pGraphics->GetBounds();
		const IRECT softGrid = bounds.GetGridCell(0, 1, 3);

		pGraphics->FillRect(COLOR_LIGHT, softGrid, new IBlend());

		pGraphics->AttachControl(new ITextControl(
			softGrid.GetGridCell(1, 24, 1).GetCentredInside(96),
			"SOFT",
			IText(24, COLOR_FONT_PRIMARY, "Roboto-Regular", IText::kStyleBold)));

		pGraphics->AttachControl(new IVKnobControl(
			softGrid.GetGridCell(8, 24, 1).GetCentredInside(96),
			SOFT_PRE_GAIN,
			"PRE-GAIN",
			true,
			DEFAULT_SPEC,
			IText(16, COLOR_FONT_SECONDARY),
			IText(10, COLOR_FONT_SECONDARY)));

		pGraphics->AttachControl(new IVKnobControl(
			softGrid.GetGridCell(9, 12, 1).GetCentredInside(96),
			SOFTNESS,
			"SOFTNESS",
			true,
			DEFAULT_SPEC,
			IText(16, COLOR_FONT_SECONDARY),
			IText(10, COLOR_FONT_SECONDARY)));

		const IRECT hardGrid = bounds.GetGridCell(1, 1, 3);
		pGraphics->FillRect(COLOR_MEDIUM, hardGrid, new IBlend());

		pGraphics->AttachControl(new ITextControl(
			hardGrid.GetGridCell(1, 24, 1).GetCentredInside(96),
			"HARD",
			IText(24, COLOR_FONT_PRIMARY, "Roboto-Regular", IText::kStyleBold)));

		pGraphics->AttachControl(new IVKnobControl(
			hardGrid.GetGridCell(8, 24, 1).GetCentredInside(96),
			HARD_PRE_GAIN,
			"PRE-GAIN",
			true,
			DEFAULT_SPEC,
			IText(16, COLOR_FONT_SECONDARY),
			IText(10, COLOR_FONT_SECONDARY)));

		pGraphics->AttachControl(new IVKnobControl(
			hardGrid.GetGridCell(9, 12, 1).GetCentredInside(96),
			THRESHOLD,
			"THRESHOLD",
			true,
			DEFAULT_SPEC,
			IText(16, COLOR_FONT_SECONDARY),
			IText(10, COLOR_FONT_SECONDARY)));

		const IRECT outGrid = bounds.GetGridCell(2, 1, 3);
		pGraphics->FillRect(COLOR_DARK, outGrid, new IBlend());
		pGraphics->AttachControl(new ITextControl(
			outGrid.GetGridCell(1, 24, 1).GetCentredInside(96),
			"OUT",
			IText(24, COLOR_FONT_PRIMARY, "Roboto-Regular", IText::kStyleBold)));

		pGraphics->AttachControl(new IVKnobControl(
			outGrid.GetGridCell(8, 24, 1).GetCentredInside(96),
			POST_GAIN,
			"POST-GAIN",
			true,
			DEFAULT_SPEC,
			IText(16, COLOR_FONT_SECONDARY),
			IText(10, COLOR_FONT_SECONDARY)));
	};
#endif
}

#if IPLUG_DSP
void ParallelClipper::ProcessBlock(sample** inputs, sample** outputs, int nFrames) {
	const double hardPreGainValue = GetParam(HARD_PRE_GAIN)->Value();
	const double thresholdValue = GetParam(THRESHOLD)->Value() * 0.01;
	const double softPreGainValue = GetParam(SOFT_PRE_GAIN)->Value();
	const double softnessValue = GetParam(SOFTNESS)->Value() * 0.01;
	const double postGainValue = GetParam(POST_GAIN)->Value() * 0.01;
	const int numberOfChannels = NOutChansConnected();

	for (int i = 0; i < numberOfChannels; i++) {
		double* input = inputs[i];
		double* output = outputs[i];

		for (int s = 0; s < nFrames; ++s, ++input, ++output) {
			double hard_output = clipping::HardClip::ClipSample(*input * hardPreGainValue, thresholdValue);
			double soft_output = clipping::SoftClipArctan::ClipSample(*input * softPreGainValue);
			double mixed_output = ((soft_output * softnessValue) + (hard_output * (1 - softnessValue)));
			*output = fmin(1, mixed_output * postGainValue);
		}
	}
}
#endif