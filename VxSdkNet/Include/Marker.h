// Declares the Marker class.
#ifndef Marker_h__
#define Marker_h__

#include "VxSdk.h"
#include "DataSource.h"
#include "ResourceRef.h"
#include "Utils.h"

namespace VxSdkNet {
    ref class Drawing;

    /// <summary>
    /// The Marker class represents the location of a resource on a drawing.
    /// </summary>
    public ref class Marker {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxMarker">The vx Marker.</param>
        Marker(VxSdk::IVxMarker* vxMarker);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Marker() {
            this->!Marker();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Marker();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Removes any resource that is associated with this marker.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value RemoveAssociation();

        /// <summary>
        /// Sets the data source associated with this marker.
        /// </summary>
        /// <param name="dataSource">The data source to associate with this marker.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the property.</returns>
        Results::Value SetAssociation(DataSource^ dataSource);

        /// <summary>
        /// Sets the drawing associated with this marker.
        /// </summary>
        /// <param name="drawing">The drawing to associate with this marker.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the property.</returns>
        Results::Value SetAssociation(Drawing^ drawing);

        /// <summary>
        /// Sets the location of the marker on the associated drawing.
        /// </summary>
        /// <param name="x">The X coordinate.</param>
        /// <param name="y">The Y coordinate.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the coordinates.</returns>
        Results::Value SetCoordinates(float x, float y);

        /// <summary>
        /// Gets the data source associated with this marker, if any.
        /// </summary>
        /// <value>The associated data source if present, otherwise <c>nullptr</c>.</value>
        property DataSource^ AssociatedDataSource {
            DataSource^ get() { return _GetAssociatedDataSource(); }
        }

        /// <summary>
        /// Gets the drawing associated with this marker, if any.
        /// </summary>
        /// <value>The associated drawing if present, otherwise <c>nullptr</c>.</value>
        property Drawing^ AssociatedDrawing {
            Drawing^ get() { return _GetAssociatedDrawing(); }
        }

        /// <summary>
        /// Gets the type of resource associated with this marker, if any.
        /// </summary>
        /// <value>The resource type.</value>
        property ResourceRef::ResourceType AssociatedResourceType {
        public:
            ResourceRef::ResourceType get() { return ResourceRef::ResourceType(_marker->resource); }
        }

        /// <summary>
        /// Gets or sets the angular coordinate indicating the direction, if any, that the marker is
        /// facing on a polar grid(e.g.: 0 (right), 90 (up), 180 (left), 270 (down)).
        /// </summary>
        /// <value>The angular direction.</value>
        property float Direction {
        public:
            float get() { return _marker->direction; }
            void set(float value) { _marker->SetDirection(value); }
        }

        /// <summary>
        /// Gets the drawing that this marker belongs to.
        /// </summary>
        /// <value>The drawing that this marker belongs to.</value>
        property Drawing^ Drawing {
        public:
            VxSdkNet::Drawing^ get() { return _GetDrawing(); }
        }

        /// <summary>
        /// Gets the unique marker identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return gcnew System::String(_marker->id); }
        }

        /// <summary>
        /// Gets or sets the layer name for the marker.
        /// </summary>
        /// <value>The layer name of the marker.</value>
        property System::String^ LayerName {
        public:
            System::String^ get() { return gcnew System::String(_marker->layerName); }
            void set(System::String^ value) {
                char layerName[64];
                VxSdk::Utilities::StrCopySafe(layerName, Utils::ConvertSysStringNonConst(value));
                _marker->SetLayerName(layerName);
            }
        }
        
        /// <summary>
        /// Gets or sets the friendly name of the marker.
        /// </summary>
        /// <value>The friendly name of the marker.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return gcnew System::String(_marker->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertSysStringNonConst(value));
                _marker->SetName(name);
            }
        }

        /// <summary>
        /// Gets the X coordinate.
        /// </summary>
        /// <value>The X coordinate.</value>
        property float X {
        public:
            float get() { return _marker->x; }
        }

        /// <summary>
        /// Gets the Y coordinate.
        /// </summary>
        /// <value>The Y coordinate.</value>
        property float Y {
        public:
            float get() { return _marker->y; }
        }

    internal:
        VxSdk::IVxMarker* _marker;
        VxSdkNet::DataSource^ _GetAssociatedDataSource();
        VxSdkNet::Drawing^ _GetAssociatedDrawing();
        VxSdkNet::Drawing^ _GetDrawing();
    };
}
#endif // Marker_h__
