// Declares the analytic config class.
#ifndef AnalyticConfig_h__
#define AnalyticConfig_h__

#include "VxSdk.h"
#include "Resolution.h"
#include "Utils.h"
#include "ResourceLimits.h"

namespace VxSdkNet {
    ref class AnalyticBehavior;
    ref class NewAnalyticBehavior;

    /// <summary>
    /// The AnalyticConfig class represents a point in time of interest with reference to a particular data source.
    /// </summary>
    public ref class AnalyticConfig {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxAnalyticConfig">The vx analytic configuration.</param>
        AnalyticConfig(VxSdk::IVxAnalyticConfig* vxAnalyticConfig);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~AnalyticConfig() {
            this->!AnalyticConfig();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !AnalyticConfig();

        /// <summary>
        /// Add a new analytic behavior to this analytic configuration.
        /// </summary>
        /// <param name="newAnalyticBehavior">The new analytic behavior to be added to the analytic configuration.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the analytic behavior.</returns>
        Results::Value AddAnalyticBehavior(NewAnalyticBehavior^ newAnalyticBehavior);

        /// <summary>
        /// Delete an analytic behavior from this analytic configuration.
        /// </summary>
        /// <param name="analyticBehavior">The analytic behavior to be deleted from the analytic configuration.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the analytic behavior.</returns>
        Results::Value DeleteAnalyticBehavior(AnalyticBehavior^ analyticBehavior);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        //<summary>
        //Gets all of the analytic behaviors for this analytic configuration.
        //</summary>
        //<value>A <c>List</c> of analytic behaviors.</value>
        property System::Collections::Generic::List<AnalyticBehavior^>^ AnalyticBehaviors {
        public:
            System::Collections::Generic::List<AnalyticBehavior^>^ get() { return _GetAnalyticBehaviors(); }
        }

        /// <summary>
        /// Gets the unique analytic configuration identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_analyticConfig->id); }
        }

        /// <summary>
        /// Specifies the resolution of the grid used for all AnalyticBehavior data.
        /// </summary>
        /// <value>The resolution value.</value>
        property Resolution^ Size {
        public:
            Resolution^ get() { return gcnew Resolution(&_analyticConfig->size); }
            void set(Resolution^ value) { _SetResolutionSize(value); }
        }

        /// <summary>
        /// Specifies the minimum confidence filtering value for detected objects in a video scene. 
        /// </summary>
        property float MinConfidence {
        public:
            float get() { return _analyticConfig->minConfidence; }
            void set(float value) { _analyticConfig->SetMinConfidence(value); }
        }

        /// <summary>
        /// Specifies the name of the PtzPreset that this configuration relates to. PTZ cameras supporting 
        /// analytics can only be configured on PTZ presets.
        /// </summary>
        property System::String^ PtzPresetName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_analyticConfig->ptzPresetName); }
            void set(System::String^ value) { 
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _analyticConfig->SetPtzPresetName(name);
            }
        }

    internal:
        VxSdk::IVxAnalyticConfig* _analyticConfig;
        void _SetResolutionSize(Resolution^ value);
        System::Collections::Generic::List<AnalyticBehavior^>^ _GetAnalyticBehaviors();
    };
}
#endif // AnalyticConfig_h__
