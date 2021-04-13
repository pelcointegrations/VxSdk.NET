// Declares the report template class.
#ifndef ReportTemplate_h__
#define ReportTemplate_h__

#include "LineCountingRequest.h"
#include "NetworkStorageInfo.h"
#include "NewReportTemplate.h"
#include "ReportField.h"
#include "ReportFilter.h"
#include "ResourceLimits.h"
#include "TimeRange.h"
#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The ReportTemplate class represents a template for an available report type that may be created.
    /// </summary>
    public ref class ReportTemplate {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxReportTemplate">The vx reportTemplate.</param>
        ReportTemplate(VxSdk::IVxReportTemplate* vxReportTemplate);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~ReportTemplate() {
            this->!ReportTemplate();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !ReportTemplate();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets or sets the duration of time, in hours, extending back from <see cref="EndTime"/> to limit collected report data
        /// to. If 0, there is no limit.
        /// </summary>
        /// <value>The duration of time, in hours.</value>
        property int Duration {
        public:
            int get() { return _reportTemplate->duration; }
            void set(int value) { _reportTemplate->SetDuration(value); }
        }
     
        /// <summary>
        /// Gets the date and time at which the point of interest occurred.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which the point of interest occurred.</value>
        property System::DateTime EndTime {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_reportTemplate->endTime); }
            void set(System::DateTime value) {
                char endTime[64];
                VxSdk::Utilities::StrCopySafe(endTime, Utils::ConvertCSharpDateTime(value).c_str());
                _reportTemplate->SetEndTime(endTime);
            }
        }

        /// <summary>
        /// Gets or sets the ordered list of report fields available to include in the report.
        /// </summary>
        /// <value>The the ordered list of report fields.</value>
        property System::Collections::Generic::List<ReportField^>^ Fields {
        public:
            System::Collections::Generic::List<ReportField^>^ get() { return _GetFields(); }
            void set(System::Collections::Generic::List<ReportField^>^ value) { _SetFields(value); }
        }

        /// <summary>
        /// Gets or sets the list of report filters to use to filter the contents of the report.
        /// </summary>
        /// <value>The list of report filters.</value>
        property System::Collections::Generic::List<ReportFilter^>^ Filters {
        public:
            System::Collections::Generic::List<ReportFilter^>^ get() { return _GetFilters(); }
            void set(System::Collections::Generic::List<ReportFilter^>^ value) { _SetFilters(value); }
        }

        /// <summary>
        /// Gets the unique identifier of the associated data source.
        /// </summary>
        /// <value>The unique identifier of the associated data source.</value>
        property System::String^ Format {
        public:
            System::String^ get() { return Utils::ConvertCppString(_reportTemplate->format); }
            void set(System::String^ value) {
                char format[64];
                VxSdk::Utilities::StrCopySafe(format, Utils::ConvertCSharpString(value).c_str());
                _reportTemplate->SetFormat(format);
            }
        }

        /// <summary>
        /// Gets the unique identifier of the associated data source.
        /// </summary>
        /// <value>The unique identifier of the associated data source.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_reportTemplate->id); }
        }

        /// <summary>
        /// Gets or sets the time interval that is used to track data in the report (days, hours, etc).
        /// </summary>
        /// <value>The time interval.</value>
        property LineCountingRequest::TimeInterval Interval {
        public:
            LineCountingRequest::TimeInterval get() { return (LineCountingRequest::TimeInterval)_reportTemplate->interval; }
            void set(LineCountingRequest::TimeInterval value) { _reportTemplate->SetInterval((VxSdk::VxTimeInterval::Value)value); }
        }

        /// <summary>
        /// Gets or sets the language to use when creating the report.
        /// </summary>
        /// <value>The language to use when creating the report.</value>
        property NewReportTemplate::VxLanguage Language {
        public:
            NewReportTemplate::VxLanguage get() { return (NewReportTemplate::VxLanguage)_reportTemplate->language; }
            void set(NewReportTemplate::VxLanguage value) { _reportTemplate->SetLanguage((VxSdk::VxLanguage::Value)value); }
        }

        /// <summary>
        /// Gets any limits related to this resource.
        /// </summary>
        /// <value>The limits related to this resource.</value>
        property ResourceLimits^ Limits {
        public:
            ResourceLimits^ get() { return _GetLimits(); }
        }

        /// <summary>
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_reportTemplate->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _reportTemplate->SetName(name);
            }
        }

        /// <summary>
        /// Gets the unique identifier of the associated data source.
        /// </summary>
        /// <value>The unique identifier of the associated data source.</value>
        property System::String^ Owner {
        public:
            System::String^ get() { return Utils::ConvertCppString(_reportTemplate->owner); }
        }

        /// <summary>
        /// Gets or sets the days of the week to automatically generate a report from this template. Ignored if
        /// <see cref="RecurrenceTime"/> is not set.
        /// </summary>
        /// <value>The days of the week to generate a report.</value>
        property System::Collections::Generic::List<TimeRange::DayOfWeek>^ Recurrence {
        public:
            System::Collections::Generic::List<TimeRange::DayOfWeek>^ get() { return _GetRecurrence(); }
            void set(System::Collections::Generic::List<TimeRange::DayOfWeek>^ value) { _SetRecurrence(value); }
        }

        /// <summary>
        /// Gets the date and time at which the point of interest occurred.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which the point of interest occurred.</value>
        property System::DateTime RecurrenceTime {
        public:
            System::DateTime get() { return Utils::ConvertCppTime(_reportTemplate->recurrenceTime); }
            void set(System::DateTime value) {
                char recurrenceTime[9];
                VxSdk::Utilities::StrCopySafe(recurrenceTime, Utils::ConvertCSharpTime(value).c_str());
                _reportTemplate->SetRecurrenceTime(recurrenceTime);
            }
        }

        /// <summary>
        /// Gets or sets the network storage location to export the report data to. Ignored if <see cref="Recurrence"/> is not set.
        /// </summary>
        /// <value>The network storage location.</value>
        property NetworkStorageInfo^ StorageLocation {
        public:
            NetworkStorageInfo^ get() { return gcnew NetworkStorageInfo(_reportTemplate->storageLocation); }
            void set(NetworkStorageInfo^ value) { _SetStorageLocation(value); }
        }

        /// <summary>
        /// Gets or sets the type of the report that this template represents.
        /// </summary>
        /// <value>The report type.</value>
        property NewReportTemplate::ReportType Type {
        public:
            NewReportTemplate::ReportType get() { return (NewReportTemplate::ReportType)_reportTemplate->type; }
        }

    internal:
        VxSdk::IVxReportTemplate* _reportTemplate;
        VxSdkNet::ResourceLimits^ _GetLimits();
        VxSdkNet::Results::Value _SetStorageLocation(NetworkStorageInfo^ storageInfo);
        System::Collections::Generic::List<TimeRange::DayOfWeek>^ _GetRecurrence();
        VxSdkNet::Results::Value _SetRecurrence(System::Collections::Generic::List<TimeRange::DayOfWeek>^ recurrence);
        System::Collections::Generic::List<ReportField^>^ _GetFields();
        VxSdkNet::Results::Value _SetFields(System::Collections::Generic::List<ReportField^>^ fields);
        System::Collections::Generic::List<ReportFilter^>^ _GetFilters();
        VxSdkNet::Results::Value _SetFilters(System::Collections::Generic::List<ReportFilter^>^ filters);
    };
}
#endif // ReportTemplate_h__
