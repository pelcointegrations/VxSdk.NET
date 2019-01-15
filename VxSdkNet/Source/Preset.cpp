/// <summary>
/// Implements the preset class.
/// </summary>
#include "Preset.h"

VxSdkNet::Preset::Preset(VxSdk::IVxPreset* vxPreset) {
    _preset = vxPreset;
}

VxSdkNet::Preset::!Preset() {
    _preset->Delete();
    _preset = nullptr;
}
