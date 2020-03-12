/// <summary>
/// Implements the analyticSession class.
/// </summary>
#include "AnalyticSession.h"
#include "AnalyticConfig.h"

using namespace System::Collections::Generic;

VxSdkNet::AnalyticSession::AnalyticSession(VxSdk::IVxAnalyticSession* vxAnalyticSession) {
    _analyticSession = vxAnalyticSession;
}

VxSdkNet::AnalyticSession::!AnalyticSession() {
    _analyticSession->Delete();
    _analyticSession = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::AnalyticSession::Refresh() {
    return (VxSdkNet::Results::Value)_analyticSession->Refresh();
}

VxSdkNet::AnalyticConfig^ VxSdkNet::AnalyticSession::_GetAnalyticConfig() {
    // Get the analytic config
    VxSdk::IVxAnalyticConfig* analyticConfig = nullptr;
    VxSdk::VxResult::Value result = _analyticSession->GetAnalyticConfig(analyticConfig);

    // Return the analytic config if GetAnalyticConfig was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::AnalyticConfig(analyticConfig);

    return nullptr;
}

VxSdkNet::DataSource^ VxSdkNet::AnalyticSession::_GetDataSource() {
    // Get the data source
    VxSdk::IVxDataSource* dataSource = nullptr;
    VxSdk::VxResult::Value result = _analyticSession->GetDataSource(dataSource);

    // Return the data source if GetDataSource was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataSource(dataSource);

    return nullptr;
}

VxSdkNet::Device^ VxSdkNet::AnalyticSession::_GetHostDevice() {
    // Get the device
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _analyticSession->GetHostDevice(device);

    // Return the device if GetHostDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Device(device);

    return nullptr;
}

VxSdkNet::ResourceLimits^ VxSdkNet::AnalyticSession::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _analyticSession->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}
