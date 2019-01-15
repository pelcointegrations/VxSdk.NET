// Declares the event class.
#ifndef NewEvent_h__
#define NewEvent_h__

#include "Utils.h"
#include "Event.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewEvent class represents a request for a new event to be generated. The
    /// event will be generated based upon the NewEvent data, its Situation configuration,
    /// and will receive a unique identifier.
    /// </summary>
    public ref class NewEvent {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewEvent() {
            Properties = gcnew System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>();
        }

        /// <summary>
        /// Gets or sets the unique identifier of the device that generated this event.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ GeneratorDeviceId;

        /// <summary>
        /// Gets or sets the unique identifier of the event. If not provided, the server will create this value.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets any additional information related to the event.
        /// </summary>
        /// <value>A <c>List</c> containing the event properties.</value>
        property System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ Properties;

        /// <summary>
        /// Gets or sets the identifier for the type of situation that led to this new event.
        /// </summary>
        /// <value>The type identifier of the situation.</value>
        property System::String^ SituationType;

        /// <summary>
        /// Gets or sets the unique identifier of the device that the situation occurred on.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ SourceDeviceId;

        /// <summary>
        /// Gets or sets the time at which the situation occurred.
        /// </summary>
        /// <value>The time.</value>
        property System::DateTime Time;
    };
}
#endif // NewEvent_h__
