// Declares the driver class.
#ifndef Driver_h__
#define Driver_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {
    ref class DataStorage;

    /// <summary>
    /// The Driver class represents a device communication driver.
    /// </summary>
    public ref class Driver {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDriver">The vx driver.</param>
        Driver(VxSdk::IVxDriver* vxDriver);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Driver() {
            this->!Driver();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Driver();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the friendly name of the driver.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_driver->name); }
        }

        /// <summary>
        /// Gets the driver type identifier.
        /// </summary>
        /// <value>The driver type identifier.</value>
        property System::String^ Type {
        public:
            System::String^ get() { return Utils::ConvertCppString(_driver->type); }
        }

        /// <summary>
        /// Gets the name of the vendor that manufactured the device that the driver is for.
        /// </summary>
        /// <value>The name of the vendor.</value>
        property System::String^ Vendor {
        public:
            System::String^ get() { return Utils::ConvertCppString(_driver->vendor); }
        }

        /// <summary>
        /// Gets the driver version number.
        /// </summary>
        /// <value>The version number.</value>
        property System::String^ Version {
        public:
            System::String^ get() { return Utils::ConvertCppString(_driver->version); }
        }

    internal:
        VxSdk::IVxDriver* _driver;
    };
}
#endif // Driver_h__
