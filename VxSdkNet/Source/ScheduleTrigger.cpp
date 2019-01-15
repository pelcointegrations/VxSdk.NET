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
