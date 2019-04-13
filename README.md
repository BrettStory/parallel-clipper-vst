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
* Following the instructions in `iPlug2\Dependencies\IPlug\VST3_SDK\README.md`
* Open git bash inside `iPlug2/Examples` and clone this repository with the following command: `git clone git@github.com:BrettStory/comet-overdrive-dist-vst.git`
* Newer versions of git will do this automatically, but with older versions of git you will need to initialize submodules by performing the following command inside of git bash: `git submodule update --init --recursive`
* Open `CometOverdrive.sln` and rebuild all
  * Check the output window to see where the VST plugin has been placed based on your system and configuration
    * Windows 32-bit will be placed at `"Program Files (x86)\Common Files\VST3"`
    * Windows 64-bit will be placed at `"Program Files\Common Files\VST3"`

## VST Development Help

If you are unfamiliar with VST Plugin development, I highly recommend reading through [Martin Finke's "Making Audio Plugins"](http://martin-finke.de/blog/tags/making_audio_plugins.html). While the tutorial series was written with the original iPlug in mind, many of the lessons are still applicable to iPlug2.