// Declares the data storage class.
#ifndef DataStorage_h__
#define DataStorage_h__

#include "Configuration.h"
#include "Device.h"
#include "DeviceAssignment.h"
#include "NewClip.h"
#include "NewDeviceAssignment.h"
#include "Driver.h"
#include "Retention.h"

namespace VxSdkNet {

    /// <summary>
    /// The DataStorage class represents a data storage provider in the system (e.g. an NSM5200
    /// storage pool or a VxRecorder) hosted by a system device. The DataStorage can be directed
    /// to store media produced by a device by assigning the device to it.
    /// </summary>
    public ref class DataStorage {
    public:

        /// <summary>
        /// Values that represent data storage hardware types.
        /// </summary>
        enum class DataStorageTypes {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>A Digital Sentry device.</summary>
            DigitalSentry,

            /// <summary>An NSM network video recorder device.</summary>
            NSM,

            /// <summary>A VideoXpert storage device.</summary>
            VideoXpertStorage,

            /// <summary>An edge storage device.</summary>
            Edge
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDataStorage">The vx data storage.</param>
        DataStorage(VxSdk::IVxDataStorage* vxDataStorage);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~DataStorage() {
            this->!DataStorage();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !DataStorage();

        /// <summary>
        /// Saves the data specified in the new clip to this data storage. Once saved, the data will
        /// be represented as a new clip (not immediately available). Data that is already saved will
        /// not be retrieved again. If there is overlap with data that is already saved, only the new
        /// data will be saved.
        /// </summary>
        /// <param name="newClip">The new clip to add to the data storage.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value AddClip(NewClip^ newClip);

        /// <summary>
        /// Assign a device to this data storage to be managed and recorded based on its configuration.
        /// </summary>
        /// <param name="newDeviceAssignment">The new device assignment to be added to the data storage.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of assigning the device.</returns>
        Results::Value AssignDevice(NewDeviceAssignment^ newDeviceAssignment);

        /// <summary>
        /// Get the data sources assigned to this data storage using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, AllTags, Capturing, Commissioned, Enabled, Encoding, HasFolderTags, Id, Ip, ManualRecording, ModifiedSince, Name, Number, Recording, State, Type, Unassigned.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of data sources.</returns>
        System::Collections::Generic::List<VxSdkNet::DataSource^>^ GetDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the device assignments for this data storage using an optional collection filter.
        /// <para>Available filters: DataSourceId, DataStorageId, DeviceId, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of device assignments.</returns>
        System::Collections::Generic::List<VxSdkNet::DeviceAssignment^>^ GetDeviceAssignments(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the resource retention information for this data storage.
        /// <para>Available filters: Id, ResourceId.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of retentions.</returns>
        System::Collections::Generic::List<VxSdkNet::Retention^>^ GetRetentions(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Unassign a device from this data storage.
        /// </summary>
        /// <param name="device">The device to be unassigned from the data storage.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of unassigning the device.</returns>
        Results::Value UnassignDevice(Device^ device);

        /// <summary>
        /// Gets the device assignments for this data storage.
        /// </summary>
        /// <value>A <c>List</c> of device assignments.</value>
        property VxSdkNet::Configuration::Storage^ Configuration {
        public:
            VxSdkNet::Configuration::Storage^ get() { return _GetStorageConfig(); }
        }

        /// <summary>
        /// Gets the data sources assigned to this data storage.
        /// </summary>
        /// <value>A <c>List</c> of data sources.</value>
        property System::Collections::Generic::List<VxSdkNet::DataSource^>^ DataSources {
        public:
            System::Collections::Generic::List<VxSdkNet::DataSource^>^ get() { return GetDataSources(nullptr); }
        }

        /// <summary>
        /// Gets the device assignments for this data storage.
        /// </summary>
        /// <value>A <c>List</c> of device assignments.</value>
        property System::Collections::Generic::List<VxSdkNet::DeviceAssignment^>^ DeviceAssignments {
        public:
            System::Collections::Generic::List<VxSdkNet::DeviceAssignment^>^ get() { return GetDeviceAssignments(nullptr); }
        }

        /// <summary>
        /// Gets the device that hosts this data storage.
        /// </summary>
        /// <value>The host device.</value>
        property VxSdkNet::Device^ HostDevice {
        public:
            VxSdkNet::Device^ get() { return _GetHostDevice(); }
        }

        /// <summary>
        /// Gets the unique identifier of the data storage.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dataStorage->id); }
        }

        /// <summary>
        /// Gets a value indicating whether the data storage is configured as a failover unit.
        /// </summary>
        /// <value><c>true</c> if the data storage is a failover unit, <c>false</c> if not.</value>
        property bool IsFailover {
        public:
            bool get() { return _dataStorage->isFailover; }
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
        /// Gets or sets the friendly name of the data storage.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dataStorage->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _dataStorage->SetName(name);
            }
        }

        /// <summary>
        /// Gets the resource retention information for this data storage.
        /// </summary>
        /// <value>A <c>List</c> of retentions.</value>
        property System::Collections::Generic::List<VxSdkNet::Retention^>^ Retentions {
        public:
            System::Collections::Generic::List<VxSdkNet::Retention^>^ get() { return GetRetentions(nullptr); }
        }

        /// <summary>
        /// Gets the type of data storage.
        /// </summary>
        /// <value>The data storage <see cref="DataStorageTypes">type</see>.</value>
        property DataStorageTypes Type {
        public:
            DataStorageTypes get() { return DataStorageTypes(_dataStorage->type); }
        }

    internal:
        VxSdk::IVxDataStorage* _dataStorage;
        VxSdkNet::Device^ _GetHostDevice();
        VxSdkNet::ResourceLimits^ _GetLimits();
        VxSdkNet::Configuration::Storage^ _GetStorageConfig();
    };
}
#endif // DataStorage_h__
