// Declares the monitor position class.
#ifndef MonitorPosition_h__
#define MonitorPosition_h__

#include "VxSdk.h"
#include "Utils.h"
#include "Rect.h"

namespace VxSdkNet {

    /// <summary>
    /// The MonitorPosition class represents a monitor position that describes where a monitor resides in a
    /// coordinate plane (specifically the IV quadrant of a Cartesian plane where 0,0 is the top left point).
    /// </summary>
    public ref class MonitorPosition {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        MonitorPosition() {
            Position = gcnew Rect();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxMonitorPosition">The vx monitor position.</param>
        MonitorPosition(VxSdk::VxMonitorPosition* vxMonitorPosition){
            MonitorId = gcnew System::String(vxMonitorPosition->monitorId);
            Position = gcnew Rect(&vxMonitorPosition->position);
        }

        /// <summary>
        /// Gets or sets the unique identifier of the monitor that this position represents.
        /// </summary>
        /// <value>The unique identifier of the monitor.</value>
        property System::String^ MonitorId;

        /// <summary>
        /// Gets or sets the position of the monitor.
        /// </summary>
        /// <value>The position of the monitor.</value>
        property Rect^ Position;
    };
}
#endif // MonitorPosition_h__
