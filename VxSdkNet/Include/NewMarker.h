// Declares the new Marker class.
#ifndef NewMarker_h__
#define NewMarker_h__

#include "Marker.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewMarker class represents a new Marker.
    /// </summary>
    public ref class NewMarker {
    public:

        /// <summary>
        /// Gets or sets the data source id to associate with the marker.
        /// </summary>
        /// <value>The data source id.</value>
        property System::String^ AssociatedDataSourceId;

        /// <summary>
        /// Gets or sets the angular coordinate indicating the direction, if any, that the marker is
        /// facing on a polar grid(e.g.: 0 (right), 90 (up), 180 (left), 270 (down)).
        /// </summary>
        /// <value>The angular direction.</value>
        property float Direction;

        /// <summary>
        /// Gets or sets the layer name of the marker, if any.
        /// </summary>
        /// <value>The friendly name of the marker.</value>
        property System::String^ LayerName;

        /// <summary>
        /// Gets or sets the friendly name of the marker.
        /// </summary>
        /// <value>The friendly name of the marker.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the X coordinate.
        /// </summary>
        /// <value>The X coordinate.</value>
        property float X;

        /// <summary>
        /// Gets or sets the Y coordinate.
        /// </summary>
        /// <value>The Y coordinate.</value>
        property float Y;
    };
}
#endif // NewMarker_h__
