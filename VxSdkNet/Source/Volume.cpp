/// <summary>
/// Implements the volume class.
/// </summary>
#include "Volume.h"

using namespace System::Collections::Generic;

VxSdkNet::Volume::Volume(VxSdk::IVxVolume* vxVolume) {
    _volume = vxVolume;
}

VxSdkNet::Volume::!Volume() {
    _volume->Delete();
    _volume = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Volume::Refresh() {
    return (VxSdkNet::Results::Value)_volume->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::Volume::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _volume->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

VxSdkNet::VolumeGroup^ VxSdkNet::Volume::_GetVolumeGroup() {
    // Get the volume group
    VxSdk::IVxVolumeGroup* volumeGroup = nullptr;
    VxSdk::VxResult::Value result = _volume->GetVolumeGroup(volumeGroup);

    // Return the volume group if GetVolumeGroup was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::VolumeGroup(volumeGroup);

    return nullptr;
}
