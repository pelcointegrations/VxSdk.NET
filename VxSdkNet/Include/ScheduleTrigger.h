// Declares the schedule trigger class.
#ifndef ScheduleTrigger_h__
#define ScheduleTrigger_h__

#include "VxSdk.h"
#include "Clip.h"

namespace VxSdkNet {

    /// <summary>
    /// The Situation class represents a schedule trigger. A schedule trigger is a time range and an optional
    /// event that together act as a trigger to activate a schedule and cause it to perform its configured action.
    /// </summary>
    public ref class ScheduleTrigger {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxScheduleTrigger">The schedule trigger.</param>
        ScheduleTrigger(VxSdk::IVxScheduleTrigger* vxScheduleTrigger);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~ScheduleTrigger() {
            this->!ScheduleTrigger();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !ScheduleTrigger();

        /// <summary>
        /// Update this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets or sets the type of event that will activate the schedule trigger, if any.
        /// </summary>
        /// <value>The event situation type.</value>
        property System::String^ EventSituationType {
        public:
             System::String^ get() { return gcnew  System::String(_scheduleTrigger->eventSituationType); }
            void set( System::String^ value) { VxSdk::Utilities::StrCopySafe(_scheduleTrigger->eventSituationType, Utils::ConvertCSharpString(value).c_str()); }
        }

        /// <summary>
        /// Gets or sets the event properties that will activate the schedule.
        /// </summary>
        /// <value>A <c>List</c> containing the event properties.</value>
        property System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ EventProperties {
        public:
            System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ get() {
                System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ mList =
                    gcnew System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>();

                for (int i = 0; i < _scheduleTrigger->eventPropertySize; i++)
                {
                    System::Collections::Generic::KeyValuePair<System::String^, System::String^> kvPair(Utils::ConvertCppString(_scheduleTrigger->eventProperties[i]->key),
                        Utils::ConvertCppString(_scheduleTrigger->eventProperties[i]->value));

                    mList->Add(kvPair);
                }

                return mList;
            }
            void set(System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ value) {
                int size = value->Count;
                VxSdk::VxKvObject *kvObj = new VxSdk::VxKvObject[size];
                for (int i = 0; i < size; i++) {
                    VxSdk::Utilities::StrCopySafe(kvObj[i].key, Utils::ConvertCSharpString(value[i].Key).c_str());
                    VxSdk::Utilities::StrCopySafe(kvObj[i].value, Utils::ConvertCSharpString(value[i].Value).c_str());
                }

                _scheduleTrigger->SetEventProperties(kvObj, size);
                delete[] kvObj;
                kvObj = nullptr;
            }
        }

        /// <summary>
        /// Gets or sets the recording framerate level.
        /// </summary>
        /// <value>The framerate level.</value>
        property Clip::RecordingFramerates Framerate {
        public:
            Clip::RecordingFramerates get() { return Clip::RecordingFramerates(_scheduleTrigger->framerate); }
            void set(Clip::RecordingFramerates value) { _scheduleTrigger->SetFramerate((VxSdk::VxRecordingFramerate::Value)value); }
        }

        /// <summary>
        /// Gets the unique identifier of the schedule trigger.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_scheduleTrigger->id); }
        }

        /// <summary>
        /// Gets or sets the amount of time, from 0 to 300 seconds, to continue to consider the schedule trigger active when it becomes
        /// inactive ("post alarm").
        /// </summary>
        /// <value>The post trigger time in seconds.</value>
        property int PostTrigger {
        public:
            int get() { return _scheduleTrigger->postTrigger; }
            void set(int value) { _scheduleTrigger->SetPostTrigger(value); }
        }

        /// <summary>
        /// Gets or sets the amount of time, from 0 to 30 seconds, to consider the schedule trigger active prior to when it becomes active
        /// ("pre alarm").
        /// </summary>
        /// <value>The pre trigger time in seconds.</value>
        property int PreTrigger {
        public:
            int get() { return _scheduleTrigger->preTrigger; }
            void set(int value) { _scheduleTrigger->SetPreTrigger(value); }
        }

        /// <summary>
        /// Gets or sets the amount of time, from 1 to 300 seconds, to consider the schedule trigger active immediately after it becomes
        /// active ("duration recording").
        /// </summary>
        /// <value>The timeout in seconds.</value>
        property int Timeout {
        public:
            int get() { return _scheduleTrigger->timeout; }
            void set(int value) { _scheduleTrigger->SetTimeout(value); }
        }

        /// <summary>
        /// Gets or sets the unique identifier of the time table assigned to the schedule trigger, if any.
        /// </summary>
        /// <value>The unique time table identifier, if any.</value>
        property System::String^ TimeTableId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_scheduleTrigger->timeTableId); }
            void set(System::String^ value) { VxSdk::Utilities::StrCopySafe(_scheduleTrigger->timeTableId, Utils::ConvertCSharpString(value).c_str()); }
        }

    internal:
        VxSdk::IVxScheduleTrigger* _scheduleTrigger;
    };
}
#endif // ScheduleTrigger_h__
