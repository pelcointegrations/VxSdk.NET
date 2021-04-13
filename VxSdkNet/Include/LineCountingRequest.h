// Declares the line counting request class.
#ifndef LineCountingRequest_h__
#define LineCountingRequest_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The LineCountingRequest class represents a request for line count values.
    /// </summary>
    public ref class LineCountingRequest {
    public:

        /// <summary>
        /// Values that represent a definite length of time.
        /// </summary>
        enum class  TimeInterval {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>A time interval of one day.</summary>
            Day,
            /// <summary>A time interval of one hour.</summary>
            Hour,
            /// <summary>A time interval of one month.</summary>
            Month
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        LineCountingRequest() {
            AnalyticBehaviorIds = gcnew System::Collections::Generic::List<System::String^>();
        }

        /// <summary>
        /// Gets or sets the list of unique identifiers of the analytic behaviors to report line counters for.
        /// </summary>
        /// <value>The list of unique identifiers.</value>
        property System::Collections::Generic::List<System::String^>^ AnalyticBehaviorIds;

        /// <summary>
        /// Gets or sets the end time of the line count interval. If not specified, the current time will be used.
        /// </summary>
        /// <value>The end time.</value>
        property System::DateTime EndTime;

        /// <summary>
        /// Gets or sets the summarization interval to use for the counter values.
        /// </summary>
        /// <value>The summarization interval.</value>
        property TimeInterval Interval;

        /// <summary>
        /// Gets or sets the start time of the line count interval.
        /// </summary>
        /// <value>The start time.</value>
        property System::DateTime StartTime;
    };
}
#endif // LineCountingRequest_h__
