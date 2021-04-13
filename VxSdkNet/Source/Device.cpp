/// <summary>
/// Implements the device class.
/// </summary>
#include "AnalyticSession.h"
#include "DbBackups.h"
#include "Device.h"
#include "Monitor.h"
#include "NewAnalyticSession.h"

using namespace System::Collections::Generic;

VxSdkNet::Device::Device(VxSdk::IVxDevice* vxDevice) {
    _device = vxDevice;
}

VxSdkNet::Device::!Device() {
    _device->Delete();
    _device = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Device::AddAnalyticSession(NewAnalyticSession^ newAnalyticSession) {
    VxSdk::VxNewAnalyticSession vxNewAnalyticSession;
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.dataEncodingId, Utils::ConvertCSharpString(newAnalyticSession->DataEncodingId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.dataSourceId, Utils::ConvertCSharpString(newAnalyticSession->DataSourceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.deviceId, Utils::ConvertCSharpString(newAnalyticSession->DeviceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.id, Utils::ConvertCSharpString(newAnalyticSession->Id).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.source, Utils::ConvertCSharpString(newAnalyticSession->Source).c_str());

    // Attempt to add the analytic session
    return VxSdkNet::Results::Value(_device->AddAnalyticSession(vxNewAnalyticSession));
}

VxSdkNet::Results::Value VxSdkNet::Device::CreateLog() {
    // Make the call to create a new log on the device
    VxSdk::VxResult::Value result = _device->CreateLog();
    // Unless there was an issue creating the log the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Device::DeleteAnalyticSession(AnalyticSession^ analyticSession) {
    // Create aa analytic session object
    VxSdk::IVxAnalyticSession* delAnalyticSession = analyticSession->_analyticSession;

    // To delete an analytic session simply make a DeleteAnalyticSession call
    VxSdk::VxResult::Value result = delAnalyticSession->DeleteAnalyticSession();
    // Unless there was an issue deleting the analytic session the result should be VxSdk::VxResult::kOK
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

List<VxSdkNet::AccessPoint^>^ VxSdkNet::Device::GetAccessPoints(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed access point objects
    List<AccessPoint^>^ mlist = gcnew List<AccessPoint^>();
    // Create a collection of unmanaged access point objects
    VxSdk::VxCollection<VxSdk::IVxAccessPoint**> accessPoints;

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
        accessPoints.filterSize = filters->Count;
        accessPoints.filters = collFilters;
    }

    // Make the GetAccessPoints call, which will return with the total count of access points, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _device->GetAccessPoints(accessPoints);
    // Unless there are no access points on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetAccessPoints call
        accessPoints.collection = new VxSdk::IVxAccessPoint * [accessPoints.collectionSize];
        result = _device->GetAccessPoints(accessPoints);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < accessPoints.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AccessPoint(accessPoints.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] accessPoints.collection;
    }
    return mlist;
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

List<VxSdkNet::AnalyticSession^>^ VxSdkNet::Device::GetAnalyticSessions(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed analytic sessions
    List<AnalyticSession^>^ mlist = gcnew List<AnalyticSession^>();
    // Create a collection of unmanaged analytic sessions
    VxSdk::VxCollection<VxSdk::IVxAnalyticSession**> analyticSessions;

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
        analyticSessions.filterSize = filters->Count;
        analyticSessions.filters = collFilters;
    }

    // Make the GetAnalyticSessions call, which will return with the total analytic session count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _device->GetAnalyticSessions(analyticSessions);
    // As long as there are analytic sessions for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxAnalyticSession collection
        analyticSessions.collection = new VxSdk::IVxAnalyticSession * [analyticSessions.collectionSize];
        result = _device->GetAnalyticSessions(analyticSessions);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < analyticSessions.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AnalyticSession(analyticSessions.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] analyticSessions.collection;
    }
    return mlist;
}

System::String^ VxSdkNet::Device::GetBackupUri() {
    char* backupEndpoint = nullptr;
    int size = 0;

    // If the backup uri is not available on the device the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _device->GetBackup(backupEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for backupEndpoint
        backupEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _device->GetBackup(backupEndpoint, size);
    }
    return Utils::ConvertCppString(backupEndpoint);
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

VxSdkNet::Results::Value VxSdkNet::Device::Replace(System::String^ replacementDeviceId) {
    // Make the call to replace this device
    VxSdk::VxResult::Value result = _device->Replace(Utils::ConvertCSharpString(replacementDeviceId).c_str());
    // Unless there was an issue replacing the device the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Device::RestoreBackup(System::String^ backupPath) {
    // Copy the backup file path to a new char
    int len = backupPath->Length + 1;
    char* backupFile = new char[len];
    VxSdk::Utilities::StrCopySafe(backupFile, Utils::ConvertCSharpString(backupPath).c_str(), len);

    // Restore the backup
    return (VxSdkNet::Results::Value)_device->RestoreBackup(backupFile);
}

VxSdkNet::Results::Value VxSdkNet::Device::Silence() {
    return (VxSdkNet::Results::Value)_device->Silence();
}

VxSdkNet::Results::Value VxSdkNet::Device::TriggerRefresh() {
    return (VxSdkNet::Results::Value)_device->TriggerRefresh();
}

VxSdkNet::Results::Value VxSdkNet::Device::UpdateSoftware(VxSdkNet::File^ updateFile) {
    return (VxSdkNet::Results::Value)_device->UpdateSoftware(*updateFile->_file);
}

bool VxSdkNet::Device::_CanCreateLogs() {
    bool result;
    _device->CanCreateLogs(result);
    return result;
}

VxSdkNet::Configuration::Auth^ VxSdkNet::Device::_GetAuthConfig() {
    // Get the auth configuration
    VxSdk::IVxConfiguration::Auth* authConfig = nullptr;
    VxSdk::VxResult::Value result = _device->GetAuthenticationConfiguration(authConfig);

    // Return the auth configuration if GetAuthenticationConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Auth(authConfig);
    }
    else if (authConfig != nullptr) {
        authConfig->Delete();
        authConfig = nullptr;
    }

    return nullptr;
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

VxSdkNet::DbBackups^ VxSdkNet::Device::_GetDatabaseBackups() {
    // Get the database backups for this this device
    VxSdk::IVxDbBackups* dbBackups = nullptr;
    VxSdk::VxResult::Value result = _device->GetDatabaseBackups(dbBackups);

    // Return the database backups if GetDatabaseBackups was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DbBackups(dbBackups);

    return nullptr;
}

VxSdkNet::Diagnostics^ VxSdkNet::Device::_GetDiagnostics() {
    // Get the diagnostics from the device
    VxSdk::VxDiagnostics* diagnostics = nullptr;
    VxSdk::VxResult::Value result = _device->GetDiagnostics(diagnostics);

    // Return the diagnostics if GetDiagnostics was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew Diagnostics(diagnostics);

    return nullptr;
}

List<System::String^>^ VxSdkNet::Device::_GetEndpoints() {
    // Create a list of strings
    List<System::String^>^ mlist = gcnew List<System::String^>();
    // Add each endpoint to the string list
    for (int i = 0; i < _device->endpointsSize; i++)
        mlist->Add(Utils::ConvertCppString(_device->endpoints[i]));

    return mlist;
}

List<System::String^>^ VxSdkNet::Device::_GetLicensableFeatures() {
    // Create a list of strings
    List<System::String^>^ mlist = gcnew List<System::String^>();
    // Add each licensable feature to the string list
    for (int i = 0; i < _device->licensableFeaturesSize; i++)
        mlist->Add(Utils::ConvertCppString(_device->licensableFeatures[i]));

    return mlist;
}

List<System::String^>^ VxSdkNet::Device::_GetLicensedFeatures() {
    // Create a list of strings
    List<System::String^>^ mlist = gcnew List<System::String^>();
    // Add each licensed feature to the string list
    for (int i = 0; i < _device->licensedFeaturesSize; i++)
        mlist->Add(Utils::ConvertCppString(_device->licensedFeatures[i]));

    return mlist;
}

VxSdkNet::ResourceLimits^ VxSdkNet::Device::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _device->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

VxSdkNet::Configuration::ThermalEtd^ VxSdkNet::Device::_GetThermalEtdConfig() {
    // Get the thermal etd configuration
    VxSdk::IVxConfiguration::ThermalEtd* thermalEtdConfig = nullptr;
    VxSdk::VxResult::Value result = _device->GetThermalEtdConfiguration(thermalEtdConfig);

    // Return the thermal etd configuration if GetThermalEtdConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::ThermalEtd(thermalEtdConfig);
    }
    else if (thermalEtdConfig != nullptr) {
        thermalEtdConfig->Delete();
        thermalEtdConfig = nullptr;
    }

    return nullptr;
}

VxSdkNet::Configuration::Time^ VxSdkNet::Device::_GetTimeConfig() {
    // Get the time configuration
    VxSdk::IVxConfiguration::Time* timeConfig = nullptr;
    VxSdk::VxResult::Value result = _device->GetTimeConfiguration(timeConfig);

    // Return the time configuration if GetTimeConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Time(timeConfig);
    }
    else if (timeConfig != nullptr) {
        timeConfig->Delete();
        timeConfig = nullptr;
    }

    return nullptr;
}

bool VxSdkNet::Device::_HasDiagnostics() {
    bool result;
    _device->HasDiagnostics(result);
    return result;
}

void VxSdkNet::Device::_SetEndpoints(List<System::String^>^ endpoints)
{
    int size = endpoints->Count;
    char** endpointUris = new char* [size];
    for (int i = 0; i < size; i++) {
        int uriLength = endpoints[i]->Length + 1;
        endpointUris[i] = new char[uriLength];
        VxSdk::Utilities::StrCopySafe(endpointUris[i], Utils::ConvertCSharpString(endpoints[i]).c_str(), uriLength);
    }

    _device->SetEndpoints(endpointUris, size);
    for (int i = 0; i < size; i++) {
        delete endpointUris[i];
        endpointUris[i] = nullptr;
    }

    delete[] endpointUris;
    endpointUris = nullptr;
}
