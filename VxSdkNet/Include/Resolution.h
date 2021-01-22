// Declares the vx Resolution class.
#ifndef Resolution_h__
#define Resolution_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Resolution class represents a resolution in pixels.
    /// </summary>
    public ref class Resolution {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        Resolution() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxResolution">The vx Resolution.</param>
        Resolution(VxSdk::VxResolution* vxResolution){
            Width = vxResolution->width;
            Height = vxResolution->height;
        }

        /// <summary>
        /// Gets or sets the width in pixels.
        /// </summary>
        /// <value>The width.</value>
        property int Width;

        /// <summary>
        /// Gets or sets height in pixels.
        /// </summary>
        /// <value>The height.</value>
        property int Height;
    };
}
#endif // Resolution_h__
