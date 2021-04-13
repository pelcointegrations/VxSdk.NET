// Declares the new digital ptz preset class.
#ifndef NewDigitalPtzPreset_h__
#define NewDigitalPtzPreset_h__

namespace VxSdkNet {

    /// <summary>
    /// The NewDigitalPtzPreset class represents a new digital PTZ preset.
    /// </summary>
    public ref class NewDigitalPtzPreset {
    public:

        /// <summary>
        /// Gets or sets the friendly description for the new PTZ preset.
        /// </summary>
        /// <value>The friendly description of the PTZ preset.</value>
        property System::String^ Description;

        /// <summary>
        /// Gets or sets the friendly name of the PTZ preset.
        /// </summary>
        /// <value>The friendly name of the PTZ preset.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the X (pan) coordinate absolute position, in degrees, relative to the (0,0) position. The -180
        /// position is leftmost while the 180 position is rightmost.
        /// </summary>
        /// <value>The X coordinate.</value>
        property float X;

        /// <summary>
        /// Gets or sets the Y (tilt) coordinate absolute position, in degrees, relative to the (0,0) position The -180
        /// position is bottommost while the 180 position is topmost.
        /// </summary>
        /// <value>The Y coordinate.</value>
        property float Y;

        /// <summary>
        /// Gets or sets the Z (zoom) coordinate absolute position relative to the 0 position. The 0 position is
        /// minimum zoom while the 100 position is maximum zoom.
        /// </summary>
        /// <value>The Z coordinate.</value>
        property float Z;
    };
}
#endif // NewDigitalPtzPreset_h__
