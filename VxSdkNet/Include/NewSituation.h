// Declares the new situation class.
#ifndef NewSituation_h__
#define NewSituation_h__

#include "Utils.h"
#include "Situation.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewSituation class represents a new situation configuration that specifies how
    /// corresponding events shall be generated and handled when the situation is detected.
    /// </summary>
    public ref class NewSituation {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewSituation() {
            SnoozeIntervals = gcnew System::Collections::Generic::List<int>();
        }

        /// <summary>
        /// Defaults this instance.
        /// </summary>
        void Default() {
            IsAckNeeded = false;
            ShouldAudiblyNotify = false;
            ShouldExpandBanner = true;
            ShouldLog = true;
            ShouldNotify = false;
            ShouldPopupBanner = true;
            AudibleLoopDelay = 0;
            AudiblePlayCount = 1;
            AutoAcknowledge = -1;
            Severity = 5;
            SnoozeIntervals = gcnew System::Collections::Generic::List<int>();
            SnoozeIntervals[0] = 60;
            SnoozeIntervals[1] = 300;
            SnoozeIntervals[2] = 600;
        }

        /// <summary>
        /// Gets or sets the seconds to wait between audible notifications.
        /// </summary>
        /// <value>The seconds between audible notifications.</value>
        property int AudibleLoopDelay;

        /// <summary>
        /// Gets or sets the amount of times to play audible notifications.
        /// </summary>
        /// <value>The amount of times to play audible notifications.</value>
        property int AudiblePlayCount;

        /// <summary>
        /// Gets or sets the number of seconds after which a generated event state will be set to AutoAcked. If less
        /// than 0, a generated event must be manually acknowledged. If 0, a generated event is set to AutoAcked immediately.
        /// </summary>
        /// <value>The number of seconds before auto-acknowledgement.</value>
        property int AutoAcknowledge;

        /// <summary>
        /// Gets or sets whether the generated events shall have an initial state of AckNeeded or NoAckNeeded.
        /// </summary>
        /// <value><c>true</c> if events will require acknowledgement, <c>false</c> if not.</value>
        property bool IsAckNeeded;

        /// <summary>
        /// Gets or sets the situation friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the severity of the generated event, from 1 (highest) to 10 (lowest).
        /// </summary>
        /// <value>The event severity.</value>
        property int Severity;

        /// <summary>
        /// Gets or sets whether a notification sound should play on supporting clients when an event is received.
        /// </summary>
        /// <value><c>true</c> if a notification sound should play, <c>false</c> if not.</value>
        property bool ShouldAudiblyNotify;

        /// <summary>
        /// Gets or sets whether the notification banner on clients should be expanded by default.
        /// </summary>
        /// <value><c>true</c> if the banner should be expanded, <c>false</c> if not.</value>
        property bool ShouldExpandBanner;

        /// <summary>
        /// Gets or sets whether events generated from this situation shall be persisted or immediately be discarded.
        /// </summary>
        /// <value><c>true</c> if events will be logged, <c>false</c> if not.</value>
        property bool ShouldLog;

        /// <summary>
        /// Gets or sets whether an event generated from the situation shall generate notifications.
        /// </summary>
        /// <value><c>true</c> if notifications will be sent, <c>false</c> if not.</value>
        property bool ShouldNotify;

        /// <summary>
        /// Gets or sets whether clients should display a popup notification banner when receiving events of this type.
        /// </summary>
        /// <value><c>true</c> if a banner should popup, <c>false</c> if not.</value>
        property bool ShouldPopupBanner;

        /// <summary>
        /// Gets or sets the default snooze intervals, in seconds, for a generated event.
        /// </summary>
        /// <value>A <c>List</c> of snooze intervals in seconds.</value>
        property System::Collections::Generic::List<int>^ SnoozeIntervals;

        /// <summary>
        /// Gets or sets the unique source identifier. This field acts an optional constraint on the source of
        /// events for this situation. If specified, any events matching the situation type must also match
        /// this SourceDeviceId in order for the situation to apply.
        /// </summary>
        /// <value>The unique source identifier.</value>
        property System::String^ SourceDeviceId;

        /// <summary>
        /// Gets or sets situation type.  The type must be of the form external/&lt;company&gt;/&lt;event&gt; where &lt;company&gt;
        /// and &lt;event&gt; are strings no greater than 64 characters each; forward slashes are not allowed. These strings
        /// describe the &lt;company&gt; that manufactured the device that was the source of the &lt;event&gt;.
        /// </summary>
        /// <value>The situation type.</value>
        property System::String^ Type;
    };
}
#endif // NewSituation_h__
