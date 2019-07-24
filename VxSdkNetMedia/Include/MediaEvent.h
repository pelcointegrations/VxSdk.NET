// Declares the MediaEvent class.
#ifndef MediaEvent_h__
#define MediaEvent_h__

#include "MediaController.h"

namespace VxSdkNet {

    /// <summary>
    /// The MediaEvent class represents an event that has been sent from a stream.
    /// </summary>
    public ref class MediaEvent {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="timeEvent">The timestamp event.</param>
        MediaEvent(MediaController::TimestampEvent* timeEvent) : _event(timeEvent) {};

        /// <summary>
        /// Gets the timestamp.
        /// </summary>
        /// <value>The current timestamp.</value>
        property System::DateTime Timestamp {
        public:
            System::DateTime get() {
                System::DateTime^ epochTime = gcnew System::DateTime(1970, 1, 1, 0, 0, 0, System::DateTimeKind::Utc);
                epochTime = epochTime->AddSeconds(_event->unixTime);
                // ticks are in 100ns increments
                return epochTime->AddTicks(_event->unixTimeMicroSeconds * 10);
            }
        }

    internal:
        MediaController::TimestampEvent* _event;
    };
}
#endif // MediaEvent_h__
