/// <summary>
/// Implements the data source config class.
/// </summary>
#include "DataSourceConfig.h"

using namespace System::Collections::Generic;

// ====================================================================================================================
// VxSdkNet::DataSourceConfig::Motion
// ====================================================================================================================

VxSdkNet::DataSourceConfig::Motion::Motion(VxSdk::IVxDataSourceConfig::Motion* vxConfigMotion) {
    _configMotion = vxConfigMotion;
}

VxSdkNet::DataSourceConfig::Motion::!Motion() {
    _configMotion->Delete();
    _configMotion = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::DataSourceConfig::Motion::Refresh() {
    return (VxSdkNet::Results::Value)_configMotion->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::DataSourceConfig::Motion::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configMotion->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::DataSourceConfig::Ptz
// ====================================================================================================================

VxSdkNet::DataSourceConfig::Ptz::Ptz(VxSdk::IVxDataSourceConfig::Ptz* vxConfigPtz) {
    _configPtz = vxConfigPtz;
}

VxSdkNet::DataSourceConfig::Ptz::!Ptz() {
    _configPtz->Delete();
    _configPtz = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::DataSourceConfig::Ptz::Refresh() {
    return (VxSdkNet::Results::Value)_configPtz->Refresh();
}

// ====================================================================================================================
// VxSdkNet::DataSourceConfig::SmartCompression
// ====================================================================================================================

VxSdkNet::DataSourceConfig::SmartCompression::SmartCompression(VxSdk::IVxDataSourceConfig::SmartCompression* vxConfigSmartCompression) {
    _configSmartCompression = vxConfigSmartCompression;
}

VxSdkNet::DataSourceConfig::SmartCompression::!SmartCompression() {
    _configSmartCompression->Delete();
    _configSmartCompression = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::DataSourceConfig::SmartCompression::Refresh() {
    return (VxSdkNet::Results::Value)_configSmartCompression->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::DataSourceConfig::SmartCompression::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configSmartCompression->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::DataSourceConfig::VideoEncoding
// ====================================================================================================================

VxSdkNet::DataSourceConfig::VideoEncoding::VideoEncoding(VxSdk::IVxDataSourceConfig::VideoEncoding* vxConfigVideoEncoding) {
    _configVideoEncoding = vxConfigVideoEncoding;
}

VxSdkNet::DataSourceConfig::VideoEncoding::!VideoEncoding() {
    _configVideoEncoding->Delete();
    _configVideoEncoding = nullptr;
}

List<VxSdkNet::VideoEncodingOption^>^ VxSdkNet::DataSourceConfig::VideoEncoding::_GetConfigurationOptions() {
    List<VideoEncodingOption^>^ mlist = gcnew List<VideoEncodingOption^>();
    for (int i = 0; i < _configVideoEncoding->configurationOptionsSize; i++)
        mlist->Add(gcnew VideoEncodingOption(_configVideoEncoding->configurationOptions[i]));

    return mlist;
}

void VxSdkNet::DataSourceConfig::VideoEncoding::_SetResolution(Resolution^ value) {
    // Create a resolution object and populate its fields using the value
    VxSdk::VxResolution vxResolution;
    vxResolution.width = value->Width;
    vxResolution.height = value->Height;

    // Make the call to set the resolution
    _configVideoEncoding->SetResolution(vxResolution);
}
