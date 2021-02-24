// Declares the object wrong way zone class.
#ifndef ObjectWrongWayZone_h__
#define ObjectWrongWayZone_h__

#include "VxSdk.h"
#include "Utils.h"
#include "GridPoint.h"
#include "ZoneVector.h"

namespace VxSdkNet {

    /// <summary>
    /// The ObjectWrongWayZone class represents the data for an analytic object wrong way zone.
    /// </summary>
    public ref class ObjectWrongWayZone {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        ObjectWrongWayZone() {
            MinTriggerAngle = 110;
            Vector = gcnew ZoneVector();
            Zone = gcnew System::Collections::Generic::List<GridPoint^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxObjectWrongWayZone">The vx object wrong way zone.</param>
        ObjectWrongWayZone(VxSdk::VxObjectWrongWayZone* vxObjectWrongWayZone) {
            Vector = gcnew ZoneVector(&vxObjectWrongWayZone->vector);
            MinTriggerAngle = vxObjectWrongWayZone->minTriggerAngle;
            Zone = gcnew System::Collections::Generic::List<GridPoint^>();
            for (int i = 0; i < vxObjectWrongWayZone->zoneSize; i++) {
                Zone->Add(gcnew GridPoint(&vxObjectWrongWayZone->zone[i]));
            }
        }

        /// <summary>
        /// Gets or sets the minimum angle between a detected object’s trajectory vector and the wrong-way
        /// zone’s vector. Any object that is traveling at an angle >= the minimum from the reference
        /// vector will be considered heading in the wrong-direction.
        /// </summary>
        /// <value>The minimum trigger angle value.</value>
        property int MinTriggerAngle;

        /// <summary>
        /// Gets or sets the wrong-way zone’s vector. The vector points in the direction that indicates the
        /// correct direction of flow. An objects heading opposite the vector are considered to be heading
        /// in the wrong direction.
        /// </summary>
        /// <value>The wrong-way zone’s vector.</value>
        property ZoneVector^ Vector;

        /// <summary>
        /// Gets or sets the list of points that make up the wrong-way zone. The zone is defined as an simple convex
        /// quadrilateral. Do NOT repeat the starting vertex at the end of the list–it is implicitly included.
        /// </summary>
        /// <value>The list of points.</value>
        property System::Collections::Generic::List<GridPoint^>^ Zone;
    };
}
#endif // ObjectWrongWayZone_h__
