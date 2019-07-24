// Declares the time table class.
#ifndef TimeTable_h__
#define TimeTable_h__

#include "VxSdk.h"
#include "Utils.h"
#include "TimeRange.h"

namespace VxSdkNet {

    /// <summary>
    /// The TimeTable class represents a named set of time ranges.
    /// </summary>
    public ref class TimeTable {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxTimeTable">The vx time table.</param>
        TimeTable(VxSdk::IVxTimeTable* vxTimeTable);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~TimeTable() {
            this->!TimeTable();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !TimeTable();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets or sets the end date of the time table, it will be considered inactive after this date.
        /// </summary>
        /// <value>The end date.</value>
        property System::DateTime EndDate {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_timeTable->endDate); }
            void set(System::DateTime value) {
                std::string val = Utils::ConvertCSharpDateTime(value);
                char* endValue = nullptr;
                if (value != System::DateTime::MinValue)
                    endValue = (char*)val.c_str();

                _timeTable->SetEndDate(endValue);
            }
        }

        /// <summary>
        /// Gets the unique bookmark identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_timeTable->id); }
        }

        /// <summary>
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_timeTable->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _timeTable->SetName(name);
            }
        }

        /// <summary>
        /// Gets or sets the start date of the time table, it will be considered active after this date.
        /// </summary>
        /// <value>The start date.</value>
        property System::DateTime StartDate {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_timeTable->startDate); }
            void set(System::DateTime value) {
                std::string val = Utils::ConvertCSharpDateTime(value);
                char* startValue = nullptr;
                if (value != System::DateTime::MinValue)
                    startValue = (char*)val.c_str();

                _timeTable->SetStartDate(startValue);
            }
        }

        /// <summary>
        /// Gets or sets the active time ranges for this time table.
        /// </summary>
        /// <value>The active time ranges.</value>
        property System::Collections::Generic::List<TimeRange^>^ WeeklyTimeRanges {
        public:
            System::Collections::Generic::List<TimeRange^>^ get() { return _GetWeeklyTimeRanges(); }
            void set(System::Collections::Generic::List<TimeRange^>^ value) { _SetWeeklyTimeRanges(value); }
        }

    internal:
        VxSdk::IVxTimeTable* _timeTable;
        System::Collections::Generic::List<TimeRange^>^ _GetWeeklyTimeRanges();
        Results::Value _SetWeeklyTimeRanges(System::Collections::Generic::List<TimeRange^>^ timeRangeList);
    };
}
#endif // TimeTable_h__
