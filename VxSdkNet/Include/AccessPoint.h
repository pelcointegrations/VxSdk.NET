// Declares the access point class.
#ifndef AccessPoint_h__
#define AccessPoint_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ResourceRel.h"
#include "ResourceLimits.h"

namespace VxSdkNet {
    ref class Device;

    /// <summary>
    /// The AccessPoint class represents an access control service (e.g. a door control
    /// or badge reader), typically hosted by an access controller <see cref="Device"/>.
    /// </summary>
    public ref class AccessPoint {
    public:

        /// <summary>
        /// Values that represent a particular type of access point.
        /// </summary>
        enum class AccessPointType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>A door.</summary>
            Door,

            /// <summary>A door with a reader.</summary>
            DoorWithReader,

            /// <summary>A gate.</summary>
            Gate
        };

        /// <summary>
        /// Values that represent possible statuses for an access point.
        /// </summary>
        enum class AccessStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The access point is closed.</summary>
            Closed,

            /// <summary>The access point has faulted.</summary>
            Faulted,

            /// <summary>The access point has been forced.</summary>
            Forced,

            /// <summary>The access point is locked.</summary>
            Locked,

            /// <summary>The access point is open.</summary>
            Opened,

            /// <summary>The access point has been propped.</summary>
            Propped,

            /// <summary>The access point is unlocked.</summary>
            Unlocked
        };

        /// <summary>
        /// Values that represent the operational state of a device.
        /// </summary>
        enum class DeviceStates {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The device is offline.</summary>
            Offline,

            /// <summary>The device is online.</summary>
            Online
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxAccessPoint">The vx access point.</param>
        AccessPoint(VxSdk::IVxAccessPoint* vxAccessPoint);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~AccessPoint() {
            this->!AccessPoint();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !AccessPoint();

        /// <summary>
        /// Gets all possible resource relations for this access point (both linked and non-linked). Each linked
        /// resource shall be considered to be related to this access point.
        /// <para>Available filters: kAdvancedQuery, kAllTags, kAllPrivateTags, kLinked.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of related resources.</returns>
        System::Collections::Generic::List<ResourceRel^>^ GetRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Locks the access point for the given amount of time (in seconds).
        /// </summary>
        /// <param name="seconds">The lock time (in seconds). If 0, stay locked indefinitely.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of disabling this access point.</returns>
        Results::Value Lock(int seconds);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Unlocks the access point for the given amount of time (in seconds).
        /// </summary>
        /// <param name="seconds">The unlock time (in seconds). If 0, stay unlocked indefinitely.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of disabling this access point.</returns>
        Results::Value Unlock(int seconds);

        /// <summary>
        /// Gets the device that hosts this access point.
        /// </summary>
        /// <value>The host device.</value>
        property VxSdkNet::Device^ HostDevice {
        public:
            VxSdkNet::Device^ get() { return _GetHostDevice(); }
        }

        /// <summary>
        /// Gets the unique access point identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_accessPoint->id); }
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
        /// Gets all possible resource relations for this access point (both linked and non-linked). Each linked resource shall be considered to be related to this access point.
        /// </summary>
        /// <value>A <c>List</c> of linked resource relations.</value>
        property System::Collections::Generic::List<ResourceRel^>^ LinkedRelations {
        public:
            System::Collections::Generic::List<ResourceRel^>^ get() {
                System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filter = gcnew System::Collections::Generic::Dictionary<Filters::Value, System::String^>();
                filter->Add(Filters::Value::Linked, "true");
                return GetRelations(filter);
            }
        }

        /// <summary>
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_accessPoint->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _accessPoint->SetName(name);
            }
        }

        /// <summary>
        /// Gets the current operational state of the access point.
        /// </summary>
        /// <value>The access point state.</value>
        property DeviceStates State {
        public:
            DeviceStates get() { return (DeviceStates)_accessPoint->state; }
        }

        /// <summary>
        /// Gets a list of the current access point statuses.
        /// </summary>
        /// <value>An access point status <c>List</c>.</value>
        property System::Collections::Generic::List<AccessStatus>^ Status {
        public:
            System::Collections::Generic::List<AccessStatus>^ get() {
                System::Collections::Generic::List<AccessStatus>^ mlist = gcnew System::Collections::Generic::List<AccessStatus>();
                for (int i = 0; i < _accessPoint->statusSize; i++)
                    mlist->Add((AccessStatus)_accessPoint->status[i]);

                return mlist;
            }
        }

        /// <summary>
        /// Gets or sets the particular type of the access point.
        /// </summary>
        /// <value>The type of access point.</value>
        property AccessPointType Type {
        public:
            AccessPointType get() { return (AccessPointType)_accessPoint->type; }
            void set(AccessPointType value) { _accessPoint->SetType((VxSdk::VxAccessPointType::Value)value); };
        }

    internal:
        VxSdk::IVxAccessPoint* _accessPoint;
        VxSdkNet::Device^ _GetHostDevice();
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // AccessPoint_h__
