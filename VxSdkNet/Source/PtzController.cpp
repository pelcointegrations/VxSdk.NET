/// <summary>
/// Implements the ptz controller class.
/// </summary>
#include "PtzController.h"

using namespace System::Collections::Generic;

VxSdkNet::PtzController::PtzController(VxSdk::IVxPtzController* ptzController) {
    _ptzController = ptzController;
}

VxSdkNet::PtzController::!PtzController() {
    _ptzController->Delete();
    _ptzController = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::PtzController::AbsoluteMove(int positionX, int positionY) {
    // Call AbsoluteMove and return the result
    VxSdk::VxResult::Value result = _ptzController->AbsoluteMove(positionX, positionY);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::AbsoluteMove(int positionX, int positionY, int positionZ) {
    // Call AbsoluteMove and return the result
    VxSdk::VxResult::Value result = _ptzController->AbsoluteMove(positionX, positionY, positionZ);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::AbsolutePan(int positionX) {
    // Call AbsolutePan and return the result
    VxSdk::VxResult::Value result = _ptzController->AbsolutePan(positionX);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::AbsoluteTilt(int positionY) {
    // Call AbsoluteTilt and return the result
    VxSdk::VxResult::Value result = _ptzController->AbsoluteTilt(positionY);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::AbsoluteZoom(int positionZ) {
    // Call AbsoluteZoom and return the result
    VxSdk::VxResult::Value result = _ptzController->AbsoluteZoom(positionZ);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::AddPreset(int index) {
    // Call AddPreset and return the result
    VxSdk::VxResult::Value result = _ptzController->AddPreset(index);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::ContinuousFocus(VxSdkNet::PtzController::FocusDirections nearFar) {
    // Call ContinuousFocus and return the result
    VxSdk::VxResult::Value result = _ptzController->ContinuousFocus((VxSdk::VxFocusDirection::Value)nearFar);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::ContinuousIris(VxSdkNet::PtzController::IrisDirections openClose) {
    // Call ContinuousIris and return the result
    VxSdk::VxResult::Value result = _ptzController->ContinuousIris((VxSdk::VxIrisDirection::Value)openClose);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::ContinuousMove(int speedX, int speedY, VxSdkNet::PtzController::ZoomDirections inOut) {
    // Call ContinuousMove and return the result
    VxSdk::VxResult::Value result = _ptzController->ContinuousMove(speedX, speedY, (VxSdk::VxZoomDirection::Value)inOut);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::DeletePreset(Preset^ preset) {
    // Call DeletePreset and return the result
    VxSdk::VxResult::Value result = _ptzController->DeletePreset(*preset->_preset);
    return VxSdkNet::Results::Value(result);
}

List<VxSdkNet::Pattern^>^ VxSdkNet::PtzController::GetPatterns(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed pattern objects
    List<Pattern^>^ mlist = gcnew List<Pattern^>();
    // Create a collection of unmanaged pattern objects
    VxSdk::VxCollection<VxSdk::IVxPattern**> patterns;

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
        patterns.filterSize = filters->Count;
        patterns.filters = collFilters;
    }

    // Make the GetPatterns call, which will return with the total pattern count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _ptzController->GetPatterns(patterns);
    // As long as the datasource has at least one pattern the GetPatterns call should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Fill the array of pointers to the proper size as determined by the previous GetPatterns call
        patterns.collection = new VxSdk::IVxPattern*[patterns.collectionSize];
        result = _ptzController->GetPatterns(patterns);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < patterns.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Pattern(patterns.collection[i]));
        }
        // Delete the memory allocated earlier
        delete[] patterns.collection;
    }
    return mlist;
}

List<VxSdkNet::Preset^>^ VxSdkNet::PtzController::GetPresets(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed preset objects
    List<Preset^>^ mlist = gcnew List<Preset^>();
    // Create a collection of unmanaged preset objects
    VxSdk::VxCollection<VxSdk::IVxPreset**> presets;

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
        presets.filterSize = filters->Count;
        presets.filters = collFilters;
    }

    // Make the GetPresets call, which will return with the total preset count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _ptzController->GetPresets(presets);
    // As long as the datasource has at least one preset the GetPresets call should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Fill the array of pointers to the proper size as determined by the previous GetPresets call
        presets.collection = new VxSdk::IVxPreset*[presets.collectionSize];
        result = _ptzController->GetPresets(presets);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < presets.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Preset(presets.collection[i]));
        }
        // Delete the memory allocated earlier
        delete[] presets.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::PtzController::Refresh() {
    return (VxSdkNet::Results::Value)_ptzController->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::PtzController::RelativeMove(int deltaX, int deltaY, int deltaZ) {
    // Call RelativeMove and return the result
    VxSdk::VxResult::Value result = _ptzController->RelativeMove(deltaX, deltaY, deltaZ);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::RelativePercentageMove(int percentageX, int percentageY) {
    // Call RelativePercentageMove and return the result
    VxSdk::VxResult::Value result = _ptzController->RelativePercentageMove(percentageX, percentageY);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::RepositionPreset(Preset^ preset) {
    // Call RepositionPreset and return the result
    VxSdk::VxResult::Value result = _ptzController->RepositionPreset(*preset->_preset);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::Stop() {
    // Call PtzStop and return the result
    VxSdk::VxResult::Value result = _ptzController->PtzStop();
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::TriggerPattern(Pattern^ pattern) {
    // Call TriggerPattern and return the result
    VxSdk::VxResult::Value result = _ptzController->TriggerPattern(*pattern->_pattern);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::TriggerPreset(int index) {
    // Call TriggerPreset and return the result
    VxSdk::VxResult::Value result = _ptzController->TriggerPreset(index);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::TriggerPreset(Preset^ preset) {
    // Call TriggerPreset and return the result
    VxSdk::VxResult::Value result = _ptzController->TriggerPreset(*preset->_preset);
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::PtzController::TriggerRefresh() {
    // Call TriggerRefresh and return the result
    VxSdk::VxResult::Value result = _ptzController->TriggerRefresh();
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::PtzLimits^ VxSdkNet::PtzController::_GetPtzLimits() {
    // Get the ptz limit values from the ptz controller
    VxSdk::VxPtzLimits* ptzLimits = nullptr;
    VxSdk::VxResult::Value result = _ptzController->GetPtzLimits(ptzLimits);

    // Return the ptz limits if GetPtzLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew PtzLimits(ptzLimits);

    return nullptr;
}

VxSdkNet::PtzLock^ VxSdkNet::PtzController::_GetPtzLock() {
    // Get the ptz lock which allows the client to make lock the ptz controller
    VxSdk::IVxPtzLock* ptzLock = nullptr;
    VxSdk::VxResult::Value result = _ptzController->GetPtzLock(ptzLock);

    // Return the ptz lock if GetPtzLock was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew PtzLock(ptzLock);

    return nullptr;
}
