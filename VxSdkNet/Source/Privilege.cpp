/// <summary>
/// Implements the privilege class.
/// </summary>

#include "Privilege.h"
#include "User.h"

using namespace System::Collections::Generic;

VxSdkNet::Privilege::Privilege(VxSdk::IVxPrivilege* vxPrivilege) {
    _privilege = vxPrivilege;
}

VxSdkNet::Privilege::!Privilege() {
    _privilege->Delete();
    _privilege = nullptr;
}

System::Collections::Generic::List<VxSdkNet::DataSource^>^ VxSdkNet::Privilege::GetLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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
    VxSdk::VxResult::Value result = _privilege->GetLinks(dataSources);
    // As long as there are data sources linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataSource collection
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _privilege->GetLinks(dataSources);
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

System::Collections::Generic::List<VxSdkNet::Device^>^ VxSdkNet::Privilege::GetLinkedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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
    VxSdk::VxResult::Value result = _privilege->GetLinks(devices);
    // As long as there are devices linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDevice collection
        devices.collection = new VxSdk::IVxDevice*[devices.collectionSize];
        result = _privilege->GetLinks(devices);
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

System::Collections::Generic::List<VxSdkNet::Drawing^>^ VxSdkNet::Privilege::GetLinkedDrawings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed drawings
    List<VxSdkNet::Drawing^>^ mlist = gcnew List<VxSdkNet::Drawing^>();
    // Create a collection of unmanaged drawings
    VxSdk::VxCollection<VxSdk::IVxDrawing**> drawings;

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
        drawings.filterSize = filters->Count;
        drawings.filters = collFilters;
    }

    // Make the GetLinks call, which will return with the total drawing count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _privilege->GetLinks(drawings);
    // As long as there are drawings linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDrawing collection
        drawings.collection = new VxSdk::IVxDrawing*[drawings.collectionSize];
        result = _privilege->GetLinks(drawings);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < drawings.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Drawing(drawings.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] drawings.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::RelayOutput^>^ VxSdkNet::Privilege::GetLinkedRelayOutputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed relay outputs
    List<VxSdkNet::RelayOutput^>^ mlist = gcnew List<VxSdkNet::RelayOutput^>();
    // Create a collection of unmanaged relay outputs
    VxSdk::VxCollection<VxSdk::IVxRelayOutput**> relayOutputs;

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
        relayOutputs.filterSize = filters->Count;
        relayOutputs.filters = collFilters;
    }

    // Make the GetLinks call, which will return with the total relay output count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _privilege->GetLinks(relayOutputs);
    // As long as there are relay outputs linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxRelayOutput collection
        relayOutputs.collection = new VxSdk::IVxRelayOutput*[relayOutputs.collectionSize];
        result = _privilege->GetLinks(relayOutputs);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < relayOutputs.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::RelayOutput(relayOutputs.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] relayOutputs.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::User^>^ VxSdkNet::Privilege::GetLinkedUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed users
    List<VxSdkNet::User^>^ mlist = gcnew List<VxSdkNet::User^>();
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

    // Make the GetLinks call, which will return with the total user count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _privilege->GetLinks(users);
    // As long as there are users linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxUser collection
        users.collection = new VxSdk::IVxUser*[users.collectionSize];
        result = _privilege->GetLinks(users);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < users.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::User(users.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] users.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::DataSource^>^ VxSdkNet::Privilege::GetUnLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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

    // Make the GetUnLinked call, which will return with the total data source count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _privilege->GetUnLinked(dataSources);
    // As long as there are data sources linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataSource collection
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _privilege->GetUnLinked(dataSources);
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

System::Collections::Generic::List<VxSdkNet::Device^>^ VxSdkNet::Privilege::GetUnLinkedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
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

    // Make the GetUnLinked call, which will return with the total device count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _privilege->GetUnLinked(devices);
    // As long as there are devices linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDevice collection
        devices.collection = new VxSdk::IVxDevice*[devices.collectionSize];
        result = _privilege->GetUnLinked(devices);
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

System::Collections::Generic::List<VxSdkNet::Drawing^>^ VxSdkNet::Privilege::GetUnLinkedDrawings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed drawings
    List<VxSdkNet::Drawing^>^ mlist = gcnew List<VxSdkNet::Drawing^>();
    // Create a collection of unmanaged drawings
    VxSdk::VxCollection<VxSdk::IVxDrawing**> drawings;

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
        drawings.filterSize = filters->Count;
        drawings.filters = collFilters;
    }

    // Make the GetLinks call, which will return with the total drawing count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _privilege->GetUnLinked(drawings);
    // As long as there are drawings linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDrawing collection
        drawings.collection = new VxSdk::IVxDrawing*[drawings.collectionSize];
        result = _privilege->GetUnLinked(drawings);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < drawings.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Drawing(drawings.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] drawings.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::RelayOutput^>^ VxSdkNet::Privilege::GetUnLinkedRelayOutputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed relay outputs
    List<VxSdkNet::RelayOutput^>^ mlist = gcnew List<VxSdkNet::RelayOutput^>();
    // Create a collection of unmanaged relay outputs
    VxSdk::VxCollection<VxSdk::IVxRelayOutput**> relayOutputs;

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
        relayOutputs.filterSize = filters->Count;
        relayOutputs.filters = collFilters;
    }

    // Make the GetLinks call, which will return with the total relay output count, this allows the
    // client to allocate memory.
    VxSdk::VxResult::Value result = _privilege->GetUnLinked(relayOutputs);
    // As long as there are relay outputs linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxRelayOutput collection
        relayOutputs.collection = new VxSdk::IVxRelayOutput*[relayOutputs.collectionSize];
        result = _privilege->GetUnLinked(relayOutputs);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < relayOutputs.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::RelayOutput(relayOutputs.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] relayOutputs.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::User^>^ VxSdkNet::Privilege::GetUnLinkedUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed users
    List<VxSdkNet::User^>^ mlist = gcnew List<VxSdkNet::User^>();
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

    // Make the GetUnLinked call, which will return with the total user count, this
    // allows the client to allocate memory.
    VxSdk::VxResult::Value result = _privilege->GetUnLinked(users);
    // As long as there are users linked the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxUser collection
        users.collection = new VxSdk::IVxUser*[users.collectionSize];
        result = _privilege->GetUnLinked(users);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < users.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::User(users.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] users.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Link(List<VxSdkNet::DataSource^>^ dataSources) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of data sources
    for (int i = 0; i < dataSources->Count; i++) {
        // Link the data sources to the privilege
        result = _privilege->Link(*dataSources[i]->_dataSource);
    }

    // Unless there was an issue linking the data sources the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Link(List<VxSdkNet::Device^>^ devices) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of devices
    for (int i = 0; i < devices->Count; i++) {
        // Link the devices to the privilege
        result = _privilege->Link(*devices[i]->_device);
    }

    // Unless there was an issue linking the devices the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Link(List<VxSdkNet::Drawing^>^ drawings) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of drawings
    for (int i = 0; i < drawings->Count; i++) {
        // Link the drawings to the privilege
        result = _privilege->Link(*drawings[i]->_drawing);
    }

    // Unless there was an issue linking the drawings the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Link(List<VxSdkNet::RelayOutput^>^ relayOutputs) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of relay outputs
    for (int i = 0; i < relayOutputs->Count; i++) {
        // Link the relay outputs to the privilege
        result = _privilege->Link(*relayOutputs[i]->_relayOutput);
    }

    // Unless there was an issue linking the relay outputs the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Link(List<VxSdkNet::User^>^ users) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of users
    for (int i = 0; i < users->Count; i++) {
        // Link the users to the privilege
        result = _privilege->Link(*users[i]->_user);
    }

    // Unless there was an issue linking the users the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Refresh() {
    return (VxSdkNet::Results::Value)_privilege->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Unlink(List<VxSdkNet::DataSource^>^ dataSources) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of data sources
    for (int i = 0; i < dataSources->Count; i++) {
        // UnLink the data sources to the privilege
        result = _privilege->UnLink(*dataSources[i]->_dataSource);
    }

    // Unless there was an issue unlinking the data sources the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Unlink(List<VxSdkNet::Device^>^ devices) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of devices
    for (int i = 0; i < devices->Count; i++) {
        // UnLink the devices to the privilege
        result = _privilege->UnLink(*devices[i]->_device);
    }

    // Unless there was an issue unlinking the devices the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Unlink(List<VxSdkNet::Drawing^>^ drawings) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of drawings
    for (int i = 0; i < drawings->Count; i++) {
        // Unlink the drawings to the privilege
        result = _privilege->UnLink(*drawings[i]->_drawing);
    }

    // Unless there was an issue unlinking the drawings the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Unlink(List<VxSdkNet::RelayOutput^>^ relayOutputs) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of relay outputs
    for (int i = 0; i < relayOutputs->Count; i++) {
        // Unlink the relay outputs to the privilege
        result = _privilege->UnLink(*relayOutputs[i]->_relayOutput);
    }

    // Unless there was an issue unlinking the relay outputs the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Privilege::Unlink(List<VxSdkNet::User^>^ users) {
    VxSdk::VxResult::Value result = VxSdk::VxResult::kUnknownError;

    // Iterate the managed list of users
    for (int i = 0; i < users->Count; i++) {
        // UnLink the data sources to the privilege
        result = _privilege->UnLink(*users[i]->_user);
    }

    // Unless there was an issue unlinking the users the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

int VxSdkNet::Privilege::_GetPriority() {
    // Get and return the priority
    int priority;
    _privilege->GetPriority(priority);
    return priority;
}

bool VxSdkNet::Privilege::_GetRestricted() {
    // Get and return the restriction state
    bool isRestricted;
    _privilege->GetRestricted(isRestricted);
    return isRestricted;
}
