// Declares the object line counter class.
#ifndef ObjectLineCounter_h__
#define ObjectLineCounter_h__

#include "VxSdk.h"
#include "Utils.h"
#include "GridPoint.h"

namespace VxSdkNet {

    /// <summary>
    /// The ObjectLineCounter class represents the data for an analytic object line counter.
    /// </summary>
    public ref class ObjectLineCounter {
    public:
        /// <summary>
        /// The type of ObjectLineCounter.
        /// </summary>
        enum class LineCounterTypes {
            Unknown,
            Unidirectional,
            Bidirectional,
            Omnidirectional
        };

    public:
        /// <summary>
        /// Default constructor.
        /// </summary>
        ObjectLineCounter() {
            EndPoint = gcnew GridPoint();
            StartPoint = gcnew GridPoint();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxObjectLineCounter">The vx object line counter.</param>
        ObjectLineCounter(VxSdk::VxObjectLineCounter* vxObjectLineCounter){
            EndPoint = gcnew GridPoint(&vxObjectLineCounter->endPoint);
            StartPoint = gcnew GridPoint(&vxObjectLineCounter->startPoint);
            EventWindowSecs = vxObjectLineCounter->eventWindowSecs;
            MaxCountThreshold = vxObjectLineCounter->maxCountThreshold;
            EventsEnabled = vxObjectLineCounter->eventsEnabled;
            LeftCountLabel = Utils::ConvertCppString(vxObjectLineCounter->leftCountLabel);
            RightCountLabel = Utils::ConvertCppString(vxObjectLineCounter->rightCountLabel);
            LineCounterType = (LineCounterTypes)vxObjectLineCounter->lineCounterType;
        }

        /// <summary>
        /// Gets or sets the ending coordinate for the object counting line.
        /// </summary>
        /// <value>The ending coordinate.</value>
        property GridPoint^ EndPoint;

        /// <summary>
        /// Gets or sets whether line counter specific events for this line counter are enabled.
        /// </summary>
        property bool EventsEnabled;

        /// <summary>
        /// Gets or sets the event’s time window for testing if the counts maximum 
        /// threshold is met within this window. For example, if max count threshold = 100 
        /// and event_window_secs = 3600 then an event would be generated if 100 objects cross 
        /// a counting line over the last hour. Once the hour elapses the event trigger’s base 
        /// count is reset and the count window slides to the next hour and starts over. Ignored 
        /// if max count threshold is not set.
        /// </summary>
        property int EventWindowSecs;

        /// <summary>
        /// Gets or sets the friendly name associated with a bidirectional counter’s left count.
        /// </summary>
        property System::String^ LeftCountLabel;

        /// <summary>
        /// Gets or sets the type of line counter (i.e. unidirectional, bidirectional, 
        /// or omnidirectional). The type defines how the line counter increments 
        /// and maintains it’s counts.
        /// </summary>
        property LineCounterTypes LineCounterType;

        /// <summary>
        /// Gets or sets the maximum count threshold that must be met before an event is triggered. This
        /// value is used by both the bidirectional capacity events and the sliding window events
        /// </summary>
        property int MaxCountThreshold;

        /// <summary>
        /// Gets or sets the friendly name associated with a bidirectional counter’s right count.
        /// </summary>
        property System::String^ RightCountLabel;

        /// <summary>
        /// Gets or sets the starting coordinate for the object counting line.
        /// </summary>
        /// <value>The starting coordinate.</value>
        property GridPoint^ StartPoint;
    };
}
#endif // ObjectLineCounter_h__
