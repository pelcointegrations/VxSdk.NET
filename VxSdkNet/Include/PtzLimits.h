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
            HasLimitPositionX = vxPtzLimits->hasLimitPositionX;
            HasLimitPositionY = vxPtzLimits->hasLimitPositionY;
            HasLimitPositionZ = vxPtzLimits->hasLimitPositionZ;
            HasLimitSpeedFocus = vxPtzLimits->hasLimitSpeedFocus;
            HasLimitSpeedIris = vxPtzLimits->hasLimitSpeedIris;
            HasLimitSpeedX = vxPtzLimits->hasLimitSpeedX;
            HasLimitSpeedY = vxPtzLimits->hasLimitSpeedY;
            HasLimitSpeedZ = vxPtzLimits->hasLimitSpeedZ;
            MaxPositionX = vxPtzLimits->maxPositionX;
            MaxPositionY = vxPtzLimits->maxPositionY;
            MaxPositionZ = vxPtzLimits->maxPositionZ;
            MaxSpeedFocus = vxPtzLimits->maxSpeedFocus;
            MaxSpeedIris = vxPtzLimits->maxSpeedIris;
            MaxSpeedX = vxPtzLimits->maxSpeedX;
            MaxSpeedY = vxPtzLimits->maxSpeedY;
            MaxSpeedZ = vxPtzLimits->maxSpeedZ;
            MinPositionX = vxPtzLimits->minPositionX;
            MinPositionY = vxPtzLimits->minPositionY;
            MinPositionZ = vxPtzLimits->minPositionZ;
            MinSpeedFocus = vxPtzLimits->minSpeedFocus;
            MinSpeedIris = vxPtzLimits->minSpeedIris;
            MinSpeedX = vxPtzLimits->minSpeedX;
            MinSpeedY = vxPtzLimits->minSpeedY;
            MinSpeedZ = vxPtzLimits->minSpeedZ;
        }

        /// <summary>
        /// Gets a value indicating whether the X coordinate limits are available.
        /// </summary>
        /// <value><c>true</c> if the limits are available, <c>false</c> if not.</value>
        property bool HasLimitPositionX;

        /// <summary>
        /// Gets a value indicating whether the Y coordinate limits are available.
        /// </summary>
        /// <value><c>true</c> if the limits are available, <c>false</c> if not.</value>
        property bool HasLimitPositionY;

        /// <summary>
        /// Gets a value indicating whether the Z coordinate limits are available.
        /// </summary>
        /// <value><c>true</c> if the limits are available, <c>false</c> if not.</value>
        property bool HasLimitPositionZ;

        /// <summary>
        /// Gets a value indicating whether the focus speed limits are available.
        /// </summary>
        /// <value><c>true</c> if the limits are available, <c>false</c> if not.</value>
        property bool HasLimitSpeedFocus;

        /// <summary>
        /// Gets a value indicating whether the iris speed limits are available.
        /// </summary>
        /// <value><c>true</c> if the limits are available, <c>false</c> if not.</value>
        property bool HasLimitSpeedIris;

        /// <summary>
        /// Gets a value indicating whether the X speed limits are available.
        /// </summary>
        /// <value><c>true</c> if the limits are available, <c>false</c> if not.</value>
        property bool HasLimitSpeedX;

        /// <summary>
        /// Gets a value indicating whether the Y speed limits are available.
        /// </summary>
        /// <value><c>true</c> if the limits are available, <c>false</c> if not.</value>
        property bool HasLimitSpeedY;

        /// <summary>
        /// Gets a value indicating whether the Z speed limits are available.
        /// </summary>
        /// <value><c>true</c> if the limits are available, <c>false</c> if not.</value>
        property bool HasLimitSpeedZ;

        /// <summary>
        /// Gets the X coordinate maximum limit.
        /// </summary>
        /// <value>The maximum X coordinate, 0 if limit is unavailable.</value>
        property int MaxPositionX;

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
        /// Gets the focus speed maximum limit.
        /// </summary>
        /// <value>The maximum focus speed, 0 if limit is unavailable.</value>
        property int MaxSpeedFocus;

        /// <summary>
        /// Gets the iris speed maximum limit.
        /// </summary>
        /// <value>The maximum iris speed, 0 if limit is unavailable.</value>
        property int MaxSpeedIris;

        /// <summary>
        /// Gets the pan speed maximum limit.
        /// </summary>
        /// <value>The maximum pan speed.</value>
        property int MaxSpeedX;

        /// <summary>
        /// Gets the tilt speed maximum limit.
        /// </summary>
        /// <value>The maximum tilt speed.</value>
        property int MaxSpeedY;

        /// <summary>
        /// Gets the zoom speed maximum limit.
        /// </summary>
        /// <value>The maximum zoom speed.</value>
        property int MaxSpeedZ;

        /// <summary>
        /// Gets the X coordinate minimum limit.
        /// </summary>
        /// <value>The minimum X coordinate, 0 if limit is unavailable.</value>
        property int MinPositionX;

        /// <summary>
        /// Gets the Y coordinate minimum limit.
        /// </summary>
        /// <value>The minimum Y coordinate, 0 if limit is unavailable.</value>
        property int MinPositionY;

        /// <summary>
        /// Gets the Z coordinate minimum limit.
        /// </summary>
        /// <value>The minimum Z coordinate, 0 if limit is unavailable.</value>
        property int MinPositionZ;

        /// <summary>
        /// Gets the focus speed minimum limit.
        /// </summary>
        /// <value>The minimum focus speed.</value>
        property int MinSpeedFocus;

        /// <summary>
        /// Gets the iris speed minimum limit.
        /// </summary>
        /// <value>The minimum iris speed.</value>
        property int MinSpeedIris;

        /// <summary>
        /// Gets the pan speed minimum limit.
        /// </summary>
        /// <value>The minimum pan speed.</value>
        property int MinSpeedX;

        /// <summary>
        /// Gets the tilt speed minimum limit.
        /// </summary>
        /// <value>The minimum tilt speed.</value>
        property int MinSpeedY;

        /// <summary>
        /// Gets the zoom speed minimum limit.
        /// </summary>
        /// <value>The minimum zoom speed.</value>
        property int MinSpeedZ;
    };
}
#endif // PtzLimits_h__
