// Declares the time range class.
#ifndef TimeRange_h__
#define TimeRange_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The TimeRange class represents a range of time, specified by three mandatory fields.  If the start time
    /// is greater than the end time, the range will be inactive.
    /// </summary>
    public ref class TimeRange {
    public:
        /// <summary>
        /// Values that represent days of the week.
        /// </summary>
        enum class DayOfWeek {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Monday.</summary>
            Monday,

            /// <summary>Tuesday.</summary>
            Tuesday,

            /// <summary>Wednesday.</summary>
            Wednesday,

            /// <summary>Thursday.</summary>
            Thursday,

            /// <summary>Friday.</summary>
            Friday,

            /// <summary>Saturday.</summary>
            Saturday,

            /// <summary>Sunday.</summary>
            Sunday
        };

    public:
        /// <summary>
        /// Constructor.
        /// </summary>
        TimeRange() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxTimeRange">The time range.</param>
        TimeRange(VxSdk::VxTimeRange* vxTimeRange) {
            Day = DayOfWeek(vxTimeRange->day);
            EndTime = Utils::ConvertTimeCharToDateTime(vxTimeRange->endTime);
            StartTime = Utils::ConvertTimeCharToDateTime(vxTimeRange->startTime);
        }

        /// <summary>
        /// Gets or sets the day of the week that this time range applies to.
        /// </summary>
        /// <value>The day of the week.</value>
        property DayOfWeek Day;

        /// <summary>
        /// Gets or sets the time at which this range ends (inclusive).
        /// </summary>
        /// <value>The end time.</value>
        property System::DateTime EndTime;

        /// <summary>
        /// Gets or sets the time at which this range begins (inclusive).
        /// </summary>
        /// <value>The start time.</value>
        property System::DateTime StartTime;
    };
}
#endif // TimeRange_h__