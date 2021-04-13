/// <summary>
/// Implements the report template class.
/// </summary>
#include "ReportTemplate.h"
#include "IVxReportTemplate.h"

using namespace System::Collections::Generic;

VxSdkNet::ReportTemplate::ReportTemplate(VxSdk::IVxReportTemplate* vxReportTemplate) {
    _reportTemplate = vxReportTemplate;
}

VxSdkNet::ReportTemplate::!ReportTemplate() {
    _reportTemplate->Delete();
    _reportTemplate = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::ReportTemplate::Refresh() {
    return (VxSdkNet::Results::Value)_reportTemplate->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::ReportTemplate::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _reportTemplate->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

VxSdkNet::Results::Value VxSdkNet::ReportTemplate::_SetStorageLocation(NetworkStorageInfo^ storageInfo) {
    VxSdk::VxNetworkStorageInfo vxNetworkStorageInfo;
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.password, Utils::ConvertCSharpString(storageInfo->Password).c_str());
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.path, Utils::ConvertCSharpString(storageInfo->Path).c_str());
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.username, Utils::ConvertCSharpString(storageInfo->Username).c_str());
    return (VxSdkNet::Results::Value)_reportTemplate->SetStorageLocation(vxNetworkStorageInfo);
}

List<VxSdkNet::TimeRange::DayOfWeek>^ VxSdkNet::ReportTemplate::_GetRecurrence() {
    List<TimeRange::DayOfWeek>^ mlist = gcnew List<TimeRange::DayOfWeek>();
    for (int i = 0; i < _reportTemplate->recurrenceSize; i++)
        mlist->Add((TimeRange::DayOfWeek)_reportTemplate->recurrence[i]);

    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::ReportTemplate::_SetRecurrence(List<TimeRange::DayOfWeek>^ recurrence) {
    // Create a new array of recurrences using the info contained in recurrence
    const int recurrenceSize = recurrence->Count;
    VxSdk::VxDayOfWeek::Value* items = nullptr;
    if (recurrenceSize > 0) {
        items = new VxSdk::VxDayOfWeek::Value[recurrenceSize];
        for (int i = 0; i < recurrenceSize; i++) {
            items[i] = (VxSdk::VxDayOfWeek::Value)recurrence[i];
        }
    }

    // Attempt to set the recurrence and return the result
    VxSdk::VxResult::Value result = _reportTemplate->SetRecurrence(items, recurrenceSize);

    delete[] items;
    items = nullptr;

    return (VxSdkNet::Results::Value)result;
}

List<VxSdkNet::ReportField^>^ VxSdkNet::ReportTemplate::_GetFields() {
    List<ReportField^>^ mlist = gcnew List<ReportField^>();
    for (int i = 0; i < _reportTemplate->fieldsSize; i++)
        mlist->Add(gcnew ReportField(_reportTemplate->fields[i]));

    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::ReportTemplate::_SetFields(List<ReportField^>^ fields) {
    // Create a new array of fields using the info contained in fields
    const int fieldsSize = fields->Count;
    VxSdk::VxReportField** vxReportFields = nullptr;
    if (fieldsSize > 0) {
        vxReportFields = new VxSdk::VxReportField*[fieldsSize];
        for (int i = 0; i < fieldsSize; i++) {
            vxReportFields[i] = new VxSdk::VxReportField();
            vxReportFields[i]->isEnabled = fields[i]->IsEnabled;
            VxSdk::Utilities::StrCopySafe(vxReportFields[i]->name, Utils::ConvertCSharpString(fields[i]->Name).c_str());
            vxReportFields[i]->type = (VxSdk::VxReportFieldType::Value)fields[i]->Type;
            vxReportFields[i]->subfieldSize = fields[i]->Subfields->Count;
            vxReportFields[i]->subfields = nullptr;
            if (vxReportFields[i]->subfieldSize > 0) {
                vxReportFields[i]->subfields = new VxSdk::VxReportField[vxReportFields[i]->subfieldSize];
                for (int ii = 0; ii < vxReportFields[i]->subfieldSize; ii++) {
                    vxReportFields[i]->subfields[ii] = VxSdk::VxReportField();
                    vxReportFields[i]->subfields[ii].isEnabled = fields[i]->Subfields[ii]->IsEnabled;
                    VxSdk::Utilities::StrCopySafe(vxReportFields[i]->subfields[ii].name, Utils::ConvertCSharpString(fields[i]->Subfields[ii]->Name).c_str());
                    vxReportFields[i]->subfields[ii].type = (VxSdk::VxReportFieldType::Value)fields[i]->Subfields[ii]->Type;
                }
            }
        }
    }

    // Attempt to set the fields and return the result
    VxSdk::VxResult::Value result = _reportTemplate->SetFields(vxReportFields, fieldsSize);

    delete[] vxReportFields;
    vxReportFields = nullptr;

    return (VxSdkNet::Results::Value)result;
}

List<VxSdkNet::ReportFilter^>^ VxSdkNet::ReportTemplate::_GetFilters() {
    List<ReportFilter^>^ mlist = gcnew List<ReportFilter^>();
    for (int i = 0; i < _reportTemplate->filtersSize; i++)
        mlist->Add(gcnew ReportFilter(_reportTemplate->filters[i]));

    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::ReportTemplate::_SetFilters(List<ReportFilter^>^ filters) {
    // Create a new array of filters using the info contained in filters
    const int filtersSize = filters->Count;
    VxSdk::VxReportFilter** vxReportFilters = nullptr;
    if (filtersSize > 0) {
        vxReportFilters = new VxSdk::VxReportFilter*[filtersSize];
        for (int i = 0; i < filtersSize; i++) {
            vxReportFilters[i] = new VxSdk::VxReportFilter();
            vxReportFilters[i]->type = (VxSdk::VxReportFilterType::Value)filters[i]->Type;
            vxReportFilters[i]->filterIdSize = filters[i]->FilterIds->Count;
            vxReportFilters[i]->filterIds = nullptr;
            if (vxReportFilters[i]->filterIdSize > 0) {
                vxReportFilters[i]->filterIds = new char*[vxReportFilters[i]->filterIdSize];
                for (int ii = 0; ii < vxReportFilters[i]->filterIdSize; ii++) {
                    int idLength = filters[i]->FilterIds[ii]->Length + 1;
                    vxReportFilters[i]->filterIds[ii] = new char[idLength];
                    VxSdk::Utilities::StrCopySafe(vxReportFilters[i]->filterIds[ii], Utils::ConvertCSharpString(filters[i]->FilterIds[ii]).c_str(), idLength);
                }
            }
        }
    }

    // Attempt to set the filters and return the result
    VxSdk::VxResult::Value result = _reportTemplate->SetFilters(vxReportFilters, filtersSize);

    delete[] vxReportFilters;
    vxReportFilters = nullptr;

    return (VxSdkNet::Results::Value)result;
}
