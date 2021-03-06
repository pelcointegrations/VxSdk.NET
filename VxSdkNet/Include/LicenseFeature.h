// Declares the license feature class.
#ifndef LicenseFeature_h__
#define LicenseFeature_h__

#include "Device.h"

namespace VxSdkNet {

    /// <summary>
    /// The LicenseFeature class represents device functionality that is enabled with a valid license.
    /// </summary>
    public ref class LicenseFeature {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxLicenseFeature">The vx license feature.</param>
        LicenseFeature(VxSdk::IVxLicenseFeature* vxLicenseFeature);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~LicenseFeature() {
            this->!LicenseFeature();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !LicenseFeature();

        /// <summary>
        /// Get the devices that have been commissioned for this feature using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of devices that have been commissioned for this feature.</returns>
        System::Collections::Generic::List<Device^>^ GetCommissionedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Applies this license feature to a device; doing so will consume an available count from the feature.
        /// </summary>
        /// <param name="device">The device to apply this license feature to.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of linking the device.</returns>
        Results::Value Link(Device^ device);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Removes this license feature from the given device, releasing it for reuse (decrements the used count).
        /// </summary>
        /// <param name="device">The device to remove this license feature from.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of unlinking the device.</returns>
        Results::Value UnLink(Device^ device);

        /// <summary>
        /// Gets the activation identifier.
        /// </summary>
        /// <value>The activation identifier.</value>
        property System::String^ ActivationId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_licenseFeature->activationId); }
        }

        /// <summary>
        /// Gets the URI to the download location of the capability request.
        /// </summary>
        /// <value>The capability request endpoint, if available.</value>
        property System::String^ CapabilityRequestEndpoint {
        public:
            System::String^ get() { return _GetCapabilityRequest(); }
        }

        /// <summary>
        /// Gets the devices that have been commissioned for this feature.
        /// </summary>
        /// <value>A <c>List</c> of devices that have been commissioned for this feature.</value>
        property System::Collections::Generic::List<Device^>^ CommissionedDevices {
        public:
            System::Collections::Generic::List<Device^>^ get() { return GetCommissionedDevices(nullptr); }
        }

        /// <summary>
        /// Gets the allowable commissions count.
        /// </summary>
        /// <value>The allowable commissions count.</value>
        property int Count {
        public:
            int get() { return _licenseFeature->count; }
        }

        /// <summary>
        /// Gets the date and time at which the feature will expire.
        /// </summary>
        /// <value>The date and time at which the feature will expire.</value>
        property System::DateTime Expiration {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_licenseFeature->expiration); }
        }

        /// <summary>
        /// Gets the unique identifier of the feature.
        /// </summary>
        /// <value>The unique identifier of the feature.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_licenseFeature->id); }
        }

        /// <summary>
        /// Gets the date and time at which the feature was installed on the host.
        /// </summary>
        /// <value>The date and time at which the feature was installed on the host.</value>
        property System::DateTime Installation {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_licenseFeature->installation); }
        }

        /// <summary>
        /// Gets a value indicating whether this is a "pending" feature, which does not enable any device
        /// functionality, or a normal feature that does.
        /// </summary>
        /// <value><c>true</c> if this is a "pending" feature, <c>false</c> if a normal feature.</value>
        property bool IsPending {
        public:
            bool get() { return _licenseFeature->isPending; }
        }

        /// <summary>
        /// Gets the supported device types that may be licensed for use with this feature.
        /// </summary>
        /// <value>A <c>List</c> of supported device types.</value>
        property System::Collections::Generic::List<Device::Types>^ LicensableDevices {
        public:
            System::Collections::Generic::List<Device::Types>^ get()
            {
                System::Collections::Generic::List<Device::Types>^ mlist = gcnew System::Collections::Generic::List<Device::Types>();
                for (int i = 0; i < _licenseFeature->licensableDevicesSize; i++)
                    mlist->Add((Device::Types)_licenseFeature->licensableDevices[i]);

                return mlist;
            }
        }

        /// <summary>
        /// Gets the name of the feature.
        /// </summary>
        /// <value>The name of the feature.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_licenseFeature->name); }
        }

        /// <summary>
        /// Gets the amount of the allowable count that is currently used by commissions.
        /// </summary>
        /// <value>The amount of the allowable count that is currently used by commissions.</value>
        property int Used {
        public:
            int get() { return _licenseFeature->used; }
        }

        /// <summary>
        /// Gets the feature version.
        /// </summary>
        /// <value>The feature version.</value>
        property System::String^ Version {
        public:
            System::String^ get() { return Utils::ConvertCppString(_licenseFeature->version); }
        }

    internal:
        VxSdk::IVxLicenseFeature* _licenseFeature;
        System::String^ _GetCapabilityRequest();
    };
}
#endif // LicenseFeature_h__
