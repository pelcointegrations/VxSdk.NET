// Declares the device search class.
#ifndef DeviceSearch_h__
#define DeviceSearch_h__

namespace VxSdkNet {

    /// <summary>
    /// The DeviceSearch class represents device search helpers used for discovery.
    /// </summary>
    public ref class DeviceSearch {
    public:

        /// <summary>
        /// Gets or sets the type identifier of the driver to use for device communication.
        /// </summary>
        /// <value>The driver type identifier.</value>
        property System::String^ DriverType;

        /// <summary>
        /// Gets or sets the host address of the device. Ignored if <c>IpStartAddress</c> and <c>IpEndAddress</c> are present.
        /// </summary>
        /// <value>The host address of the device.</value>
        property System::String^ Host;

        /// <summary>
        /// Gets or sets the IP ending address (inclusive). If present, this must be the same format as <c>IpStartAddress</c>
        /// and must be present if <c>IpStartAddress</c> is present. Address range from <c>IpStartAddress</c> must not
        /// exceed 1024 addresses.
        /// </summary>
        /// <value>The IP ending address (inclusive).</value>
        property System::String^ IpEndAddress;

        /// <summary>
        /// Gets or sets the IP starting address (inclusive). If present, this must be the same format as <c>IpEndAddress</c>
        /// and must be present if <c>IpEndAddress</c> is present.
        /// </summary>
        /// <value>The IP starting address (inclusive).</value>
        property System::String^ IpStartAddress;

        /// <summary>
        /// Gets or sets the account password to communicate with the device(s), if any.
        /// </summary>
        /// <value>The account password.</value>
        property System::String^ Password;

        /// <summary>
        /// Gets or sets the device(s) port.
        /// </summary>
        /// <value>The device(s) port.</value>
        property int Port;

        /// <summary>
        /// Gets or sets the account username to communicate with the device(s), if any.
        /// </summary>
        /// <value>The account username.</value>
        property System::String^ Username;
    };
}
#endif // DeviceSearch_h__
