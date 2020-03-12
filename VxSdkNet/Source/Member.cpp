/// <summary>
/// Implements the member class.
/// </summary>
#include "Member.h"

using namespace System::Collections::Generic;

VxSdkNet::Member::Member(VxSdk::IVxMember* vxMember) {
    _member = vxMember;
}

VxSdkNet::Member::!Member() {
    _member->Delete();
    _member = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Member::Refresh() {
    return (VxSdkNet::Results::Value)_member->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Member::TriggerRefresh() {
    return (VxSdkNet::Results::Value)_member->TriggerRefresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::Member::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _member->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}