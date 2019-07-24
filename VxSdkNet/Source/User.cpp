/// <summary>
/// Implements the user class.
/// </summary>

#include "User.h"

using namespace System::Collections::Generic;

VxSdkNet::User::User(VxSdk::IVxUser* vxUser) {
    _user = vxUser;
}

VxSdkNet::User::!User() {
    _user->Delete();
    _user = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::User::AddToRole(VxSdkNet::Role^ role) {
    // Make the call to add the user to the role
    VxSdk::VxResult::Value result = _user->AddToRole(*role->_role);
    // Unless there was an issue adding the user the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

System::Collections::Generic::List<VxSdkNet::DataObject^>^ VxSdkNet::User::GetDataObjects(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data objects
    List<DataObject^>^ mlist = gcnew List<DataObject^>();
    // Create a collection of unmanaged data objects
    VxSdk::VxCollection<VxSdk::IVxDataObject**> dataObjects;

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
        dataObjects.filterSize = filters->Count;
        dataObjects.filters = collFilters;
    }

    // Make the GetDataObjects call, which will return with the total data object count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _user->GetDataObjects(dataObjects);
    // As long as there are data objects linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataObject collection
        dataObjects.collection = new VxSdk::IVxDataObject*[dataObjects.collectionSize];
        result = _user->GetDataObjects(dataObjects);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataObjects.collectionSize; i++)
                mlist->Add(gcnew DataObject(dataObjects.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataObjects.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::Role^>^ VxSdkNet::User::GetRoles(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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
    VxSdk::VxResult::Value result = _user->GetRoles(roles);
    // As long as there are roles linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxRole collection
        roles.collection = new VxSdk::IVxRole*[roles.collectionSize];
        result = _user->GetRoles(roles);
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

System::Collections::Generic::List<VxSdkNet::Tag^>^ VxSdkNet::User::GetTags(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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

    // Make the GetTags call, which will return with the total tag count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _user->GetTags(tags);
    // As long as there are tags linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxTag collection
        tags.collection = new VxSdk::IVxTag*[tags.collectionSize];
        result = _user->GetTags(tags);
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

VxSdkNet::Results::Value VxSdkNet::User::Refresh() {
    return (VxSdkNet::Results::Value)_user->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::User::RemoveFromRole(VxSdkNet::Role^ role) {
    // Make the call to remove the user from the role
    VxSdk::VxResult::Value result = _user->RemoveFromRole(*role->_role);
    // Unless there was an issue removing the user from the role the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::User::SetPassword(System::String^ newPassword, bool mustChangePassword) {
    char password[64];
    VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(newPassword).c_str());

    // Make the call to set the users password
    VxSdk::VxResult::Value result = _user->SetPassword(password, mustChangePassword);
    // Unless there was an issue setting the password the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

bool VxSdkNet::User::_GetAccountState() {
    // Get and return the account state
    bool state;
    _user->GetAccountState(state);
    return state;
}
