// Declares the new rule class.
#ifndef NewRule_h__
#define NewRule_h__

#include "Rule.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewRule class represents a new rule.
    /// </summary>
    public ref class NewRule {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewRule() {
            RuleTriggers = gcnew System::Collections::Generic::List<RuleTrigger^>();
            TimeTables = gcnew System::Collections::Generic::List<TimeTable^>();
        }

        /// <summary>
        /// Gets or sets whether the new rule will be enabled or not.
        /// </summary>
        /// <value><c>true</c> to enable the new rule, otherwise <c>false</c>.</value>
        property bool IsEnabled;

        /// <summary>
        /// Gets or sets the friendly name of the rule.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets the triggers that, when any activate, cause the rule to run its script. If empty or null, this rule
        /// must be manually triggered.
        /// </summary>
        /// <value>A <c>List</c> of triggers to be used by this rule.</value>
        property System::Collections::Generic::List<RuleTrigger^>^ RuleTriggers;

        /// <summary>
        /// Gets or sets the script to run when the rule is triggered.
        /// </summary>
        /// <value>The script.</value>
        property System::String^ Script;

        /// <summary>
        /// Gets the time tables that will be associated with this rule. The rule will only
        /// automatically run its script if a trigger occurs during the times contained by the time tables
        /// specified here. If empty, no active time ranges are available for this rule (it must be manually
        /// triggered). If null, no time filters will be applied (the new rule is always active).
        /// </summary>
        /// <value>A <c>List</c> of time tables to be used by this rule.</value>
        property System::Collections::Generic::List<TimeTable^>^ TimeTables;
    };
}
#endif // NewRule_h__
