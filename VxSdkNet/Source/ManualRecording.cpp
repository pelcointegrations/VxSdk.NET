/// <summary>
/// Implements the manual recording class.
/// </summary>
#include "ManualRecording.h"

using namespace System::Collections::Generic;

VxSdkNet::ManualRecording::ManualRecording(VxSdk::IVxManualRecording* vxManualRecording) {
    _manualRecording = vxManualRecording;
}

VxSdkNet::ManualRecording::!ManualRecording() {
    _manualRecording->Delete();
    _manualRecording = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::ManualRecording::Refresh() {
    return (VxSdkNet::Results::Value)_manualRecording->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::ManualRecording::ResetExpirationTimers() {
    return (VxSdkNet::Results::Value)_manualRecording->ResetExpirationTimers();
}

VxSdkNet::DataSource^ VxSdkNet::ManualRecording::_GetDataSource() {
    // Get the data source
    VxSdk::IVxDataSource* dataSource = nullptr;
    VxSdk::VxResult::Value result = _manualRecording->GetDataSource(dataSource);

    // Return the data source if GetDataSource was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataSource(dataSource);

    return nullptr;
}
