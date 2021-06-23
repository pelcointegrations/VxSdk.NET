// Declares the vx file recovery class.
#ifndef VxFileRecovery_h__
#define VxFileRecovery_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The VxFileRecovery class represents a file recovery controller/monitoring resource for a recorder.
    /// </summary>
    public ref class VxFileRecovery {
    public:

        /// <summary>
        /// Values that represent the status of a file recovery.
        /// </summary>
        enum class FileRecoveryStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The file recovery failed.</summary>
            Failed,

            /// <summary>The file recovery process is idle.</summary>
            Idle,

            /// <summary>The file recovery is in progress.</summary>
            InProgress,

            /// <summary>The file recovery succeeded.</summary>
            Success
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxFileRecovery">The vx file recovery.</param>
        VxFileRecovery(VxSdk::IVxFileRecovery* vxFileRecovery);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~VxFileRecovery() {
            this->!VxFileRecovery();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !VxFileRecovery();

        /// <summary>
        /// Halts any file recovery in process.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of halting the file recovery process.</returns>
        Results::Value Halt();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Triggers a file recovery.
        /// </summary>
        /// <param name="volumeId">The unique identifier of the volume to recover files from.</param>
        /// <param name="startTime">The start time; files created before this time will not be recovered.</param>
        /// <param name="endTime">The end time; files created after this time will not be recovered.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of triggering the file recovery.</returns>
        Results::Value Trigger(System::String^ volumeId, System::DateTime startTime, System::DateTime endTime);

        /// <summary>
        /// Gets the number of files recovered.
        /// </summary>
        /// <value>The number of files recovered..</value>
        property int FilesRecovered {
        public:
            int get() { return _vxFileRecovery->filesRecovered; }
        }

        /// <summary>
        /// Gets the current status of the file recovery.
        /// </summary>
        /// <value>The current status.</value>
        property FileRecoveryStatus Status {
        public:
            FileRecoveryStatus get() { return (FileRecoveryStatus)_vxFileRecovery->status; }
        }

        /// <summary>
        /// Gets the message about the current status of the file recovery, if any.
        /// </summary>
        /// <value>The message about the current status, if any.</value>
        property System::String^ StatusMessage {
        public:
            System::String^ get() { return Utils::ConvertCppString(_vxFileRecovery->statusMessage); }
        }

    internal:
        VxSdk::IVxFileRecovery* _vxFileRecovery;
    };
}
#endif // VxFileRecovery_h__
