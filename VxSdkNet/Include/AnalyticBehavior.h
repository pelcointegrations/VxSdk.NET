// Declares the analytic behavior class.
#ifndef AnalyticBehavior_h__
#define AnalyticBehavior_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ObjectCounter.h"
#include "ObjectZone.h"
#include "ResourceLimits.h"

namespace VxSdkNet {

    /// <summary>
    /// The AnalyticBehavior class represents a point in time of interest with reference to a particular data source.
    /// </summary>
    public ref class AnalyticBehavior {
    public:

        /// <summary>
        /// Values that represent the type of analytic behavior being performed.
        /// </summary>
        enum class AnalyticBehaviorType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Object counting analytic.</summary>
            ObjectCounter,

            /// <summary>Object detected in zone analytic.</summary>
            ObjectInZone
        };

        /// <summary>
        /// Values that represent the type of object this analytic pertains to.
        /// </summary>
        enum class AnalyticObjectType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>A person object type.</summary>
            Person,

            /// <summary>A vehicle object type.</summary>
            Vehicle
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxAnalyticBehavior">The vx analyticBehavior.</param>
        AnalyticBehavior(VxSdk::IVxAnalyticBehavior* vxAnalyticBehavior);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~AnalyticBehavior() {
            this->!AnalyticBehavior();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !AnalyticBehavior();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();
        
        /// <summary>
        /// Gets the type of analytic behavior being performed.
        /// </summary>
        /// <value>The analytic behavior type.</value>
        property AnalyticBehaviorType BehaviorType {
        public:
            AnalyticBehaviorType get() { return (AnalyticBehaviorType)_analyticBehavior->behaviorType; }
        }

        /// <summary>
        /// Gets the unique identifier of the analytic behavior.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_analyticBehavior->id); }
        }

        /// <summary>
        /// Gets or sets whether or not this analytic behavior is enabled.
        /// </summary>
        /// <value><c>true</c> if enabled, otherwise <c>false</c>.</value>
        property bool IsEnabled {
        public:
            bool get() { return _analyticBehavior->isEnabled; }
            void set(bool value) { value ? _analyticBehavior->Enable() : _analyticBehavior->Disable(); }
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
        /// Gets or sets the friendly name of the analytic behavior.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_analyticBehavior->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _analyticBehavior->SetName(name);
            }
        }

        /// <summary>
        /// Gets or sets the object counter data used when <see cref="behaviorType"/> is set to
        /// <see cref="VxAnalyticBehaviorType::kObjectCounter"/>.
        /// </summary>
        /// <value>The object counter.</value>
        property ObjectCounter^ ObjectCounter {
        public:
            VxSdkNet::ObjectCounter^ get() { return gcnew VxSdkNet::ObjectCounter(&_analyticBehavior->objectCounter); }
            void set(VxSdkNet::ObjectCounter^ value) { return _SetObjectCounter(value); }
        }

        /// <summary>
        /// Gets or sets the type of object this analytic pertains to.
        /// </summary>
        /// <value>The analytic object type.</value>
        property AnalyticObjectType ObjectType {
        public:
            AnalyticObjectType get() { return (AnalyticObjectType)_analyticBehavior->objectType; }
            void set(AnalyticObjectType value) { _analyticBehavior->SetObjectType((VxSdk::VxAnalyticObjectType::Value)value); }
        }

        /// <summary>
        /// Gets or sets the object zone data used to configure analytics of <see cref="behaviorType"/> is set
        /// to <see cref="VxAnalyticBehaviorType::kObjectInZone"/>.
        /// </summary>
        /// <value>The object zone.</value>
        property ObjectZone^ ObjectZone {
        public:
            VxSdkNet::ObjectZone^ get() { return gcnew VxSdkNet::ObjectZone(&_analyticBehavior->objectZone); }
            void set(VxSdkNet::ObjectZone^ value) { return _SetObjectZone(value); }
        }

        /// <summary>
        /// Gets or sets the sensitivity of the analysis. Higher values increase sensitivity.
        /// </summary>
        /// <value>The sensitivity of the analysis.</value>
        property int Sensitivity {
        public:
            int get() { return _analyticBehavior->sensitivity; }
            void set(int value) { _analyticBehavior->SetSensitivity(value); }
        }

        /// <summary>
        /// Gets or sets the severity value for events generated from this analytic behavior, from 1 (highest) to 10 (lowest).
        /// If set, overrides the corresponding situation severity.
        /// </summary>
        /// <value>The severity value.</value>
        property int Severity {
        public:
            int get() { return _analyticBehavior->severity; }
            void set(int value) { _analyticBehavior->SetSeverity(value); }
        }

    internal:
        VxSdk::IVxAnalyticBehavior* _analyticBehavior;
        VxSdkNet::ResourceLimits^ _GetLimits();
        void _SetObjectCounter(VxSdkNet::ObjectCounter^ objectCounter);
        void _SetObjectZone(VxSdkNet::ObjectZone^ objectZone);     
    };
}
#endif // AnalyticBehavior_h__
