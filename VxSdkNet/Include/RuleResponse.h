// Declares the rule response class.
#ifndef RuleResponse_h__
#define RuleResponse_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The RuleResponse class represents a rule response. The response may be configured to either execute a Groovy
    /// script or generate an event in the system when triggered.
    /// </summary>
    public ref class RuleResponse {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        RuleResponse() {
            UsedSourceEventFields = gcnew System::Collections::Generic::List<System::String^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxRuleResponse">The rule response.</param>
        RuleResponse(VxSdk::VxRuleResponse* vxRuleResponse) {
            UsedSourceEventFields = gcnew System::Collections::Generic::List<System::String^>();
            for (int i = 0; i < vxRuleResponse->usedSourceEventFieldsSize; i++)
                UsedSourceEventFields->Add(Utils::ConvertCppString(vxRuleResponse->usedSourceEventFields[i]));

            IsCustomScript = vxRuleResponse->isCustomScript;
            Script = Utils::ConvertCppString(vxRuleResponse->script);
            SituationType = Utils::ConvertCppString(vxRuleResponse->situationType);
        }

        /// <summary>
        /// Gets or sets whether this response will run a custom script or generate an event on the system.
        /// </summary>
        /// <value>
        /// <c>true</c> to run a custom script (ignore the <c>SituationType</c> and <c>UsedSourceEventFields</c>
        /// properties); <c>false</c> to generate an event (ignore the <c>Script</c> property).
        /// </value>
        property bool IsCustomScript;

        /// <summary>
        /// Gets or sets the Groovy script to run when the associated rule is triggered.
        /// Ignored if <c>IsCustomScript</c> is <c>false</c>.
        /// </summary>
        /// <value>The script.</value>
        property System::String^ Script;

        /// <summary>
        /// Gets or sets the situation type to generate an event for. Ignored if <c>IsCustomScript</c> is <c>true</c>.
        /// </summary>
        /// <value>The situation type.</value>
        property System::String^ SituationType;

        /// <summary>
        /// Gets the list of fields from the source event to copy to the generated event. The event time is always copied.
        /// Restricted to severity, source_device_id, properties. Ignored if <c>IsCustomScript</c> is <c>true</c>.
        /// </summary>
        /// <returns>The list of fields from the source event to copy to the generated event, if any.</returns>
        property System::Collections::Generic::List<System::String^>^ UsedSourceEventFields;
    };
}
#endif // RuleResponse_h__