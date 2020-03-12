// Declares the new device class.
#ifndef NewDevice_h__
#define NewDevice_h__

#include "Device.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewDevice class represents a new device.
    /// </summary>
    public ref class NewDevice {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewDevice() {
            Endpoints = gcnew System::Collections::Generic::List<System::String^>();
        }

        /// <summary>
        /// Gets or sets the associated driver type identifier.
        /// </summary>
        /// <value>The associated driver type identifier.</value>
        property System::String^ DriverType;

        /// <summary>
        /// Gets or sets the list of source URIs that the device will support. If the device type is <c>Generic</c>
        /// then at least 1 URI must be provided. The URI must be unique, otherwise <c>Conflict</c> will  be returned.
        /// </summary>
        /// <value>A <c>List</c> of source URIs.</value>
        property System::Collections::Generic::List<System::String^>^ Endpoints;

        /// <summary>
        /// Gets or sets the host address of the device. If set, takes precedence over the ip. The combination
        /// of <c>Host</c>, <c>Ip</c>, <c>Port</c> and <c>Type</c> must be unique.
        /// <para> NOTE: One of either <c>Host</c> or <c>Ip</c> must be provided. </para>
        /// </summary>
        property System::String^ Host;

        /// <summary>
        /// Gets or sets the ID of the device.
        /// </summary>
        /// <value>The ID.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets the IP of the device.
        /// </summary>
        /// <remarks>
        /// DEPRECATED: Use <see cref="Host"/> instead.
        /// </remarks>
        /// <value>The IP.</value>
        property System::String^ Ip;

        /// <summary>
        /// Gets or sets the model name of the device, if any.
        /// </summary>
        /// <value>The model name.</value>
        property System::String^ Model;

        /// <summary>
        /// Gets or sets the friendly name of the device.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the account password used to communicate with the device, if any.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ Password;

        /// <summary>
        /// Gets or sets the port associated with the device, if any.
        /// </summary>
        /// <value>The port.</value>
        property int Port;

        /// <summary>
        /// Gets or sets the serial number of the device, if any.
        /// </summary>
        /// <value>The serial number.</value>
        property System::String^ Serial;

        /// <summary>
        /// Gets or sets whether to have this device automatically commissioned when created.
        /// </summary>
        /// <value><c>true</c> to automatically commissioned the device, otherwise <c>false</c>.</value>
        property bool ShouldAutoCommission;

        /// <summary>
        /// Gets or sets the type of device.
        /// </summary>
        /// <value>The device <see cref="Device::Types">Type</see>.</value>
        property Device::Types Type;

        /// <summary>
        /// Gets or sets the account username used to communicate with the device, if any.
        /// </summary>
        /// <value>The username.</value>
        property System::String^ Username;

        /// <summary>
        /// Gets or sets the device vendor, if any.
        /// </summary>
        /// <value>The device vendor.</value>
        property System::String^ Vendor;

        /// <summary>
        /// Gets or sets the current version of software running on the device, if any.
        /// </summary>
        /// <value>The software version.</value>
        property System::String^ Version;
    };
}
#endif // NewDevice_h__
