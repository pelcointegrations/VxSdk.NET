// Declares the StreamingEvent class.
#ifndef StreamingEvent_h__
#define StreamingEvent_h__

#include "MediaController.h"

namespace VxSdkNet {

    /// <summary>
    /// The MediaEvent class represents an event that has been sent from a stream.
    /// </summary>
    public ref class StreamingEvent {
    public:

        /// <summary>
        /// Values that represent the streaming events.
        /// </summary>
        enum class EventTypes {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The connection to the stream was lost.</summary>
            ConnectionLost
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="streamEvent">The streaming event.</param>
        StreamingEvent(MediaController::StreamEvent* streamEvent) : _streamEvent(streamEvent) {};

        /// <summary>
        /// Gets the event type.
        /// </summary>
        /// <value>The event type.</value>
        property EventTypes EventType {
        public:
            EventTypes get() {
                return (EventTypes)_streamEvent->eventType;
            }
        }

    internal:
        MediaController::StreamEvent* _streamEvent;
    };
}
#endif // StreamingEvent_h__
