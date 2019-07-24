// Declares the event class.
#ifndef Event_h__
#define Event_h__

#include "Utils.h"
#include "Device.h"
#include "Situation.h"
#include "User.h"

namespace VxSdkNet {

    /// <summary>
    /// The Event class represents an instance of a particular situation that has occurred.
    /// </summary>
    public ref class Event {
    public:

        /// <summary>
        /// Values that represent the current acknowledgement state of an event.
        /// </summary>
        enum class AckStates {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The event needs acknowledgement.</summary>
            AckNeeded,

            /// <summary>The event is acknowledged.</summary>
            Acked,

            /// <summary>The event is auto-acknowledged.</summary>
            AutoAcked,

            /// <summary>No event acknowledgement is needed.</summary>
            NoAckNeeded,

            /// <summary>The event has been silenced.</summary>
            Silenced
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxEvent">The vx event.</param>
        Event(VxSdk::IVxEvent* vxEvent);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Event() {
            this->!Event();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Event();

        /// <summary>
        /// Acknowledge the event.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value Acknowledge() { return (Results::Value)_event->Acknowledge(); }

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh() { return (VxSdkNet::Results::Value)_event->Refresh(); }

        /// <summary>
        /// Silence the event for a given amount of time.
        /// </summary>
        /// <param name="wakeup">The delay, in seconds, to apply prior to the event being brought to
        /// the user�s attention.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value Silence(int wakeup) { return (Results::Value)_event->Silence(wakeup); }

        /// <summary>
        /// Gets the identifier of the client that set the current ackState, if any.
        /// </summary>
        /// <value>The client identifier.</value>
        property System::String^ AckClientId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->ackClientId); }
        }

        /// <summary>
        /// Gets the friendly name of the client that set the current <see cref="AckState"/>, if any.
        /// </summary>
        /// <value>The friendly name of the client.</value>
        property System::String^ AckClientName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->ackClientName); }
        }

        /// <summary>
        /// Gets the current acknowledgement state of the event.
        /// </summary>
        /// <value>The current acknowledgement state.</value>
        property AckStates AckState {
        public:
            AckStates get() { return (AckStates)_event->ackState; }
        }

        /// <summary>
        /// Gets the time at which the current <see cref="AckState"/> was set.
        /// </summary>
        /// <value>The event acknowledgement time.</value>
        property System::DateTime AckTime {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_event->ackTime); }
        }

        /// <summary>
        /// Gets the name of the user that set the current <see cref="AckState"/>, if any.
        /// </summary>
        /// <value>The user name.</value>
        property System::String^ AckUserName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->ackUser); }
        }

        /// <summary>
        /// Gets the unique identifier of the device that created and injected this
        /// event into the system.
        /// </summary>
        /// <value>The identifier of the generator device.</value>
        property VxSdkNet::Device^ GeneratorDevice {
        public:
            VxSdkNet::Device^ get() { return _GetGeneratorDevice(); }
        }

        /// <summary>
        /// Gets the unique identifier of the device that created and injected this
        /// event into the system.
        /// </summary>
        /// <value>The identifier of the generator device.</value>
        property System::String^ GeneratorDeviceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->generatorDeviceId); }
        }

        /// <summary>
        /// Gets the friendly name of the generator device, if any.
        /// </summary>
        /// <value>The friendly name of the generator device.</value>
        property System::String^ GeneratorDeviceName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->generatorDeviceName); }
        }

        /// <summary>
        /// Gets the unique identifier created by the device that generated the event.
        /// </summary>
        /// <value>The events unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->id); }
        }

        /// <summary>
        /// Gets a value indicating whether the event is in its initial generated state (its ackState has not been updated).
        /// </summary>
        /// <value><c>true</c> if the event is in its initial generated state, <c>false</c> if not.</value>
        property bool IsInitial {
        public:
            bool get() { return _event->isInitial; }
        }

        /// <summary>
        /// Gets a list of the properties associated with the event, if any.
        /// </summary>
        /// <value>The event properties.</value>
        property System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ Properties {
        public:
            System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ get() {
                return _GetProperties();
            }
        }

        /// <summary>
        /// Gets the severity of the event, from 1 (highest) to 10 (lowest).
        /// </summary>
        /// <value>The event severity.</value>
        property unsigned short Severity {
        public:
            unsigned short get() { return _event->severity; }
        }

        /// <summary>
        /// Gets a value indicating whether a notification sound should play on supporting clients when an event is received.
        /// </summary>
        /// <value><c>true</c> if a notification sound should play, <c>false</c> if not.</value>
        property bool ShouldAudiblyNotify {
        public:
            bool get() { return _event->shouldAudiblyNotify; }
        }

        /// <summary>
        /// Gets the type of the situation that led to the generation of this Event.
        /// </summary>
        /// <value>The type of the situation.</value>
        property VxSdkNet::Situation^ Situation {
        public:
            VxSdkNet::Situation^ get() { return _GetSituation(); }
        }

        /// <summary>
        /// Gets the name of the situation that led to the generation of this event.
        /// </summary>
        /// <value>The name of the situation.</value>
        property System::String^ SituationName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->situationName); }
        }

        /// <summary>
        /// Gets the type of the situation that led to the generation of this Event.
        /// </summary>
        /// <value>The type of the situation.</value>
        property System::String^ SituationType {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->situationType); }
        }

        /// <summary>
        /// Gets the client identifier of the client that was the cause of the situation, if any.
        /// </summary>
        /// <value>The client identifier.</value>
        property System::String^ SourceClientId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->sourceClientId); }
        }

        /// <summary>
        /// Gets the unique identifier of the device that the situation occurred on.
        /// </summary>
        /// <value>The unique identifier of the source device.</value>
        property VxSdkNet::Device^ SourceDevice {
        public:
            VxSdkNet::Device^ get() { return _GetSourceDevice(); }
        }

        /// <summary>
        /// Gets the unique identifier of the device that the situation occurred on.
        /// </summary>
        /// <value>The unique identifier of the source device.</value>
        property System::String^ SourceDeviceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->sourceDeviceId); }
        }

        /// <summary>
        /// Gets the friendly name of the source device.
        /// </summary>
        /// <value>The friendly name of the source device.</value>
        property System::String^ SourceDeviceName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->sourceDeviceName); }
        }

        /// <summary>
        /// Gets the name of the user that was the cause of the situation, if any.
        /// </summary>
        /// <value>The user name.</value>
        property VxSdkNet::User^ SourceUser {
        public:
            VxSdkNet::User^ get() { return _GetSourceUser(); }
        }

        /// <summary>
        /// Gets the name of the user that was the cause of the situation, if any.
        /// </summary>
        /// <value>The user name.</value>
        property System::String^ SourceUserName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_event->sourceUserName); }
        }

        /// <summary>
        /// Gets the time at which the situation occurred.
        /// </summary>
        /// <value>The event time.</value>
        property System::DateTime Time {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_event->time); }
        }

        /// <summary>
        /// Gets the delay, in seconds, prior to bringing the event to the users attention; typically used for silencing the event.
        /// </summary>
        /// <value>The delay, in seconds.</value>
        property int Wakeup {
        public:
            int get() { return _event->wakeup; }
        }

    internal:
        VxSdk::IVxEvent* _event;
        VxSdkNet::Device^ _GetGeneratorDevice();
        System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ _GetProperties();
        VxSdkNet::Situation^ _GetSituation();
        VxSdkNet::Device^ _GetSourceDevice();
        VxSdkNet::User^ _GetSourceUser();
    };
}
#endif // Event_h__
