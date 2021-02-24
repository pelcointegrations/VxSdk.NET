// Declares the zone vector class.
#ifndef ZoneVector_h__
#define ZoneVector_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Vector class represents a starting coordinate and the angle from the horizontal axis the vector is pointing.
    /// </summary>
    public ref class ZoneVector {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        ZoneVector() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxVector">The vx vector.</param>
        ZoneVector(VxSdk::VxVector* vxVector){
			Angle = vxVector->angle;
            X = vxVector->x;
            Y = vxVector->y;
        }

        /// <summary>
        /// Gets or sets the direction as a counter-clockwise angle, in degrees, from the horizontal axis.
        /// </summary>
        /// <value>The direction in degrees.</value>
        property int Angle;

        /// <summary>
        /// Gets or sets the starting x-axis coordinate value.
        /// </summary>
        /// <value>The starting x-axis coordinate value.</value>
        property float X;

        /// <summary>
        /// Gets or sets the starting y-axis coordinate value.
        /// </summary>
        /// <value>The starting y-axis coordinate value.</value>
        property float Y;
    };
}
#endif // ZoneVector_h__
