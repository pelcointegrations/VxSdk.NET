// Declares the report filter class.
#ifndef ReportFilter_h__
#define ReportFilter_h__

#include "ResourceRef.h"
#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The ReportFilter class represents a filter within a report.
    /// </summary>
    public ref class ReportFilter {
    public:

        /// <summary>
        /// Values that represent a type of resource to filter by in a report.
        /// </summary>
        enum class ReportFilterType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>An analytic behavior report filter.</summary>
            AnalyticBehavior,

            /// <summary>A data source report filter.</summary>
            DataSource,

            /// <summary>A data storage report filter.</summary>
            DataStorage,

            /// <summary>A device report filter.</summary>
            Device,

            /// <summary>A role report filter.</summary>
            Role,

            /// <summary>A situation report filter.</summary>
            Situation,

            /// <summary>A user report filter.</summary>
            User
        };

        /// <summary>
        /// Default constructor.
        /// </summary>
        ReportFilter()
        {
            FilterIds = gcnew System::Collections::Generic::List<System::String^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxReportFilter">The vx report filter.</param>
        ReportFilter(VxSdk::VxReportFilter* vxReportFilter){
            Type = (ReportFilterType)vxReportFilter->type;
            FilterIds = gcnew System::Collections::Generic::List<System::String^>();
            for (int i = 0; i < vxReportFilter->filterIdSize; i++) {
                FilterIds->Add(Utils::ConvertCppString(vxReportFilter->filterIds[i]));
            }
        }

        /// <summary>
        /// Gets or sets the list of unique identifiers to filter by (based on type). For instance, if the type is a
        /// data source, this will be the list of data source IDs to limit the report contents to.
        /// </summary>
        /// <value>The list of resource IDs to filter.</value>
        property System::Collections::Generic::List<System::String^>^ FilterIds;

        /// <summary>
        /// Gets or sets the resource type.
        /// </summary>
        /// <value>The resource type.</value>
        property ReportFilterType Type;
    };
}
#endif // ReportFilter_h__
