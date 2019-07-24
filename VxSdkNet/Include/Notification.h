// Declares the notification class.
#ifndef Notification_h__
#define Notification_h__

#include "VxSdk.h"
#include "Role.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Notification class represents a particular notification configuration for a situation.
    /// </summary>
    public ref class Notification {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxNotification">The vx notification.</param>
        Notification(VxSdk::IVxNotification* vxNotification);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Notification() {
            this->!Notification();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Notification();

        /// <summary>
        /// Add a role to the list of roles that this notification serves.
        /// </summary>
        /// <param name="role">The role to add to this notification.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the role.</returns>
        VxSdkNet::Results::Value AddRole(Role^ role);

        /// <summary>
        /// Get the roles that this notification serves using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, Internal, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the roles on the system.</returns>
        System::Collections::Generic::List<Role^>^ GetRoles(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Remove a role from the list of roles that this notification serves.
        /// </summary>
        /// <param name="role">The role to remove from this notification.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the role.</returns>
        VxSdkNet::Results::Value RemoveRole(Role^ role);

        /// <summary>
        /// Gets the unique notification identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_notification->id); }
        }

        /// <summary>
        /// Gets the role ids that this notification serves.
        /// </summary>
        /// <value>A <c>List</c> of role ids.</value>
        property System::Collections::Generic::List<System::String^>^ RoleIds {
        public:
            System::Collections::Generic::List<System::String^>^ get() { return _GetRoleIds(); }
        }

        /// <summary>
        /// Gets the roles that this notification serves.
        /// </summary>
        /// <value>A <c>List</c> of roles.</value>
        property System::Collections::Generic::List<Role^>^ Roles {
        public:
            System::Collections::Generic::List<Role^>^ get() { return GetRoles(nullptr); }
        }

    internal:
        VxSdk::IVxNotification* _notification;
        System::Collections::Generic::List<System::String^>^ _GetRoleIds();
    };
}
#endif // Notification_h__
