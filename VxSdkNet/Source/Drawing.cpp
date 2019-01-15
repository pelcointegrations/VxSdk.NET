/// <summary>
/// Implements the Drawing class.
/// </summary>
#include "Drawing.h"

using namespace System::Collections::Generic;

VxSdkNet::Drawing::Drawing(VxSdk::IVxDrawing* vxDrawing) {
    _drawing = vxDrawing;
}

VxSdkNet::Drawing::!Drawing() {
    _drawing->Delete();
    _drawing = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Drawing::AddMarker(NewMarker^ newMarker) {
    // Create a new marker object and populate its fields using newMarker
    VxSdk::VxNewMarker vxNewMarker;
    VxSdk::Utilities::StrCopySafe(vxNewMarker.associatedDataSourceId, Utils::ConvertSysString(newMarker->AssociatedDataSourceId));
    VxSdk::Utilities::StrCopySafe(vxNewMarker.layerName, Utils::ConvertSysString(newMarker->LayerName));
    VxSdk::Utilities::StrCopySafe(vxNewMarker.name, Utils::ConvertSysString(newMarker->Name));
    vxNewMarker.direction = newMarker->Direction;
    vxNewMarker.x = newMarker->X;
    vxNewMarker.y = newMarker->Y;

    // Make the call to add the marker to the drawing
    VxSdk::VxResult::Value result = _drawing->AddMarker(vxNewMarker);
    // Unless there was an issue creating the marker the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Drawing::DeleteImage() {
    return (VxSdkNet::Results::Value)_drawing->DeleteImage();
}

VxSdkNet::Results::Value VxSdkNet::Drawing::DeleteLock() {
    // Get the lock for this drawing
    VxSdk::IVxResourceLock* lock = nullptr;
    VxSdk::VxResult::Value result = _drawing->GetLock(lock);

    // Delete the lock if present
    if (result == VxSdk::VxResult::kOK && lock != nullptr)
        return (VxSdkNet::Results::Value)lock->DeleteResourceLock();

    return (VxSdkNet::Results::Value)result;
}

VxSdkNet::Results::Value VxSdkNet::Drawing::DeleteMarker(Marker^ marker) {
    return (VxSdkNet::Results::Value)marker->_marker->DeleteMarker();
}

System::String^ VxSdkNet::Drawing::GetImageUri() {
    char* imageEndpoint = nullptr;
    int size = 0;

    // If the rtsp uri is not available on the datasource the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _drawing->GetImage(imageEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for rtspEndpoint
        imageEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _drawing->GetImage(imageEndpoint, size);
    }
    return gcnew System::String(imageEndpoint);
}

VxSdkNet::ResourceLock^ VxSdkNet::Drawing::GetLock() {
    // Get the lock for this drawing
    VxSdk::IVxResourceLock* lock = nullptr;
    VxSdk::VxResult::Value result = _drawing->GetLock(lock);

    // Return the lock if present
    if (result == VxSdk::VxResult::kOK && lock != nullptr)
        return gcnew VxSdkNet::ResourceLock(lock);

    return nullptr;
}

System::Collections::Generic::List<VxSdkNet::Marker^>^ VxSdkNet::Drawing::GetMarkers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed marker objects
    List<VxSdkNet::Marker^>^ mlist = gcnew List<VxSdkNet::Marker^>();
    // Create a collection of unmanaged marker objects
    VxSdk::VxCollection<VxSdk::IVxMarker**> markers;

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
        markers.filterSize = filters->Count;
        markers.filters = collFilters;
    }

    // Make the GetMarkers call, which will return with the total marker count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _drawing->GetMarkers(markers);
    // Unless there are no markers on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxMarker collection
        markers.collection = new VxSdk::IVxMarker*[markers.collectionSize];
        result = _drawing->GetMarkers(markers);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < markers.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Marker(markers.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] markers.collection;
    }
    return mlist;
}

bool VxSdkNet::Drawing::HasMarkerWithResource(System::String^ resourceId) {
    // Create the initial result
    bool result = false;
    // Create a collection of unmanaged marker objects
    VxSdk::VxCollection<VxSdk::IVxMarker**> markers;
    markers.filterSize = 1;
    VxSdk::VxCollectionFilter filters[1];
    markers.filters = filters;
    markers.filters[0].key = VxSdk::VxCollectionFilterItem::kResourceId;
    VxSdk::Utilities::StrCopySafe(markers.filters[0].value, Utils::ConvertSysString(resourceId));

    // Make the GetMarkers call, which will return with the total marker count, this allows the client to allocate memory.
    _drawing->GetMarkers(markers);
    // Unless there are no markers on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (markers.collectionSize > 0) {
        result = true;
    }
    
    return result;
}

VxSdkNet::Results::Value VxSdkNet::Drawing::Refresh() {
    return (VxSdkNet::Results::Value)_drawing->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Drawing::SetImage(System::String^ imagePath) {
    // Copy the image path to a new char
    int len = imagePath->Length + 1;
    char* image = new char[len];
    VxSdk::Utilities::StrCopySafe(image, Utils::ConvertSysString(imagePath), len);

    // Set the image path
    return (VxSdkNet::Results::Value)_drawing->SetImage(image);
}

VxSdkNet::Results::Value VxSdkNet::Drawing::SetLock() {
    return (VxSdkNet::Results::Value)_drawing->SetLock();
}
