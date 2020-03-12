// Declares the new schedule trigger class.
#ifndef NewScheduleTrigger_h__
#define NewScheduleTrigger_h__

#include "Utils.h"
#include "Clip.h"
#include "TimeTable.h"
#include "ScheduleTrigger.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewScheduleTrigger class represents a new schedule trigger configuration that specifies a time
    /// range and an optional event that together act as a trigger to activate a schedule.
    /// </summary>
    public ref class NewScheduleTrigger {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewScheduleTrigger() {
            EventProperties = gcnew System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>();
        }

        /// <summary>
        /// Gets or sets the action performed when the schedule trigger activates.
        /// </summary>
        /// <value>The <see cref="ScheduleTrigger::Actions">Action</see>.</value>
        property ScheduleTrigger::Actions Action;

        /// <summary>
        /// Gets or sets the type of event that will activate the schedule trigger. If set, the schedule trigger is
        /// considered an "event" trigger, otherwise it is considered a "timed" trigger. If set, the schedule trigger
        /// only activates when this type of event occurs.
        /// <para>See <see cref="InactiveEventSituationType"/> for information on when the trigger will deactivate.</para>
        /// </summary>
        /// <value>The event situation type.</value>
        property System::String^ EventSituationType;

        /// <summary>
        /// Gets or sets the event properties that will activate the schedule.
        /// </summary>
        /// <value>A <c>List</c> containing the event properties.</value>
        property System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ EventProperties;

        /// <summary>
        /// Gets or sets the recording framerate level.
        /// </summary>
        /// <value>The framerate level.</value>
        property Clip::RecordingFramerates Framerate;

        /// <summary>
        /// Gets or sets the unique identifier of the schedule trigger.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets the type of event that will cause this schedule trigger to no longer be considered active. If
        /// set, the schedule trigger event state will no longer be considered active. If not set, the schedule trigger
        /// event status will immediately be considered inactive after event occurs.
        /// <para>NOTE: This property is ignored if <see cref="EventSituationType"/> is not set.</para>
        /// </summary>
        /// <value>The event situation type.</value>
        property System::String^ InactiveEventSituationType;

        /// <summary>
        /// Gets or sets the amount of time, from 0 to 300 seconds, to continue to consider the schedule trigger active when it becomes
        /// inactive ("post alarm").
        /// </summary>
        /// <value>The post trigger time in seconds.</value>
        property int PostTrigger;

        /// <summary>
        /// Gets or sets the amount of time, from 0 to 30 seconds, to consider the schedule trigger active prior to when it becomes active
        /// ("pre alarm").
        /// </summary>
        /// <value>The pre trigger time in seconds.</value>
        property int PreTrigger;

        /// <summary>
        /// Gets or sets the amount of time, from 1 to 300 seconds, to consider the schedule trigger active immediately after it becomes
        /// active ("duration recording").
        /// </summary>
        /// <value>The timeout in seconds.</value>
        property int Timeout;

        /// <summary>
        /// Gets or sets the unique identifier of the time table assigned to the schedule trigger, if any.
        /// </summary>
        /// <value>The unique time table identifier, if any.</value>
        property System::String^ TimeTableId;
    };
}
#endif // NewScheduleTrigger_h__
