/// <summary>
/// Implements the time table class.
/// </summary>
#include "TimeTable.h"

using namespace System::Collections::Generic;

VxSdkNet::TimeTable::TimeTable(VxSdk::IVxTimeTable* vxTimeTable) {
    _timeTable = vxTimeTable;
}

VxSdkNet::TimeTable::!TimeTable() {
    _timeTable->Delete();
    _timeTable = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::TimeTable::Refresh() {
    return (VxSdkNet::Results::Value)_timeTable->Refresh();
}

System::Collections::Generic::List<VxSdkNet::TimeRange^>^ VxSdkNet::TimeTable::_GetWeeklyTimeRanges() {
    // Create a list of managed time range objects
    List<VxSdkNet::TimeRange^>^ mlist = gcnew List<VxSdkNet::TimeRange^>();
    // Add each time range to the list
    for (int i = 0; i < _timeTable->weeklyTimeRangeSize; i++)
        mlist->Add(gcnew VxSdkNet::TimeRange(_timeTable->weeklyTimeRanges[i]));

    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::TimeTable::_SetWeeklyTimeRanges(System::Collections::Generic::List<VxSdkNet::TimeRange^>^ timeRangeList) {
    // Create a new array of VxTimeRange objects using the info contained in timeRangeList
    const int timeRangeListSize = timeRangeList->Count;
    VxSdk::VxTimeRange** timeRanges = nullptr;
    if (timeRangeListSize > 0) {
        timeRanges = new VxSdk::VxTimeRange*[timeRangeListSize];
        for (int i = 0; i < timeRangeListSize; i++) {
            timeRanges[i] = new VxSdk::VxTimeRange();
            timeRanges[i]->day = (VxSdk::VxDayOfWeek::Value)timeRangeList[i]->Day;
            VxSdk::Utilities::StrCopySafe(timeRanges[i]->startTime, Utils::ConvertCSharpTime(timeRangeList[i]->StartTime).c_str());
            VxSdk::Utilities::StrCopySafe(timeRanges[i]->endTime, Utils::ConvertCSharpTime(timeRangeList[i]->EndTime).c_str());
        }
    }
    // Attempt to set the weekly time ranges and return the result
    VxSdkNet::Results::Value result = (VxSdkNet::Results::Value)_timeTable->SetWeeklyTimeRanges(timeRanges, timeRangeListSize);
    for (int i = 0; i < timeRangeListSize; i++) {
        delete[] timeRanges[i];
    }

    delete[] timeRanges;
    timeRanges = nullptr;

    return result;
}
