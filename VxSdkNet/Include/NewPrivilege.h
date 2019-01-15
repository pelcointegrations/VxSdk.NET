// Declares the new privilege class.
#ifndef NewPrivilege_h__
#define NewPrivilege_h__

#include "Privilege.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewTag class represents a new privilege.
    /// </summary>
    public ref class NewPrivilege {
    public:

        /// <summary>
        /// Gets or sets the identifier of the permission being granted by this privilege.
        /// </summary>
        /// <value>The permission identifier.</value>
        property Privilege::PermissionIds PermissionId;

        /// <summary>
        /// Gets or sets the relative priority for the privilege, from 1 to 250. Smaller numbers have higher
        /// priority than larger numbers (e.g. 1 is the highest priority).
        /// </summary>
        /// <value>The priority.</value>
        property int Priority;
    };
}
#endif // NewPrivilege_h__
