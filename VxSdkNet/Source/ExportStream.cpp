/// <summary>
/// Implements the export stream class.
/// </summary>
#include "ExportStream.h"

using namespace System::Collections::Generic;

VxSdkNet::ExportStream::ExportStream(VxSdk::IVxExportStream* vxExportStream) {
    _exportStream = vxExportStream;
}

VxSdkNet::ExportStream::!ExportStream() {
    _exportStream->Delete();
    _exportStream = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::ExportStream::Halt() {
    return (VxSdkNet::Results::Value)_exportStream->Halt();
}

VxSdkNet::Results::Value VxSdkNet::ExportStream::Prepare() {
    return (VxSdkNet::Results::Value)_exportStream->Prepare();
}

VxSdkNet::Results::Value VxSdkNet::ExportStream::Refresh() {
    return (VxSdkNet::Results::Value)_exportStream->Refresh();
}

List<VxSdkNet::ExportStreamClip^>^ VxSdkNet::ExportStream::_GetStreamClips() {
    // Create a list of managed export stream clip objects
    List<VxSdkNet::ExportStreamClip^>^ mlist = gcnew List<VxSdkNet::ExportStreamClip^>();
    // Add each clip in the export stream to the list
    for (int i = 0; i < _exportStream->exportStreamClipSize; i++)
        mlist->Add(gcnew VxSdkNet::ExportStreamClip(_exportStream->exportStreamClips[i]));

    return mlist;
}

