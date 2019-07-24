/// <summary>
/// Implements the log class.
/// </summary>
#include "Log.h"

VxSdkNet::Log::Log(VxSdk::IVxLog* vxLog) {
    _log = vxLog;
}

VxSdkNet::Log::!Log() {
    _log->Delete();
    _log = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Log::Refresh() {
    return (VxSdkNet::Results::Value)_log->Refresh();
}

System::String^ VxSdkNet::Log::_GetLogEndpoint() {
    char* logEndpoint = nullptr;
    int size = 0;

    // If the log endpoint is not available on the system the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _log->GetLogEndpoint(logEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for logEndpoint
        logEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _log->GetLogEndpoint(logEndpoint, size);
    }
    return Utils::ConvertCppString(logEndpoint);
}


