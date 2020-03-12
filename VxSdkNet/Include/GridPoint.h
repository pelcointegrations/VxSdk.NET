// Declares the vx point class.
#ifndef Point_h__
#define Point_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Point class represents a location on a Cartesian grid.
    /// </summary>
    public ref class GridPoint {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        GridPoint() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxPoint">The vx point.</param>
        GridPoint(VxSdk::VxPoint* vxPoint){
            X = vxPoint->x;
            Y = vxPoint->y;
        }

        /// <summary>
        /// Gets or sets the X-axis coordinate value.
        /// </summary>
        /// <value>The X-axis coordinate value.</value>
        property int X;

        /// <summary>
        /// Gets or sets the Y-axis coordinate value.
        /// </summary>
        /// <value>The Y-axis coordinate value.</value>
        property int Y;
    };
}
#endif // Point_h__
