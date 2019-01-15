/// <summary>
/// Implements the relay output class.
/// </summary>
#include "Device.h"
#include "RelayOutput.h"

using namespace System::Collections::Generic;

VxSdkNet::RelayOutput::RelayOutput(VxSdk::IVxRelayOutput* vxRelayOutput) {
    _relayOutput = vxRelayOutput;
}

VxSdkNet::RelayOutput::!RelayOutput() {
    _relayOutput->Delete();
    _relayOutput = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::RelayOutput::Refresh() {
    return (VxSdkNet::Results::Value)_relayOutput->Refresh();
}

VxSdkNet::Device^ VxSdkNet::RelayOutput::_GetHostDevice() {
    // Get the host device
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _relayOutput->GetHostDevice(device);

    // Return the host device if GetHostDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Device(device);

    return nullptr;
}

void VxSdkNet::RelayOutput::_SetRelayState(RelayStates state) {
    switch(state) {
        case RelayStates::Active:
            _relayOutput->Activate();
            return;
        case RelayStates::Inactive:
            _relayOutput->Deactivate();
            return;
        case RelayStates::Unknown:
            return;
    }
}
