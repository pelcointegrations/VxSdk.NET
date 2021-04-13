// Declares the new monitor class.
#ifndef NewMonitor_h__
#define NewMonitor_h__

#include "Utils.h"
#include "Monitor.h"
#include "VxNewMonitor.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewMonitor class represents a new monitor to be created on the system.
    /// </summary>
    public ref class NewMonitor {
    public:

        /// <summary>
        /// Gets or sets the unique identifier of the monitor host device.
        /// </summary>
        /// <value>The unique host identifier.</value>
        property System::String^ HostDeviceId;

        /// <summary>
        /// Gets or sets the cell grid layout of the monitor.
        /// </summary>
        /// <value>The cell grid layout.</value>
        property Monitor::Layouts Layout;

        /// <summary>
        /// Gets or sets the friendly name of the monitor.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the unique number of the monitor.
        /// </summary>
        /// <value>The monitor number.</value>
        property int Number;

        /// <summary>
        /// Gets or sets the horizontal resolution.
        /// </summary>
        /// <value>The horizontal resolution.</value>
        property int ResolutionX;

        /// <summary>
        /// Gets or sets the vertical resolution.
        /// </summary>
        /// <value>The vertical resolution.</value>
        property int ResolutionY;
    };
}
#endif // NewMonitor_h__
