// Declares the schedule class.
#ifndef Schedule_h__
#define Schedule_h__

#include "VxSdk.h"
#include "Utils.h"
#include "DataSource.h"
#include "NewScheduleTrigger.h"
#include "ScheduleTrigger.h"
#include "ResourceLimits.h"

namespace VxSdkNet {

    /// <summary>
    /// The Schedule class represents a recording schedule. A schedule is a group of 0 or more resources associated with a
    /// set of time and/or event based schedule triggers that, when any are active, cause the scheduled action to be performed.
    /// </summary>
    public ref class Schedule {
    public:

        /// <summary>
        /// Values that represent schedule recording actions.
        /// </summary>
        enum class Actions {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Record only the resource (associated with the Schedule) that was
            /// the source of the event causing the schedule trigger to activate.</summary>
            EventSourceRecord,

            /// <summary>Record all resources associated with the schedule.</summary>
            Record
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxSchedule">The vx schedule.</param>
        Schedule(VxSdk::IVxSchedule* vxSchedule);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Schedule() {
            this->!Schedule();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Schedule();

        /// <summary>
        /// Add a new schedule trigger to the schedule.
        /// </summary>
        /// <param name="newScheduleTrigger">The new schedule trigger to add.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the schedule trigger.</returns>
        VxSdkNet::Results::Value AddScheduleTrigger(VxSdkNet::NewScheduleTrigger^ newScheduleTrigger);

        /// <summary>
        /// Delete a schedule trigger from the schedule.  This will delete the schedule trigger from any other schedules as well.
        /// </summary>
        /// <param name="scheduleTrigger">The schedule trigger to delete.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the schedule trigger.</returns>
        VxSdkNet::Results::Value DeleteScheduleTrigger(VxSdkNet::ScheduleTrigger^ scheduleTrigger);

        /// <summary>
        /// Get the data sources linked to the schedule using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of data sources.</returns>
        System::Collections::Generic::List<DataSource^>^ GetLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Add data sources to the schedule.
        /// </summary>
        /// <param name="dataSources">A <c>List</c> containing the data sources to be added.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the data sources.</returns>
        Results::Value Link(System::Collections::Generic::List<DataSource^>^ dataSources);

        /// <summary>
        /// Update this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Delete existing data sources from the schedule.
        /// </summary>
        /// <param name="dataSources">A <c>List</c> containing the data sources to be deleted.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the data sources.</returns>
        Results::Value Unlink(System::Collections::Generic::List<DataSource^>^ dataSources);

        /// <summary>
        /// Gets or sets the action performed when the schedule is active.
        /// </summary>
        /// <value>The <see cref="Actions">Action</see>.</value>
        property Actions Action {
        public:
            Actions get() { return (Actions)_schedule->action; }
            void set(Actions value) { _schedule->SetAction((VxSdk::VxScheduleAction::Value)value); }
        }

        /// <summary>
        /// Gets the unique identifier of the schedule.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_schedule->id); }
        }

        /// <summary>
        /// Gets any limits related to this resource.
        /// </summary>
        /// <value>The limits related to this resource.</value>
        property ResourceLimits^ Limits {
        public:
            ResourceLimits^ get() { return _GetLimits(); }
        }

        /// <summary>
        /// Gets the data sources associated with this schedule.
        /// </summary>
        /// <value>A <c>List</c> of data sources.</value>
        property System::Collections::Generic::List<DataSource^>^ LinkedDataSources {
        public:
            System::Collections::Generic::List<DataSource^>^ get() { return GetLinkedDataSources(nullptr); }
        }

        /// <summary>
        /// Gets or sets the friendly name of the schedule.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_schedule->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _schedule->SetName(name);
            }
        }

        /// <summary>
        /// Gets the schedule triggers associated with this schedule.
        /// </summary>
        /// <value>The <c>List</c> of schedule triggers associated with this schedule.</value>
        property System::Collections::Generic::List<ScheduleTrigger^>^ ScheduleTriggers {
        public:
            System::Collections::Generic::List<ScheduleTrigger^>^ get() { return _GetScheduleTriggers(); }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the schedule applies to all data sources.
        /// </summary>
        /// <value><c>true</c> if this schedule applies to all data sources, <c>false</c> if not.</value>
        property bool UseAllDataSources {
        public:
            bool get() { return _schedule->useAllDataSources; }
            void set(bool value) { _schedule->SetUseAllDataSources(value); }
        }

    internal:
        VxSdk::IVxSchedule* _schedule;
        VxSdkNet::ResourceLimits^ _GetLimits();
        System::Collections::Generic::List<ScheduleTrigger^>^ _GetScheduleTriggers();
    };
}
#endif // Schedule_h__
