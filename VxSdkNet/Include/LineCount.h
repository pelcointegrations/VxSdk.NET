// Declares the line count class.
#ifndef LineCount_h__
#define LineCount_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The LineCount class represents line counting information based on a line counting request. A line count is the
    /// number of times an identified object has crossed a configured object line counter within an interval specified
    /// in the line counting request.
    /// </summary>
    public ref class LineCount {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxLineCount">The line count.</param>
        LineCount(VxSdk::VxLineCount* vxLineCount){
            AnalyticBehaviorId = Utils::ConvertCppString(vxLineCount->analyticBehaviorId);
            EndTime = Utils::ConvertCppDateTime(vxLineCount->endTime);
            StartTime = Utils::ConvertCppDateTime(vxLineCount->startTime);
            Count = vxLineCount->count;
            CountCorrection = vxLineCount->countCorrection;
            InCount = vxLineCount->inCount;
            InCountCorrection = vxLineCount->inCountCorrection;
            OutCount = vxLineCount->outCount;
            OutCountCorrection = vxLineCount->outCountCorrection;
        }

        /// <summary>
        /// Gets the unique identifier of the analytic behavior this line count information is for.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ AnalyticBehaviorId;

        /// <summary>
        /// Gets the summarized line counter value for uni-directional and omni-directional counter types.
        /// </summary>
        /// <value>The summarized line counter value.</value>
        property int Count;

        /// <summary>
        /// Gets the correction value for the <see cref="Count"/> of uni-directional and omni-directional counter types.
        /// </summary>
        /// <value>The correction value.</value>
        property int CountCorrection;

        /// <summary>
        /// Gets the end time of the line count interval.
        /// </summary>
        /// <value>The end time.</value>
        property System::DateTime EndTime;

        /// <summary>
        /// Gets the summarized in line counter value for bi-directional counter types.
        /// </summary>
        /// <value>The summarized in line counter value.</value>
        property int InCount;

        /// <summary>
        /// Gets the correction value for the <see cref="InCount"/> of bi-directional counter types.
        /// </summary>
        /// <value>The correction value.</value>
        property int InCountCorrection;

        /// <summary>
        /// Gets the summarized out line counter value for bi-directional counter types.
        /// </summary>
        /// <value>The summarized out line counter value.</value>
        property int OutCount;

        /// <summary>
        /// Gets the correction value for the <see cref="OutCount"/> of bi-directional counter types.
        /// </summary>
        /// <value>The correction value.</value>
        property int OutCountCorrection;

        /// <summary>
        /// Gets the start time of the line count interval.
        /// </summary>
        /// <value>The start time.</value>
        property System::DateTime StartTime;
    };
}
#endif // LineCount_h__
