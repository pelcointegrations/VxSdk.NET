// Declares the rule class.
#ifndef Rule_h__
#define Rule_h__

#include "VxSdk.h"
#include "TimeTable.h"
#include "RuleTrigger.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Rule class represents a set of rule triggers that, when any occur during times when the rule is active, cause a script to run. A rule can be read as follows:
    /// "If enabled, when any specified triggers occur during specified times, run the associated script."
    /// </summary>
    public ref class Rule {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxRule">The vx rule.</param>
        Rule(VxSdk::IVxRule* vxRule);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Rule() {
            this->!Rule();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Rule();

        /// <summary>
        /// Halts the script that this rule is running, if any. This has no effect if the script is not currently running.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of halting the script.</returns>
        Results::Value HaltScript();
        
        /// <summary>
        /// Get the time tables associated with this rule using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the associated time tables.</returns>
        System::Collections::Generic::List<TimeTable^>^ GetTimeTables(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the unique rule identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_rule->id); }
        }

        /// <summary>
        /// Gets or sets whether the rule will be enabled or not.
        /// </summary>
        /// <value><c>true</c> to enable new rule, otherwise <c>false</c>.</value>
        property bool IsEnabled {
        public:
            bool get() { return _rule->isEnabled; }
            void set(bool value) { value ? _rule->Enable() : _rule->Disable(); }
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
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_rule->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _rule->SetName(name);
            }
        }

        /// <summary>
        /// Gets or sets the script to run when the rule is triggered.
        /// </summary>
        /// <value>The script.</value>
        property System::String^ Script {
        public:
            System::String^ get() { return _GetScript(); }
            void set(System::String^ value) { _SetScript(value); }
        }

        /// <summary>
        /// Gets or sets the time tables that will be associated with this rule. The rule will only
        /// automatically run its script if a trigger occurs during the times contained by the time tables
        /// specified here. If empty, no active time ranges are available for this rule (it must be manually
        /// triggered). If null, no time filters will be applied (the new rule is always active).
        /// </summary>
        /// <value>A <c>List</c> of time tables to be used by this rule.</value>
        property System::Collections::Generic::List<TimeTable^>^ TimeTables {
        public:
            System::Collections::Generic::List<TimeTable^>^ get() { return GetTimeTables(nullptr); }
            void set(System::Collections::Generic::List<TimeTable^>^ value) { _SetTimeTables(value); }
        }

        /// <summary>
        /// Gets or sets the triggers that, when any activate, cause the rule to run its script. If empty or null, this rule
        /// must be manually triggered.
        /// </summary>
        /// <value>A <c>List</c> of triggers to be used by this rule.</value>
        property System::Collections::Generic::List<RuleTrigger^>^ Triggers {
        public:
            System::Collections::Generic::List<RuleTrigger^>^ get() { return _GetTriggers(); }
            void set(System::Collections::Generic::List<RuleTrigger^>^ value) { _SetTriggers(value); }
        }

    internal:
        VxSdk::IVxRule* _rule;
        VxSdkNet::ResourceLimits^ _GetLimits();
        System::String^ _GetScript();
        System::Collections::Generic::List<RuleTrigger^>^ _GetTriggers();
        Results::Value _SetScript(System::String^ scriptData);
        Results::Value _SetTimeTables(System::Collections::Generic::List<TimeTable^>^ timeTableList);
        Results::Value _SetTriggers(System::Collections::Generic::List<RuleTrigger^>^ triggerList);
    };
}
#endif // Rule_h__
