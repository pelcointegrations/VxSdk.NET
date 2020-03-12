/// <summary>
/// Implements the analytic config class.
/// </summary>
#include "AnalyticConfig.h"
#include "AnalyticBehavior.h"
#include "NewAnalyticBehavior.h"

using namespace System::Collections::Generic;

VxSdkNet::AnalyticConfig::AnalyticConfig(VxSdk::IVxAnalyticConfig* vxAnalyticConfig) {
    _analyticConfig = vxAnalyticConfig;
}

VxSdkNet::AnalyticConfig::!AnalyticConfig() {
    _analyticConfig->Delete();
    _analyticConfig = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::AnalyticConfig::AddAnalyticBehavior(VxSdkNet::NewAnalyticBehavior^ newAnalyticBehavior) {
    // Create an analytic behavior object and populate its fields using newAnalyticBehavior
    VxSdk::VxNewAnalyticBehavior vxNewAnalyticBehavior;
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticBehavior.id, Utils::ConvertCSharpString(newAnalyticBehavior->Id).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticBehavior.name, Utils::ConvertCSharpString(newAnalyticBehavior->Name).c_str());
    vxNewAnalyticBehavior.isEnabled = newAnalyticBehavior->IsEnabled;
    vxNewAnalyticBehavior.sensitivity = newAnalyticBehavior->Sensitivity;
    vxNewAnalyticBehavior.severity = newAnalyticBehavior->Severity;
    vxNewAnalyticBehavior.behaviorType = (VxSdk::VxAnalyticBehaviorType::Value)newAnalyticBehavior->BehaviorType;
    vxNewAnalyticBehavior.objectType = (VxSdk::VxAnalyticObjectType::Value)newAnalyticBehavior->ObjectType;
    if (newAnalyticBehavior->ObjectCounter != nullptr) {
        vxNewAnalyticBehavior.objectCounter.intersectionArea = (VxSdk::VxIntersectionArea::Value)newAnalyticBehavior->ObjectCounter->IntersectionArea;
        vxNewAnalyticBehavior.objectCounter.endPoint.x = newAnalyticBehavior->ObjectCounter->EndPoint->X;
        vxNewAnalyticBehavior.objectCounter.endPoint.y = newAnalyticBehavior->ObjectCounter->EndPoint->Y;
        vxNewAnalyticBehavior.objectCounter.startPoint.x = newAnalyticBehavior->ObjectCounter->StartPoint->X;
        vxNewAnalyticBehavior.objectCounter.startPoint.y = newAnalyticBehavior->ObjectCounter->StartPoint->Y;
    }

    if (newAnalyticBehavior->ObjectZone != nullptr) {
        vxNewAnalyticBehavior.objectZone.verticesSize = newAnalyticBehavior->ObjectZone->Vertices->Count;
        vxNewAnalyticBehavior.objectZone.vertices = new VxSdk::VxPoint[vxNewAnalyticBehavior.objectZone.verticesSize];
        for (int i = 0; i < vxNewAnalyticBehavior.objectZone.verticesSize; i++) {
            vxNewAnalyticBehavior.objectZone.vertices[i].x = newAnalyticBehavior->ObjectZone->Vertices[i]->X;
            vxNewAnalyticBehavior.objectZone.vertices[i].y = newAnalyticBehavior->ObjectZone->Vertices[i]->Y;
        }
    }

    // Make the call to add the analytic behavior
    VxSdk::VxResult::Value result = _analyticConfig->AddAnalyticBehavior(vxNewAnalyticBehavior);
    // Unless there was an issue creating the analytic behavior the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::AnalyticConfig::DeleteAnalyticBehavior(VxSdkNet::AnalyticBehavior^ analyticBehavior) {
    // To delete an analytic behavior simply make a DeleteAnalyticBehavior call
    VxSdk::VxResult::Value result = analyticBehavior->_analyticBehavior->DeleteAnalyticBehavior();
    // Unless there was an issue deleting the analytic behavior the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::AnalyticConfig::Refresh() {
    return (VxSdkNet::Results::Value)_analyticConfig->Refresh();
}

List<VxSdkNet::AnalyticBehavior^>^ VxSdkNet::AnalyticConfig::GetAnalyticBehaviors(Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed analytic behavior objects
    List<VxSdkNet::AnalyticBehavior^>^ mlist = gcnew List<VxSdkNet::AnalyticBehavior^>();
    // Create a collection of unmanaged analytic behavior objects
    VxSdk::VxCollection<VxSdk::IVxAnalyticBehavior**> analyticBehaviors;

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
        analyticBehaviors.filterSize = filters->Count;
        analyticBehaviors.filters = collFilters;
    }

    // Make the GetAnalyticBehaviors call, which will return with the total analytic behavior count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _analyticConfig->GetAnalyticBehaviors(analyticBehaviors);
    // Unless there are no analytic behaviors on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxAnalyticBehavior collection
        analyticBehaviors.collection = new VxSdk::IVxAnalyticBehavior*[analyticBehaviors.collectionSize];
        result = _analyticConfig->GetAnalyticBehaviors(analyticBehaviors);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < analyticBehaviors.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AnalyticBehavior(analyticBehaviors.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] analyticBehaviors.collection;
    }
    return mlist;
}

VxSdkNet::ResourceLimits^ VxSdkNet::AnalyticConfig::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _analyticConfig->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

void VxSdkNet::AnalyticConfig::_SetGridSize(GridPoint^ value) {
    // Create a point object and populate its fields using the value
    VxSdk::VxPoint vxPoint;
    vxPoint.x = value->X;
    vxPoint.y = value->Y;

    // Make the call to set the size
    _analyticConfig->SetSize(vxPoint);
}
