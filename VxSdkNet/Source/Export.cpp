/// <summary>
/// Implements the export class.
/// </summary>
#include "Export.h"

using namespace System::Collections::Generic;

VxSdkNet::Export::Export(VxSdk::IVxExport* vxExport) {
    _export = vxExport;
}

VxSdkNet::Export::!Export() {
    _export->Delete();
    _export = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Export::Refresh() {
    return (VxSdkNet::Results::Value)_export->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Export::RestoreExport() {
    return (VxSdkNet::Results::Value)_export->RestoreExport();
}

VxSdkNet::Results::Value VxSdkNet::Export::TrashExport() {
    return (VxSdkNet::Results::Value)_export->TrashExport();
}

List<VxSdkNet::ExportClip^>^ VxSdkNet::Export::_GetClips() {
    // Create a list of managed export objects
    List<VxSdkNet::ExportClip^>^ mlist = gcnew List<VxSdkNet::ExportClip^>();
    // Add each clip in the export to the list
    for (int i = 0; i < _export->exportClipSize; i++)
        mlist->Add(gcnew VxSdkNet::ExportClip(_export->exportClips[i]));

    return mlist;
}

VxSdkNet::ExportStream^ VxSdkNet::Export::_GetExportStream() {
    // Get the export stream for this export
    VxSdk::IVxExportStream* exportStream = nullptr;
    VxSdk::VxResult::Value result = _export->GetExportStream(exportStream);

    // Return the export stream if GetExportStream was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::ExportStream(exportStream);

    return nullptr;
}

VxSdkNet::User^ VxSdkNet::Export::_GetOwner() {
    // Get the user that owns this export
    VxSdk::IVxUser* user = nullptr;
    VxSdk::VxResult::Value result = _export->GetOwner(user);

    // Return the user if GetOwner was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::User(user);

    return nullptr;
}
