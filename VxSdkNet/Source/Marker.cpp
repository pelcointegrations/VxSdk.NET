/// <summary>
/// Implements the Marker class.
/// </summary>
#include "Marker.h"
#include "Drawing.h"

using namespace System::Collections::Generic;

VxSdkNet::Marker::Marker(VxSdk::IVxMarker* vxMarker) {
    _marker = vxMarker;
}

VxSdkNet::Marker::!Marker() {
    _marker->Delete();
    _marker = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Marker::Refresh() {
    return (VxSdkNet::Results::Value)_marker->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Marker::RemoveAssociation() {
    return (VxSdkNet::Results::Value)_marker->DeleteAssociation();
}

VxSdkNet::Results::Value VxSdkNet::Marker::SetAssociation(DataSource^ dataSource) {
    // Make the call to set the associated data source
    VxSdk::VxResult::Value result = _marker->SetAssociation(*dataSource->_dataSource);
    // Unless there was an issue associating the data source the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Marker::SetAssociation(VxSdkNet::Drawing^ drawing) {
    // Make the call to set the associated drawing
    VxSdk::VxResult::Value result = _marker->SetAssociation(*drawing->_drawing);
    // Unless there was an issue associating the drawing the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Marker::SetCoordinates(float x, float y) {
    return (VxSdkNet::Results::Value)_marker->SetCoordinates(x, y);
}

VxSdkNet::DataSource^ VxSdkNet::Marker::_GetAssociatedDataSource() {
    // Get the data source
    VxSdk::IVxDataSource* dataSource = nullptr;
    VxSdk::VxResult::Value result = _marker->GetAssociation(dataSource);

    // Return the data source if GetAssociation was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataSource(dataSource);

    return nullptr;
}

VxSdkNet::Drawing^ VxSdkNet::Marker::_GetAssociatedDrawing() {
    // Get the drawing
    VxSdk::IVxDrawing* drawing = nullptr;
    VxSdk::VxResult::Value result = _marker->GetAssociation(drawing);

    // Return the drawing if GetAssociation was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Drawing(drawing);

    return nullptr;
}

VxSdkNet::Drawing^ VxSdkNet::Marker::_GetDrawing() {
    // Get the drawing
    VxSdk::IVxDrawing* drawing = nullptr;
    VxSdk::VxResult::Value result = _marker->GetDrawing(drawing);

    // Return the drawing if GetDrawing was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Drawing(drawing);

    return nullptr;
}

VxSdkNet::ResourceLimits^ VxSdkNet::Marker::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _marker->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}
