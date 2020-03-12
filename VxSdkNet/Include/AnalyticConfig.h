// Declares the analytic config class.
#ifndef AnalyticConfig_h__
#define AnalyticConfig_h__

#include "VxSdk.h"
#include "GridPoint.h"
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
        /// Gets the analytic behaviors for this analytic configuration.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of analytic behaviors.</returns>
        System::Collections::Generic::List<AnalyticBehavior^>^ GetAnalyticBehaviors(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets all of the analytic behaviors for this analytic configuration.
        /// </summary>
        /// <value>A <c>List</c> of analytic behaviors.</value>
        property System::Collections::Generic::List<AnalyticBehavior^>^ AnalyticBehaviors {
        public:
            System::Collections::Generic::List<AnalyticBehavior^>^ get() { return GetAnalyticBehaviors(nullptr); }
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
        /// Gets any limits related to this resource.
        /// </summary>
        /// <value>The limits related to this resource.</value>
        property ResourceLimits^ Limits {
        public:
            ResourceLimits^ get() { return _GetLimits(); }
        }

        /// <summary>
        /// Gets or sets the coordinate system used for all analytic behavior data.
        /// </summary>
        /// <value>The coordinate system value.</value>
        property GridPoint^ Size {
        public:
            GridPoint^ get() { return gcnew GridPoint(&_analyticConfig->size); }
            void set(GridPoint^ value) { _SetGridSize(value); }
        }

    internal:
        VxSdk::IVxAnalyticConfig* _analyticConfig;
        VxSdkNet::ResourceLimits^ _GetLimits();
        void _SetGridSize(GridPoint^ value);
    };
}
#endif // AnalyticConfig_h__
