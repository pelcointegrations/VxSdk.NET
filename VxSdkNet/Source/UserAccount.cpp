/// <summary>
/// Implements the user account class.
/// </summary>

#include "UserAccount.h"

using namespace System::Collections::Generic;

VxSdkNet::UserAccount::UserAccount(VxSdk::IVxUserAccount* vxUserAccount) {
    _userAccount = vxUserAccount;
}

VxSdkNet::UserAccount::!UserAccount() {
    _userAccount->Delete();
    _userAccount = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::UserAccount::Refresh() {
    return (VxSdkNet::Results::Value)_userAccount->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::UserAccount::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _userAccount->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}
