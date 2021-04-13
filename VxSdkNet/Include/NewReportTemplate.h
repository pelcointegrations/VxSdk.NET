// Declares the new report template class.
#ifndef NewReportTemplate_h__
#define NewReportTemplate_h__

#include "LineCountingRequest.h"
#include "NetworkStorageInfo.h"
#include "ReportField.h"
#include "ReportFilter.h"
#include "TimeRange.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewReportTemplate class represents a new report template to be created.
    /// </summary>
    public ref class NewReportTemplate {
    public:
        /// <summary>
        /// Values that represent languages supported by VideoXpert.
        /// </summary>
        enum class VxLanguage {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Arabic language.</summary>
            Arabic,

            /// <summary>Bulgarian language.</summary>
            Bulgarian,

            /// <summary>Chinese language.</summary>
            Chinese,

            /// <summary>Croatian language.</summary>
            Croatian,

            /// <summary>Czech language.</summary>
            Czech,

            /// <summary>English language.</summary>
            English,

            /// <summary>French language.</summary>
            French,

            /// <summary>German language.</summary>
            German,

            /// <summary>Hungarian language.</summary>
            Hungarian,

            /// <summary>Italian language.</summary>
            Italian,

            /// <summary>Japanese language.</summary>
            Japanese,

            /// <summary>Korean language.</summary>
            Korean,

            /// <summary>Polish language.</summary>
            Polish,

            /// <summary>Portuguese language.</summary>
            Portuguese,

            /// <summary>Romanian language.</summary>
            Romanian,

            /// <summary>Russian language.</summary>
            Russian,

            /// <summary>Spanish language.</summary>
            Spanish,

            /// <summary>Turkish language.</summary>
            Turkish
        };

        /// <summary>
        /// Values that represent report types.
        /// </summary>
        enum class ReportType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>A report about data sources.</summary>
            Camera,

            /// <summary>A report about data sources accessibility by each role.</summary>
            CameraRoleAccess,

            /// <summary>A report about devices.</summary>
            Device,

            /// <summary>A report about events.</summary>
            Event,

            /// <summary>A report containing analytic line counting data from data sources.</summary>
            LineCount,

            /// <summary>A report about gaps.</summary>
            RecordingGap,

            /// <summary>A report about roles.</summary>
            Role,

            /// <summary>A report about data storages.</summary>
            Storage,

            /// <summary>A report about the health of the system.</summary>
            SystemStatus,

            /// <summary>A report about users.</summary>
            User,

            /// <summary>A report about user-related events.</summary>
            UserAction
        };

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewReportTemplate()
        {
            Fields = gcnew System::Collections::Generic::List<ReportField^>();
            Filters = gcnew System::Collections::Generic::List<ReportFilter^>();
            Recurrence = gcnew System::Collections::Generic::List<TimeRange::DayOfWeek>();
            StorageLocation = gcnew NetworkStorageInfo();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxNewReportTemplate">The vx new report template.</param>
        NewReportTemplate(VxSdk::VxNewReportTemplate* vxNewReportTemplate) {
            Duration = vxNewReportTemplate->duration;
            EndTime = Utils::ConvertCppDateTime(vxNewReportTemplate->endTime);
            Format = Utils::ConvertCppString(vxNewReportTemplate->format);
            Interval = (LineCountingRequest::TimeInterval)vxNewReportTemplate->interval;
            Language = (VxLanguage)vxNewReportTemplate->language;
            Name = Utils::ConvertCppString(vxNewReportTemplate->name);
            RecurrenceTime = Utils::ConvertCppTime(vxNewReportTemplate->recurrenceTime);
            StorageLocation = gcnew NetworkStorageInfo(vxNewReportTemplate->storageLocation);
            Type = (ReportType)vxNewReportTemplate->type;

            Fields = gcnew System::Collections::Generic::List<ReportField^>();
            for (int i = 0; i < vxNewReportTemplate->fieldsSize; i++) {
                Fields->Add(gcnew ReportField(vxNewReportTemplate->fields[i]));
            }

            Filters = gcnew System::Collections::Generic::List<ReportFilter^>();
            for (int i = 0; i < vxNewReportTemplate->filtersSize; i++) {
                Filters->Add(gcnew ReportFilter(vxNewReportTemplate->filters[i]));
            }

            Recurrence = gcnew System::Collections::Generic::List<TimeRange::DayOfWeek>();
            for (int i = 0; i < vxNewReportTemplate->recurrenceSize; i++) {
                Recurrence->Add((TimeRange::DayOfWeek)vxNewReportTemplate->recurrence[i]);
            }
        }

        /// <summary>
        /// Gets or sets the duration of time, in hours, extending back from <see cref="EndTime"/> to limit collected report data
        /// to. If 0, there is no limit.
        /// </summary>
        /// <value>The duration of time, in hours.</value>
        property int Duration;

        /// <summary>
        /// Gets or sets the end time at which the collected report data is limited to. If not specified, report data will be
        /// collected up to the current time at which the report is generated.
        /// </summary>
        /// <value>The end time.</value>
        property System::DateTime EndTime;

        /// <summary>
        /// Gets or sets the ordered list of report fields available to include in the report.
        /// </summary>
        /// <value>The the ordered list of report fields.</value>
        property System::Collections::Generic::List<ReportField^>^ Fields;

        /// <summary>
        /// Gets or sets the list of report filters to use to filter the contents of the report.
        /// </summary>
        /// <value>The list of report filters.</value>
        property System::Collections::Generic::List<ReportFilter^>^ Filters;

        /// <summary>
        /// Gets or sets the desired format for the contents of the report.
        /// </summary>
        /// <value>The format.</value>
        property System::String^ Format;

        /// <summary>
        /// Gets or sets the time interval that is used to track data in the report (days, hours, etc).
        /// </summary>
        /// <value>The time interval.</value>
        property LineCountingRequest::TimeInterval Interval;

        /// <summary>
        /// Gets or sets the language to use when creating the report.
        /// </summary>
        /// <value>The language to use when creating the report.</value>
        property VxLanguage Language;

        /// <summary>
        /// Gets or sets friendly name of the report template.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the days of the week to automatically generate a report from this template. Ignored if
        /// <see cref="RecurrenceTime"/> is not set.
        /// </summary>
        /// <value>The days of the week to generate a report.</value>
        property System::Collections::Generic::List<TimeRange::DayOfWeek>^ Recurrence;

        /// <summary>
        /// Gets or sets the time at which to perform automatic report generation on given recur days, from 00:00:00 to 23:59:59.
        /// Ignored if <see cref="Recurrence"/> is not set.
        /// </summary>
        /// <value>The automatic generation time.</value>
        property System::DateTime RecurrenceTime;

        /// <summary>
        /// Gets or sets the network storage location to export the report data to. Ignored if <see cref="Recurrence"/> is not set.
        /// </summary>
        /// <value>The network storage location.</value>
        property NetworkStorageInfo^ StorageLocation;

        /// <summary>
        /// Gets or sets the type of the report that this template represents.
        /// </summary>
        /// <value>The report type.</value>
        property ReportType Type;
    };
}
#endif // NewReportTemplate_h__
