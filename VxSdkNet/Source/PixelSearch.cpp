/// <summary>
/// Implements the pixel search class.
/// </summary>
#include "PixelSearch.h"
#include "Clip.h"

using namespace System::Collections::Generic;

VxSdkNet::PixelSearch::PixelSearch(VxSdk::IVxPixelSearch* vxPixelSearch) {
    _pixelSearch = vxPixelSearch;
}

VxSdkNet::PixelSearch::!PixelSearch() {
    _pixelSearch->Delete();
    _pixelSearch = nullptr;
}

System::Collections::Generic::List<VxSdkNet::Clip^>^ VxSdkNet::PixelSearch::GetClips(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed clips
    List<Clip^>^ mlist = gcnew List<Clip^>();
    // Create a collection of unmanaged clips
    VxSdk::VxCollection<VxSdk::IVxClip**> clips;

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
        clips.filterSize = filters->Count;
        clips.filters = collFilters;
    }

    // Make the GetClips call, which will return with the total clip count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _pixelSearch->GetClips(clips);
    // As long as there are clip results from this pixel search the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxClip collection
        clips.collection = new VxSdk::IVxClip*[clips.collectionSize];
        result = _pixelSearch->GetClips(clips);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < clips.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Clip(clips.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] clips.collection;
    }
    return mlist;
}

VxSdkNet::PixelSearch::SearchStatus VxSdkNet::PixelSearch::_GetStatus() {
    // Get the search status
    VxSdk::VxSearchStatus::Value searchStatus;
    _pixelSearch->GetSearchStatus(searchStatus);

    return (VxSdkNet::PixelSearch::SearchStatus)searchStatus;
}
