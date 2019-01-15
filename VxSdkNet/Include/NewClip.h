// Declares the new clip class.
#ifndef NewClip_h__
#define NewClip_h__

#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewClip class represents a request to create a new clip on a data storage using data from another data storage. The new
    /// clip will have the same recording type as the data it is based on, defaulting to Timed. Typically this is used to save data
    /// from a camera supporting edge storage to a recorder.
    /// </summary>
    public ref class NewClip {
    public:

        /// <summary>
        /// Gets or sets the unique identifier of the data source that generated the desired data.
        /// </summary>
        /// <value>The unique identifier of the data source.</value>
        property System::String^ DataSourceId;

        /// <summary>
        /// Gets or sets the unique identifier of the data storage to retrieve the data from. The host device type must be
        /// <c>Camera</c> (it must be a camera supporting edge storage).
        /// </summary>
        /// <value>The unique identifier of the data storage.</value>
        property System::String^ DataStorageId;

        /// <summary>
        /// Gets or sets the time at which to end the clip.
        /// </summary>
        /// <value>The end time.</value>
        property System::DateTime EndTime;

        /// <summary>
        /// Gets or sets the time at which to begin the clip.
        /// </summary>
        /// <value>The start time.</value>
        property System::DateTime StartTime;
    };
}
#endif // NewClip_h__
