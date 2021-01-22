// Declares the object zone class.
#ifndef ObjectInZone_h__
#define ObjectInZone_h__

#include "VxSdk.h"
#include "Utils.h"
#include "GridPoint.h"

namespace VxSdkNet {

    /// <summary>
    /// The ObjectInZone class represents the data for an analytic object zone.
    /// </summary>
    public ref class ObjectInZone {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        ObjectInZone() {
            Vertices = gcnew System::Collections::Generic::List<GridPoint^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxObjectZone">The vx object zone.</param>
        ObjectInZone(VxSdk::VxObjectInZone* vxObjectInZone) {
            Vertices = gcnew System::Collections::Generic::List<GridPoint^>();
            for (int i = 0; i < vxObjectInZone->verticesSize; i++) {
                Vertices->Add(gcnew GridPoint(&vxObjectInZone->vertices[i]));
            }
        }

        /// <summary>
        /// Gets or sets the list of points that make up the zone. Must contain at least 3 points, which together
        /// specify the closed polygonal zone within which to look for objects of the prescribed type.
        /// </summary>
        /// <value>The list of points.</value>
        property System::Collections::Generic::List<GridPoint^>^ Vertices;
    };
}
#endif // ObjectInZone_h__
