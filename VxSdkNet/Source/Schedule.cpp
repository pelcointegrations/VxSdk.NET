/// <summary>
/// Implements the schedule class.
/// </summary>
#include "Schedule.h"

using namespace System::Collections::Generic;

VxSdkNet::Schedule::Schedule(VxSdk::IVxSchedule* vxSchedule) {
    _schedule = vxSchedule;
}

VxSdkNet::Schedule::!Schedule() {
    _schedule->Delete();
    _schedule = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Schedule::AddScheduleTrigger(VxSdkNet::NewScheduleTrigger^ newScheduleTrigger) {
    // Create a new schedule trigger object
    VxSdk::VxNewScheduleTrigger newTrigger;
    VxSdk::Utilities::StrCopySafe(newTrigger.id, Utils::ConvertCSharpString(newScheduleTrigger->Id).c_str());
    VxSdk::Utilities::StrCopySafe(newTrigger.eventSituationType, Utils::ConvertCSharpString(newScheduleTrigger->EventSituationType).c_str());
    VxSdk::Utilities::StrCopySafe(newTrigger.inactiveEventSituationType, Utils::ConvertCSharpString(newScheduleTrigger->InactiveEventSituationType).c_str());
    VxSdk::Utilities::StrCopySafe(newTrigger.timeTableId, Utils::ConvertCSharpString(newScheduleTrigger->TimeTableId).c_str());
    newTrigger.postTrigger = newScheduleTrigger->PostTrigger;
    newTrigger.preTrigger = newScheduleTrigger->PreTrigger;
    newTrigger.timeout = newScheduleTrigger->Timeout;
    newTrigger.framerate = VxSdk::VxRecordingFramerate::Value(newScheduleTrigger->Framerate);
    newTrigger.action = (VxSdk::VxScheduleAction::Value)newScheduleTrigger->Action;

    // Add any event properties to the new schedule trigger   
    newTrigger.eventPropertySize = newScheduleTrigger->EventProperties->Count;
    if (newTrigger.eventPropertySize > 0) {
        newTrigger.eventProperties = new VxSdk::VxKvObject[newTrigger.eventPropertySize];
        for (int i = 0; i < newTrigger.eventPropertySize; i++) {
            VxSdk::Utilities::StrCopySafe(newTrigger.eventProperties[i].key,
                Utils::ConvertCSharpString(newScheduleTrigger->EventProperties[i].Key).c_str());
            VxSdk::Utilities::StrCopySafe(newTrigger.eventProperties[i].value,
                Utils::ConvertCSharpString(newScheduleTrigger->EventProperties[i].Value).c_str());
        }
    }

    VxSdk::VxResult::Value result = _schedule->AddScheduleTrigger(newTrigger);
    delete[] newTrigger.eventProperties;
    newTrigger.eventProperties = nullptr;

    // Add the schedule trigger to the schedule
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Schedule::DeleteScheduleTrigger(VxSdkNet::ScheduleTrigger^ scheduleTrigger) {
    // Delete the schedule trigger
    return VxSdkNet::Results::Value(scheduleTrigger->_scheduleTrigger->DeleteScheduleTrigger());
}

List<VxSdkNet::DataSource^>^ VxSdkNet::Schedule::GetLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data source objects
    List<VxSdkNet::DataSource^>^ mlist = gcnew List<VxSdkNet::DataSource^>();
    // Create a collection of unmanaged data source objects
    VxSdk::VxCollection<VxSdk::IVxDataSource**> dataSources;

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
        dataSources.filterSize = filters->Count;
        dataSources.filters = collFilters;
    }

    // Make the GetLinks call, which will return with the total data source count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _schedule->GetLinks(dataSources);
    // The result should be kInsufficientSize if the number of data sources on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataSource collection
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _schedule->GetLinks(dataSources);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataSources.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::DataSource(dataSources.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataSources.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::Schedule::Link(List<VxSdkNet::DataSource^>^ dataSources) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of data sources
    for (int i = 0; i < dataSources->Count; i++) {
        // Link the data sources to the schedule
        result = _schedule->Link(*dataSources[i]->_dataSource);
    }

    // Unless there was an issue linking the data sources the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}


VxSdkNet::Results::Value VxSdkNet::Schedule::Refresh() {
    return (VxSdkNet::Results::Value)_schedule->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Schedule::Unlink(List<VxSdkNet::DataSource^>^ dataSources) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of data sources
    for (int i = 0; i < dataSources->Count; i++) {
        // UnLink the data sources to the schedule
        result = _schedule->UnLink(*dataSources[i]->_dataSource);
    }

    // Unless there was an issue unlinking the data sources the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::ResourceLimits^ VxSdkNet::Schedule::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _schedule->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

List<VxSdkNet::ScheduleTrigger^>^ VxSdkNet::Schedule::_GetScheduleTriggers() {
    // Create a list of managed trigger objects
    List<VxSdkNet::ScheduleTrigger^>^ mlist = gcnew List<VxSdkNet::ScheduleTrigger^>();
    // Create a collection of unmanaged trigger objects
    VxSdk::VxCollection<VxSdk::IVxScheduleTrigger**> scheduleTriggers;

    // Make the GetScheduleTriggers call, which will return with the total trigger count,
    // this allows the client to allocate memory
    VxSdk::VxResult::Value result = _schedule->GetScheduleTriggers(scheduleTriggers);
    // Unless there are no triggers associated with the schedule, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxScheduleTrigger collection
        scheduleTriggers.collection = new VxSdk::IVxScheduleTrigger*[scheduleTriggers.collectionSize];
        result = _schedule->GetScheduleTriggers(scheduleTriggers);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < scheduleTriggers.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::ScheduleTrigger(scheduleTriggers.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] scheduleTriggers.collection;
    }
    return mlist;
}
