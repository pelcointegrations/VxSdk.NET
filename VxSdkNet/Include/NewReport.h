// Declares the new report class.
#ifndef NewReport_h__
#define NewReport_h__

namespace VxSdkNet {

    /// <summary>
    /// The NewReport class represents a request to generate a new report.
    /// </summary>
    public ref class NewReport {
    public:

        /// <summary>
        /// Gets or sets the friendly name of the new report. If not specified, the name of the report template will be used.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the unique identifier of the report template to use to generate the new report.
        /// </summary>
        /// <value>The unique identifier of the report template.</value>
        property System::String^ TemplateId;
    };
}
#endif // NewReport_h__
