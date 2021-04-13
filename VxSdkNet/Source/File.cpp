/// <summary>
/// Implements the file class.
/// </summary>
#include "File.h"

VxSdkNet::File::File(VxSdk::IVxFile* vxFile) {
    _file = vxFile;
}

VxSdkNet::File::!File() {
    _file->Delete();
    _file = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::File::Refresh() {
    return (VxSdkNet::Results::Value)_file->Refresh();
}

System::String^ VxSdkNet::File::_GetFileEndpoint() {
    char* fileEndpoint = nullptr;
    int size = 0;

    // If the file endpoint is not available on the system the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _file->GetFileEndpoint(fileEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for fileEndpoint
        fileEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _file->GetFileEndpoint(fileEndpoint, size);
    }
    return Utils::ConvertCppString(fileEndpoint);
}


