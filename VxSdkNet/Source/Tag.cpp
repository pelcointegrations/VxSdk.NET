/// <summary>
/// Implements the tag class.
/// </summary>

#include "Device.h"
#include "Tag.h"
#include "User.h"

using namespace System::Collections::Generic;

VxSdkNet::Tag::Tag(VxSdk::IVxTag* vxTag) {
    _tag = vxTag;
}

VxSdkNet::Tag::!Tag() {
    _tag->Delete();
    _tag = nullptr;
}

System::Collections::Generic::List<VxSdkNet::DataSource^>^ VxSdkNet::Tag::GetLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data sources
    List<DataSource^>^ mlist = gcnew List<DataSource^>();
    // Create a collection of unmanaged data sources
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

    // Make the GetLinkedDataSources call, which will return with the total data source count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _tag->GetLinks(dataSources);
    // As long as there are data sources linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataSource collection
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _tag->GetLinks(dataSources);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataSources.collectionSize; i++)
                mlist->Add(gcnew DataSource(dataSources.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataSources.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::Device^>^ VxSdkNet::Tag::GetLinkedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed devices
    List<Device^>^ mlist = gcnew List<Device^>();
    // Create a collection of unmanaged devices
    VxSdk::VxCollection<VxSdk::IVxDevice**> devices;

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
        devices.filterSize = filters->Count;
        devices.filters = collFilters;
    }

    // Make the GetLinkedDevices call, which will return with the total device count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _tag->GetLinks(devices);
    // As long as there are devices linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDevice collection
        devices.collection = new VxSdk::IVxDevice*[devices.collectionSize];
        result = _tag->GetLinks(devices);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < devices.collectionSize; i++)
                mlist->Add(gcnew Device(devices.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] devices.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::Tag::Link(List<VxSdkNet::DataSource^>^ dataSources) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of data sources
    for (int i = 0; i < dataSources->Count; i++) {
        // Link the data sources to the tag
        result = _tag->Link(*dataSources[i]->_dataSource);
    }

    // Unless there was an issue linking the data sources the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Tag::Link(List<VxSdkNet::Device^>^ devices) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of devices
    for (int i = 0; i < devices->Count; i++) {
        // Link the devices to the tag
        result = _tag->Link(*devices[i]->_device);
    }

    // Unless there was an issue linking the devices the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Tag::Merge(VxSdkNet::Tag^ tag) {
    // Make the call to merge this tag into an existing tag
    VxSdk::VxResult::Value result = _tag->Merge(*tag->_tag);
    // Unless there was an issue merging tags the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Tag::Refresh() {
    return (VxSdkNet::Results::Value)_tag->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Tag::Unlink(List<VxSdkNet::DataSource^>^ dataSources) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of data sources
    for (int i = 0; i < dataSources->Count; i++) {
        // UnLink the data sources to the tag
        result = _tag->UnLink(*dataSources[i]->_dataSource);
    }

    // Unless there was an issue unlinking the data sources the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Tag::Unlink(List<VxSdkNet::Device^>^ devices) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of devices
    for (int i = 0; i < devices->Count; i++) {
        // UnLink the devices to the tag
        result = _tag->UnLink(*devices[i]->_device);
    }

    // Unless there was an issue unlinking the devices the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::User^ VxSdkNet::Tag::_GetOwner() {
    // Get the user that owns this tag
    VxSdk::IVxUser* user = nullptr;
    VxSdk::VxResult::Value result = _tag->GetOwner(user);

    // Return the user if GetOwner was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::User(user);

    return nullptr;
}

VxSdkNet::Tag^ VxSdkNet::Tag::_GetParent() {
    // Get the parent tag of this tag, if available
    VxSdk::IVxTag* tag = nullptr;
    VxSdk::VxResult::Value result = _tag->GetParent(tag);

    // Return the parent tag if GetParent was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Tag(tag);

    return nullptr;
}
