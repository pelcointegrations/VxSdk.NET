// Declares the alarm input class.
#ifndef AlarmInput_h__
#define AlarmInput_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ResourceLimits.h"

namespace VxSdkNet {
    ref class Device;

    /// <summary>
    /// The AlarmInput class represents a physical alarm input.
    /// </summary>
    public ref class AlarmInput {
    public:

        /// <summary>
        /// Values that represent the state of an alarm input.
        /// </summary>
        enum class AlarmStates {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The alarm input is active.</summary>
            Active,

            /// <summary>The alarm input is inactive.</summary>
            Inactive
        };

        /// <summary>
        /// Values that represent the types of alarm inputs.
        /// </summary>
        enum class AlarmInputTypes {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The alarm input is a generic alarm.</summary>
            Alarm,

            /// <summary>The alarm input is a fire alarm.</summary>
            Fire
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxAlarmInput">The vx alarm input.</param>
        AlarmInput(VxSdk::IVxAlarmInput* vxAlarmInput);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~AlarmInput() {
            this->!AlarmInput();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !AlarmInput();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets or sets the friendly description of the alarm input.
        /// </summary>
        /// <value>The friendly description.</value>
        property System::String^ Description {
        public:
            System::String^ get() { return Utils::ConvertCppString(_alarmInput->description); }
            void set(System::String^ value) {
                char description[255];
                VxSdk::Utilities::StrCopySafe(description, Utils::ConvertCSharpString(value).c_str());
                _alarmInput->SetDescription(description);
            }
        }

        /// <summary>
        /// Gets the device that hosts this alarm input.
        /// </summary>
        /// <value>The host device.</value>
        property VxSdkNet::Device^ HostDevice {
        public:
            VxSdkNet::Device^ get() { return _GetHostDevice(); }
        }

        /// <summary>
        /// Gets the unique alarm input identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_alarmInput->id); }
        }

        /// <summary>
        /// Gets any limits related to this resource.
        /// </summary>
        /// <value>The limits related to this resource.</value>
        property ResourceLimits^ Limits {
        public:
            ResourceLimits^ get() { return _GetLimits(); }
        }

        /// <summary>
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_alarmInput->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _alarmInput->SetName(name);
            }
        }

        /// <summary>
        /// Gets the current state of this alarm input.
        /// </summary>
        /// <value>The alarm input state.</value>
        property AlarmStates State {
        public:
            AlarmStates get() { return AlarmStates(_alarmInput->state); }
        }

        /// <summary>
        /// Gets or sets the particular type of this alarm input
        /// </summary>
        /// <value>The alarm input type.</value>
        property AlarmInputTypes Type {
        public:
            AlarmInputTypes get() { return AlarmInputTypes(_alarmInput->type); }
            void set(AlarmInputTypes value) { _alarmInput->SetType((VxSdk::VxAlarmInputType::Value)value); }
        }

    internal:
        VxSdk::IVxAlarmInput* _alarmInput;
        VxSdkNet::Device^ _GetHostDevice();
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // AlarmInput_h__
