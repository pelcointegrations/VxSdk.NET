// Declares the new analytic config class.
#ifndef NewAnalyticConfig_h__
#define NewAnalyticConfig_h__

#include "Resolution.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewAnalyticConfig class represents a request for the creation of a new analytic config.
    /// </summary>
    public ref class NewAnalyticConfig {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewAnalyticConfig() {
            MinConfidence = 0.5f;
            Size = gcnew Resolution();
        }

        /// <summary>
        /// Gets or sets the minimum confidence filtering value for detected objects in a video
        /// scene. Objects that have a detected confidence value less than the minimum will
        /// not be processed by the associated list of analytic behaviors.
        /// </summary>
        /// <value>The minimum confidence filtering value.</value>
        property float MinConfidence;

        /// <summary>
        /// Gets or sets the name of the PTZ preset that this configuration relates to. 
        /// PTZ cameras supporting analytics can only be configured on PTZ presets.
        /// </summary>
        /// <value>The PTZ preset name.</value>
        property System::String^ PtzPresetName;

        /// <summary>
        /// Gets or sets the resolution of the grid used for all analytic behaviors. The origin
        /// for the grid is the upper left corner.
        /// </summary>
        /// <value>The grid resolution.</value>
        property Resolution^ Size;
    };
}
#endif // NewAnalyticConfig_h__
