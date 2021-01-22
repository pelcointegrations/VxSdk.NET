// Declares the new recording class.
#ifndef NewRecording_h__
#define NewRecording_h__

#include "Recording.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewRecording class represents a request for a new recording to be generated.
    /// </summary>
    public ref class NewRecording {
    public:

        /// <summary>
        /// Gets or sets the unique identifier of the data source to record.
        /// </summary>
        /// <value>The unique identifier of the data source to record.</value>
        property System::String^ DataSourceId;

        /// <summary>
        /// Gets or sets the situation type that will automatically end the recording when a matching event occurs.
        /// </summary>
        /// <value>The situation type.</value>
        property System::String^ EndEvent;

        /// <summary>
        /// Gets or sets the unique identifier of recording.
        /// </summary>
        /// <value>The unique identifier of the recording.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets the friendly name of the recording which can be used to identify recordings to stop.
        /// </summary>
        /// <value>The friendly name of the recording.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the maximum amount of time, in seconds, to record before stopping.
        /// </summary>
        /// <value>The maximum amount of time, in seconds, to record before stopping.</value>
        property int MaxRecordingTime;

        /// <summary>
        /// Gets or sets the amount of time, in seconds, to record after the recording would otherwise be stopped.
        /// </summary>
        /// <value>The amount of time, in seconds, to record after the recording would otherwise be stopped.</value>
        property int PostRecord;

        /// <summary>
        /// Gets or sets the amount of time, in seconds, to record prior to the recording start time.
        /// </summary>
        /// <value>The amount of time, in seconds, to record prior to the recording start time.</value>
        property int PreRecord;

        /// <summary>
        /// Gets or sets the framerate to record at.
        /// </summary>
        /// <value>The framerate to record at.</value>
        property Recording::RecordingFramerates Framerate;

        /// <summary>
        /// Gets or sets the type of this recording which will show up in the corresponding clips
        /// </summary>
        /// <value>The type of this recording which will show up in the corresponding clips</value>
        property Recording::RecordingTypes RecordingType;

        /// <summary>
        /// Gets or sets the source that will be used to filter <see cref="EndEvent"/>.
        /// </summary>
        /// <value>The source reference.</value>
        property ResourceRef^ EndEventSource;

        /// <summary>
        /// Gets or sets the time at which the recording should begin (may be in the recent past). The recording
        /// <see cref="PreRecord"/> and <see cref="MaxRecordingTime"/> will reference to this time. Defaults to the time
        /// at which the server processes the request.
        /// </summary>
        /// <value>The <c>DateTime</c> at which the recording should begin, otherwise a default <c>DateTime</c>.</value>
        property System::DateTime StartTime;
    };
}
#endif // NewRecording_h__
