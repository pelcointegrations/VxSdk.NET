/// <summary>
/// Implements the vx file class.
/// </summary>
#include "VxFile.h"

VxSdkNet::VxFile::VxFile(VxSdk::IVxFile* vxFile) {
    _vxFile = vxFile;
}

VxSdkNet::VxFile::!VxFile() {
    _vxFile->Delete();
    _vxFile = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::VxFile::Refresh() {
    return (VxSdkNet::Results::Value)_vxFile->Refresh();
}

System::String^ VxSdkNet::VxFile::_GetFileEndpoint() {
    char* fileEndpoint = nullptr;
    int size = 0;

    // If the file endpoint is not available on the system the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _vxFile->GetFileEndpoint(fileEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for fileEndpoint
        fileEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _vxFile->GetFileEndpoint(fileEndpoint, size);
    }
    return Utils::ConvertCppString(fileEndpoint);
}


