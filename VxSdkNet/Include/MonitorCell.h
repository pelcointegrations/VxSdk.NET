// Declares the MonitorCell class.
#ifndef MonitorCell_h__
#define MonitorCell_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ResourceLimits.h"

namespace VxSdkNet {

    /// <summary>
    /// The MonitorCell class represents a single viewport, hosted on a monitor, that can play media from a data source.
    /// </summary>
    public ref class MonitorCell {
    public:

        /// <summary>
        /// Values that represent rotation types (in 90 degree increments).
        /// </summary>
        enum class RotationType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>0 degrees.</summary>
            Rotate0,
            /// <summary>90 degrees.</summary>
            Rotate90,
            /// <summary>180 degrees.</summary>
            Rotate180,
            /// <summary>270 degrees.</summary>
            Rotate270
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxMonitorCell">The monitor cell.</param>
        MonitorCell(VxSdk::IVxMonitorCell* vxMonitorCell);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~MonitorCell() {
            this->!MonitorCell();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !MonitorCell();

        /// <summary>
        /// Removes the active data source from this cell.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the active data source.</returns>
        Results::Value Disconnect();

        /// <summary>
        /// Sets the position of the display data to live.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of going to live.</returns>
        Results::Value GoToLive();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Sets the height and width of the crop bounds applied to the video.
        /// </summary>
        /// <param name="height">The height as a percentage (0-1).</param>
        /// <param name="width">The width as a percentage (0-1).</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the crop bounds.</returns>
        Results::Value SetCropBounds(float height, float width);

        /// <summary>
        /// Sets the X, Y and Z locations of the crop bounds or immersive position.
        /// </summary>
        /// <param name="x">The x location.</param>
        /// <param name="y">The y location.</param>
        /// <param name="z">The z location.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the location.</returns>
        Results::Value SetLocation(int x, int y, int z);

        /// <summary>
        /// Gets or sets the height of the crop bounds expressed as a percentage (0-1).
        /// </summary>
        /// <value>The height as a percentage (e.g. 0.5 for 50% of the video frame height).</value>
        property float CropHeight {
        public:
            float get() { return _monitorCell->cropHeight; }
            void set(float value) { _monitorCell->SetCropHeight(value); }
        }

        /// <summary>
        /// Gets or sets the width of the crop bounds expressed as a percentage (0-1).
        /// </summary>
        /// <value>The width as a percentage (e.g. 0.5 for 50% of the video frame width).</value>
        property float CropWidth {
        public:
            float get() { return _monitorCell->cropWidth; }
            void set(float value) { _monitorCell->SetCropWidth(value); }
        }

        /// <summary>
        /// Gets or sets the unique identifier of the data source that this cell shall display.
        /// </summary>
        /// <value>The unique identifier of the data source.</value>
        property System::String^ DataSourceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_monitorCell->dataSourceId); }
            void set(System::String^ value) {
                char id[64];
                VxSdk::Utilities::StrCopySafe(id, Utils::ConvertCSharpString(value).c_str());
                _monitorCell->SetDataSource(id);
            }
        }

        /// <summary>
        /// Gets the unique index of this cell based on its position within the current layout.
        /// </summary>
        /// <value>The index.</value>
        property int Index {
        public:
            int get() { return _monitorCell->index; }
        }

        /// <summary>
        /// Gets or sets whether or not the analytics overlay is enabled.
        /// </summary>
        /// <value><c>true</c> to enable the analytics overlay, otherwise <c>false</c>.</value>
        property bool IsAnalyticsOverlayEnabled {
        public:
            bool get() { return _monitorCell->isAnalyticsOverlayEnabled; }
            void set(bool value) { value ? _monitorCell->EnableAnalyticsOverlay() : _monitorCell->DisableAnalyticsOverlay(); }
        }

        /// <summary>
        /// Gets or sets whether or not the cell is part of the monitor's sync group.
        /// </summary>
        /// <value><c>true</c> to join the sync group, <c>false</c> to leave.</value>
        property bool IsInSync {
        public:
            bool get() { return _monitorCell->isInSync; }
            void set(bool value) { value ? _monitorCell->JoinSyncGroup() : _monitorCell->LeaveSyncGroup(); }
        }

        /// <summary>
        /// Gets or sets whether or not the statistics overlay is enabled.
        /// </summary>
        /// <value><c>true</c> to enable the statistics overlay, otherwise <c>false</c>.</value>
        property bool IsStatisticsOverlayEnabled {
        public:
            bool get() { return _monitorCell->isStatisticsOverlayEnabled; }
            void set(bool value) { value ? _monitorCell->EnableStatisticsOverlay() : _monitorCell->DisableStatisticsOverlay(); }
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
        /// Gets or sets the X location of the crop bounds or immersive position.
        /// </summary>
        /// <value>The X location.</value>
        property int LocationX {
        public:
            int get() { return _monitorCell->x; }
            void set(int value) { _monitorCell->SetLocationX(value); }
        }

        /// <summary>
        /// Gets or sets the Y location of the crop bounds or immersive position.
        /// </summary>
        /// <value>The Y location.</value>
        property int LocationY {
        public:
            int get() { return _monitorCell->y; }
            void set(int value) { _monitorCell->SetLocationY(value); }
        }

        /// <summary>
        /// Gets or sets the Z location of the immersive position.
        /// </summary>
        /// <value>The Z location.</value>
        property int LocationZ {
        public:
            int get() { return _monitorCell->z; }
            void set(int value) { _monitorCell->SetLocationZ(value); }
        }

        /// <summary>
        /// Gets or sets the rotation applied to the video.
        /// </summary>
        /// <value>The rotation.</value>
        property RotationType Rotation {
        public:
            RotationType get() { return (RotationType)_monitorCell->rotation; }
            void set(RotationType value) { _monitorCell->SetRotation((VxSdk::VxRotationType::Value)value); }
        }

        /// <summary>
        /// Gets or sets the play speed of the display data.
        /// </summary>
        /// <value>The speed.</value>
        property float Speed {
        public:
            float get() { return _monitorCell->speed; }
            void set(float value) { _monitorCell->SetSpeed(value); }
        }

        /// <summary>
        /// Gets or sets the time at which the data should seek to (does not track time as the data plays).
        /// </summary>
        /// <value>The seek time.</value>
        property System::DateTime Time {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_monitorCell->time); }
            void set(System::DateTime value) {
                char temp[64];
                VxSdk::Utilities::StrCopySafe(temp, Utils::ConvertCSharpDateTime(value).c_str());
                _monitorCell->SetTime(temp);
            }
        }

        /// <summary>
        /// Gets the wall clock time at which the data playback should begin.
        /// </summary>
        /// <value>The time.</value>
        property System::DateTime TimeAnchor {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_monitorCell->timeAnchor); }
        }

    internal:
        VxSdk::IVxMonitorCell* _monitorCell;
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // MonitorCell_h__
