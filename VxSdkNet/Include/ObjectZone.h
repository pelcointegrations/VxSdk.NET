// Declares the object zone class.
#ifndef ObjectZone_h__
#define ObjectZone_h__

#include "VxSdk.h"
#include "Utils.h"
#include "GridPoint.h"

namespace VxSdkNet {

    /// <summary>
    /// The ObjectZone class represents the data for an analytic object zone.
    /// </summary>
    public ref class ObjectZone {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        ObjectZone() {
            Vertices = gcnew System::Collections::Generic::List<GridPoint^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxObjectZone">The vx object zone.</param>
        ObjectZone(VxSdk::VxObjectZone* vxObjectZone) {
            Vertices = gcnew System::Collections::Generic::List<GridPoint^>();
            for (int i = 0; i < vxObjectZone->verticesSize; i++) {
                Vertices->Add(gcnew GridPoint(&vxObjectZone->vertices[i]));
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
#endif // ObjectZone_h__
