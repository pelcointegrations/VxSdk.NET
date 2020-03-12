/// <summary>
/// Implements the schedule trigger class.
/// </summary>
#include "ScheduleTrigger.h"

using namespace System;
using namespace System::Collections::Generic;

VxSdkNet::ScheduleTrigger::ScheduleTrigger(VxSdk::IVxScheduleTrigger* vxScheduleTrigger) {
    _scheduleTrigger = vxScheduleTrigger;
}

VxSdkNet::ScheduleTrigger::!ScheduleTrigger() {
    _scheduleTrigger->Delete();
    _scheduleTrigger = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::ScheduleTrigger::Refresh() {
    return (VxSdkNet::Results::Value)_scheduleTrigger->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::ScheduleTrigger::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _scheduleTrigger->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}
