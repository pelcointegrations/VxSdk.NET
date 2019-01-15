// Declares the preset class.
#ifndef Preset_h__
#define Preset_h__

#include "VxSdk.h"

namespace VxSdkNet {

    /// <summary>
    /// The Preset class represents a predefined point that a PTZ device can PTZ to when triggered.
    /// </summary>
    public ref class Preset {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxPreset">The vx preset.</param>
        Preset(VxSdk::IVxPreset* vxPreset);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Preset() {
            this->!Preset();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Preset();

        /// <summary>
        /// Gets the friendly description of the preset.
        /// </summary>
        /// <value>The friendly description.</value>
        property System::String^ Description {
        public:
            System::String^ get() { return gcnew System::String(_preset->description); }
        }

        /// <summary>
        /// Gets the unique numerical sequence value of this preset.
        /// </summary>
        /// <value>The unique numerical sequence value.</value>
        property int Index {
        public:
            int get() { return _preset->index; }
        }

        /// <summary>
        /// Gets whether this preset is digital.
        /// </summary>
        /// <value><c>true</c> if a digital preset, otherwise <c>false</c>.</value>
        property bool IsDigital {
        public:
            bool get() { return _preset->isDigital; }
        }

        /// <summary>
        /// Gets the friendly name of the preset.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return gcnew System::String(_preset->name); }
        }

        /// <summary>
        /// Gets the X (pan) coordinate absolute position, in degrees, relative to the (0, 0) position.
        /// The -180 position is leftmost while the 180 position is rightmost (digital presets only).
        /// </summary>
        /// <value>The x coordinate.</value>
        property float X {
        public:
            float get() { return _preset->x; }
        }

        /// <summary>
        /// Gets the Y (tilt) coordinate absolute position, in degrees, relative to the (0, 0) position.
        /// The -180 position is bottommost while the 180 position is topmost (digital presets only).
        /// </summary>
        /// <value>The y coordinate.</value>
        property float Y {
        public:
            float get() { return _preset->y; }
        }

        /// <summary>
        /// Gets the Z (zoom) coordinate absolute position relative to the 0 position.
        /// The 0 position is minimum zoom while the 100 position is maximum zoom (digital presets only).
        /// </summary>
        /// <value>The z coordinate.</value>
        property float Z {
        public:
            float get() { return _preset->z; }
        }

    internal:
        VxSdk::IVxPreset* _preset;
    };
}
#endif // Preset_h__
