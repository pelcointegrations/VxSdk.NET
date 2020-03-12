/// <summary>
/// Implements the MonitorCell class.
/// </summary>
#include "MonitorCell.h"

VxSdkNet::MonitorCell::MonitorCell(VxSdk::IVxMonitorCell* vxMonitorCell) {
    _monitorCell = vxMonitorCell;
}

VxSdkNet::MonitorCell::!MonitorCell() {
    _monitorCell->Delete();
    _monitorCell = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::MonitorCell::Disconnect() {
    // Call SetDataSource with a nullptr to remove the current data source
    return (VxSdkNet::Results::Value)_monitorCell->SetDataSource(nullptr);
}

VxSdkNet::Results::Value VxSdkNet::MonitorCell::GoToLive() {
    // Call SetTime with a nullptr to move the playback position to live
    return (VxSdkNet::Results::Value)_monitorCell->SetTime(nullptr);
}

VxSdkNet::Results::Value VxSdkNet::MonitorCell::Refresh() {
    return (VxSdkNet::Results::Value)_monitorCell->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::MonitorCell::SetCropBounds(float height, float width) {
    return (VxSdkNet::Results::Value)_monitorCell->SetCropBounds(height, width);
}

VxSdkNet::Results::Value VxSdkNet::MonitorCell::SetLocation(int x, int y, int z) {
    return (VxSdkNet::Results::Value)_monitorCell->SetLocation(x, y, z);
}

VxSdkNet::ResourceLimits^ VxSdkNet::MonitorCell::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _monitorCell->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}
