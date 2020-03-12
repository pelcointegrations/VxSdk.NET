// Declares the new member class.
#ifndef NewMember_h__
#define NewMember_h__

#include "Member.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewMember class represents a new member system.
    /// </summary>
    public ref class NewMember {
    public:

        /// <summary>
        /// Gets or sets the host address of the system.
        /// </summary>
        /// <value>The host address.</value>
        property System::String^ Host;

        /// <summary>
        /// Gets or sets the password for access to the member.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ Password;

        /// <summary>
        /// Gets or sets the username for access to the member.
        /// </summary>
        /// <value>The username.</value>
        property System::String^ Username;

        /// <summary>
        /// Gets or sets the bandwidth available between the aggregator system and the member system (in kbps).
        /// </summary>
        /// <value>The bandwidth in kbps.</value>
        property int Bandwidth;

        /// <summary>
        /// Gets or sets the host port of the system.
        /// </summary>
        /// <value>The host port.</value>
        property int Port;

        /// <summary>
        /// Gets or sets the network streaming capabilities that the member shall expose to its clients (via data interfaces).
        /// </summary>
        /// <value>The network streaming capabilities.</value>
        property Member::RtspCapability RtspCapabilities;
    };
}
#endif // NewMember_h__
