/// <summary>
/// Implements the data source class.
/// </summary>
#include "AnalyticSession.h"
#include "Bookmark.h"
#include "DataStorage.h"
#include "Gap.h"
#include "NewAnalyticSession.h"
#include "ResourceRel.h"
#include "UserInfo.h"
#include "Tag.h"

using namespace System::Collections::Generic;

VxSdkNet::DataSource::DataSource(VxSdk::IVxDataSource* vxDataSource) {
    _dataSource = vxDataSource;
}

VxSdkNet::DataSource::!DataSource() {
    _dataSource->Delete();
    _dataSource = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::DataSource::AddAnalyticSession(NewAnalyticSession^ newAnalyticSession) {
    VxSdk::VxNewAnalyticSession vxNewAnalyticSession;
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.dataEncodingId, Utils::ConvertCSharpString(newAnalyticSession->DataEncodingId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.dataSourceId, Utils::ConvertCSharpString(newAnalyticSession->DataSourceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.deviceId, Utils::ConvertCSharpString(newAnalyticSession->DeviceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.id, Utils::ConvertCSharpString(newAnalyticSession->Id).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.source, Utils::ConvertCSharpString(newAnalyticSession->Source).c_str());

    // Attempt to add the analytic session
    return VxSdkNet::Results::Value(_dataSource->AddAnalyticSession(vxNewAnalyticSession));
}

VxSdkNet::DataSession^ VxSdkNet::DataSource::CreateMjpegStream() {
    // Create a data session object
    VxSdk::IVxDataSession* dataSession;

    // If the mjpeg protocol is not available on the datasource the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kOK
    VxSdk::VxResult::Value result = _dataSource->CreateMjpegDataSession(dataSession);
    if (result == VxSdk::VxResult::kOK)
        return gcnew DataSession(dataSession);

    return nullptr;
}

VxSdkNet::PixelSearch^ VxSdkNet::DataSource::CreatePixelSearch(NewPixelSearch^ newPixelSearch) {
    VxSdk::VxNewPixelSearch vxNewPixelSearch;
    VxSdk::Utilities::StrCopySafe(vxNewPixelSearch.searchEndTime, Utils::ConvertCSharpDateTime(newPixelSearch->SearchEndTime).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewPixelSearch.searchStartTime, Utils::ConvertCSharpDateTime(newPixelSearch->SearchStartTime).c_str());
    vxNewPixelSearch.columns = newPixelSearch->Columns;
    vxNewPixelSearch.rows = newPixelSearch->Rows;
    vxNewPixelSearch.zoneSize = static_cast<int>(newPixelSearch->Zones->Count);
    vxNewPixelSearch.zones = new VxSdk::VxRect[vxNewPixelSearch.zoneSize];
    for (int i = 0; i < vxNewPixelSearch.zoneSize; i++) {
        vxNewPixelSearch.zones[i].height = newPixelSearch->Zones[i]->Height;
        vxNewPixelSearch.zones[i].left = newPixelSearch->Zones[i]->Left;
        vxNewPixelSearch.zones[i].top = newPixelSearch->Zones[i]->Top;
        vxNewPixelSearch.zones[i].width = newPixelSearch->Zones[i]->Width;
    }

    // Attempt to create the pixel search
    VxSdkNet::PixelSearch^ retPixelSearch = nullptr;
    VxSdk::IVxPixelSearch* pixelSearchItem = nullptr;
    VxSdk::VxResult::Value result = _dataSource->CreatePixelSearch(vxNewPixelSearch, pixelSearchItem);

    // Unless there was an issue initiating the pixel search the result should be VxSdk::VxResult::kOK
    if (result == VxSdk::VxResult::kOK) {
        // The pixelSearchItem returned from the data source contains the pixel search results.
        retPixelSearch = gcnew VxSdkNet::PixelSearch(pixelSearchItem);
    }
    return retPixelSearch;
}

VxSdkNet::Results::Value VxSdkNet::DataSource::DeleteAnalyticSession(AnalyticSession^ analyticSession) {
    // Create aa analytic session object
    VxSdk::IVxAnalyticSession* delAnalyticSession = analyticSession->_analyticSession;

    // To delete an analytic session simply make a DeleteAnalyticSession call
    VxSdk::VxResult::Value result = delAnalyticSession->DeleteAnalyticSession();
    // Unless there was an issue deleting the analytic session the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::DataSource::DeletePixelSearch(PixelSearch^ pixelSearchItem) {
    // Create a pixel search object
    VxSdk::IVxPixelSearch* delPixelSearch = pixelSearchItem->_pixelSearch;

    // To delete a pixel search simply make a DeletePixelSearch call
    VxSdk::VxResult::Value result = delPixelSearch->DeletePixelSearch();
    // Unless there was an issue deleting the pixel search the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

List<VxSdkNet::DataStorage^>^ VxSdkNet::DataSource::GetAllDataStorages(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data storages
    List<DataStorage^>^ mlist = gcnew List<DataStorage^>();
    // Create a collection of unmanaged data storages
    VxSdk::VxCollection<VxSdk::IVxDataStorage**> dataStorages;

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
        dataStorages.filterSize = filters->Count;
        dataStorages.filters = collFilters;
    }

    // Make the GetAllDataStorages call, which will return with the total data storage count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetAllDataStorages(dataStorages);
    // As long as there are data storages from this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataStorage collection
        dataStorages.collection = new VxSdk::IVxDataStorage*[dataStorages.collectionSize];
        result = _dataSource->GetAllDataStorages(dataStorages);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataStorages.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::DataStorage(dataStorages.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataStorages.collection;
    }
    return mlist;
}

List<VxSdkNet::AnalyticSession^>^ VxSdkNet::DataSource::GetAnalyticSessions(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed analytic sessions
    List<AnalyticSession^>^ mlist = gcnew List<AnalyticSession^>();
    // Create a collection of unmanaged analytic sessions
    VxSdk::VxCollection<VxSdk::IVxAnalyticSession**> analyticSessions;

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
        analyticSessions.filterSize = filters->Count;
        analyticSessions.filters = collFilters;
    }

    // Make the GetAnalyticSessions call, which will return with the total analytic session count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetAnalyticSessions(analyticSessions);
    // As long as there are analytic sessions for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxAnalyticSession collection
        analyticSessions.collection = new VxSdk::IVxAnalyticSession*[analyticSessions.collectionSize];
        result = _dataSource->GetAnalyticSessions(analyticSessions);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < analyticSessions.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AnalyticSession(analyticSessions.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] analyticSessions.collection;
    }
    return mlist;
}

List<VxSdkNet::ResourceRel^>^ VxSdkNet::DataSource::GetAudioRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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

    // Make the GetAudioRelations call, which will return with the total resource count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetAudioRelations(resourceRels);
    // As long as there are related resources for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxResourceRel collection
        resourceRels.collection = new VxSdk::IVxResourceRel*[resourceRels.collectionSize];
        result = _dataSource->GetAudioRelations(resourceRels);
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

System::Collections::Generic::List<VxSdkNet::Bookmark^>^ VxSdkNet::DataSource::GetBookmarks(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed bookmarks
    List<Bookmark^>^ mlist = gcnew List<Bookmark^>();
    // Create a collection of unmanaged bookmarks
    VxSdk::VxCollection<VxSdk::IVxBookmark**> bookmarks;

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
        bookmarks.filterSize = filters->Count;
        bookmarks.filters = collFilters;
    }

    // Make the GetBookmarks call, which will return with the total bookmark count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetBookmarks(bookmarks);
    // As long as there are bookmarks from this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxBookmark collection
        bookmarks.collection = new VxSdk::IVxBookmark*[bookmarks.collectionSize];
        result = _dataSource->GetBookmarks(bookmarks);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < bookmarks.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Bookmark(bookmarks.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] bookmarks.collection;
    }
    return mlist;
}

List<VxSdkNet::Clip^>^ VxSdkNet::DataSource::GetClips(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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
            VxSdk::Utilities::StrCopySafe(collFilters[i++].value, Utils::ConvertCSharpString(kvp->Value).c_str());
        }

        // Add the filters to the collection 
        clips.filterSize = filters->Count;
        clips.filters = collFilters;
    }

    // Make the GetClips call, which will return with the total clip count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetClips(clips);
    // As long as there are clips from this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxClip collection
        clips.collection = new VxSdk::IVxClip*[clips.collectionSize];
        result = _dataSource->GetClips(clips);
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

List<VxSdkNet::DataStorage^>^ VxSdkNet::DataSource::GetDataStorages(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data storages
    List<DataStorage^>^ mlist = gcnew List<DataStorage^>();
    // Create a collection of unmanaged data storages
    VxSdk::VxCollection<VxSdk::IVxDataStorage**> dataStorages;

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
        dataStorages.filterSize = filters->Count;
        dataStorages.filters = collFilters;
    }

    // Make the GetDataStorages call, which will return with the total data storage count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetDataStorages(dataStorages);
    // As long as there are data storages from this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataStorage collection
        dataStorages.collection = new VxSdk::IVxDataStorage*[dataStorages.collectionSize];
        result = _dataSource->GetDataStorages(dataStorages);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataStorages.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::DataStorage(dataStorages.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataStorages.collection;
    }
    return mlist;
}

List<VxSdkNet::Clip^>^ VxSdkNet::DataSource::GetEdgeClips(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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
            VxSdk::Utilities::StrCopySafe(collFilters[i++].value, Utils::ConvertCSharpString(kvp->Value).c_str());
        }

        // Add the filters to the collection 
        clips.filterSize = filters->Count;
        clips.filters = collFilters;
    }

    // Make the GetEdgeClips call, which will return with the total clip count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetEdgeClips(clips);
    // As long as there are clips from this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxClip collection
        clips.collection = new VxSdk::IVxClip*[clips.collectionSize];
        result = _dataSource->GetEdgeClips(clips);
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

List<VxSdkNet::Gap^>^ VxSdkNet::DataSource::GetGaps(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed gaps
    List<Gap^>^ mlist = gcnew List<Gap^>();
    // Create a collection of unmanaged gaps
    VxSdk::VxCollection<VxSdk::IVxGap**> gaps;

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
        gaps.filterSize = filters->Count;
        gaps.filters = collFilters;
    }

    // Make the GetGaps call, which will return with the total gap count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetGaps(gaps);
    // As long as there are gaps for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxGap collection
        gaps.collection = new VxSdk::IVxGap*[gaps.collectionSize];
        result = _dataSource->GetGaps(gaps);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < gaps.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Gap(gaps.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] gaps.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::ResourceRel^>^ VxSdkNet::DataSource::GetMetadataRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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

    // Make the GetMetadataRelations call, which will return with the total resource count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetMetadataRelations(resourceRels);
    // As long as there are related resources for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxResourceRel collection
        resourceRels.collection = new VxSdk::IVxResourceRel*[resourceRels.collectionSize];
        result = _dataSource->GetMetadataRelations(resourceRels);
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

List<VxSdkNet::Tag^>^ VxSdkNet::DataSource::GetTags(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed tags
    List<Tag^>^ mlist = gcnew List<Tag^>();
    // Create a collection of unmanaged tags
    VxSdk::VxCollection<VxSdk::IVxTag**> tags;

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
        tags.filterSize = filters->Count;
        tags.filters = collFilters;
    }

    // Make the GetTags call, which will return with the total tag count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetTags(tags);
    // As long as there are tags from this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxtag collection
        tags.collection = new VxSdk::IVxTag*[tags.collectionSize];
        result = _dataSource->GetTags(tags);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < tags.collectionSize; i++)
                mlist->Add(gcnew Tag(tags.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] tags.collection;
    }
    return mlist;
}

List<VxSdkNet::ResourceRel^>^ VxSdkNet::DataSource::GetVideoRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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

    // Make the GetVideoRelations call, which will return with the total resource count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetVideoRelations(resourceRels);
    // As long as there are related resources for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxResourceRel collection
        resourceRels.collection = new VxSdk::IVxResourceRel*[resourceRels.collectionSize];
        result = _dataSource->GetVideoRelations(resourceRels);
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

VxSdkNet::Results::Value VxSdkNet::DataSource::Refresh() {
    return (VxSdkNet::Results::Value)_dataSource->Refresh();
}

bool VxSdkNet::DataSource::_CanPixelSearch() {
    bool result;
    _dataSource->CanPixelSearch(result);
    return result;
}

bool VxSdkNet::DataSource::_CanPtz() {
    bool result;
    _dataSource->CanPtz(result);
    return result;
}

List<VxSdkNet::AnalyticConfig^>^ VxSdkNet::DataSource::GetAnalyticConfigs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed analytic configs
    List<AnalyticConfig^>^ mlist = gcnew List<AnalyticConfig^>();

    // Create a collection of unmanaged analytic configs
    VxSdk::VxCollection<VxSdk::IVxAnalyticConfig**> analyticConfigs;

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
        analyticConfigs.filterSize = filters->Count;
        analyticConfigs.filters = collFilters;
    }

    // Make the GetAnalyticConfigs call, which will return with the total analytic config count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetAnalyticConfigs(analyticConfigs);
    // As long as there are analytic configs for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxAnalyticConfig collection
        analyticConfigs.collection = new VxSdk::IVxAnalyticConfig*[analyticConfigs.collectionSize];
        result = _dataSource->GetAnalyticConfigs(analyticConfigs);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < analyticConfigs.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AnalyticConfig(analyticConfigs.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] analyticConfigs.collection;
    }
    return mlist;
}

List<VxSdkNet::DataInterface^>^ VxSdkNet::DataSource::_GetDataInterfaces() {
    // Create a list of managed export objects
    List<DataInterface^>^ mlist = gcnew List<DataInterface^>();
    for (int i = 0; i < _dataSource->dataInterfaceSize; i++)
        mlist->Add(gcnew DataInterface(_dataSource->dataInterfaces[i]));

    return mlist;
}

VxSdkNet::Device^ VxSdkNet::DataSource::_GetHostDevice() {
    // Get the device which hosts this data source
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _dataSource->GetHostDevice(device);

    // Return the device if GetHostDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew Device(device);

    return nullptr;
}

VxSdkNet::ResourceLimits^ VxSdkNet::DataSource::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _dataSource->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

List<VxSdkNet::LinkedPtzInfo^>^ VxSdkNet::DataSource::_GetLinkedPtzInfo() {
    // Create a list of managed linked ptz info objects
    List<LinkedPtzInfo^>^ mlist = gcnew List<LinkedPtzInfo^>();
    // Add each linked ptz info to the list
    for (int i = 0; i < _dataSource->linkedPtzInfoSize; i++) {
        mlist->Add(gcnew LinkedPtzInfo(_dataSource->linkedPtzInfo[i]));
    }

    return mlist;
}

VxSdkNet::Member^ VxSdkNet::DataSource::_GetMember() {
    // Get the member that this data source resides in.
    VxSdk::IVxMember* member = nullptr;
    VxSdk::VxResult::Value result = _dataSource->GetMember(member);

    // Return the member if GetMember was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew Member(member);

    return nullptr;
}

VxSdkNet::Configuration::Motion^ VxSdkNet::DataSource::_GetMotionConfig() {
    // Get the motion config
    VxSdk::IVxConfiguration::Motion* motionConfig = nullptr;
    VxSdk::VxResult::Value result = _dataSource->GetMotionConfiguration(motionConfig);

    // Return the motion config if GetMotionConfiguration was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Configuration::Motion(motionConfig);

    return nullptr;
}

System::Collections::Generic::List<VxSdkNet::UserInfo^>^ VxSdkNet::DataSource::_GetMultiviewInfo() {
    // Create a list of managed user info objects
    List<UserInfo^>^ mlist = gcnew List<UserInfo^>();
    // Create a collection of unmanaged user info objects
    VxSdk::VxCollection<VxSdk::IVxUserInfo**> userInfos;

    // Make the GetMultiviewInfo call, which will return with the total user info object count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dataSource->GetMultiviewInfo(userInfos);
    // As long as there are user info objects for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxUserInfo collection
        userInfos.collection = new VxSdk::IVxUserInfo*[userInfos.collectionSize];
        result = _dataSource->GetMultiviewInfo(userInfos);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < userInfos.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::UserInfo(userInfos.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] userInfos.collection;
    }
    return mlist;
}

VxSdkNet::PtzController^ VxSdkNet::DataSource::_GetPtzController() {
    // Check to ensure this datasource is a ptz camera
    bool isPtz;
    VxSdk::VxResult::Value result = _dataSource->CanPtz(isPtz);

    if (isPtz) {
        // Get the ptz controller which allows the client to make ptz calls
        VxSdk::IVxPtzController* ptzController = nullptr;
        result = _dataSource->GetPtzController(ptzController);

        // Return the ptz controller if GetPtzController was successful
        if (result == VxSdk::VxResult::kOK)
            return gcnew PtzController(ptzController);
    }
    return nullptr;
}

System::String^ VxSdkNet::DataSource::_GetRtspEndpoint() {
    char* rtspEndpoint = nullptr;
    int size = 0;

    // If the rtsp uri is not available on the datasource the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _dataSource->GetRtspEndpoint(rtspEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for rtspEndpoint
        rtspEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _dataSource->GetRtspEndpoint(rtspEndpoint, size);
    }
    return Utils::ConvertCppString(rtspEndpoint);
}
