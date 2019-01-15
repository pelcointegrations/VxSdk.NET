/// <summary>
/// Implements the resourceRel class.
/// </summary>

#include "ResourceRel.h"

using namespace System::Collections::Generic;

VxSdkNet::ResourceRel::ResourceRel(VxSdk::IVxResourceRel* vxResourceRel) {
    _resourceRel = vxResourceRel;
}

VxSdkNet::ResourceRel::!ResourceRel() {
    _resourceRel->Delete();
    _resourceRel = nullptr;
}


VxSdkNet::Results::Value VxSdkNet::ResourceRel::Refresh() {
    return (VxSdkNet::Results::Value)_resourceRel->Refresh();
}

VxSdkNet::DataSource^ VxSdkNet::ResourceRel::_GetResource() {
    // Get the data source object
    VxSdk::IVxDataSource* dataSource = nullptr;
    VxSdk::VxResult::Value result = _resourceRel->GetResource(dataSource);

    // Return the data source if GetResource was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataSource(dataSource);

    return nullptr;
}
