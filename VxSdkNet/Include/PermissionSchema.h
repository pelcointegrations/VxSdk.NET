// Declares the permission schema class.
#ifndef PermissionSchema_h__
#define PermissionSchema_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The PermissionSchema class represents static system permission information in a machine-readable manner. This
    /// indicates permission groups, hierarchy, and resource restriction information.
    /// </summary>
    public ref class PermissionSchema {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        PermissionSchema()
        {
            Restrictions = gcnew System::Collections::Generic::List<Privilege::ResourceTypes>();
            Permissions = gcnew System::Collections::Generic::List<PermissionSchema^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxPermissionSchema">The vx permission schema.</param>
        PermissionSchema(VxSdk::VxPermissionSchema* vxPermissionSchema){
            IsGroup = vxPermissionSchema->isGroup;
            PermissionId = (Privilege::PermissionIds)vxPermissionSchema->permissionId;
            Restrictions = gcnew System::Collections::Generic::List<Privilege::ResourceTypes>();
            for (int i = 0; i < vxPermissionSchema->restrictionsSize; i++) {
                Restrictions->Add((Privilege::ResourceTypes)vxPermissionSchema->restrictions[i]);
            }

            Permissions = gcnew System::Collections::Generic::List<PermissionSchema^>();
            for (int i = 0; i < vxPermissionSchema->permissionsSize; i++) {
                Permissions->Add(gcnew PermissionSchema(vxPermissionSchema->permissions[i]));
            }
        }

        /// <summary>
        /// Gets or sets whether or not this represents a permission group.
        /// </summary>
        /// <value><c>true</c> if this represents a permission group; <c>false</c> if a permission.</value>
        property bool IsGroup;

        /// <summary>
        /// Gets or sets the permission being granted by this field or field group.
        /// </summary>
        /// <value>The permission ID.</value>
        property Privilege::PermissionIds PermissionId;

        /// <summary>
        /// Gets or sets the list the resource types that may be restricted by this permission, if any.
        /// </summary>
        /// <value>The list of resource types, if any.</value>
        property System::Collections::Generic::List<PermissionSchema^>^ Permissions;;

        /// <summary>
        /// Gets or sets the recursive list of permission schema. Indicates permission hierarchy; nested items are
        /// children while containing items are parents.
        /// </summary>
        /// <value>The recursive list of permission schema.</value>
        property System::Collections::Generic::List<Privilege::ResourceTypes>^ Restrictions;
    };
}
#endif // PermissionSchema_h__
