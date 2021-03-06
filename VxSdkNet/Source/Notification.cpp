/// <summary>
/// Implements the notification class.
/// </summary>
#include "Notification.h"

using namespace System::Collections::Generic;

VxSdkNet::Notification::Notification(VxSdk::IVxNotification* vxNotification) {
    _notification = vxNotification;
}

VxSdkNet::Notification::!Notification() {
    _notification->Delete();
    _notification = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Notification::AddRole(VxSdkNet::Role^ role) {
    // Make the call to add the role to the notification
    VxSdk::VxResult::Value result = _notification->AddRole(*role->_role);
    // Unless there was an issue adding the role the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Notification::AddUser(VxSdkNet::User^ user) {
    // Make the call to add the user to the notification
    VxSdk::VxResult::Value result = _notification->AddUser(*user->_user);
    // Unless there was an issue adding the user the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

System::Collections::Generic::List<VxSdkNet::Role^>^ VxSdkNet::Notification::GetRoles(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed roles
    List<Role^>^ mlist = gcnew List<Role^>();
    // Create a collection of unmanaged roles
    VxSdk::VxCollection<VxSdk::IVxRole**> roles;

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
        roles.filterSize = filters->Count;
        roles.filters = collFilters;
    }

    // Make the GetRoles call, which will return with the total role count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _notification->GetRoles(roles);
    // As long as there are roles linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxRole collection
        roles.collection = new VxSdk::IVxRole*[roles.collectionSize];
        result = _notification->GetRoles(roles);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < roles.collectionSize; i++)
                mlist->Add(gcnew Role(roles.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] roles.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::User^>^ VxSdkNet::Notification::GetUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed users
    List<User^>^ mlist = gcnew List<User^>();
    // Create a collection of unmanaged users
    VxSdk::VxCollection<VxSdk::IVxUser**> users;

    if (filters != nullptr && filters->Count > 0) {
        // Create our filter
        VxSdk::VxCollectionFilter* collFilters = new VxSdk::VxCollectionFilter[filters->Count];
        int i = 0;
        for each (KeyValuePair<Filters::Value, System::String^> ^ kvp in filters)
        {
            collFilters[i].key = static_cast<VxSdk::VxCollectionFilterItem::Value>(kvp->Key);
            VxSdk::Utilities::StrCopySafe(collFilters[i++].value, Utils::ConvertCSharpString(kvp->Value).c_str());
        }

        // Add the filters to the collection 
        users.filterSize = filters->Count;
        users.filters = collFilters;
    }

    // Make the GetUsers call, which will return with the total user count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _notification->GetUsers(users);
    // As long as there are users linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxUser collection
        users.collection = new VxSdk::IVxUser * [users.collectionSize];
        result = _notification->GetUsers(users);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < users.collectionSize; i++)
                mlist->Add(gcnew User(users.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] users.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::Notification::Refresh() {
    return (VxSdkNet::Results::Value)_notification->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Notification::RemoveRole(VxSdkNet::Role^ role) {
    // Make the call to remove the role from the notification
    VxSdk::VxResult::Value result = _notification->RemoveRole(*role->_role);
    // Unless there was an issue removing the role the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Notification::RemoveUser(VxSdkNet::User^ user) {
    // Make the call to remove the user from the notification
    VxSdk::VxResult::Value result = _notification->RemoveUser(*user->_user);
    // Unless there was an issue removing the user the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

System::Collections::Generic::List<System::String^>^ VxSdkNet::Notification::_GetRoleIds() {
    // Create a list of strings
    List<System::String^>^ mlist = gcnew List<System::String^>();
    // Add each role id to the string list
    for (int i = 0; i < _notification->roleIdSize; i++)
        mlist->Add(Utils::ConvertCppString(_notification->roleIds[i]));

    return mlist;
}

System::Collections::Generic::List<System::String^>^ VxSdkNet::Notification::_GetUserIds() {
    // Create a list of strings
    List<System::String^>^ mlist = gcnew List<System::String^>();
    // Add each user id to the string list
    for (int i = 0; i < _notification->userIdSize; i++)
        mlist->Add(Utils::ConvertCppString(_notification->userIds[i]));

    return mlist;
}
