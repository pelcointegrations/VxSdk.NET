// Declares the new volume group class.
#ifndef NewVolumeGroup_h__
#define NewVolumeGroup_h__

#include "VolumeGroup.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewVolumeGroup class represents a new volume group to be created.
    /// </summary>
    public ref class NewVolumeGroup {
    public:

        /// <summary>
        /// Gets or sets whether or not this volume group is an "archive volume group", which will act as storage for the
        /// oldest available data.
        /// </summary>
        /// <value><c>true</c> to set this volume group an "archive volume group", otherwise <c>false</c>.</value>
        property bool IsArchiveGroup;

        /// <summary>
        /// Gets or sets the friendly name of the volume group.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;
    };
}
#endif // NewVolumeGroup_h__
