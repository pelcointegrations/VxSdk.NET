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
    vxNewAnalyticBehavior.severity = newAnalyticBehavior->Severity;
    vxNewAnalyticBehavior.behaviorType = (VxSdk::VxAnalyticBehaviorType::Value)newAnalyticBehavior->BehaviorType;
    vxNewAnalyticBehavior.objectType = (VxSdk::VxAnalyticObjectType::Value)newAnalyticBehavior->ObjectType;
    if (newAnalyticBehavior->ObjectLineCounter != nullptr) {
        vxNewAnalyticBehavior.objectLineCounter.endPoint.x = newAnalyticBehavior->ObjectLineCounter->EndPoint->X;
        vxNewAnalyticBehavior.objectLineCounter.endPoint.y = newAnalyticBehavior->ObjectLineCounter->EndPoint->Y;
        vxNewAnalyticBehavior.objectLineCounter.startPoint.x = newAnalyticBehavior->ObjectLineCounter->StartPoint->X;
        vxNewAnalyticBehavior.objectLineCounter.startPoint.y = newAnalyticBehavior->ObjectLineCounter->StartPoint->Y;
        vxNewAnalyticBehavior.objectLineCounter.eventWindowSecs = newAnalyticBehavior->ObjectLineCounter->EventWindowSecs;
        vxNewAnalyticBehavior.objectLineCounter.eventsEnabled = newAnalyticBehavior->ObjectLineCounter->EventsEnabled;
        vxNewAnalyticBehavior.objectLineCounter.maxCountThreshold = newAnalyticBehavior->ObjectLineCounter->MaxCountThreshold;
        VxSdk::Utilities::StrCopySafe(vxNewAnalyticBehavior.objectLineCounter.leftCountLabel, Utils::ConvertCSharpString(newAnalyticBehavior->ObjectLineCounter->LeftCountLabel).c_str());
        VxSdk::Utilities::StrCopySafe(vxNewAnalyticBehavior.objectLineCounter.rightCountLabel, Utils::ConvertCSharpString(newAnalyticBehavior->ObjectLineCounter->RightCountLabel).c_str());
        vxNewAnalyticBehavior.objectLineCounter.lineCounterType = (VxSdk::VxLineCounterType::Value)newAnalyticBehavior->ObjectLineCounter->LineCounterType;
    }

    if (newAnalyticBehavior->ObjectInZone != nullptr) {
        vxNewAnalyticBehavior.objectInZone.verticesSize = newAnalyticBehavior->ObjectInZone->Vertices->Count;
        vxNewAnalyticBehavior.objectInZone.vertices = new VxSdk::VxPoint[vxNewAnalyticBehavior.objectInZone.verticesSize];
        for (int i = 0; i < vxNewAnalyticBehavior.objectInZone.verticesSize; i++) {
            vxNewAnalyticBehavior.objectInZone.vertices[i].x = newAnalyticBehavior->ObjectInZone->Vertices[i]->X;
            vxNewAnalyticBehavior.objectInZone.vertices[i].y = newAnalyticBehavior->ObjectInZone->Vertices[i]->Y;
        }
    }

    if (newAnalyticBehavior->ObjectWrongWayZone != nullptr) {
        vxNewAnalyticBehavior.objectWrongWayZone.vector.angle = newAnalyticBehavior->ObjectWrongWayZone->Vector->Angle;
        vxNewAnalyticBehavior.objectWrongWayZone.vector.x = newAnalyticBehavior->ObjectWrongWayZone->Vector->X;
        vxNewAnalyticBehavior.objectWrongWayZone.vector.y = newAnalyticBehavior->ObjectWrongWayZone->Vector->Y;
        vxNewAnalyticBehavior.objectWrongWayZone.minTriggerAngle = newAnalyticBehavior->ObjectWrongWayZone->MinTriggerAngle;
        vxNewAnalyticBehavior.objectWrongWayZone.zoneSize = newAnalyticBehavior->ObjectWrongWayZone->Zone->Count;
        vxNewAnalyticBehavior.objectWrongWayZone.zone = new VxSdk::VxPoint[vxNewAnalyticBehavior.objectWrongWayZone.zoneSize];
        for (int i = 0; i < vxNewAnalyticBehavior.objectWrongWayZone.zoneSize; i++) {
            vxNewAnalyticBehavior.objectWrongWayZone.zone[i].x = newAnalyticBehavior->ObjectWrongWayZone->Zone[i]->X;
            vxNewAnalyticBehavior.objectWrongWayZone.zone[i].y = newAnalyticBehavior->ObjectWrongWayZone->Zone[i]->Y;
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

List<VxSdkNet::AnalyticBehavior^>^ VxSdkNet::AnalyticConfig::_GetAnalyticBehaviors() {
    List<AnalyticBehavior^>^ mlist = gcnew List<AnalyticBehavior^>();
    for (int i = 0; i < _analyticConfig->analyticBehaviorSize; i++)
        mlist->Add(gcnew AnalyticBehavior(_analyticConfig->analyticBehaviors[i]));

    return mlist;
}

void VxSdkNet::AnalyticConfig::_SetResolutionSize(Resolution^ value) {
    // Create a point object and populate its fields using the value
    VxSdk::VxResolution vxResolution;
    vxResolution.width = value->Width;
    vxResolution.height = value->Height;

    // Make the call to set the size
    _analyticConfig->SetSize(vxResolution);
}
