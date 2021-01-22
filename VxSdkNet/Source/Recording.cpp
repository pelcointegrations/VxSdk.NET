/// <summary>
/// Implements the recording class.
/// </summary>
#include "Recording.h"

using namespace System::Collections::Generic;

VxSdkNet::Recording::Recording(VxSdk::IVxRecording* vxRecording) {
    _recording = vxRecording;
}

VxSdkNet::Recording::!Recording() {
    _recording->Delete();
    _recording = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Recording::Refresh() {
    return (VxSdkNet::Results::Value)_recording->Refresh();
}

VxSdkNet::DataSource^ VxSdkNet::Recording::_GetDataSource() {
    // Get the data source
    VxSdk::IVxDataSource* dataSource = nullptr;
    VxSdk::VxResult::Value result = _recording->GetDataSource(dataSource);

    // Return the data source if GetDataSource was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataSource(dataSource);

    return nullptr;
}
