// Declares the Drawing class.
#ifndef Drawing_h__
#define Drawing_h__

#include "VxSdk.h"
#include "Utils.h"
#include "NewMarker.h"
#include "Marker.h"
#include "ResourceLock.h"

namespace VxSdkNet {

    /// <summary>
    /// The Drawing class represents a diagrammatic representation of an area. A drawing may
    /// contain any number of markers to represent points of interest within the area.
    /// </summary>
    public ref class Drawing {
    public:

        /// <summary>
        /// Values that represent which provider is associated with a drawing
        /// </summary>
        enum class DrawingProvider {
            /// <summary>Unset or unknown provider</summary>
            Unknown,
            /// <summary>Esri drawing provider</summary>
            Esri,
            /// <summary>Serenity drawing provider</summary>
            Serenity
        };
    
    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDrawing">The vx Drawing.</param>
        Drawing(VxSdk::IVxDrawing* vxDrawing);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Drawing() {
            this->!Drawing();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Drawing();

        /// <summary>
        /// Creates a new marker.
        /// </summary>
        /// <param name="newMarker">The new marker to be added.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value AddMarker(NewMarker^ newMarker);

        /// <summary>
        /// Deletes the binary drawing image data.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the image.</returns>
        Results::Value DeleteImage();

        /// <summary>
        /// Deletes the resource lock, if any.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the lock.</returns>
        Results::Value DeleteLock();

        /// <summary>
        /// Deletes a marker.
        /// </summary>
        /// <param name="marker">The marker to be deleted.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value DeleteMarker(Marker^ marker);

        /// <summary>
        /// Gets the image uri, if any.
        /// </summary>
        /// <returns>The image uri.</returns>
        System::String^ GetImageUri();

        /// <summary>
        /// Gets the resource lock, if any.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        ResourceLock^ GetLock();

        /// <summary>
        /// Get the markers associated with this drawing using an optional collection filter.
        /// <para>Available filters: LayerName, ModifiedSince, ResourceId.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of the associated markers.</returns>
        System::Collections::Generic::List<Marker^>^ GetMarkers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Determines if a drawing contains a marker with the given resource id.
        /// </summary>
        /// <returns><c>true</c> if this drawing has a marker with the given resource id, otherwise <c>false</c>.</returns>
        bool HasMarkerWithResource(System::String^ resourceId);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Sets the binary drawing image data. The maximum allowable size of the image is 128 MB.
        /// Supported file types are DWG, JPG and PNG.
        /// </summary>
        /// <param name="imagePath">The local path to the image file.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value SetImage(System::String^ imagePath);

        /// <summary>
        /// Sets a resource lock on this drawing, owned by the current user.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value SetLock();

        /// <summary>
        /// Gets or sets an integer that defines an ARGB color for the map background.
        /// </summary>
        /// <value>An integer that defines an ARGB color.</value>
        property unsigned int BackgroundColor {
        public:
            unsigned int get() { return _drawing->backgroundColor; }
            void set(unsigned int value) { _drawing->SetBackgroundColor(value); }
        }

        /// <summary>
        /// Gets or sets an integer that defines an ARGB color for the camera number text.
        /// </summary>
        /// <value>An integer that defines an ARGB color.</value>
        property unsigned int CameraNumberColor {
        public:
            unsigned int get() { return _drawing->cameraNumberColor; }
            void set(unsigned int value) { _drawing->SetCameraNumberColor(value); }
        }

        /// <summary>
        /// Gets the unique drawing identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_drawing->id); }
        }

        /// <summary>
        /// Gets the last modified date of the drawing.
        /// </summary>
        /// <value>Last modified date.</value>
        property System::DateTime LastModified {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_drawing->lastModified); }
        }

        /// <summary>
        /// Gets any limits related to this resource.
        /// </summary>
        /// <value>The limits related to this resource.</value>
        property ResourceLimits^ Limits {
        public:
            ResourceLimits^ get() { return _GetLimits(); }
        }

        /// <summary>
        /// Gets the markers associated with this drawing.
        /// </summary>
        /// <value>A <c>List</c> of the associated markers.</value>
        property System::Collections::Generic::List<Marker^>^ Markers {
        public:
            System::Collections::Generic::List<Marker^>^ get() { return GetMarkers(nullptr); }
        }

        /// <summary>
        /// Gets or sets the size, in pixels, of marker icons.
        /// </summary>
        /// <value>The size, in pixels.</value>
        property int MarkerSize {
        public:
            int get() { return _drawing->markerSize; }
            void set(int value) { _drawing->SetMarkerSize(value); }
        }

        /// <summary>
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_drawing->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _drawing->SetName(name);
            }
        }

        /// <summary>
        /// Gets the image mime type
        /// </summary>
        /// <value>The Mime type.</value>
        property System::String^ MimeType {
        public:
            System::String^ get() { return Utils::ConvertCppString(_drawing->mimeType); }
        }

        /// <summary>
        /// Gets the provider of the drawing
        /// </summary>
        /// <value>The drawing <see cref="DrawingProvider">Provider</see>.</value>
        property DrawingProvider Provider {
        public:
            DrawingProvider get() { return DrawingProvider(_drawing->provider); }
        }

        /// <summary>
        /// Gets or sets whether the camera number text overlays should be displayed. 
        /// </summary>
        /// <value><c>true</c> to display camera number text overlays, <c>false</c> if not.</value>
        property bool ShowCameraNumbers {
        public:
            bool get() { return _drawing->showCameraNumbers; }
            void set(bool value) { _drawing->SetShowCameraNumbers(value); }
        }

    internal:
        VxSdk::IVxDrawing* _drawing;
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // Drawing_h__
