// Declares the export clip class.
#ifndef ExportClip_h__
#define ExportClip_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The ExportClip class represents an individual range of media data belonging to an
    /// Export. This data shall be exported when the Export is triggered.
    /// </summary>
    public ref class ExportClip {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxClip">The vx clip.</param>
        ExportClip(VxSdk::IVxExportClip* vxClip);

        /// <summary>
        /// Gets the data source unique identifier of the export media.
        /// </summary>
        /// <value>The unique identifier of the data source.</value>
        property System::String^ DataSourceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_exportClip->dataSourceId); }
        }

        /// <summary>
        /// Gets the time at which the export media ends.
        /// </summary>
        /// <value>The end time.</value>
        property System::DateTime EndTime {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_exportClip->endTime); }
        }

        /// <summary>
        /// Gets the unique identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_exportClip->id); }
        }

        /// <summary>
        /// Gets the time at which the export media begins.
        /// </summary>
        /// <value>The start time.</value>
        property System::DateTime StartTime {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_exportClip->startTime); }
        }

    internal:
        VxSdk::IVxExportClip* _exportClip;
    };
}
#endif // ExportClip_h__
