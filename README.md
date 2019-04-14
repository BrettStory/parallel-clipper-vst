# parallel-clipper-vst

A VST plugin that provides an overdrive effect using a combination of soft and hard clipping.

## Notes

* I have not confirmed that this builds successfully on any platform other than Windows
* Visual Studio must be run as an administrator to build this VST effect
* For some reason, this builds in Visual Studio 2017, but not Visual Studio 2019
* Steinberg has a [dual VST3 SDK license](https://sdk.steinberg.net/viewtopic.php?f=4&t=282)
  * If you plan on selling a VST plug-in, you must have an agreement with Steinberg
  * Open source VST plug-ins must be compliant with [General Public License (GPL) Version 3](http://www.gnu.org/licenses/gpl-3.0.html)

## Build on Windows

* You must clone [iPlug2](https://github.com/BrettStory/iPlug2) before cloning this repository
  * parallel-clipper-vst is a submodule of my iPlug2 fork, so if you run `git submodule update --init --recursive` from inside the base of the iPlug2 repository, you should automatically have access to parallel-clipper-vst
  * You may also need to run `git submodule update --init --recursive` from inside `iPlug2\Examples\parallel-clipper-vst`
* Follow the instructions in `iPlug2\Dependencies\IPlug\VST3_SDK\README.md`
  * This plug-in is verified to work with [VST3 SDK 3.6.13 (build 81)](https://sdk.steinberg.net/viewtopic.php?f=6&t=667)
* Open `CometOverdrive.sln` and rebuild all
  * Check the output window to see where the VST plugin has been placed based on your system and configuration
    * Windows 32-bit will be placed at `"Program Files (x86)\Common Files\VST3"`
    * Windows 64-bit will be placed at `"Program Files\Common Files\VST3"`

## Using Parallel Clipper

If you are building this plug-in yourself, the VST3 file should go into the proper folder automatically. If you're simply downloading a release, the best place to put them depends on which version you're using: 

* Windows 32-bit should be placed at `"Program Files (x86)\Common Files\VST3"`
* Windows 64-bit should be placed at `"Program Files\Common Files\VST3"`

Parallel Clipper is a fairly straight forward plug-in with only 4 knobs: Pre-Gain (soft), Softness, Pre-Gain (hard), and Threshold.

### Pre-Gain (Soft)

The soft pre-gain goes from 0 to 100 and is a direct multiplyer of the input volume. This affects the volume of your input before applying a soft clip. Soft clipping will often require a much higher pre-gain value than hard clipping.

### Softness

Softness is a percentage value between 0% and 100% that describes how much of the final mix will be from soft clipping and how much will be from hard clipping. A softness value of 100% will only use soft clipping (it will not use hard clipping at all) and a softness value of 0% will only use hard clipping. Values inbetween will mix accordingly.

### Pre-Gain (Hard)

The hard pre-gain goes from 0 to 100 and is a direct multiplyer of the input volume. This affects the volume of your input before applying a hard clip. Pre-gain may not be necessary with the proper threshold, but it may allow you to fine-tune the threshold.

### Threshold

Threshold is a value between 0.1% and 100% (0% has no purpose here). In this case, 100% means that nothing will get clipped unless it is already above maximum volume (only a possibility with pre-gain). If 0% means no volume, that means the threshold is some value between no volume nad full volume where anything above that threshold will be boosted to full volume. It goes without saying that too low of a threshold will boost all background noise too, so it could be useful to have a noise gate process your audio before hitting the hard clip.

## VST Development Help

If you are unfamiliar with VST Plugin development, I highly recommend reading through [Martin Finke's "Making Audio Plugins"](http://martin-finke.de/blog/tags/making_audio_plugins.html). While the tutorial series was written with the original iPlug in mind, many of the lessons are still applicable to iPlug2.