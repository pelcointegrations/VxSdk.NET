// Declares the time range class.
#ifndef RuleTrigger_h__
#define RuleTrigger_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ResourceRef.h"

namespace VxSdkNet {

    /// <summary>
    /// The RuleTrigger class represents a condition in a rule that, if true, causes the rule to run its script
    /// (if triggered during an active time of the rule).
    /// </summary>
    public ref class RuleTrigger {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        RuleTrigger() {
            ResourceRefs = gcnew System::Collections::Generic::List<ResourceRef^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxRuleTrigger">The time range.</param>
        RuleTrigger(VxSdk::VxRuleTrigger* vxRuleTrigger) {
            ResourceRefs = gcnew System::Collections::Generic::List<ResourceRef^>();
            for (int i = 0; i < vxRuleTrigger->sourceRefSize; i++)
                ResourceRefs->Add(gcnew ResourceRef(&vxRuleTrigger->sourceRef[i]));

            SituationType = Utils::ConvertCppString(vxRuleTrigger->situationType);
        }

        /// <summary>
        /// Gets or sets situation type. This trigger will be checked each time this type of situation occurs.
        /// </summary>
        /// <value>The situation type. If empty, this trigger will always be inactive.</value>
        property System::String^ SituationType;

        /// <summary>
        /// Gets the resource reference that this trigger is associated with.
        /// </summary>
        /// <returns>The resource reference. If empty, no source filter will be applied (all sources are valid).</returns>
        property System::Collections::Generic::List<ResourceRef^>^ ResourceRefs;
    };
}
#endif // RuleTrigger_h__