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
            System::String^ get() { return gcnew System::String(_deviceAssignment->id); }
        }

    internal:
        VxSdk::IVxDeviceAssignment* _deviceAssignment;
        VxSdkNet::DataStorage^ _GetDataStorage();
        VxSdkNet::Device^ _GetDevice();
    };
}
#endif // DeviceAssignment_h__
