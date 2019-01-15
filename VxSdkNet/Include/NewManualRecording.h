// Declares the new manual recording class.
#ifndef NewManualRecording_h__
#define NewManualRecording_h__

#include "ManualRecording.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewManualRecording class represents a request for a new manual recording to be generated.
    /// </summary>
    public ref class NewManualRecording {
    public:

        /// <summary>
        /// Gets or sets the unique identifier of the data source to manually record.
        /// </summary>
        /// <value>The unique identifier of the data source to manually record.</value>
        property System::String^ DataSourceId;

        /// <summary>
        /// Gets or sets the amount of time, from 0 to 30 seconds, to record after the manual recording is stopped.
        /// </summary>
        /// <value>The amount of time, in seconds, to record after the manual recording is stopped.</value>
        property int PostRecord;

        /// <summary>
        /// Gets or sets the amount of time, from 0 to 30 seconds, to record prior to the manual recording start time.
        /// </summary>
        /// <value>The amount of time, in seconds, to record prior to the manual recording start time.</value>
        property int PreRecord;
    };
}
#endif // NewManualRecording_h__
