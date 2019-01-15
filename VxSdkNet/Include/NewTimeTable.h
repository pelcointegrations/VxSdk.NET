// Declares the new time table class.
#ifndef NewTimeTable_h__
#define NewTimeTable_h__

#include "TimeTable.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewTimeTable class represents a new time table.
    /// </summary>
    public ref class NewTimeTable {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewTimeTable() {
            WeeklyTimeRanges = gcnew System::Collections::Generic::List<TimeRange^>();
        }

        /// <summary>
        /// Gets or sets the end date of the time table, it will be considered inactive after this date.
        /// </summary>
        /// <value>The end date.</value>
        property System::DateTime EndDate;

        /// <summary>
        /// Gets or sets the unique identifier of the time table.
        /// </summary>
        /// <value>The unique identifier of the time table.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets the friendly name of the time table.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the start date of the time table, it will be considered active after this date.
        /// </summary>
        /// <value>The start date.</value>
        property System::DateTime StartDate;

        /// <summary>
        /// Gets or sets the active time ranges for this time table.
        /// </summary>
        /// <value>The active time ranges.</value>
        property System::Collections::Generic::List<TimeRange^>^ WeeklyTimeRanges;
    };
}
#endif // NewTimeTable_h__
