/// <summary>
/// Implements the analyticBehavior class.
/// </summary>
#include "AnalyticBehavior.h"

using namespace System::Collections::Generic;

VxSdkNet::AnalyticBehavior::AnalyticBehavior(VxSdk::IVxAnalyticBehavior* vxAnalyticBehavior) {
    _analyticBehavior = vxAnalyticBehavior;
}

VxSdkNet::AnalyticBehavior::!AnalyticBehavior() {
    _analyticBehavior->Delete();
    _analyticBehavior = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::AnalyticBehavior::Refresh() {
    return (VxSdkNet::Results::Value)_analyticBehavior->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::AnalyticBehavior::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _analyticBehavior->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

void VxSdkNet::AnalyticBehavior::_SetObjectCounter(VxSdkNet::ObjectCounter^ objectCounter) {
    VxSdk::VxObjectCounter vxObjectCounter;
    vxObjectCounter.intersectionArea = (VxSdk::VxIntersectionArea::Value)objectCounter->IntersectionArea;
    vxObjectCounter.endPoint.x = objectCounter->EndPoint->X;
    vxObjectCounter.endPoint.y = objectCounter->EndPoint->Y;
    vxObjectCounter.startPoint.x = objectCounter->StartPoint->X;
    vxObjectCounter.startPoint.y = objectCounter->StartPoint->Y;

    _analyticBehavior->SetObjectCounter(vxObjectCounter);
}

void VxSdkNet::AnalyticBehavior::_SetObjectZone(VxSdkNet::ObjectZone^ objectZone) {
    VxSdk::VxObjectZone vxObjectZone;
    vxObjectZone.verticesSize = objectZone->Vertices->Count;
    vxObjectZone.vertices = new VxSdk::VxPoint[vxObjectZone.verticesSize];
    for (int i = 0; i < vxObjectZone.verticesSize; i++) {
        vxObjectZone.vertices[i].x = objectZone->Vertices[i]->X;
        vxObjectZone.vertices[i].y = objectZone->Vertices[i]->Y;
    }

    _analyticBehavior->SetObjectZone(vxObjectZone);
}
