/// <summary>
/// Implements the role class.
/// </summary>

#include "Role.h"
#include "User.h"

using namespace System::Collections::Generic;

VxSdkNet::Role::Role(VxSdk::IVxRole* vxRole) {
    _role = vxRole;
}

VxSdkNet::Role::!Role() {
    _role->Delete();
    _role = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Role::AddPrivilege(VxSdkNet::NewPrivilege^ newPrivilege) {
    VxSdk::VxNewPrivilege vxNewPrivilege;
    vxNewPrivilege.permissionId = VxSdk::VxPermissionId::Value(newPrivilege->PermissionId);
    vxNewPrivilege.priority = newPrivilege->Priority;

    // Make the call to add the privilege to the role
    VxSdk::VxResult::Value result = _role->AddPrivilege(vxNewPrivilege);
    // Unless there was an issue merging tags the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

System::Collections::Generic::List<VxSdkNet::User^>^ VxSdkNet::Role::GetUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed users
    List<User^>^ mlist = gcnew List<User^>();
    // Create a collection of unmanaged users
    VxSdk::VxCollection<VxSdk::IVxUser**> users;

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
        users.filterSize = filters->Count;
        users.filters = collFilters;
    }

    // Make the GetUsers call, which will return with the total user count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _role->GetUsers(users);
    // As long as there are users linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxUser collection
        users.collection = new VxSdk::IVxUser*[users.collectionSize];
        result = _role->GetUsers(users);
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

VxSdkNet::Results::Value VxSdkNet::Role::Refresh() {
    return (VxSdkNet::Results::Value)_role->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Role::RemovePrivilege(VxSdkNet::Privilege^ privilegeItem) {
    // Create a privilege object using the privilegeItem
    VxSdk::IVxPrivilege* delPrivilege = privilegeItem->_privilege;

    // To remove a privilege simply make a DeletePrivilege call
    VxSdk::VxResult::Value result = delPrivilege->DeletePrivilege();
    // Unless there was an issue removing the privilege the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::ResourceLimits^ VxSdkNet::Role::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _role->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

System::Collections::Generic::List<VxSdkNet::Privilege^>^ VxSdkNet::Role::_GetPrivileges() {
    // Create a list of managed privileges
    List<Privilege^>^ mlist = gcnew List<Privilege^>();
    // Create a collection of unmanaged privileges
    VxSdk::VxCollection<VxSdk::IVxPrivilege**> privileges;

    // Make the GetPrivileges call, which will return with the total privilege count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _role->GetPrivileges(privileges);
    // As long as there are privileges linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxPrivilege collection
        privileges.collection = new VxSdk::IVxPrivilege*[privileges.collectionSize];
        result = _role->GetPrivileges(privileges);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < privileges.collectionSize; i++)
                mlist->Add(gcnew Privilege(privileges.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] privileges.collection;
    }
    return mlist;
}
