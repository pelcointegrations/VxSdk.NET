/// <summary>
/// Implements the alarm input class.
/// </summary>
#include "AlarmInput.h"
#include "Device.h"

using namespace System::Collections::Generic;

VxSdkNet::AlarmInput::AlarmInput(VxSdk::IVxAlarmInput* vxAlarmInput) {
    _alarmInput = vxAlarmInput;
}

VxSdkNet::AlarmInput::!AlarmInput() {
    _alarmInput->Delete();
    _alarmInput = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::AlarmInput::Refresh() {
    return (VxSdkNet::Results::Value)_alarmInput->Refresh();
}

VxSdkNet::Device^ VxSdkNet::AlarmInput::_GetHostDevice() {
    // Get the host device
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _alarmInput->GetHostDevice(device);

    // Return the host device if GetHostDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Device(device);

    return nullptr;
}
