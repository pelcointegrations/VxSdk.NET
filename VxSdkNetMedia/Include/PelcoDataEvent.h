// Declares the PelcoDataManagedEvent class.
#ifndef PelcoDataManagedEvent_h__
#define PelcoDataManagedEvent_h__

#include "MediaController.h"

namespace VxSdkNet {

    /// <summary>
    /// The PelcoDataManagedEvent class represents an Pelco data event that has been sent from a stream.
    /// </summary>
    public ref class PelcoDataManagedEvent {
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
        /// <param name="pelcoDataEvent">The Pelco data event.</param>
        PelcoDataManagedEvent(MediaController::PelcoDataEvent* pelcoDataEvent) : _pelcoDataEvent(pelcoDataEvent) {};

        /// <summary>
        /// Gets the event type.
        /// </summary>
        /// <value>The event type.</value>
        property EventTypes EventType {
        public:
            EventTypes get() {
                return (EventTypes)_pelcoDataEvent->eventType;
            }
        }
        
        /// <summary>
        /// Gets the Pelco data string.
        /// </summary>
        /// <value>The Pelco data string.</value>
        property System::String^ PelcoData {
        public:
            System::String^ get() { return gcnew System::String(reinterpret_cast<char*>(_pelcoDataEvent->pelcoData)); }
        }
        
    internal:
        MediaController::PelcoDataEvent* _pelcoDataEvent;
    };
}
#endif // PelcoDataManagedEvent_h__
