/// <summary>
/// Implements the analyticBehavior class.
/// </summary>
#include "AnalyticBehavior.h"
#include "Utils.h"

using namespace System::Collections::Generic;

VxSdkNet::AnalyticBehavior::AnalyticBehavior(VxSdk::IVxAnalyticBehavior* vxAnalyticBehavior) {
    _analyticBehavior = vxAnalyticBehavior;
}

VxSdkNet::Results::Value VxSdkNet::AnalyticBehavior::Refresh() {
    return (VxSdkNet::Results::Value)_analyticBehavior->Refresh();
}

void VxSdkNet::AnalyticBehavior::_SetObjectLineCounter(VxSdkNet::ObjectLineCounter^ objectLineCounter) {
    VxSdk::VxObjectLineCounter vxObjectLineCounter;
    vxObjectLineCounter.endPoint.x = objectLineCounter->EndPoint->X;
    vxObjectLineCounter.endPoint.y = objectLineCounter->EndPoint->Y;
    vxObjectLineCounter.startPoint.x = objectLineCounter->StartPoint->X;
    vxObjectLineCounter.startPoint.y = objectLineCounter->StartPoint->Y;
    vxObjectLineCounter.eventWindowSecs = objectLineCounter->EventWindowSecs;
    vxObjectLineCounter.eventsEnabled = objectLineCounter->EventsEnabled;
    VxSdk::Utilities::StrCopySafe(vxObjectLineCounter.leftCountLabel, Utils::ConvertCSharpString(objectLineCounter->LeftCountLabel).c_str());
    VxSdk::Utilities::StrCopySafe(vxObjectLineCounter.rightCountLabel, Utils::ConvertCSharpString(objectLineCounter->RightCountLabel).c_str());
    vxObjectLineCounter.lineCounterType = (VxSdk::VxLineCounterType::Value)objectLineCounter->LineCounterType;
    vxObjectLineCounter.maxCountThreshold = objectLineCounter->MaxCountThreshold;

    _analyticBehavior->SetObjectLineCounter(vxObjectLineCounter);
}

void VxSdkNet::AnalyticBehavior::_SetObjectInZone(VxSdkNet::ObjectInZone^ objectInZone) {
    VxSdk::VxObjectInZone vxObjectZone;
    vxObjectZone.verticesSize = objectInZone->Vertices->Count;
    vxObjectZone.vertices = new VxSdk::VxPoint[vxObjectZone.verticesSize];
    for (int i = 0; i < vxObjectZone.verticesSize; i++) {
        vxObjectZone.vertices[i].x = objectInZone->Vertices[i]->X; 
        vxObjectZone.vertices[i].y = objectInZone->Vertices[i]->Y;
    }

    _analyticBehavior->SetObjectInZone(vxObjectZone); 
}
