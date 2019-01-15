/// <summary>
/// Implements the device assignment class.
/// </summary>
#include "Device.h"
#include "DataStorage.h"

using namespace System::Collections::Generic;

VxSdkNet::DeviceAssignment::DeviceAssignment(VxSdk::IVxDeviceAssignment* vxDeviceAssignment) {
    _deviceAssignment = vxDeviceAssignment;
}

VxSdkNet::DeviceAssignment::!DeviceAssignment() {
    _deviceAssignment->Delete();
    _deviceAssignment = nullptr;
}

List<VxSdkNet::DataSource^>^ VxSdkNet::DeviceAssignment::GetDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data source objects
    List<VxSdkNet::DataSource^>^ mlist = gcnew List<VxSdkNet::DataSource^>();
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
    VxSdk::VxResult::Value result = _deviceAssignment->GetDataSources(dataSources);
    // Unless there are no data sources on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetDataSources call
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _deviceAssignment->GetDataSources(dataSources);
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

VxSdkNet::DataStorage^ VxSdkNet::DeviceAssignment::_GetDataStorage() {
    // Get the data storage object
    VxSdk::IVxDataStorage* dataStorage = nullptr;
    VxSdk::VxResult::Value result = _deviceAssignment->GetDataStorage(dataStorage);

    // Return the data storage if GetDataStorage was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataStorage(dataStorage);

    // Return nullptr if GetDataStorage is unsuccessful
    return nullptr;
}

VxSdkNet::Device^ VxSdkNet::DeviceAssignment::_GetDevice() {
    // Get the device object
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _deviceAssignment->GetDevice(device);

    // Return the device if GetDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Device(device);

    // Return nullptr if GetDevice is unsuccessful
    return nullptr;
}
