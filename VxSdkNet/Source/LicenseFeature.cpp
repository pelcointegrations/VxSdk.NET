/// <summary>
/// Implements the license feature class.
/// </summary>
#include "LicenseFeature.h"

using namespace System::Collections::Generic;

VxSdkNet::LicenseFeature::LicenseFeature(VxSdk::IVxLicenseFeature* vxLicenseFeature) {
    _licenseFeature = vxLicenseFeature;
}

VxSdkNet::LicenseFeature::!LicenseFeature() {
    _licenseFeature->Delete();
    _licenseFeature = nullptr;
}

List<VxSdkNet::Device^>^ VxSdkNet::LicenseFeature::GetCommissionedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed device objects
    List<VxSdkNet::Device^>^ mlist = gcnew List<VxSdkNet::Device^>();
    // Create a collection of unmanaged device objects
    VxSdk::VxCollection<VxSdk::IVxDevice**> devices;

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
        devices.filterSize = filters->Count;
        devices.filters = collFilters;
    }

    // Make the GetCommissionedDevices call, which will return with the total count of devices, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _licenseFeature->GetCommissionedDevices(devices);
    // Unless there are no devices on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetCommissionedDevices call
        devices.collection = new VxSdk::IVxDevice*[devices.collectionSize];
        result = _licenseFeature->GetCommissionedDevices(devices);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < devices.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Device(devices.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] devices.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::LicenseFeature::Link(VxSdkNet::Device^ device) {
    // Link a device to this license feature
    VxSdk::VxResult::Value result = _licenseFeature->Link(*device->_device);
    // Unless there was an issue linking the device the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::LicenseFeature::Refresh() {
    return (VxSdkNet::Results::Value)_licenseFeature->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::LicenseFeature::UnLink(VxSdkNet::Device^ device) {
    // Unlink a device from this license feature
    VxSdk::VxResult::Value result = _licenseFeature->UnLink(*device->_device);
    // Unless there was an issue unlinking the device the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

System::String^ VxSdkNet::LicenseFeature::_GetCapabilityRequest() {
    char* capRequestEndpoint = nullptr;
    int size = 0;

    // If the capability request uri is not available the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _licenseFeature->GetCapabilityRequest(capRequestEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for capRequestEndpoint
        capRequestEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _licenseFeature->GetCapabilityRequest(capRequestEndpoint, size);
    }
    return Utils::ConvertCppString(capRequestEndpoint);
}