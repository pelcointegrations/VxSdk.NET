// Declares the object counter class.
#ifndef ObjectCounter_h__
#define ObjectCounter_h__

#include "VxSdk.h"
#include "Utils.h"
#include "GridPoint.h"

namespace VxSdkNet {

    /// <summary>
    /// The ObjectCounter class represents the data for an analytic object counter.
    /// </summary>
    public ref class ObjectCounter {
    public:

        /// <summary>
        /// Values that represent the area of an intersection.
        /// </summary>
        enum class IntersectionAreas {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>East-bound left area.</summary>
            EastboundLeft,

            /// <summary>East-bound pedestrian area.</summary>
            EastboundPedestrian,

            /// <summary>East-bound right area.</summary>
            EastboundRight,

            /// <summary>East-bound through area.</summary>
            EastboundThrough,

            /// <summary>North-bound left area.</summary>
            NorthboundLeft,

            /// <summary>North-bound pedestrian area.</summary>
            NorthboundPedestrian,

            /// <summary>North-bound right area.</summary>
            NorthboundRight,

            /// <summary>North-bound through area.</summary>
            NorthboundThrough,

            /// <summary>South-bound left area.</summary>
            SouthboundLeft,

            /// <summary>South-bound pedestrian area.</summary>
            SouthboundPedestrian,

            /// <summary>South-bound right area.</summary>
            SouthboundRight,

            /// <summary>South-bound through area.</summary>
            SouthboundThrough,

            /// <summary>West-bound left area.</summary>
            WestboundLeft,

            /// <summary>West-bound pedestrian area.</summary>
            WestboundPedestrian,

            /// <summary>West-bound right area.</summary>
            WestboundRight,

            /// <summary>West-bound through area.</summary>
            WestboundThrough
        };

        /// <summary>
        /// Default constructor.
        /// </summary>
        ObjectCounter() {
            EndPoint = gcnew GridPoint();
            StartPoint = gcnew GridPoint();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxObjectCounter">The vx object counter.</param>
        ObjectCounter(VxSdk::VxObjectCounter* vxObjectCounter){
            EndPoint = gcnew GridPoint(&vxObjectCounter->endPoint);
            IntersectionArea = (IntersectionAreas)vxObjectCounter->intersectionArea;
            StartPoint = gcnew GridPoint(&vxObjectCounter->startPoint);
        }

        /// <summary>
        /// Gets or sets the ending coordinate for the object counting line.
        /// </summary>
        /// <value>The ending coordinate.</value>
        property GridPoint^ EndPoint;

        /// <summary>
        /// Gets or sets the specific area of an intersection associated with this object counter.
        /// </summary>
        /// <value>The intersection area.</value>
        property IntersectionAreas IntersectionArea;

        /// <summary>
        /// Gets or sets the starting coordinate for the object counting line.
        /// </summary>
        /// <value>The starting coordinate.</value>
        property GridPoint^ StartPoint;
    };
}
#endif // ObjectCounter_h__
