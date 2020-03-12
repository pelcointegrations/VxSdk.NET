// Declares the member class.
#ifndef Member_h__
#define Member_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ResourceLimits.h"

namespace VxSdkNet {

    /// <summary>
    /// The Member class represents a member system.
    /// </summary>
    public ref class Member {
    public:

        /// <summary>
        /// Values that represent operational states for a member system.
        /// </summary>
        enum class  MemberState {
            /// <summary>Unable to determine status or an error was returned.</summary>
            Unknown,

            /// <summary>Online; available.</summary>
            Online,

            /// <summary>Being added; unavailable.</summary>
            Pending,

            /// <summary>Being removed; unavailable.</summary>
            Removing,

            /// <summary>Invalid credentials; unavailable.</summary>
            Unauthorized,

            /// <summary>Offline; unavailable.</summary>
            Unavailable
        };

        /// <summary>
        /// Values that represent network streaming capabilities.
        /// </summary>
        enum class RtspCapability {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>TCP streaming capability.</summary>
            Tcp,

            /// <summary>TCP and UDP streaming capabilities.</summary>
            TcpUdp,

            /// <summary>TCP, UDP and multicast streaming capabilities.</summary>
            TcpUdpMulticast
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxMember">The vx member.</param>
        Member(VxSdk::IVxMember* vxMember);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Member() {
            this->!Member();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Member();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Triggers a refresh of this member system; ensures that the aggregating system is in sync with the
        /// member system.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of refreshing the member system.</returns>
        Results::Value TriggerRefresh();

        /// <summary>
        /// Gets or sets the bandwidth available between the aggregator system and the member system (in kbps).
        /// </summary>
        /// <value>The bandwidth in kbps.</value>
        property int Bandwidth {
        public:
            int get() { return _member->bandwidth; }
            void set(int value) { _member->SetBandwidth(value); }
        }

        /// <summary>
        /// Gets or sets the host address of the system.
        /// </summary>
        /// <value>The host address.</value>
        property System::String^ Host {
        public:
            System::String^ get() { return Utils::ConvertCppString(_member->host); }
            void set(System::String^ value) {
                char host[256];
                VxSdk::Utilities::StrCopySafe(host, Utils::ConvertCSharpString(value).c_str());
                _member->SetHost(host);
            }
        }

        /// <summary>
        /// Gets the unique identifier of the member system.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_member->id); }
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
        /// Gets the friendly name for the member system. This value comes from the system name field,
        /// containing the system’s friendly name. This is not an alias for the system.
        /// </summary>
        /// <value>The friendly name of the member system.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_member->name); }
        }

        /// <summary>
        /// Gets or sets the password for access to the member.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ Password {
        public:
            void set(System::String^ value) {
                char password[64];
                VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(value).c_str());
                _member->SetPassword(password);
            }
        }

        /// <summary>
        /// Gets or sets the host port of the system.
        /// </summary>
        /// <value>The host port.</value>
        property int Port {
        public:
            int get() { return _member->hostPort; }
            void set(int value) { _member->SetHostPort(value); }
        }

        /// <summary>
        /// Gets or sets the network streaming capabilities that the member shall expose to its clients (via data interfaces).
        /// </summary>
        /// <value>The network streaming capabilities.</value>
        property RtspCapability RtspCapabilities {
        public:
            RtspCapability get() { return (RtspCapability)_member->rtspCapability; }
            void set(RtspCapability value) { _member->SetRtspCapability((VxSdk::VxRtspCapability::Value)value); }
        }

        /// <summary>
        /// Gets the current operational state.
        /// </summary>
        /// <value>The current operational state.</value>
        property MemberState State {
        public:
            MemberState get() { return (MemberState)_member->state; }
        }

        /// <summary>
        /// Gets or sets the username for access to the member.
        /// </summary>
        /// <value>The username.</value>
        property System::String^ Username {
        public:
            System::String^ get() { return Utils::ConvertCppString(_member->username); }
            void set(System::String^ value) {
                char username[64];
                VxSdk::Utilities::StrCopySafe(username, Utils::ConvertCSharpString(value).c_str());
                _member->SetUsername(username);
            }
        }

    internal:
        VxSdk::IVxMember* _member;
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // Member_h__
