// Declares the recording class.
#ifndef Recording_h__
#define Recording_h__

#include "VxSdk.h"
#include "DataSource.h"
#include "Privilege.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Recording class represents an instance of an active recording (the action, not the recorded clip).
    /// Each recording will cause its specified data source to be recorded by all data storages that the
    /// data source is assigned to.
    /// </summary>
    public ref class Recording {
    public:

        /// <summary>
        /// Values that represent the video framerate level.
        /// </summary>
        enum class RecordingFramerates {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Low framerate.</summary>
            Low,

            /// <summary>Normal framerate.</summary>
            Normal
        };

        /// <summary>
        /// Values that represent the type of trigger that caused the recording.
        /// </summary>
        enum class RecordingTypes {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Hardware or software alarm.</summary>
            Alarm,

            /// <summary>Video analytic (non-motion).</summary>
            Analytic,

            /// <summary>General system event.</summary>
            Event,

            /// <summary>Manual user initiation.</summary>
            Manual,

            /// <summary>Motion anayltic.</summary>
            Motion,

            /// <summary>Time-based (continuous); no event.</summary>
            Timed
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxRecording">The vx recording.</param>
        Recording(VxSdk::IVxRecording* vxRecording);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Recording() {
            this->!Recording();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Recording();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the data source that is being recorded.
        /// </summary>
        /// <value>The data source being recorded.</value>
        property VxSdkNet::DataSource^ DataSource {
        public:
            VxSdkNet::DataSource^ get() { return _GetDataSource(); }
        }

        /// <summary>
        /// Gets the unique identifier of the data source that is being recorded.
        /// </summary>
        /// <value>The unique identifier of the data source.</value>
        property System::String^ DataSourceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_recording->dataSourceId); }
        }

        /// <summary>
        /// Gets the situation type that will automatically end the recording when a matching event occurs.
        /// </summary>
        /// <value>The situation type, if any.</value>
        property System::String^ EndEvent {
        public:
            System::String^ get() { return Utils::ConvertCppString(_recording->endEvent); }
        }

        /// <summary>
        /// Gets the source ID that will be used to filter <see cref="EndEvent"/>.
        /// </summary>
        /// <value>The source ID.</value>
        property System::String^ EndEventSourceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_recording->endEventSourceId); }
        }

        /// <summary>
        /// Gets the type of resource that the <see cref="EndEventSourceId"/> specifies.
        /// </summary>
        /// <value>The resource type.</value>
        property ResourceRef::ResourceType EndEventSourceType {
        public:
            ResourceRef::ResourceType get() { return (ResourceRef::ResourceType)_recording->endEventSourceType; }
        }

        /// <summary>
        /// Gets the framerate to record at.
        /// </summary>
        /// <value>The framerate.</value>
        property RecordingFramerates Framerate {
        public:
            RecordingFramerates get() { return (RecordingFramerates)_recording->framerate; }
        }

        /// <summary>
        /// Gets the unique recording identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_recording->id); }
        }

        /// <summary>
        /// Gets the maximum amount of time, in seconds, to record before stopping.
        /// </summary>
        /// <value>The maximum recording time.</value>
        property int MaxRecordingTime {
        public:
            int get() { return _recording->maxRecordingTime; }
        }

        /// <summary>
        /// Gets the friendly name of the recording which can be used to identify recordings to stop.
        /// </summary>
        /// <value>The friendly name of the recording.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_recording->name); }
        }

        /// <summary>
        /// Gets the name of the user that created this recording.
        /// </summary>
        /// <value>The owner name.</value>
        property System::String^ OwnerName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_recording->owner); }
        }

        /// <summary>
        /// Gets the amount of time, in seconds, to record after the recording would otherwise be stopped.
        /// </summary>
        /// <value>The time to record after the recording would otherwise be stopped.</value>
        property int PostRecord {
        public:
            int get() { return _recording->postRecord; }
        }

        /// <summary>
        /// Gets the amount of time, in seconds, to record prior to the recording start time.
        /// </summary>
        /// <value>The time to record prior to the recording start time.</value>
        property int PreRecord {
        public:
            int get() { return _recording->preRecord; }
        }

        /// <summary>
        /// Gets the type of this recording which will show up in the corresponding clips.
        /// </summary>
        /// <value>The recording type.</value>
        property RecordingTypes RecordingType {
        public:
            RecordingTypes get() { return (RecordingTypes)_recording->recordType; }
        }

        /// <summary>
        /// Gets the time at which the recording should begin (may be in the recent past). The recording
        /// <see cref="PreRecord"/> and <see cref="MaxRecordingTime"/> will reference to this time. Defaults to the time
        /// at which the server processes the request.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which the recording should begin.</value>
        property System::DateTime StartTime {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_recording->startTime); }
        }

    internal:
        VxSdk::IVxRecording* _recording;
        VxSdkNet::DataSource^ _GetDataSource();
    };
}
#endif // Recording_h__
