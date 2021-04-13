// Declares the network storage info class.
#ifndef NetworkStorageInfo_h__
#define NetworkStorageInfo_h__

namespace VxSdkNet {

    /// <summary>
    /// The NetworkStorageInfo class represents information about a network storage resource.
    /// </summary>
    public ref class NetworkStorageInfo {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NetworkStorageInfo() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxNetworkStorageInfo">The vx network storage info.</param>
        NetworkStorageInfo(VxSdk::VxNetworkStorageInfo vxNetworkStorageInfo) {
            Password = Utils::ConvertCppString(vxNetworkStorageInfo.password);
            Path = Utils::ConvertCppString(vxNetworkStorageInfo.path);
            Username = Utils::ConvertCppString(vxNetworkStorageInfo.username);
        }

        /// <summary>
        /// Gets or sets the password for access to the resource.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ Password;

        /// <summary>
        /// Gets or sets the UNC network path of the resource.
        /// </summary>
        /// <value>The UNC network path.</value>
        property System::String^ Path;

        /// <summary>
        /// Gets or sets the username for access to the resource.
        /// </summary>
        /// <value>The username.</value>
        property System::String^ Username;
    };
}
#endif // NetworkStorageInfo_h__
