/// <summary>
/// Implements the bookmark class.
/// </summary>
#include "Report.h"

using namespace System::Collections::Generic;

VxSdkNet::Report::Report(VxSdk::IVxReport* vxReport) {
    _report = vxReport;
}

VxSdkNet::Report::!Report() {
    _report->Delete();
    _report = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Report::Refresh() {
    return (VxSdkNet::Results::Value)_report->Refresh();
}


System::String^ VxSdkNet::Report::_GetReportEndpoint() {
    char* reportEndpoint = nullptr;
    int size = 0;

    // If the report uri is not available the result will return VxSdk::VxResult::kActionUnavailable,
    // otherwise VxSdk::VxResult::kInsufficientSize
    VxSdk::VxResult::Value result = _report->GetReportEndpoint(reportEndpoint, size);
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for reportEndpoint
        reportEndpoint = new char[size];
        // The result should now be kOK since we have allocated enough space
        _report->GetReportEndpoint(reportEndpoint, size);
    }
    return Utils::ConvertCppString(reportEndpoint);
}

VxSdkNet::ReportTemplate^ VxSdkNet::Report::_GetReportTemplate() {
    // Get the report template
    VxSdk::IVxReportTemplate* reportTemplate = nullptr;
    VxSdk::VxResult::Value result = _report->GetReportTemplate(reportTemplate);

    // Return the report template if GetReportTemplate was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::ReportTemplate(reportTemplate);

    return nullptr;
}
