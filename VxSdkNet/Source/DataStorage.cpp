/// <summary>
/// Implements the data storage class.
/// </summary>
#include "DataStorage.h"

using namespace System::Collections::Generic;

VxSdkNet::DataStorage::DataStorage(VxSdk::IVxDataStorage* vxDataStorage) {
    _dataStorage = vxDataStorage;
}

VxSdkNet::DataStorage::!DataStorage() {
    _dataStorage->Delete();
    _dataStorage = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::DataStorage::AddClip(VxSdkNet::NewClip^ newClip) {
    // Create a new clip object and populate its fields using newClip
    VxSdk::VxNewClip vxNewClip;
    VxSdk::Utilities::StrCopySafe(vxNewClip.dataSourceId, Utils::ConvertSysString(newClip->DataSourceId));
    VxSdk::Utilities::StrCopySafe(vxNewClip.dataStorageId, Utils::ConvertSysString(newClip->DataStorageId));
    VxSdk::Utilities::StrCopySafe(vxNewClip.startTime, Utils::ConvertDateTimeToChar(newClip->StartTime));
    VxSdk::Utilities::StrCopySafe(vxNewClip.endTime, Utils::ConvertDateTimeToChar(newClip->EndTime));

    // Make the call to add the clip to the data storage 
    VxSdk::VxResult::Value result = _dataStorage->AddClip(vxNewClip);
    // Unless there was an issue adding the clip the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::DataStorage::AssignDevice(VxSdkNet::NewDeviceAssignment^ newDeviceAssignment) {
    // Create a new device assignment object and populate its fields using newDeviceAssignment
    VxSdk::VxNewDeviceAssignment vxNewDeviceAssignment;
    VxSdk::Utilities::StrCopySafe(vxNewDeviceAssignment.deviceId, Utils::ConvertSysString(newDeviceAssignment->DeviceId));
    int size = newDeviceAssignment->DataSourceIds->Count;

    vxNewDeviceAssignment.dataSourceIdSize = size;
    vxNewDeviceAssignment.dataSourceIds = new char*[size];
    for (int i = 0; i < size; i++) {
        int idLength = newDeviceAssignment->DataSourceIds[i]->Length + 1;
        vxNewDeviceAssignment.dataSourceIds[i] = new char[idLength];
        VxSdk::Utilities::StrCopySafe(vxNewDeviceAssignment.dataSourceIds[i], Utils::ConvertSysString(newDeviceAssignment->DataSourceIds[i]), idLength);
    }

    // Make the call to add the situation into VideoXpert
    VxSdk::VxResult::Value result = _dataStorage->AssignDevice(vxNewDeviceAssignment);
    // Unless there was an issue adding the situation the result should be VxSdk::VxResult::kOK
    if (result == VxSdk::VxResult::kOK) {
        // Remove the memory we previously allocated
        delete[] vxNewDeviceAssignment.dataSourceIds;
    }
    return VxSdkNet::Results::Value(result);
}

List<VxSdkNet::DataSource^>^ VxSdkNet::DataStorage::GetDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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
            VxSdk::Utilities::StrCopySafe(collFilters[i++].value, Utils::ConvertSysString(kvp->Value));
        }

        // Add the filters to the collection 
        dataSources.filterSize = filters->Count;
        dataSources.filters = collFilters;
    }

    // Make the GetDataSources call, which will return with the total count of data sources, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataStorage->GetDataSources(dataSources);
    // Unless there are no data sources on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetDataSources call
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _dataStorage->GetDataSources(dataSources);
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

List<VxSdkNet::DeviceAssignment^>^ VxSdkNet::DataStorage::GetDeviceAssignments(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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
            VxSdk::Utilities::StrCopySafe(collFilters[i++].value, Utils::ConvertSysString(kvp->Value));
        }

        // Add the filters to the collection 
        deviceAssignments.filterSize = filters->Count;
        deviceAssignments.filters = collFilters;
    }

    // Make the GetDeviceAssignments call, which will return with the total count of device assignments, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataStorage->GetDeviceAssignments(deviceAssignments);
    // Unless there are no device assignments on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetDeviceAssignments call
        deviceAssignments.collection = new VxSdk::IVxDeviceAssignment*[deviceAssignments.collectionSize];
        result = _dataStorage->GetDeviceAssignments(deviceAssignments);
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

VxSdkNet::Results::Value VxSdkNet::DataStorage::Refresh() {
    return (VxSdkNet::Results::Value)_dataStorage->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::DataStorage::UnassignDevice(VxSdkNet::Device^ device) {
    // Create an IVxDevice object using the device
    VxSdk::IVxDevice* delDevice = device->_device;

    // Call UnassignDevice using the IVxDevice object
    VxSdk::VxResult::Value result = _dataStorage->UnassignDevice(*delDevice);
    // Unless there was an issue unassigning the device the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Device^ VxSdkNet::DataStorage::_GetHostDevice() {
    // Get the device which hosts this data storage
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _dataStorage->GetHostDevice(device);

    // Return the device if GetHostDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew Device(device);

    return nullptr;
}

VxSdkNet::Configuration::Storage^ VxSdkNet::DataStorage::_GetStorageConfig() {
    // Get the storage config
    VxSdk::IVxConfiguration::Storage* storageConfig = nullptr;
    VxSdk::VxResult::Value result = _dataStorage->GetStorageConfiguration(storageConfig);

    // Return the storage config if GetStorageConfiguration was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Configuration::Storage(storageConfig);

    return nullptr;
}
