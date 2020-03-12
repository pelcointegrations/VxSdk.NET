// Declares the new device assignment class.
#ifndef NewDeviceAssignment_h__
#define NewDeviceAssignment_h__

#include "Utils.h"
#include "VxNewDeviceAssignment.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewDeviceAssignment class represents a new device assignment.
    /// </summary>
    public ref class NewDeviceAssignment {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewDeviceAssignment() {
            DataSourceIds = gcnew System::Collections::Generic::List<System::String^>();
        }

        /// <summary>
        /// Gets the data sources that will be included in this device assignment.
        /// </summary>
        /// <value>A <c>List</c> of data sources.</value>
        property System::Collections::Generic::List<System::String^>^ DataSourceIds;

        /// <summary>
        /// Gets or sets the unique ID of the device to assign.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ DeviceId;

        /// <summary>
        /// Gets or sets the unique ID of the volume group to use for this device. If not provided, a volume
        /// group will be selected automatically.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ VolumeGroupId;
    };
}
#endif // NewDeviceAssignment_h__
