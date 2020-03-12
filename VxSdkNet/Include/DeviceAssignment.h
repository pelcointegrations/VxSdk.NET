// Declares the device assignment class.
#ifndef DeviceAssignment_h__
#define DeviceAssignment_h__

#include "VxSdk.h"
#include "DataSource.h"

namespace VxSdkNet {
    ref class DataStorage;
    ref class Driver;

    /// <summary>
    /// The DeviceAssignment class represents a device assignment.
    /// </summary>
    public ref class DeviceAssignment {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDeviceAssignment">The vx device assignment.</param>
        DeviceAssignment(VxSdk::IVxDeviceAssignment* vxDeviceAssignment);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~DeviceAssignment() {
            this->!DeviceAssignment();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !DeviceAssignment();

        /// <summary>
        /// Get the data sources assigned by this device assignment using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, AllTags, Capturing, Commissioned, Enabled, Encoding, HasFolderTags, Id, Ip, ManualRecording, ModifiedSince, Name, Number, Recording, State, Type, Unassigned.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of data sources.</returns>
        System::Collections::Generic::List<DataSource^>^ GetDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the data sources assigned by this device assignment.
        /// </summary>
        /// <value>A <c>List</c> of data sources.</value>
        property System::Collections::Generic::List<VxSdkNet::DataSource^>^ DataSources {
        public:
            System::Collections::Generic::List<VxSdkNet::DataSource^>^ get() { return GetDataSources(nullptr); }
        }

        /// <summary>
        /// Gets the data storage that this device assignment is for.
        /// </summary>
        /// <value>The <see cref="DataStorage"/> for this assignment.</value>
        property VxSdkNet::DataStorage^ DataStorage {
        public:
            VxSdkNet::DataStorage^ get() { return _GetDataStorage(); }
        }

        /// <summary>
        /// Gets the assigned device.
        /// </summary>
        /// <value>The assigned <see cref="Device"/>.</value>
        property VxSdkNet::Device^ Device {
        public:
            VxSdkNet::Device^ get() { return _GetDevice(); }
        }

        /// <summary>
        /// Gets the unique identifier of the device assignment.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_deviceAssignment->id); }
        }

        /// <summary>
        /// Gets any limits related to this resource.
        /// </summary>
        /// <value>The limits related to this resource.</value>
        property ResourceLimits^ Limits {
        public:
            ResourceLimits^ get() { return _GetLimits(); }
        }

        /// <summary>
        /// Gets or sets the unique identifier of the volume group to use for this device. If not provided, a volume
        /// group will be selected automatically.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ VolumeGroupId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_deviceAssignment->volumeGroupId); }
            void set(System::String^ value) {
                char volumeGroupId[64];
                VxSdk::Utilities::StrCopySafe(volumeGroupId, Utils::ConvertCSharpString(value).c_str());
                _deviceAssignment->SetVolumeGroupId(volumeGroupId);
            }
        }

    internal:
        VxSdk::IVxDeviceAssignment* _deviceAssignment;
        VxSdkNet::DataStorage^ _GetDataStorage();
        VxSdkNet::Device^ _GetDevice();
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // DeviceAssignment_h__
