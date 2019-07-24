// Declares the privilege class.
#ifndef Privilege_h__
#define Privilege_h__

#include "VxSdk.h"
#include "Utils.h"
#include "Device.h"
#include "Drawing.h"

namespace VxSdkNet {
    ref class User;

    /// <summary>
    /// The Privilege class represents a specific permission that is given to a role.
    /// </summary>
    public ref class Privilege {
    public:
        enum class PermissionIds  {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>View live media.</summary>
            ViewLiveMedia,

            /// <summary>Use PTZ mode.</summary>
            UsePtzMode,

            /// <summary>Lock PTZ mode.</summary>
            LockPtzMode,

            /// <summary>Record media.</summary>
            RecordMedia,

            /// <summary>Launch saved views remotely.</summary>
            LaunchSavedViewsRemotely,

            /// <summary>Access alarms.</summary>
            AccessAlarms,

            /// <summary>Access relays.</summary>
            AccessRelays,

            /// <summary>View recorded media.</summary>
            ViewRecordedMedia,

            /// <summary>System bookmarks.</summary>
            SystemBookmarks,

            /// <summary>System locks.</summary>
            SystemLocks,

            /// <summary>Export media clips.</summary>
            ExportMediaClips,

            /// <summary>Manage exports.</summary>
            ManageExports,

            /// <summary>Use map.</summary>
            UseMap,

            /// <summary>View maps.</summary>
            ViewMaps,

            /// <summary>Place cameras on map.</summary>
            PlaceCamerasOnMap,

            /// <summary>Manage map files.</summary>
            ManageMapFiles,

            /// <summary>Define ptz presets.</summary>
            DefinePtzPresets,

            /// <summary>Manage camera tours.</summary>
            ManageCameraTours,

            /// <summary>Access user workspaces.</summary>
            AccessUserWorkspaces,

            /// <summary>Manage system workspaces.</summary>
            ManageSystemWorkspaces,

            /// <summary>AuditUser activity.</summary>
            AuditUserActivity,

            /// <summary>Multiview qty.</summary>
            MultiviewQty,

            /// <summary>View event history.</summary>
            ViewEventHistory,

            /// <summary>Handle events.</summary>
            HandleEvents,

            /// <summary>Configure events.</summary>
            ConfigureEvents,

            /// <summary>Manage user accounts.</summary>
            ManageUserAccounts,

            /// <summary>Assign roles to users.</summary>
            AssignRolesToUsers,

            /// <summary>Reset user passwords.</summary>
            ResetUserPasswords,

            /// <summary>Manage roles.</summary>
            ManageRoles,

            /// <summary>Manage system tags.</summary>
            ManageSystemTags,

            /// <summary>Manage I/O.</summary>
            ManageIO,

            /// <summary>Manage device licenses.</summary>
            ManageDeviceLicenses,

            /// <summary>Update device software.</summary>
            UpdateDeviceSoftware,

            /// <summary>Setup edge devices.</summary>
            SetupEdgeDevices,

            /// <summary>Manage display devices.</summary>
            ManageDisplayDevices,

            /// <summary>Configure monitor wall decoders.</summary>
            ConfigureMonitorWallDecoders,

            /// <summary>Manage system licenses.</summary>
            ManageSystemLicenses,

            /// <summary>Set system locale options.</summary>
            SetSystemLocaleOptions,

            /// <summary>Define system shortcuts.</summary>
            DefineSystemShortcuts,

            /// <summary>Configure recording.</summary>
            ConfigureRecording,

            /// <summary>View system health.</summary>
            ViewSystemHealth,

            /// <summary>Manage system servers.</summary>
            ManageSystemServers,

            /// <summary>Manage member systems.</summary>
            ManageMemberSystems
        };

        /// <summary>
        /// Values that represent a type of resource.
        /// </summary>
        enum class ResourceTypes {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>A data source.</summary>
            DataSource,

            /// <summary>A device.</summary>
            Device,

            /// <summary>A user.</summary>
            User,

            /// <summary>A drawing resource.</summary>
            Drawing,

            /// <summary>A drawing resource.</summary>
            DataStorage,

            /// <summary>A user resource.</summary>
            Tag,

            /// <summary>A relay output resource.</summary>
            RelayOutput
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxPrivilege">The vx privilege.</param>
        Privilege(VxSdk::IVxPrivilege* vxPrivilege);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Privilege() {
            this->!Privilege();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Privilege();

        /// <summary>
        /// Get the data sources associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of data sources.</returns>
        System::Collections::Generic::List<DataSource^>^ GetLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the devices associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of devices.</returns>
        System::Collections::Generic::List<Device^>^ GetLinkedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the drawings associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of drawings.</returns>
        System::Collections::Generic::List<Drawing^>^ GetLinkedDrawings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the relay outputs associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of relay outputs.</returns>
        System::Collections::Generic::List<RelayOutput^>^ GetLinkedRelayOutputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the users associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of users.</returns>
        System::Collections::Generic::List<User^>^ GetLinkedUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the data sources not associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of data sources.</returns>
        System::Collections::Generic::List<DataSource^>^ GetUnLinkedDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the devices not associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of devices.</returns>
        System::Collections::Generic::List<Device^>^ GetUnLinkedDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the drawings not associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of drawings.</returns>
        System::Collections::Generic::List<Drawing^>^ GetUnLinkedDrawings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the relay outputs not associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of relay outputs.</returns>
        System::Collections::Generic::List<RelayOutput^>^ GetUnLinkedRelayOutputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the users not associated with this privilege using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of users.</returns>
        System::Collections::Generic::List<User^>^ GetUnLinkedUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Associate data sources with this privilege.
        /// </summary>
        /// <param name="dataSources">A <c>List</c> containing the data sources to be added.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the data sources.</returns>
        VxSdkNet::Results::Value Link(System::Collections::Generic::List<DataSource^>^ dataSources);

        /// <summary>
        /// Associate devices with this privilege.
        /// </summary>
        /// <param name="devices">A <c>List</c> containing the devices to be added.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the devices.</returns>
        VxSdkNet::Results::Value Link(System::Collections::Generic::List<Device^>^ devices);

        /// <summary>
        /// Associate drawings with this privilege.
        /// </summary>
        /// <param name="drawings">A <c>List</c> containing the drawings to be linked.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of linking the drawings.</returns>
        VxSdkNet::Results::Value Link(System::Collections::Generic::List<Drawing^>^ drawings);

        /// <summary>
        /// Associate relay outputs with this privilege.
        /// </summary>
        /// <param name="relayOutputs">A <c>List</c> containing the relay outputs to be linked.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of linking the relay outputs.</returns>
        VxSdkNet::Results::Value Link(System::Collections::Generic::List<RelayOutput^>^ relayOutputs);

        /// <summary>
        /// Associate users with this privilege.
        /// </summary>
        /// <param name="users">A <c>List</c> containing the data sources to be added.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the data sources.</returns>
        VxSdkNet::Results::Value Link(System::Collections::Generic::List<User^>^ users);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Remove data source associations from this privilege.
        /// </summary>
        /// <param name="dataSources">A <c>List</c> containing the data sources to be removed.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the data sources.</returns>
        VxSdkNet::Results::Value Unlink(System::Collections::Generic::List<DataSource^>^ dataSources);

        /// <summary>
        /// Remove device associations from this privilege.
        /// </summary>
        /// <param name="devices">A <c>List</c> containing the devices to be removed.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the devices.</returns>
        VxSdkNet::Results::Value Unlink(System::Collections::Generic::List<Device^>^ devices);

        /// <summary>
        /// Remove drawings associations from this privilege.
        /// </summary>
        /// <param name="drawings">A <c>List</c> containing the drawings to be removed.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the drawings.</returns>
        VxSdkNet::Results::Value Unlink(System::Collections::Generic::List<Drawing^>^ drawings);

        /// <summary>
        /// Remove relay outputs associations from this privilege.
        /// </summary>
        /// <param name="relayOutputs">A <c>List</c> containing the relay outputs to be removed.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the relay outputs.</returns>
        VxSdkNet::Results::Value Unlink(System::Collections::Generic::List<RelayOutput^>^ relayOutputs);

        /// <summary>
        /// Remove user associations from this privilege.
        /// </summary>
        /// <param name="users">A <c>List</c> containing the users to be removed.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the users.</returns>
        VxSdkNet::Results::Value Unlink(System::Collections::Generic::List<User^>^ users);

        /// <summary>
        /// Gets the unique identifier for this privilege.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_privilege->id); }
        }

        /// <summary>
        /// Gets or sets whether the privilege is excluded from the associated resources.
        /// </summary>
        /// <value><c>true</c> if the privilege is excluded, <c>false</c> if not.</value>
        property bool IsExcludeRestricted {
        public:
            bool get() { return _privilege->excludeRestricted; }
            void set(bool value) { _privilege->SetExcludeRestricted(value); }
        }

        /// <summary>
        /// Gets or sets whether the privilege is restricted to the associated resources.
        /// </summary>
        /// <value><c>true</c> if restricted, <c>false</c> if not.</value>
        property bool IsRestricted {
        public:
            bool get() { return _GetRestricted(); }
            void set(bool value) { _privilege->SetRestricted(value); }
        }

        /// <summary>
        /// Gets the data sources associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of data sources.</value>
        property System::Collections::Generic::List<DataSource^>^ LinkedDataSources {
        public:
            System::Collections::Generic::List<DataSource^>^ get() { return GetLinkedDataSources(nullptr); }
        }

        /// <summary>
        /// Gets the devices associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of devices.</value>
        property System::Collections::Generic::List<Device^>^ LinkedDevices {
        public:
            System::Collections::Generic::List<Device^>^ get() { return GetLinkedDevices(nullptr); }
        }

        /// <summary>
        /// Gets the drawings associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of drawings.</value>
        property System::Collections::Generic::List<Drawing^>^ LinkedDrawings {
        public:
            System::Collections::Generic::List<Drawing^>^ get() { return GetLinkedDrawings(nullptr); }
        }

        /// <summary>
        /// Gets the relay outputs associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of relay outputs.</value>
        property System::Collections::Generic::List<RelayOutput^>^ LinkedRelayOutputs {
        public:
            System::Collections::Generic::List<RelayOutput^>^ get() { return GetLinkedRelayOutputs(nullptr); }
        }

        /// <summary>
        /// Gets the users associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of users.</value>
        property System::Collections::Generic::List<User^>^ LinkedUsers {
        public:
            System::Collections::Generic::List<User^>^ get() { return GetLinkedUsers(nullptr); }
        }

        /// <summary>
        /// Gets the identifier of the permission being granted by this privilege.
        /// </summary>
        /// <value>The permission identifier.</value>
        property PermissionIds PermissionId {
        public:
            PermissionIds get() { return (PermissionIds)_privilege->permissionId; }
        }

        /// <summary>
        /// Gets or sets the relative priority for the privilege, from 1 to 250. Smaller numbers have higher
        /// priority than larger numbers (e.g. 1 is the highest priority).
        /// </summary>
        /// <value>The priority.</value>
        property int Priority {
        public:
            int get() { return _GetPriority(); }
            void set(int value) { _privilege->SetPriority(value); }
        }

        /// <summary>
        /// Gets the resource type, if any, that can be linked to this privilege.
        /// </summary>
        /// <value>The resource type.</value>
        property ResourceTypes ResourceType {
        public:
            ResourceTypes get() { return (ResourceTypes)_privilege->resourceType; }
        }

        /// <summary>
        /// Gets the data sources not associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of data sources.</value>
        property System::Collections::Generic::List<DataSource^>^ UnLinkedDataSources {
        public:
            System::Collections::Generic::List<DataSource^>^ get() { return GetUnLinkedDataSources(nullptr); }
        }

        /// <summary>
        /// Gets the devices not associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of devices.</value>
        property System::Collections::Generic::List<Device^>^ UnLinkedDevices {
        public:
            System::Collections::Generic::List<Device^>^ get() { return GetUnLinkedDevices(nullptr); }
        }

        /// <summary>
        /// Gets the drawings not associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of drawings.</value>
        property System::Collections::Generic::List<Drawing^>^ UnLinkedDrawings {
        public:
            System::Collections::Generic::List<Drawing^>^ get() { return GetUnLinkedDrawings(nullptr); }
        }

        /// <summary>
        /// Gets the relay outputs not associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of relay outputs.</value>
        property System::Collections::Generic::List<RelayOutput^>^ UnLinkedRelayOutputs {
        public:
            System::Collections::Generic::List<RelayOutput^>^ get() { return GetUnLinkedRelayOutputs(nullptr); }
        }

        /// <summary>
        /// Gets the users not associated with this privilege.
        /// </summary>
        /// <value>A <c>List</c> of users.</value>
        property System::Collections::Generic::List<User^>^ UnLinkedUsers {
        public:
            System::Collections::Generic::List<User^>^ get() { return GetUnLinkedUsers(nullptr); }
        }

    internal:
        VxSdk::IVxPrivilege* _privilege;
        int _GetPriority();
        bool _GetRestricted();
    };
}
#endif // Privilege_h__
