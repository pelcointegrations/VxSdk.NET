// Declares the linked ptz info class.
#ifndef LinkedPtzInfo_h__
#define LinkedPtzInfo_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The LinkedPtzInfo class represents linked PTZ information.
    /// </summary>
    public ref class LinkedPtzInfo {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        LinkedPtzInfo() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxLinkedPtzInfo">The vx linked ptz info.</param>
        LinkedPtzInfo(VxSdk::VxLinkedPtzInfo vxLinkedPtzInfo){
            Ip = Utils::ConvertCppString(vxLinkedPtzInfo.ip);
            Name = Utils::ConvertCppString(vxLinkedPtzInfo.name);
        }

        /// <summary>
        /// Gets or sets the IP of the tracking data source.
        /// </summary>
        /// <value>The IP.</value>
        property System::String^ Ip;

        /// <summary>
        /// Gets or sets the name of the tracking data source.
        /// </summary>
        /// <value>The name.</value>
        property System::String^ Name;
    };
}
#endif // LinkedPtzInfo_h__
