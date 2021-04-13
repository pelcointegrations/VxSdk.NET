// Declares the export estimate class.
#ifndef ExportEstimate_h__
#define ExportEstimate_h__

namespace VxSdkNet {

    /// <summary>
    /// The ExportEstimate class represents an estimate for an export.
    /// </summary>
    public ref class ExportEstimate {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        ExportEstimate() {
        }

        /// <summary>
        /// Gets or sets whether the server was able to estimate the entire requested export.
        /// </summary>
        /// <value>
        /// <c>true</c> if the server was unable to estimate the entire export because it was too large
        /// and the <see cref="Size"/> value is a minimum amount and not the actual estimate.
        /// </value>
        property bool IsTooLarge;

        /// <summary>
        /// Gets or sets the estimated file size of the exported media in kilobytes (KB); will be 0 if
        /// unknown or unavailable.
        /// </summary>
        /// <value>The estimated file size in kilobytes (KB).</value>
        property int Size;
    };
}
#endif // ExportEstimate_h__
