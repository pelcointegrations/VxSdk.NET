/// <summary>
/// Implements the rule class.
/// </summary>
#include "Rule.h"

using namespace System::Collections::Generic;

VxSdkNet::Rule::Rule(VxSdk::IVxRule* vxRule) {
    _rule = vxRule;
}

VxSdkNet::Rule::!Rule() {
    _rule->Delete();
    _rule = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Rule::HaltScript() {
    return (Results::Value)_rule->HaltScript();
}

System::Collections::Generic::List<VxSdkNet::TimeTable^>^ VxSdkNet::Rule::GetTimeTables(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed time table objects
    List<VxSdkNet::TimeTable^>^ mlist = gcnew List<VxSdkNet::TimeTable^>();
    // Create a collection of unmanaged time table objects
    VxSdk::VxCollection<VxSdk::IVxTimeTable**> timeTables;
    
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
        timeTables.filterSize = filters->Count;
        timeTables.filters = collFilters;
    }

    // Make the GetTimeTables call, which will return with the total time table count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _rule->GetTimeTables(timeTables);
    // The result should be kInsufficientSize if the number of time tables for the rule are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxTimeTable collection
        timeTables.collection = new VxSdk::IVxTimeTable*[timeTables.collectionSize];
        result = _rule->GetTimeTables(timeTables);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < timeTables.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::TimeTable(timeTables.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] timeTables.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::Rule::Refresh() {
    return (VxSdkNet::Results::Value)_rule->Refresh();
}

System::String ^ VxSdkNet::Rule::_GetScript() {
    char* scriptData = nullptr;
    int size = 0;

    // If the script data is not available the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _rule->GetScript(scriptData, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the script data
        scriptData = new char[size];
        // The result should now be kOK since we have allocated enough space
        _rule->GetScript(scriptData, size);
    }

    System::String^ script = Utils::ConvertCppString(scriptData);
    delete[] scriptData;
    scriptData = nullptr;

    return script;
}

System::Collections::Generic::List<VxSdkNet::RuleTrigger^>^ VxSdkNet::Rule::_GetTriggers() {
    // Create a list of managed rule trigger objects
    List<VxSdkNet::RuleTrigger^>^ mlist = gcnew List<VxSdkNet::RuleTrigger^>();
    // Add each rule trigger to the list
    for (int i = 0; i < _rule->triggerSize; i++) {
        mlist->Add(gcnew VxSdkNet::RuleTrigger(_rule->triggers[i]));
    }

    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::Rule::_SetScript(System::String ^ scriptData) {
    // Set the script value for the rule
    std::string val = Utils::ConvertCSharpString(scriptData);
    return (VxSdkNet::Results::Value)_rule->SetScript((char*)val.c_str());
}

VxSdkNet::Results::Value VxSdkNet::Rule::_SetTimeTables(System::Collections::Generic::List<TimeTable^>^ timeTableList) {
    // Create a new char array of time table ids using the info contained in timeTableList
    const int timeTableListSize = timeTableList->Count;
    char** timeTableIds = nullptr;
    if (timeTableListSize > 0) {
        timeTableIds = new char*[timeTableListSize];
        for (int i = 0; i < timeTableListSize; i++) {
            int idSize = timeTableList[i]->Id->Length + 1;
            timeTableIds[i] = new char[idSize];
            VxSdk::Utilities::StrCopySafe(timeTableIds[i], Utils::ConvertCSharpString(timeTableList[i]->Id).c_str(), idSize);
        }
    }

    // Attempt to set the time tables and return the result
    VxSdk::VxResult::Value result = _rule->SetTimeTables(timeTableIds, timeTableListSize);
    for (int i = 0; i < timeTableListSize; i++) {
        delete[] timeTableIds[i];
    }

    delete[] timeTableIds;
    timeTableIds = nullptr;

    return (VxSdkNet::Results::Value)result;
}

VxSdkNet::Results::Value VxSdkNet::Rule::_SetTriggers(System::Collections::Generic::List<RuleTrigger^>^ triggerList) {
    // Create a new array of VxRuleTrigger objects using the info contained in triggerList
    const int triggerListSize = triggerList->Count;
    VxSdk::VxRuleTrigger** triggers = nullptr;
    if (triggerListSize > 0) {
        triggers = new VxSdk::VxRuleTrigger*[triggerListSize];
        for (int i = 0; i < triggerListSize; i++) {
            triggers[i] = new VxSdk::VxRuleTrigger();
            VxSdk::Utilities::StrCopySafe(triggers[i]->situationType, Utils::ConvertCSharpString(triggerList[i]->SituationType).c_str());
            triggers[i]->sourceRefSize = triggerList[i]->ResourceRefs->Count;
            triggers[i]->sourceRef = new VxSdk::VxResourceRef[triggers[i]->sourceRefSize];
            for (int ii = 0; ii < triggers[i]->sourceRefSize; ii++) {
                VxSdk::Utilities::StrCopySafe(triggers[i]->sourceRef[ii].id, Utils::ConvertCSharpString(triggerList[i]->ResourceRefs[ii]->Id).c_str());
                triggers[i]->sourceRef[ii].type = (VxSdk::VxResourceType::Value)triggerList[i]->ResourceRefs[ii]->Type;
            }
        }
    }

    // Attempt to set the triggers and return the result
    VxSdkNet::Results::Value result = (VxSdkNet::Results::Value)_rule->SetTriggers(triggers, triggerListSize);
    for (int i = 0; i < triggerListSize; i++) {
        delete triggers[i];
    }

    delete[] triggers;
    triggers = nullptr;

    return result;
}
