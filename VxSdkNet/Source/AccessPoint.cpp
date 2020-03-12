/// <summary>
/// Implements the access point class.
/// </summary>
#include "AccessPoint.h"
#include "Device.h"

using namespace System::Collections::Generic;

VxSdkNet::AccessPoint::AccessPoint(VxSdk::IVxAccessPoint* vxAccessPoint) {
    _accessPoint = vxAccessPoint;
}

VxSdkNet::AccessPoint::!AccessPoint() {
    _accessPoint->Delete();
    _accessPoint = nullptr;
}

List<VxSdkNet::ResourceRel^>^ VxSdkNet::AccessPoint::GetRelations(Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed related resources
    List<ResourceRel^>^ mlist = gcnew List<ResourceRel^>();
    // Create a collection of unmanaged related resources
    VxSdk::VxCollection<VxSdk::IVxResourceRel**> resourceRels;

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
        resourceRels.filterSize = filters->Count;
        resourceRels.filters = collFilters;
    }

    // Make the GetRelations call, which will return with the total resource count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _accessPoint->GetRelations(resourceRels);
    // As long as there are related resources for this access point the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxResourceRel collection
        resourceRels.collection = new VxSdk::IVxResourceRel * [resourceRels.collectionSize];
        result = _accessPoint->GetRelations(resourceRels);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < resourceRels.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::ResourceRel(resourceRels.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] resourceRels.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::AccessPoint::Lock(int seconds) {
    return (Results::Value)_accessPoint->Lock(seconds);
}

VxSdkNet::Results::Value VxSdkNet::AccessPoint::Refresh() {
    return (Results::Value)_accessPoint->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::AccessPoint::Unlock(int seconds) {
    return (Results::Value)_accessPoint->Unlock(seconds);
}

VxSdkNet::Device^ VxSdkNet::AccessPoint::_GetHostDevice() {
    // Get the host device
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _accessPoint->GetHostDevice(device);

    // Return the host device if GetHostDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew Device(device);

    return nullptr;
}

VxSdkNet::ResourceLimits^ VxSdkNet::AccessPoint::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _accessPoint->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}
