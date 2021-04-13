// Declares the report class.
#ifndef Report_h__
#define Report_h__

#include "NewReportTemplate.h"
#include "ReportTemplate.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Report class represents a generated (or generating) system report.
    /// </summary>
    public ref class Report {
    public:

        /// <summary>
        /// Values that represent the status of a report.
        /// </summary>
        enum class ReportStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The report failed to be generated.</summary>
            Failed,

            /// <summary>The report is being generated.</summary>
            InProgress,

            /// <summary>The report is queued to be generated.</summary>
            Pending,

            /// <summary>The report was successfully generated.</summary>
            Successful
        };

        /// <summary>
        /// Values that represent the reason for a report failing to be generated.
        /// </summary>
        enum class ReportStatusReason {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The configured storage location is full.</summary>
            StorageFull,

            /// <summary>The configured storage location cannot be used because the configured credentials are invalid.</summary>
            StorageUnauthenticated,

            /// <summary>The configured storage location is unavailable.</summary>
            StorageUnavailable,

            /// <summary>The report could not be generated because the user is not authorized to access the data required to create the report.</summary>
            Unauthorized
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxReport">The vx report.</param>
        Report(VxSdk::IVxReport* vxReport);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Report() {
            this->!Report();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Report();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the format of the contents of the report.
        /// </summary>
        /// <value>The report format.</value>
        property System::String^ Format {
        public:
            System::String^ get() { return Utils::ConvertCppString(_report->format); }
        }

        /// <summary>
        /// Gets the unique identifier of the report.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_report->id); }
        }

        /// <summary>
        /// Gets the friendly name of the report.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_report->name); }
        }

        /// <summary>
        /// Gets the owner of the report. If present, indicates that this resource is owned by a user (it is private)
        /// and this is their username. If not present, indicates that this resource is not owned (it is public).
        /// </summary>
        /// <value>The owner of the report.</value>
        property System::String^ Owner {
        public:
            System::String^ get() { return Utils::ConvertCppString(_report->owner); }
        }

        /// <summary>
        /// Gets the URI to the download location of the actual report data. This endpoint will only be present if the
        /// report has been successfully generated and is available for download.
        /// </summary>
        /// <value>The report endpoint, if available.</value>
        property System::String^ ReportEndpoint {
        public:
            System::String^ get() { return _GetReportEndpoint(); }
        }

        /// <summary>
        /// Gets the current generation status of this report.
        /// </summary>
        /// <value>The current generation status of this report.</value>
        property ReportStatus Status {
        public:
            ReportStatus get() { return (ReportStatus)(_report->status); }
        }

        /// <summary>
        /// Gets the optional reason for the current generation status of this report; typically used to express the reason
        /// for a failure.
        /// </summary>
        /// <value>The reason for the current generation status of this report.</value>
        property ReportStatusReason StatusReason {
        public:
            ReportStatusReason get() { return (ReportStatusReason)(_report->statusReason); }
        }

        /// <summary>
        /// Gets the report template that this report was generated from.
        /// </summary>
        /// <value>The report template.</value>
        property ReportTemplate^ Template {
        public:
            ReportTemplate^ get() { return _GetReportTemplate(); }
        }

        /// <summary>
        /// Gets the date and time at which the report was generated.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which the report was generated.</value>
        property System::DateTime Time {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_report->time); }
        }

        /// <summary>
        /// Gets the type of this report.
        /// </summary>
        /// <value>The type of this report.</value>
        property NewReportTemplate::ReportType Type {
        public:
            NewReportTemplate::ReportType get() { return (NewReportTemplate::ReportType)(_report->type); }
        }

    internal:
        VxSdk::IVxReport* _report;
        System::String^ _GetReportEndpoint();
        ReportTemplate^ _GetReportTemplate();
    };
}
#endif // Report_h__
