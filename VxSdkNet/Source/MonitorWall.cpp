/// <summary>
/// Implements the monitor class.
/// </summary>
#include "Device.h"
#include "MonitorWall.h"

using namespace System::Collections::Generic;

VxSdkNet::MonitorWall::MonitorWall(VxSdk::IVxMonitorWall* vxMonitorWall) {
    _monitorWall = vxMonitorWall;
}

VxSdkNet::MonitorWall::!MonitorWall() {
    _monitorWall->Delete();
    _monitorWall = nullptr;
}

List<VxSdkNet::Monitor^>^ VxSdkNet::MonitorWall::GetMonitors(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed monitor objects
    List<VxSdkNet::Monitor^>^ mlist = gcnew List<VxSdkNet::Monitor^>();
    // Create a collection of unmanaged monitor objects
    VxSdk::VxCollection<VxSdk::IVxMonitor**> monitors;

    if (filters != nullptr && filters->Count > 0) {
        // Create our filter
        VxSdk::VxCollectionFilter* collFilters = new VxSdk::VxCollectionFilter[filters->Count];
        int i = 0;
        for each (KeyValuePair<Filters::Value, System::String^>^ kvp in filters)
        {
            collFilters[i].key = static_cast<VxSdk::VxCollectionFilterItem::Value>(kvp->Key);
            VxSdk::Utilities::StrCopySafe(collFilters[i++].value, Utils::ConvertCSharpString(kvp->Value).c_str());
        }

        // Add the filters to the collection 
        monitors.filterSize = filters->Count;
        monitors.filters = collFilters;
    }

    // Make the GetExports call, which will return with the total export count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _monitorWall->GetMonitors(monitors);
    // Unless there are no exports on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxExport collection
        monitors.collection = new VxSdk::IVxMonitor*[monitors.collectionSize];
        result = _monitorWall->GetMonitors(monitors);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < monitors.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Monitor(monitors.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] monitors.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::MonitorWall::Refresh() {
    return (VxSdkNet::Results::Value)_monitorWall->Refresh();
}
