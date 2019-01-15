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
