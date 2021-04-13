// Declares the situation class.
#ifndef Situation_h__
#define Situation_h__

#include "VxSdk.h"
#include "Device.h"
#include "NewNotification.h"

namespace VxSdkNet {

    /// <summary>
    /// The Situation class represents a particular situation configuration that specifies
    /// how corresponding events shall be generated and handled when the situation is detected.
    /// </summary>
    public ref class Situation {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxSituation">The situation.</param>
        Situation(VxSdk::IVxSituation* vxSituation);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Situation() {
            this->!Situation();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Situation();

        /// <summary>
        /// Add a new notification to the list of notifications that this situation serves.
        /// </summary>
        /// <param name="newNotification">The new notification to be added to the situation.</param>
        /// <returns><c>nullptr</c> if it fails, else the new notification.</returns>
        Notification^ AddNotification(NewNotification^ newNotification);

        /// <summary>
        /// Deletes the custom audio file.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the custom audio file.</returns>
        Results::Value DeleteAudioFile();

        /// <summary>
        /// Gets the custom audio file uri, if any.
        /// </summary>
        /// <returns>The audio file uri.</returns>
        System::String^ GetAudioFileUri();

        /// <summary>
        /// Get the data sources associated with this situation using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of data sources.</returns>
        System::Collections::Generic::List<DataSource^>^ GetLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the devices associated with this situation using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of devices.</returns>
        System::Collections::Generic::List<Device^>^ GetLinkedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the notifications configured for this situation using an optional collection filter.
        /// <para>Available filters: ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of notifications.</returns>
        System::Collections::Generic::List<Notification^>^ GetNotifications(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Associate a data source with this situation.
        /// </summary>
        /// <param name="dataSource">The data source to associate the situation with.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of linking the data source.</returns>
        Results::Value Link(DataSource^ dataSource);

        /// <summary>
        /// Associate a device with this situation.
        /// </summary>
        /// <param name="device">The device to associate the situation with.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of linking the device.</returns>
        Results::Value Link(Device^ device);

        /// <summary>
        /// Update this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Removes a notification from the list of notifications that this situation serves.
        /// </summary>
        /// <param name="notification">The notification to be removed.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the notification.</returns>
        Results::Value RemoveNotification(Notification^ notification);

        /// <summary>
        /// Sets the custom audio file used by clients for audible notifications. The maximum allowable size
        /// of the file is 5 MB.
        /// </summary>
        /// <param name="audioFilePath">The local path to the audio file.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the audio file.</returns>
        Results::Value SetAudioFile(System::String^ audioFilePath);

        /// <summary>
        /// Remove device association from this situation.
        /// </summary>
        /// <param name="device">The device to remove association with.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of unlinking the device.</returns>
        Results::Value UnLink(Device^ device);

        /// <summary>
        /// Remove data source association from this situation.
        /// </summary>
        /// <param name="dataSource">The data source to remove association with.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of unlinking the data source.</returns>
        Results::Value UnLink(DataSource^ dataSource);

        /// <summary>
        /// Gets or sets the seconds to wait between audible notifications.
        /// </summary>
        /// <value>The seconds between audible notifications.</value>
        property int AudibleLoopDelay {
        public:
            int get() { return _situation->audibleLoopDelay; }
            void set(int value) { _situation->SetAudibleLoopDelay(value); }
        }

        /// <summary>
        /// Gets or sets the amount of times to play audible notifications.
        /// </summary>
        /// <value>The amount of times to play audible notifications.</value>
        property int AudiblePlayCount {
        public:
            int get() { return _situation->audiblePlayCount; }
            void set(int value) { _situation->SetAudiblePlayCount(value); }
        }

        /// <summary>
        /// Gets or sets the number of seconds after which a generated event state will be set to AutoAcked.
        /// </summary>
        /// <value>The number of seconds before auto-acknowledgement.</value>
        property int AutoAcknowledge {
        public:
            int get() { return _situation->autoAcknowledgeTime; }
            void set(int value) { _situation->SetAutoAcknowledgeTime(value); }
        }

        /// <summary>
        /// Gets or sets whether the generated events shall have an initial state of AckNeeded or NoAckNeeded.
        /// </summary>
        /// <value><c>true</c> if events will require acknowledgement, <c>false</c> if not.</value>
        property bool IsAckNeeded {
        public:
            bool get() { return _situation->isAckNeeded; }
            void set(bool value) { _situation->SetAckNeeded(value); }
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
        /// Gets the data sources associated with this situation.
        /// </summary>
        /// <value>A <c>List</c> of data sources.</value>
        property System::Collections::Generic::List<DataSource^>^ LinkedDataSources {
        public:
            System::Collections::Generic::List<DataSource^>^ get() { return GetLinkedDataSources(nullptr); }
        }

        /// <summary>
        /// Gets the devices associated with this situation.
        /// </summary>
        /// <value>A <c>List</c> of devices.</value>
        property System::Collections::Generic::List<Device^>^ LinkedDevices {
        public:
            System::Collections::Generic::List<Device^>^ get() { return GetLinkedDevices(nullptr); }
        }

        /// <summary>
        /// Gets or sets the situation friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_situation->name); }
            void set(System::String^ value) {
                char name[MAX_SITUATION_NAME_LENGTH];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _situation->SetName(name);
            }
        }

        /// <summary>
        /// Gets the notifications configured for this situation.
        /// </summary>
        /// <value>A <c>List</c> of notifications.</value>
        property System::Collections::Generic::List<Notification^>^ Notifications {
        public:
            System::Collections::Generic::List<Notification^>^ get() { return GetNotifications(nullptr); }
        }

        /// <summary>
        /// Gets the name of the key in the properties map corresponding to the service identifier for the source of this situation, if any.
        /// </summary>
        /// <value>The service property identifier for the source of this situation.</value>
        property System::String^ ServicePropertyId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_situation->servicePropertyId); }
        }

        /// <summary>
        /// Gets the resource type of the service corresponding to the source of this situation, if any.
        /// </summary>
        /// <value>The service type for the source of this situation.</value>
        property System::String^ ServiceType {
        public:
            System::String^ get() { return Utils::ConvertCppString(_situation->serviceType); }
        }

        /// <summary>
        /// Gets or sets the severity of the generated event, from 1 (highest) to 10 (lowest).
        /// </summary>
        /// <value>The event severity.</value>
        property int Severity {
        public:
            int get() { return _situation->severity; }
            void set(int value) { _situation->SetSeverity(value); }
        }

        /// <summary>
        /// Gets or sets whether a notification sound should play on supporting clients when an event is received.
        /// </summary>
        /// <value><c>true</c> if audio should play on event notification, <c>false</c> if not.</value>
        property bool ShouldAudiblyNotify {
        public:
            bool get() { return _situation->shouldAudiblyNotify; }
            void set(bool value) { _situation->SetAudiblyNotify(value); }
        }

        /// <summary>
        /// Gets or sets whether the notification banner on clients should be expanded by default.
        /// </summary>
        /// <value><c>true</c> if the banner should be expanded, <c>false</c> if not.</value>
        property bool ShouldExpandBanner {
        public:
            bool get() { return _situation->shouldExpandBanner; }
            void set(bool value) { _situation->SetExpandBanner(value); }
        }

        /// <summary>
        /// Gets or sets whether events generated from this situation shall be persisted or immediately be discarded.
        /// </summary>
        /// <value><c>true</c> if events will be logged, <c>false</c> if not.</value>
        property bool ShouldLog {
        public:
            bool get() { return _situation->shouldLog; }
            void set(bool value) { _situation->SetLog(value); }
        }

        /// <summary>
        /// Gets or sets whether an event generated from the situation shall generate notifications.
        /// </summary>
        /// <value><c>true</c> if notifications will be sent, <c>false</c> if not.</value>
        property bool ShouldNotify {
        public:
            bool get() { return _situation->shouldNotify; }
            void set(bool value) { _situation->SetNotify(value); }
        }

        /// <summary>
        /// Gets or sets whether clients should display a popup notification banner when receiving events of this type.
        /// </summary>
        /// <value><c>true</c> if a banner should popup, <c>false</c> if not.</value>
        property bool ShouldPopupBanner {
        public:
            bool get() { return _situation->shouldPopupBanner; }
            void set(bool value) { _situation->SetPopupBanner(value); }
        }

        /// <summary>
        /// Gets or sets the default snooze intervals, in seconds, for a generated event.
        /// </summary>
        /// <value>A <c>List</c> of snooze intervals in seconds.</value>
        property System::Collections::Generic::List<int>^ SnoozeIntervals {
        public:
            System::Collections::Generic::List<int>^ get() { return _GetSnoozeIntervals(); }
            void set(System::Collections::Generic::List<int>^ value) {
                int snoozeIntervalSize = value->Count;
                int* snoozeIntervals = new int[snoozeIntervalSize];
                for (int i = 0; i < snoozeIntervalSize; i++)
                    snoozeIntervals[i] = value[i];

                _situation->SetSnoozeIntervals(snoozeIntervals, snoozeIntervalSize);
            }
        }

        /// <summary>
        /// Gets the unique source identifier.
        /// </summary>
        /// <value>The unique source identifier.</value>
        property System::String^ SourceDeviceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_situation->sourceDeviceId); }
        }

        /// <summary>
        /// Gets a list of device types that may be the source of events for this situation.
        /// </summary>
        /// <value>A <c>List</c> of device types.</value>
        property System::Collections::Generic::List<Device::Types>^ SourceDeviceTypes {
        public:
            System::Collections::Generic::List<Device::Types>^ get() {
                System::Collections::Generic::List<Device::Types>^ mlist = gcnew System::Collections::Generic::List<Device::Types>();
                for (int i = 0; i < _situation->sourceDeviceTypesSize; i++)
                    mlist->Add((Device::Types)_situation->sourceDeviceTypes[i]);

                return mlist;
            }
        }

        /// <summary>
        /// Gets the situation type.
        /// </summary>
        /// <value>The situation type.</value>
        property System::String^ Type {
        public:
            System::String^ get() { return Utils::ConvertCppString(_situation->type); }
        }

        /// <summary>
        /// Gets the situation type opposite of this situation, if any.
        /// </summary>
        /// <value>The opposite situation type.</value>
        property System::String^ TypeOpposite {
        public:
            System::String^ get() { return Utils::ConvertCppString(_situation->typeOpposite); }
        }

    internal:
        VxSdk::IVxSituation* _situation;
        VxSdkNet::ResourceLimits^ _GetLimits();
        System::Collections::Generic::List<int>^ _GetSnoozeIntervals();
    };
}
#endif // Situation_h__
