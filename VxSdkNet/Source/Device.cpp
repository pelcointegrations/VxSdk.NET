/// <summary>
/// Implements the device class.
/// </summary>
#include "Device.h"
#include "Monitor.h"

using namespace System::Collections::Generic;

VxSdkNet::Device::Device(VxSdk::IVxDevice* vxDevice) {
    _device = vxDevice;
}

VxSdkNet::Device::!Device() {
    _device->Delete();
    _device = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Device::CreateLog() {
    // Make the call to create a new log on the device
    VxSdk::VxResult::Value result = _device->CreateLog();
    // Unless there was an issue creating the log the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Device::DeleteLog(VxSdkNet::Log^ logItem) {
    // Create a log object using the logItem
    VxSdk::IVxLog* delLog = logItem->_log;

    // To delete a log simply make a DeleteLog call
    VxSdk::VxResult::Value result = delLog->DeleteLog();
    // Unless there was an issue deleting the log the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

List<VxSdkNet::AlarmInput^>^ VxSdkNet::Device::GetAlarmInputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed alarm input objects
    List<AlarmInput^>^ mlist = gcnew List<AlarmInput^>();
    // Create a collection of unmanaged alarm input objects
    VxSdk::VxCollection<VxSdk::IVxAlarmInput**> alarmInputs;

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
        alarmInputs.filterSize = filters->Count;
        alarmInputs.filters = collFilters;
    }

    // Make the GetAlarmInputs call, which will return with the total count of alarm inputs, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _device->GetAlarmInputs(alarmInputs);
    // Unless there are no alarm inputs hosted on the device, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetAlarmInputs call
        alarmInputs.collection = new VxSdk::IVxAlarmInput*[alarmInputs.collectionSize];
        result = _device->GetAlarmInputs(alarmInputs);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < alarmInputs.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AlarmInput(alarmInputs.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] alarmInputs.collection;
    }
    return mlist;
}

List<VxSdkNet::DataSource^>^ VxSdkNet::Device::GetDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data source objects
    List<DataSource^>^ mlist = gcnew List<DataSource^>();
    // Create a collection of unmanaged data source objects
    VxSdk::VxCollection<VxSdk::IVxDataSource**> dataSources;

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
        dataSources.filterSize = filters->Count;
        dataSources.filters = collFilters;
    }

    // Make the GetDataSources call, which will return with the total count of data sources, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _device->GetDataSources(dataSources);
    // Unless there are no data sources hosted on the device, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetDataSources call
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _device->GetDataSources(dataSources);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataSources.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::DataSource(dataSources.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataSources.collection;
    }
    return mlist;
}

List<VxSdkNet::DeviceAssignment^>^ VxSdkNet::Device::GetDeviceAssignments(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed device assignment objects
    List<DeviceAssignment^>^ mlist = gcnew List<DeviceAssignment^>();
    // Create a collection of unmanaged device assignment objects
    VxSdk::VxCollection<VxSdk::IVxDeviceAssignment**> deviceAssignments;

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
        deviceAssignments.filterSize = filters->Count;
        deviceAssignments.filters = collFilters;
    }

    // Make the GetDeviceAssignments call, which will return with the total count of device assignments, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _device->GetDeviceAssignments(deviceAssignments);
    // Unless there are no device assignments hosted on the device, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetDeviceAssignments call
        deviceAssignments.collection = new VxSdk::IVxDeviceAssignment*[deviceAssignments.collectionSize];
        result = _device->GetDeviceAssignments(deviceAssignments);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < deviceAssignments.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::DeviceAssignment(deviceAssignments.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] deviceAssignments.collection;
    }
    return mlist;
}

List<VxSdkNet::Log^>^ VxSdkNet::Device::GetLogs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed log objects
    List<Log^>^ mlist = gcnew List<Log^>();
    // Create a collection of unmanaged log objects
    VxSdk::VxCollection<VxSdk::IVxLog**> logs;

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
        logs.filterSize = filters->Count;
        logs.filters = collFilters;
    }

    // Make the GetLogs call, which will return with the total count of logs, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _device->GetLogs(logs);
    // Unless there are no logs on the device, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetLogs call
        logs.collection = new VxSdk::IVxLog*[logs.collectionSize];
        result = _device->GetLogs(logs);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < logs.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Log(logs.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] logs.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::Monitor^>^ VxSdkNet::Device::GetMonitors(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed monitor objects
    List<Monitor^>^ mlist = gcnew List<Monitor^>();
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

    // Make the GetMonitors call, which will return with the total count of monitors, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _device->GetMonitors(monitors);
    // Unless there are no monitors hosted by the device, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetMonitors call
        monitors.collection = new VxSdk::IVxMonitor*[monitors.collectionSize];
        result = _device->GetMonitors(monitors);
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

List<VxSdkNet::RelayOutput^>^ VxSdkNet::Device::GetRelayOutputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed relay output objects
    List<RelayOutput^>^ mlist = gcnew List<RelayOutput^>();
    // Create a collection of unmanaged relay output objects
    VxSdk::VxCollection<VxSdk::IVxRelayOutput**> relayOutputs;

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
        relayOutputs.filterSize = filters->Count;
        relayOutputs.filters = collFilters;
    }

    // Make the GetRelayOutputs call, which will return with the total count of relay outputs, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _device->GetRelayOutputs(relayOutputs);
    // Unless there are no relay outputs hosted on the device, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetRelayOutputs call
        relayOutputs.collection = new VxSdk::IVxRelayOutput*[relayOutputs.collectionSize];
        result = _device->GetRelayOutputs(relayOutputs);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < relayOutputs.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::RelayOutput(relayOutputs.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] relayOutputs.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::Device::Refresh() {
    return (VxSdkNet::Results::Value)_device->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Device::Silence() {
    return (VxSdkNet::Results::Value)_device->Silence();
}

bool VxSdkNet::Device::_CanCreateLogs() {
    bool result;
    _device->CanCreateLogs(result);
    return result;
}

VxSdkNet::DataStorage^ VxSdkNet::Device::_GetDataStorage() {
    // Get the data storage hosted by this device
    VxSdk::IVxDataStorage* dataStorage = nullptr;
    VxSdk::VxResult::Value result = _device->GetDataStorage(dataStorage);

    // Return the driver if GetDataStorage was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataStorage(dataStorage);

    return nullptr;
}
