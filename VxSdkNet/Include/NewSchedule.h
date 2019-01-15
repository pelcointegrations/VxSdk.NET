// Declares the new schedule class.
#ifndef NewSchedule_h__
#define NewSchedule_h__

#include "Schedule.h"
#include "NewScheduleTrigger.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewSchedule class represents a new schedule.
    /// </summary>
    public ref class NewSchedule {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewSchedule() {
            ScheduleTriggers = gcnew System::Collections::Generic::List<NewScheduleTrigger^>();
        }

        /// <summary>
        /// Gets or sets the event action to use for the schedule.
        /// </summary>
        /// <value>The event <see cref="Schedule::Actions">Action</see>.</value>
        property Schedule::Actions Action;

        /// <summary>
        /// Gets or sets the unique schedule identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets the friendly name of the schedule.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets the triggers that shall be included in this schedule.
        /// </summary>
        /// <value>A <c>List</c> of triggers included in the schedule.</value>
        property System::Collections::Generic::List<NewScheduleTrigger^>^ ScheduleTriggers;

        /// <summary>
        /// Gets or sets whether the schedule will apply to all data sources regardless of what data sources are linked to
        /// the schedule.
        /// </summary>
        /// <value><c>true</c> if the schedule will apply to all data sources, <c>false</c> if not.</value>
        property bool UseAllDataSources;
    };
}
#endif // NewSchedule_h__
