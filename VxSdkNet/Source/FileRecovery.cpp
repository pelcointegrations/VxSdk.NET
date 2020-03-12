/// <summary>
/// Implements the file recovery class.
/// </summary>
#include "FileRecovery.h"

using namespace System::Collections::Generic;

VxSdkNet::FileRecovery::FileRecovery(VxSdk::IVxFileRecovery* vxFileRecovery) {
    _fileRecovery = vxFileRecovery;
}

VxSdkNet::FileRecovery::!FileRecovery() {
    _fileRecovery->Delete();
    _fileRecovery = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::FileRecovery::Halt() {
    return (VxSdkNet::Results::Value)_fileRecovery->Halt();
}

VxSdkNet::Results::Value VxSdkNet::FileRecovery::Refresh() {
    return (VxSdkNet::Results::Value)_fileRecovery->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::FileRecovery::Trigger(System::String^ volumeId, System::DateTime startTime, System::DateTime endTime) {
    return (VxSdkNet::Results::Value)_fileRecovery->Trigger(Utils::ConvertCSharpString(volumeId).c_str(), Utils::ConvertCSharpDateTime(startTime).c_str(), Utils::ConvertCSharpDateTime(endTime).c_str());
}