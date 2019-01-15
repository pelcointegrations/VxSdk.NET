// Declares the new export clip class.
#ifndef NewExportClip_h__
#define NewExportClip_h__

#include "Utils.h"
#include "Export.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewExportClip class represents a new export clip.
    /// </summary>
    public ref class NewExportClip {
    public:

        /// <summary>
        /// Gets or sets the specific data encoding to export (quality, framerate, and resolution). This can be obtained from the desired data interface of
        /// the clip. If not specified, the server shall select the data encoding.
        /// </summary>
        /// <value>The specific data encoding to export.</value>
        property System::String^ DataEncodingId;

        /// <summary>
        /// Gets or sets the unique identifier of the data source.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ DataSourceId;

        /// <summary>
        /// Gets or sets the time at which the clip ends.
        /// </summary>
        /// <value>The end time.</value>
        property System::DateTime EndTime;

        /// <summary>
        /// Gets or sets the time at which the clip begins.
        /// </summary>
        /// <value>The start time.</value>
        property System::DateTime StartTime;
    };
}
#endif // NewExportClip_h__
