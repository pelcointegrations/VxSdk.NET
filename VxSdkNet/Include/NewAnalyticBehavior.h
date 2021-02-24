// Declares the new analytic behavior class.
#ifndef NewAnalyticBehavior_h__
#define NewAnalyticBehavior_h__

#include "AnalyticBehavior.h"
#include "ObjectLineCounter.h"
#include "ObjectInZone.h"
#include "ObjectWrongWayZone.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewAnalyticBehavior class represents a request for the creation of a new analytic behavior.
    /// </summary>
    public ref class NewAnalyticBehavior {
    public:

        /// <summary>
        /// Gets or sets the type of analytic behavior being performed.
        /// </summary>
        /// <value>The analytic behavior type.</value>
        property AnalyticBehavior::AnalyticBehaviorType BehaviorType;

        /// <summary>
        /// Gets or sets the unique identifier of the analytic behavior. The server will generate this value if not supplied.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets whether or not this analytic behavior is enabled.
        /// </summary>
        /// <value><c>true</c> if enabled, otherwise <c>false</c>.</value>
        property bool IsEnabled;

        /// <summary>
        /// Gets or sets the friendly name of the analytic behavior.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the object line counter data used when <see cref="BehaviorType"/> is set to
        /// <see cref="AnalyticBehavior::AnalyticBehaviorType::ObjectLineCounter"/>.
        /// </summary>
        /// <value>The object line counter.</value>
        property ObjectLineCounter^ ObjectLineCounter;

        /// <summary>
        /// Gets or sets the type of object this analytic pertains to.
        /// </summary>
        /// <value>The analytic object type.</value>
        property AnalyticBehavior::AnalyticObjectType ObjectType;

        /// <summary>
        /// Gets or sets the object in zone data used to configure analytics of <see cref="BehaviorType"/> is set
        /// to <see cref="AnalyticBehavior::AnalyticBehaviorType::ObjectInZone"/>.
        /// </summary>
        /// <value>The object in zone.</value>
        property ObjectInZone^ ObjectInZone;

        /// <summary>
        /// Gets or sets the object wrong way zone data used to configure analytics of <see cref="BehaviorType"/> is set
        /// to <see cref="AnalyticBehavior::AnalyticBehaviorType::ObjectWrongWay"/>.
        /// </summary>
        /// <value>The object wrong way zone.</value>
        property ObjectWrongWayZone^ ObjectWrongWayZone;

        /// <summary>
        /// Gets or sets the severity value for events generated from this analytic behavior, from 1 (highest) to 10 (lowest).
        /// If set, overrides the corresponding situation severity.
        /// </summary>
        /// <value>The severity value.</value>
        property int Severity;
    };
}
#endif // NewAnalyticBehavior_h__
