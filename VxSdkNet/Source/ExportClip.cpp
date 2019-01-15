/// <summary>
/// Implements the export clip class.
/// </summary>
#include "ExportClip.h"

VxSdkNet::ExportClip::ExportClip(VxSdk::IVxExportClip* vxExportClip) {
    _exportClip = vxExportClip;
}
