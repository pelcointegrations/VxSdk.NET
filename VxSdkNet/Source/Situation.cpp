/// <summary>
/// Implements the situation class.
/// </summary>
#include "Situation.h"

using namespace System;
using namespace System::Collections::Generic;

VxSdkNet::Situation::Situation(VxSdk::IVxSituation* vxSituation) {
    _situation = vxSituation;
}

VxSdkNet::Situation::!Situation() {
    _situation->Delete();
    _situation = nullptr;
}

VxSdkNet::Notification^ VxSdkNet::Situation::AddNotification(VxSdkNet::NewNotification^ newNotification) {
    auto roles = newNotification->Roles;

    // Create a notification object and populate its fields using newNotification
    VxSdk::VxNewNotification vxNotification;
    vxNotification.roleIdSize = static_cast<int>(roles->Count);
    if (vxNotification.roleIdSize > 0) {
        vxNotification.roleIds = new char*[vxNotification.roleIdSize];
        for (int i = 0; i < vxNotification.roleIdSize; i++) {
            int idLength = roles[i]->Id->Length + 1;
            vxNotification.roleIds[i] = new char[idLength];
            VxSdk::Utilities::StrCopySafe(vxNotification.roleIds[i], Utils::ConvertCSharpString(roles[i]->Id).c_str(), idLength);
        }
    }

    VxSdkNet::Notification^ retNotification = nullptr;
    // Make the call to add the notification to the situation
    VxSdk::IVxNotification* notificationItem = nullptr;
    VxSdk::VxResult::Value result = _situation->AddNotification(vxNotification, notificationItem);

    // Unless there was an issue adding the notification the result should be VxSdk::VxResult::kOK
    if (result == VxSdk::VxResult::kOK) {
        retNotification = gcnew VxSdkNet::Notification(notificationItem);
    }
    return retNotification;
}

VxSdkNet::Results::Value VxSdkNet::Situation::DeleteAudioFile() {
    return (Results::Value)_situation->DeleteAudioFile();
}

System::String^ VxSdkNet::Situation::GetAudioFileUri() {
    char* audioEndpoint = nullptr;
    int size = 0;

    // If the audio file uri is not available on the situation the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _situation->GetAudioFile(audioEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for audioEndpoint
        audioEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _situation->GetAudioFile(audioEndpoint, size);
    }
    return Utils::ConvertCppString(audioEndpoint);
}

System::Collections::Generic::List<VxSdkNet::DataSource^>^ VxSdkNet::Situation::GetLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data sources
    List<VxSdkNet::DataSource^>^ mlist = gcnew List<VxSdkNet::DataSource^>();
    // Create a collection of unmanaged data sources
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

    // Make the GetLinks call, which will return with the total data source count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _situation->GetLinks(dataSources);
    // As long as there are data sources linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataSource collection
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _situation->GetLinks(dataSources);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataSources.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::DataSource(dataSources.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataSources.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::Device^>^ VxSdkNet::Situation::GetLinkedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed devices
    List<VxSdkNet::Device^>^ mlist = gcnew List<VxSdkNet::Device^>();
    // Create a collection of unmanaged devices
    VxSdk::VxCollection<VxSdk::IVxDevice**> devices;

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
        devices.filterSize = filters->Count;
        devices.filters = collFilters;
    }

    // Make the GetLinks call, which will return with the total device count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _situation->GetLinks(devices);
    // As long as there are devices linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDevice collection
        devices.collection = new VxSdk::IVxDevice*[devices.collectionSize];
        result = _situation->GetLinks(devices);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < devices.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Device(devices.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] devices.collection;
    }
    return mlist;
}

List<VxSdkNet::Notification^>^ VxSdkNet::Situation::GetNotifications(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed notification objects
    List<VxSdkNet::Notification^>^ mlist = gcnew List<VxSdkNet::Notification^>();
    // Create a collection of unmanaged notification objects
    VxSdk::VxCollection<VxSdk::IVxNotification**> notifications;

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
        notifications.filterSize = filters->Count;
        notifications.filters = collFilters;
    }

    // Make the GetNotifications call, which will return with the total notification count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _situation->GetNotifications(notifications);
    // The result should be kInsufficientSize if the number of notifications assigned to the situation are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxNotification collection
        notifications.collection = new VxSdk::IVxNotification*[notifications.collectionSize];
        result = _situation->GetNotifications(notifications);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < notifications.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Notification(notifications.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] notifications.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::Situation::Link(VxSdkNet::DataSource^ dataSource) {
    // Link a data source to a situation
    VxSdk::VxResult::Value result = _situation->Link(*dataSource->_dataSource);
    // Unless there was an issue linking the data source the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Situation::Link(VxSdkNet::Device^ device) {
    // Link a device to a situation
    VxSdk::VxResult::Value result = _situation->Link(*device->_device);
    // Unless there was an issue linking the device the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Situation::Refresh() {
    return (VxSdkNet::Results::Value)_situation->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Situation::RemoveNotification(VxSdkNet::Notification^ notification) {
    // Create a notification object using the notificationItem
    VxSdk::IVxNotification* delNotification = notification->_notification;

    // To delete a notification simply make a DeleteNotification call
    VxSdk::VxResult::Value result = delNotification->DeleteNotification();
    // Unless there was an issue deleting the notification the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Situation::SetAudioFile(System::String^ audioPath) {
    // Copy the audio path to a new char
    int len = audioPath->Length + 1;
    char* audio = new char[len];
    VxSdk::Utilities::StrCopySafe(audio, Utils::ConvertCSharpString(audioPath).c_str(), len);

    // Set the audio path
    return (VxSdkNet::Results::Value)_situation->SetAudioFile(audio);
}

VxSdkNet::Results::Value VxSdkNet::Situation::UnLink(VxSdkNet::DataSource^ dataSource) {
    // Unlink a data source from a situation
    VxSdk::VxResult::Value result = _situation->UnLink(*dataSource->_dataSource);
    // Unless there was an issue unlinking the data source the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Situation::UnLink(VxSdkNet::Device^ device) {
    // Unlink a device from a situation
    VxSdk::VxResult::Value result = _situation->UnLink(*device->_device);
    // Unless there was an issue unlinking the device the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::ResourceLimits^ VxSdkNet::Situation::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _situation->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

List<int>^ VxSdkNet::Situation::_GetSnoozeIntervals() {
    // Create a managed list of integers
    List<int>^ mlist = gcnew List<int>();
    // Add each snooze interval to the list
    for (int i = 0; i < _situation->snoozeIntervalSize; i++)
        mlist->Add(_situation->snoozeIntervals[i]);

    return mlist;
}
