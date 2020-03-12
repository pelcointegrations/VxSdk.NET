// Declares the monitor selection class.
#ifndef MonitorSelection_h__
#define MonitorSelection_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The MonitorSelection class represents information for a selected monitor/cell within a monitor wall.
    /// </summary>
    public ref class MonitorSelection {
    public:

        /// <summary>
        /// Values that represent the input mode for a monitor cell.
        /// </summary>
        enum class CellInputMode {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Digital PTZ mode.</summary>
            DigitalPtz,

            /// <summary>Navigation mode.</summary>
            Navigation,

            /// <summary>Playback mode.</summary>
            Playback,

            /// <summary>PTZ mode.</summary>
            Ptz
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxMonitorSelection">The vx monitor selection.</param>
        MonitorSelection(VxSdk::VxMonitorSelection* vxMonitorSelection){
            LastModified = Utils::ConvertCppString(vxMonitorSelection->lastModified);
            Owner = Utils::ConvertCppString(vxMonitorSelection->owner);
            Cell = vxMonitorSelection->cell;
            Monitor = vxMonitorSelection->monitor;
            InputMode = (CellInputMode)vxMonitorSelection->inputMode;
        }

        /// <summary>
        /// Gets or sets the index of the selected cell within the selected monitor.
        /// </summary>
        /// <value>The cell index.</value>
        property int Cell;
        /// <summary>
        /// Gets or sets the input mode of the selected cell.
        /// </summary>
        /// <value>The input mode.</value>
        property CellInputMode InputMode;
        /// <summary>
        /// Gets or sets the time of the last modification for this monitor selection.
        /// </summary>
        /// <value>The last modified time.</value>
        property System::String^ LastModified;
        /// <summary>
        /// Gets or sets the index of the selected monitor.
        /// </summary>
        /// <value>The monitor index.</value>
        property int Monitor;
        /// <summary>
        /// Gets or sets the name of the user that owns this monitor selection.
        /// </summary>
        /// <value>The owner name.</value>
        property System::String^ Owner;
    };
}
#endif // MonitorSelection_h__
