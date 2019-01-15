// Declares the resource ref class.
#ifndef ResourceRef_h__
#define ResourceRef_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The ResourceRef class represents a reference to a resource on the VideoXpert system (i.e. a device, datasource, tag, etc.).
    /// </summary>
    public ref class ResourceRef {
    public:

        /// <summary>
        /// Values that represent a type of resource.
        /// </summary>
        enum class ResourceType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>A data source resource.</summary>
            DataSource,
            /// <summary>A device resource.</summary>
            Device,
            /// <summary>A user resource.</summary>
            User,
            /// <summary>A drawing resource.</summary>
            Drawing,
            /// <summary>A data storage resource.</summary>
            DataStorage,
            /// <summary>A tag resource.</summary>
            Tag
        };

    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        ResourceRef() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxResourceRef">The resource ref.</param>
        ResourceRef(VxSdk::VxResourceRef* vxResourceRef) {
            Id = gcnew System::String(vxResourceRef->id);
            Type = ResourceType(vxResourceRef->type);
        }

        /// <summary>
        /// Gets or sets the unique resource identifier. This must match exactly with the unique identifier of
        /// the resource being referenced.
        /// </summary>
        /// <value>The unique resource identifier.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets the type of resource being referenced.
        /// </summary>
        /// <value>The resource type.</value>
        property ResourceType Type;
    };
}
#endif // ResourceRef_h__