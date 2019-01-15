// Declares the rect class.
#ifndef Rect_h__
#define Rect_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Rect class represents rectangular integer coordinates indicated by a combination of left, top, width, and height values.
    ///a monitor position that describes where a monitor resides in a
    /// coordinate plane (specifically the IV quadrant of a Cartesian plane where 0,0 is the top left point).
    /// </summary>
    public ref class Rect {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        Rect() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxRect">The vx monitor position.</param>
        Rect(VxSdk::VxRect* vxRect){
            Height = vxRect->height;
            Left = vxRect->left;
            Top = vxRect->top;
            Width = vxRect->width;
        }

        /// <summary>
        /// Gets or sets the height.
        /// </summary>
        /// <value>The height value.</value>
        property int Height;

        /// <summary>
        /// Gets or sets the left coordinate position.
        /// </summary>
        /// <value>The left coordinate position.</value>
        property int Left;

        /// <summary>
        /// Gets or sets the top coordinate position.
        /// </summary>
        /// <value>The top coordinate position.</value>
        property int Top;

        /// <summary>
        /// Gets or sets the width.
        /// </summary>
        /// <value>The width value.</value>
        property int Width;
    };
}
#endif // Rect_h__
