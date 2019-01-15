// Declares the ptz limits class.
#ifndef PtzLimits_h__
#define PtzLimits_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The PtzLimits class represents the value limits for a ptz controller.
    /// </summary>
    public ref class PtzLimits {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxPtzLimits">The ptz limits.</param>
        PtzLimits(VxSdk::VxPtzLimits* vxPtzLimits){
            MinPositionY = vxPtzLimits->minPositionY;
            MaxPositionY = vxPtzLimits->maxPositionY;
            MaxPositionZ = vxPtzLimits->maxPositionZ;
            MinSpeedX = vxPtzLimits->minSpeedX;
            MaxSpeedX = vxPtzLimits->maxSpeedX;
            MinSpeedY = vxPtzLimits->minSpeedY;
            MaxSpeedY = vxPtzLimits->maxSpeedY;
        }

        /// <summary>
        /// Gets the Y coordinate minimum limit.
        /// </summary>
        /// <value>The minimum Y coordinate, 0 if limit is unavailable.</value>
        property int MinPositionY;

        /// <summary>
        /// Gets the Y coordinate maximum limit.
        /// </summary>
        /// <value>The maximum Y coordinate, 0 if limit is unavailable.</value>
        property int MaxPositionY;

        /// <summary>
        /// Gets the Z coordinate maximum limit.
        /// </summary>
        /// <value>The maximum Z coordinate, 0 if limit is unavailable.</value>
        property int MaxPositionZ;

        /// <summary>
        /// Gets the pan speed minimum limit.
        /// </summary>
        /// <value>The minimum pan speed.</value>
        property int MinSpeedX;

        /// <summary>
        /// Gets the pan speed maximum limit.
        /// </summary>
        /// <value>The maximum pan speed.</value>
        property int MaxSpeedX;

        /// <summary>
        /// Gets the tilt speed minimum limit.
        /// </summary>
        /// <value>The minimum tilt speed.</value>
        property int MinSpeedY;

        /// <summary>
        /// Gets the tilt speed maximum limit.
        /// </summary>
        /// <value>The maximum tilt speed.</value>
        property int MaxSpeedY;
    };
}
#endif // PtzLimits_h__
