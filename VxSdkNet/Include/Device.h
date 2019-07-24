// Declares the device class.
#ifndef Device_h__
#define Device_h__

#include "AlarmInput.h"
#include "DataSource.h"
#include "DeviceAssignment.h"
#include "DataStorage.h"
#include "Log.h"
#include "RelayOutput.h"

namespace VxSdkNet {
    ref class Monitor;

    /// <summary>
    /// The Device class represents a particular physical device in the system.
    /// </summary>
    public ref class Device {
    public:

        /// <summary>
        /// Values that represent the operational state of a device.
        /// </summary>
        enum class DeviceStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Being prepared for use.</summary>
            Initializing,

            /// <summary>Invalid/missing credentials.</summary>
            Unauthenticated,

            /// <summary>Device identity mismatch.</summary>
            IdInconsistent,

            /// <summary>NSM5200 manager.</summary>
            NsmManager,

            /// <summary>NSM5200 member.</summary>
            NsmMember
        };

        /// <summary>
        /// Values that represent device types.
        /// </summary>
        enum class Types {
            /// <summary>A VideoXpert Accessory Server.</summary>
            Acc,

            /// <summary>An AccessController device.</summary>
            AccessController,

            /// <summary>An All in One VideoXpert server (VxPro).</summary>
            AllInOne,

            /// <summary>A camera device.</summary>
            Camera,

            /// <summary>A VideoXpert Core device.</summary>
            Core,

            /// <summary>A decoder device.</summary>
            Decoder,

            /// <summary>An encoder device.</summary>
            Encoder,

            /// <summary>An external device.</summary>
            External,

            /// <summary>A generic device.</summary>
            Generic,

            /// <summary>A VideoXpert MediaGateway device.</summary>
            Mg,

            /// <summary>A monitor device.</summary>
            Monitor,

            /// <summary>A network storage device.</summary>
            Recorder,

            /// <summary>A UI device.</summary>
            Ui,

            /// <summary>An error or unknown value was returned.</summary>
            Unknown
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDevice">The vx device.</param>
        Device(VxSdk::IVxDevice* vxDevice);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Device() {
            this->!Device();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Device();

        /// <summary>
        /// Creates a new log for this device, the contents of which shall be determined by the server by default.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of creating the log.</returns>
        Results::Value CreateLog();

        /// <summary>
        /// Delete a log from this device.
        /// </summary>
        /// <param name="logItem">The log to be deleted from this device.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the log.</returns>
        Results::Value DeleteLog(Log^ logItem);

        /// <summary>
        /// Get the alarm inputs hosted by this device using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name, State.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of alarm inputs.</returns>
        System::Collections::Generic::List<AlarmInput^>^ GetAlarmInputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the data sources hosted by this device using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, AllTags, Capturing, Commissioned, Enabled, Encoding, HasFolderTags, Id, Ip, ManualRecording, ModifiedSince, Name, Number, Recording, State, Type, Unassigned.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of data sources.</returns>
        System::Collections::Generic::List<DataSource^>^ GetDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the assignments to a data storage for this device using an optional collection filter.
        /// <para>Available filters: DataSourceId, DataStorageId, DeviceId, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of device assignments.</returns>
        System::Collections::Generic::List<DeviceAssignment^>^ GetDeviceAssignments(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the logs for this device using an optional collection filter.
        /// <para>Available filters: Initiated, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of logs.</returns>
        System::Collections::Generic::List<Log^>^ GetLogs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the monitors residing on the device, if any, using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name, Number.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of monitors.</returns>
        System::Collections::Generic::List<Monitor^>^ GetMonitors(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the relay outputs hosted by this device using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Enabled, Id, ModifiedSince, Name, State.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of relay outputs.</returns>
        System::Collections::Generic::List<RelayOutput^>^ GetRelayOutputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Silences all audible alarms on the device.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value Silence();

        /// <summary>
        /// Gets the alarm inputs hosted by this device.
        /// </summary>
        /// <value>A <c>List</c> of alarm inputs.</value>
        property System::Collections::Generic::List<AlarmInput^>^ AlarmInputs {
        public:
            System::Collections::Generic::List<AlarmInput^>^ get() { return GetAlarmInputs(nullptr); }
        }

        /// <summary>
        /// Gets a value indicating whether this device is capable of generating logs.
        /// </summary>
        /// <value><c>true</c> if this device is capable of generating logs, <c>false</c> if not.</value>
        property bool CanCreateLogs {
        public:
            bool get() { return _CanCreateLogs(); }
        }

        /// <summary>
        /// Gets the data sources hosted by this device.
        /// </summary>
        /// <value>A <c>List</c> of data sources.</value>
        property System::Collections::Generic::List<DataSource^>^ DataSources {
        public:
            System::Collections::Generic::List<DataSource^>^ get() { return GetDataSources(nullptr); }
        }

        /// <summary>
        /// Gets the data storage hosted by this device, if any.
        /// </summary>
        /// <value>The data storage hosted by this device if available, otherwise <c>nullptr</c>.</value>
        property VxSdkNet::DataStorage^ DataStorage {
        public:
            VxSdkNet::DataStorage^ get() { return _GetDataStorage(); }
        }

        /// <summary>
        /// Gets the assignments to a data storage for this device.
        /// </summary>
        /// <value>A <c>List</c> of device assignments.</value>
        property System::Collections::Generic::List<DeviceAssignment^>^ DeviceAssignments {
        public:
            System::Collections::Generic::List<DeviceAssignment^>^ get() { return GetDeviceAssignments(nullptr); }
        }

        /// <summary>
        /// Gets the driver device identifier.
        /// </summary>
        /// <value>The driver device identifier.</value>
        property System::String^ DriverDeviceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->driverDeviceId); }
        }

        /// <summary>
        /// Gets the driver type identifier.
        /// </summary>
        /// <value>The driver type identifier.</value>
        property System::String^ DriverTypeId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->driverTypeId); }
            void set(System::String^ value) {
                char driverTypeId[64];
                VxSdk::Utilities::StrCopySafe(driverTypeId, Utils::ConvertCSharpString(value).c_str());
                _device->SetDriverTypeId(driverTypeId);
            }
        }

        /// <summary>
        /// Gets the unique identifier of the device.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->id); }
        }

        /// <summary>
        /// Gets or sets the IP of the device.
        /// </summary>
        /// <value>The IP.</value>
        property System::String^ Ip {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->ip); }
            void set(System::String^ value) {
                char ip[64];
                VxSdk::Utilities::StrCopySafe(ip, Utils::ConvertCSharpString(value).c_str());
                _device->SetIp(ip);
            }
        }

        /// <summary>
        /// Gets a value indicating whether the device is commissioned.
        /// </summary>
        /// <value><c>true</c> if commissioned, <c>false</c> if not.</value>
        property bool IsCommissioned {
        public:
            bool get() { return _device->isCommissioned; }
        }

        /// <summary>
        /// Gets a value indicating whether a license is required for commissioning the device.
        /// </summary>
        /// <value><c>true</c> if license required, <c>false</c> if not.</value>
        property bool IsLicenseRequired {
        public:
            bool get() { return _device->isLicenseRequired; }
        }

        /// <summary>
        /// Gets the logs for this device.
        /// </summary>
        /// <value>A <c>List</c> of logs.</value>
        property System::Collections::Generic::List<Log^>^ Logs {
        public:
            System::Collections::Generic::List<Log^>^ get() { return GetLogs(nullptr); }
        }

        /// <summary>
        /// Gets the device model.
        /// </summary>
        /// <value>The model name.</value>
        property System::String^ Model {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->model); }
        }

        /// <summary>
        /// Gets the monitors residing on the device, if any.
        /// </summary>
        /// <value>A <c>List</c> of monitors.</value>
        property System::Collections::Generic::List<Monitor^>^ Monitors {
        public:
            System::Collections::Generic::List<Monitor^>^ get() { return GetMonitors(nullptr); }
        }

        /// <summary>
        /// Gets or sets the friendly name of the device.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _device->SetName(name);
            }
        }

        /// <summary>
        /// Sets the account password used to communicate with the device, if any.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ Password {
        public:
            void set(System::String^ value) {
                char password[64];
                VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(value).c_str());
                _device->SetPassword(password);
            }
        }

        /// <summary>
        /// Gets the Port of the device.
        /// </summary>
        /// <value>The Port.</value>
        property int Port {
        public:
            int get() { return _device->port; }
            void set(int value) { _device->SetDevicePort(value); }
        }

        /// <summary>
        /// Gets the relay outputs hosted by this device.
        /// </summary>
        /// <value>A <c>List</c> of relay outputs.</value>
        property System::Collections::Generic::List<RelayOutput^>^ RelayOutputs {
        public:
            System::Collections::Generic::List<RelayOutput^>^ get() { return GetRelayOutputs(nullptr); }
        }

        /// <summary>
        /// Gets the serial number.
        /// </summary>
        /// <value>The serial number.</value>
        property System::String^ Serial {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->serial); }
        }

        /// <summary>
        /// Gets the current operational state of the device.
        /// </summary>
        /// <value>The current state of the device.</value>
        property DataSource::States State {
        public:
            DataSource::States get() { return DataSource::States(_device->state); }
        }

        /// <summary>
        /// Gets the current device status.
        /// </summary>
        /// <value>A device status <c>List</c>.</value>
        property System::Collections::Generic::List<DeviceStatus>^ Status {
        public:
            System::Collections::Generic::List<DeviceStatus>^ get() {
                System::Collections::Generic::List<DeviceStatus>^ mlist = gcnew System::Collections::Generic::List<DeviceStatus>();
                for (int i = 0; i < _device->statusSize; i++)
                    mlist->Add((DeviceStatus)_device->status[i]);

                return mlist;
            }
        }

        /// <summary>
        /// Gets the type of device.
        /// </summary>
        /// <value>The device <see cref="Types">Type</see>.</value>
        property Types Type {
        public:
            Types get() { return Types(_device->type); }
        }

        /// <summary>
        /// Gets or sets the account username used to communicate with the device, if any.
        /// </summary>
        /// <value>The username.</value>
        property System::String^ Username {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->username); }
            void set(System::String^ value) {
                char username[64];
                VxSdk::Utilities::StrCopySafe(username, Utils::ConvertCSharpString(value).c_str());
                _device->SetUsername(username);
            }
        }

        /// <summary>
        /// Gets the device vendor, if any.
        /// </summary>
        /// <value>The name of the devices vendor.</value>
        property System::String^ Vendor {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->vendor); }
        }

        /// <summary>
        /// Gets or sets the current version of software running on the device.
        /// </summary>
        /// <value>The software version.</value>
        property System::String^ Version {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->version); }
            void set(System::String^ value) {
                char version[64];
                VxSdk::Utilities::StrCopySafe(version, Utils::ConvertCSharpString(value).c_str());
                _device->SetVersion(version);
            }
        }

        /// <summary>
        /// Gets the virtual IP of the device, if any.
        /// </summary>
        /// <value>The virtual IP.</value>
        property System::String^ VirtualIp {
        public:
            System::String^ get() { return Utils::ConvertCppString(_device->virtualIp); }
        }

    internal:
        VxSdk::IVxDevice* _device;
        bool _CanCreateLogs();
        VxSdkNet::DataStorage^ _GetDataStorage();
    };
}
#endif // Device_h__
