/// <summary>
/// Implements the volumeGroup class.
/// </summary>
#include "VolumeGroup.h"
#include "Volume.h"

using namespace System::Collections::Generic;

VxSdkNet::VolumeGroup::VolumeGroup(VxSdk::IVxVolumeGroup* vxVolumeGroup) {
    _volumeGroup = vxVolumeGroup;
}

VxSdkNet::VolumeGroup::!VolumeGroup() {
    _volumeGroup->Delete();
    _volumeGroup = nullptr;
}

List<VxSdkNet::ResourceRel^>^ VxSdkNet::VolumeGroup::GetVolumeRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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

    // Make the GetVolumeRelations call, which will return with the total resource count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _volumeGroup->GetVolumeRelations(resourceRels);
    // As long as there are related resources for this volume group the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxResourceRel collection
        resourceRels.collection = new VxSdk::IVxResourceRel * [resourceRels.collectionSize];
        result = _volumeGroup->GetVolumeRelations(resourceRels);
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

VxSdkNet::Results::Value VxSdkNet::VolumeGroup::Refresh() {
    return (VxSdkNet::Results::Value)_volumeGroup->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::VolumeGroup::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _volumeGroup->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

List<VxSdkNet::Volume^>^ VxSdkNet::VolumeGroup::_GetVolumes() {
    // Create a list of managed volume objects
    List<Volume^>^ mlist = gcnew List<Volume^>();
    for (int i = 0; i < _volumeGroup->volumesSize; i++)
        mlist->Add(gcnew Volume(_volumeGroup->volumes[i]));

    return mlist;
}
