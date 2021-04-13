/// <summary>
/// Implements the monitor class.
/// </summary>
#include "Device.h"
#include "Monitor.h"
#include "MonitorCell.h"

using namespace System::Collections::Generic;

VxSdkNet::Monitor::Monitor(VxSdk::IVxMonitor* vxMonitor) {
    _monitor = vxMonitor;
}

VxSdkNet::Monitor::!Monitor() {
    _monitor->Delete();
    _monitor = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Monitor::Refresh() {
    return (VxSdkNet::Results::Value)_monitor->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Monitor::SetResolution(int resolutionX, int resolutionY) {
    return (VxSdkNet::Results::Value)_monitor->SetResolution(resolutionX, resolutionY);
}

VxSdkNet::Device^ VxSdkNet::Monitor::_GetHostDevice() {
    // Get the device which hosts this monitor
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _monitor->GetHostDevice(device);

    // Return the device if GetHostDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew Device(device);

    return nullptr;
}

VxSdkNet::ResourceLimits^ VxSdkNet::Monitor::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _monitor->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

List<VxSdkNet::MonitorCell^>^ VxSdkNet::Monitor::_GetMonitorCells() {
    // Create a list of managed monitor cell objects
    List<MonitorCell^>^ mlist = gcnew List<MonitorCell^>();
    // Create a collection of unmanaged monitor cell objects
    VxSdk::VxCollection<VxSdk::IVxMonitorCell**> monitorCells;

    // Make the call, which will return with the total count of monitor cells, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _monitor->GetMonitorCells(monitorCells);
    // Unless there are no monitor cells on the monitor, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetMonitorCells call
        monitorCells.collection = new VxSdk::IVxMonitorCell*[monitorCells.collectionSize];
        result = _monitor->GetMonitorCells(monitorCells);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < monitorCells.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::MonitorCell(monitorCells.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] monitorCells.collection;
    }
    return mlist;
}

List<VxSdkNet::Monitor::Layouts>^ VxSdkNet::Monitor::_GetAvailableLayouts() {
    // Create a list of managed layout objects
    List<VxSdkNet::Monitor::Layouts>^ mlist = gcnew List<VxSdkNet::Monitor::Layouts>();
    // Create a collection of unmanaged layout objects
    VxSdk::VxCollection<VxSdk::VxCellLayout::Value*> availableLayouts;

    // Make the call, which will return with the total count of available layouts, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _monitor->GetAvailableLayouts(availableLayouts);
    // Unless there are no available layouts for the monitor, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetAvailableLayouts call
        availableLayouts.collection = new VxSdk::VxCellLayout::Value[availableLayouts.collectionSize];
        result = _monitor->GetAvailableLayouts(availableLayouts);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < availableLayouts.collectionSize; i++)
            {
                VxSdkNet::Monitor::Layouts limit = (VxSdkNet::Monitor::Layouts)availableLayouts.collection[i];
                mlist->Add(limit);
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] availableLayouts.collection;
    }
    return mlist;
}
