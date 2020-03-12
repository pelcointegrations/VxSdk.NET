/// <summary>
/// Implements the ptz lock class.
/// </summary>
#include "PtzLock.h"

VxSdkNet::PtzLock::PtzLock(VxSdk::IVxPtzLock* vxPtzLock) {
    _ptzLock = vxPtzLock;
}

VxSdkNet::PtzLock::!PtzLock() {
    _ptzLock->Delete();
    _ptzLock = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::PtzLock::Lock(int expireTime) {
    // Call Lock and return the result
    VxSdk::VxResult::Value result = _ptzLock->Lock(expireTime);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzLock::Refresh() {
    return (VxSdkNet::Results::Value)_ptzLock->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::PtzLock::Unlock() {
    // Call Unlock and return the result
    VxSdk::VxResult::Value result = _ptzLock->Unlock();
    return VxSdkNet::Results::Value(result);
}

int VxSdkNet::PtzLock::_GetExpireTime() {
    // Get and return the expire time
    int expireTime;
    _ptzLock->GetExpireTime(expireTime);
    return expireTime;
}

VxSdkNet::ResourceLimits^ VxSdkNet::PtzLock::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _ptzLock->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

bool VxSdkNet::PtzLock::_GetLockState() {
    // Get and return the current lock state
    bool lockStatus;
    _ptzLock->GetLockState(lockStatus);
    return lockStatus;
}

System::String^ VxSdkNet::PtzLock::_GetOwner() {
    char* owner = nullptr;
    int size = 0;

    // The owner can be empty if the ptz controller is not currently locked. If that is the case then the result
    // returned will be VxSdk::VxResult::kOk and owner will remain a nullptr. Otherwise the return is
    // VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _ptzLock->GetOwner(owner, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for owner
        owner = new char[size];
        // The result should now be kOK since we have allocated enough space
        _ptzLock->GetOwner(owner, size);
    }
    return Utils::ConvertCppString(owner);
}
