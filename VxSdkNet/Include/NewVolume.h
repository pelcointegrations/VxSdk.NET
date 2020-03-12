// Declares the new volume class.
#ifndef NewVolume_h__
#define NewVolume_h__

#include "Volume.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewVolume class represents a new volume to be created.
    /// </summary>
    public ref class NewVolume {
    public:

        /// <summary>
        /// Gets or sets the percentage of the volume to keep free.
        /// </summary>
        /// <value>The buffer percentage (0 - 1).</value>
        property float Buffer;

        /// <summary>
        /// Gets or sets the domain for the volume network path. Note: Ignored if the <see cref="Path"/> is not a UNC path.
        /// </summary>
        /// <value>The domain name.</value>
        property System::String^ Domain;

        /// <summary>
        /// Gets or sets whether or not this is a NAS volume that shares bandwidth with data streams (bandwidth will be
        /// reserved for NAS operations).
        /// </summary>
        /// <value><c>true</c> to share bandwidth with data streams, otherwise <c>false</c>.</value>
        property bool IsBandwidthReserved;

        /// <summary>
        /// Gets or sets the password for access to the network path. Note: Ignored if the <see cref="Path"/> is not a UNC path.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ Password;

        /// <summary>
        /// Gets or sets the fully qualified Windows directory path.
        /// </summary>
        /// <value>The directory path.</value>
        property System::String^ Path;

        /// <summary>
        /// Gets or sets the username for access to the network path. Note: Ignored if the <see cref="Path"/> is not a UNC path.
        /// </summary>
        /// <value>The username.</value>
        property System::String^ Username;
    };
}
#endif // NewVolume_h__
