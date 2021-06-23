/// <summary>
/// Implements the vx file recovery class.
/// </summary>
#include "VxFileRecovery.h"

using namespace System::Collections::Generic;

VxSdkNet::VxFileRecovery::VxFileRecovery(VxSdk::IVxFileRecovery* vxFileRecovery) {
    _vxFileRecovery = vxFileRecovery;
}

VxSdkNet::VxFileRecovery::!VxFileRecovery() {
    _vxFileRecovery->Delete();
    _vxFileRecovery = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::VxFileRecovery::Halt() {
    return (VxSdkNet::Results::Value)_vxFileRecovery->Halt();
}

VxSdkNet::Results::Value VxSdkNet::VxFileRecovery::Refresh() {
    return (VxSdkNet::Results::Value)_vxFileRecovery->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::VxFileRecovery::Trigger(System::String^ volumeId, System::DateTime startTime, System::DateTime endTime) {
    return (VxSdkNet::Results::Value)_vxFileRecovery->Trigger(Utils::ConvertCSharpString(volumeId).c_str(), Utils::ConvertCSharpDateTime(startTime).c_str(), Utils::ConvertCSharpDateTime(endTime).c_str());
}