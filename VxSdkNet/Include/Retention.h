// Declares the retention class.
#ifndef Retention_h__
#define Retention_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ResourceRef.h"

namespace VxSdkNet {

    /// <summary>
    /// The Retention class represents retention information for a referenced resource.
    /// </summary>
    public ref class Retention {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        Retention() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxRetention">The vx retention.</param>
        Retention(VxSdk::VxRetention* vxRetention){
            OldestRecording = Utils::ConvertCppDateTime(vxRetention->oldestRecording);
            Resource = gcnew ResourceRef(&vxRetention->resourceRef);
        }

        /// <summary>
        /// Gets or sets the time of the oldest recording for the resource.
        /// </summary>
        /// <value>The oldest recording time.</value>
        property System::DateTime OldestRecording;

        /// <summary>
        /// Gets or sets the reference to the resource.
        /// </summary>
        /// <value>The resource reference.</value>
        property ResourceRef^ Resource;
    };
}
#endif // Retention_h__
