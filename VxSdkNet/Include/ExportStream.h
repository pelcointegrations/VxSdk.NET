// Declares the export stream class.
#ifndef ExportStream_h__
#define ExportStream_h__

#include "VxSdk.h"
#include "ExportStreamClip.h"
#include "User.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The ExportStream class represents streaming access information for an export resource.
    /// </summary>
    public ref class ExportStream {
    public:

        /// <summary>
        /// Values that represent status of an export stream.
        /// </summary>
        enum class States {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The export stream preparation has failed.</summary>
            Failed,

            /// <summary>The export stream needs preparation.</summary>
            NeedsPreparation,

            /// <summary>The export stream is being prepared.</summary>
            Preparing,

            /// <summary>The export stream is ready.</summary>
            Ready
        };

        /// <summary>
        /// Values that represent the reason for the current status of an export stream.
        /// </summary>
        enum class StateReasons {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The export data is unretrievable.</summary>
            ExportDataUnretrievable,

            /// <summary>The temporary export storage is full.</summary>
            ExportTempStorageFull
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxExportStream">The vx export stream.</param>
        ExportStream(VxSdk::IVxExportStream* vxExportStream);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~ExportStream() {
            this->!ExportStream();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !ExportStream();

        /// <summary>
        /// Halts any pending stream preparation. May only be performed when the export stream is being prepared.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of halting the export stream preparation.</returns>
        Results::Value Halt();

        /// <summary>
        /// Begins or re-starts preparation for streaming. May only be performed when the export stream needs
        /// preparation or has failed.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of preparing the export stream.</returns>
        Results::Value Prepare();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the export stream clips, which provide streaming playback information for each export clip.
        /// </summary>
        /// <value>The <c>List</c> of export stream clips.</value>
        property System::Collections::Generic::List<ExportStreamClip^>^ ExportStreamClips {
        public:
            System::Collections::Generic::List<ExportStreamClip^>^ get() { return _GetStreamClips(); }
        }

        /// <summary>
        /// Gets a value from 0 to 100. This specifies how close stream preparation is to completion, where 100
        /// indicates that stream is ready for streaming. This will only be populated when the status is
        /// preparing, failed, or ready. In a failed state, this represents how much progress was made (if any)
        /// prior to the failure.
        /// </summary>
        /// <value>The percent complete.</value>
        property float PercentComplete {
        public:
            float get() { return _exportStream->percentComplete; }
        }

        /// <summary>
        /// Gets the estimated time remaining, in seconds, until the export is 100% ready to be streamed. This
        ///  will only be populated when the status is preparing or ready.
        /// </summary>
        /// <value>The seconds remaining.</value>
        property int SecondsRemaining {
        public:
            int get() { return _exportStream->secondsRemaining; }
        }

        /// <summary>
        /// Gets the current status of the export stream.
        /// </summary>
        /// <value>The current export stream status.</value>
        property States Status {
        public:
            States get() { return (States)_exportStream->status; }
        }

        /// <summary>
        /// Gets the optional reason for the current status of this export stream.
        /// </summary>
        /// <value>The current export stream status reason.</value>
        property StateReasons StatusReason {
        public:
            StateReasons get() { return (StateReasons)_exportStream->statusReason; }
        }

    internal:
        VxSdk::IVxExportStream* _exportStream;
        System::Collections::Generic::List<ExportStreamClip^>^ _GetStreamClips();
    };
}
#endif // ExportStream_h__
