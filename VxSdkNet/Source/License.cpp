/// <summary>
/// Implements the license class.
/// </summary>
#include "License.h"

using namespace System::Collections::Generic;

VxSdkNet::License::License(VxSdk::IVxLicense* vxLicense) {
    _license = vxLicense;
}

VxSdkNet::License::!License() {
    _license->Delete();
    _license = nullptr;
}

List<VxSdkNet::LicenseFeature^>^ VxSdkNet::License::_GetLicenseFeatures() {
    // Create a list of managed license feature objects
    List<VxSdkNet::LicenseFeature^>^ mlist = gcnew List<VxSdkNet::LicenseFeature^>();
    // Create a collection of unmanaged license feature objects
    VxSdk::VxCollection<VxSdk::IVxLicenseFeature**> licenseFeatures;

    // Make the GetLicenseFeatures call, which will return with the total count of license features, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _license->GetLicenseFeatures(licenseFeatures);
    // Unless there are no license features on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetLicenseFeatures call
        licenseFeatures.collection = new VxSdk::IVxLicenseFeature*[licenseFeatures.collectionSize];
        result = _license->GetLicenseFeatures(licenseFeatures);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < licenseFeatures.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::LicenseFeature(licenseFeatures.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] licenseFeatures.collection;
    }
    return mlist;
}
