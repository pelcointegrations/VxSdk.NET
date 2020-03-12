// Declares the role class.
#ifndef Role_h__
#define Role_h__

#include "VxSdk.h"
#include "Utils.h"
#include "NewPrivilege.h"

namespace VxSdkNet {

    /// <summary>
    /// The Role class represents a collection of permissions which can be assigned to a user.
    /// </summary>
    public ref class Role {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxRole">The vx role.</param>
        Role(VxSdk::IVxRole* vxRole);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Role() {
            this->!Role();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Role();

        /// <summary>
        /// Add a new privilege to the role.
        /// </summary>
        /// <param name="newPrivilege">The new privilege to add.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the privilege.</returns>
        VxSdkNet::Results::Value AddPrivilege(VxSdkNet::NewPrivilege^ newPrivilege);

        /// <summary>
        /// Get the users assigned to this role using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, FirstName, LastName, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of users.</returns>
        System::Collections::Generic::List<User^>^ GetUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Update this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Remove a privilege from the role.
        /// </summary>
        /// <param name="privilegeItem">The privilege to remove.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the privilege.</returns>
        VxSdkNet::Results::Value RemovePrivilege(VxSdkNet::Privilege^ privilegeItem);

        /// <summary>
        /// Gets the unique identifier for this role.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_role->id); }
        }

        /// <summary>
        /// Indicates that the role was created internally on the server and is read-only.
        /// </summary>
        /// <value>The read-only value.</value>
        property bool IsReadOnly {
        public:
            bool get() { return _role->isReadOnly; }
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
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_role->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _role->SetName(name);
            }
        }

        /// <summary>
        /// Gets the privileges assigned to this role.
        /// </summary>
        /// <value>A <c>List</c> of privileges.</value>
        property System::Collections::Generic::List<Privilege^>^ Privileges {
        public:
            System::Collections::Generic::List<Privilege^>^ get() { return _GetPrivileges(); }
        }

        /// <summary>
        /// Gets the users assigned to this role.
        /// </summary>
        /// <value>A <c>List</c> of users.</value>
        property System::Collections::Generic::List<User^>^ Users {
        public:
            System::Collections::Generic::List<User^>^ get() { return GetUsers(nullptr); }
        }

    internal:
        VxSdk::IVxRole* _role;
        VxSdkNet::ResourceLimits^ _GetLimits();
        System::Collections::Generic::List<Privilege^>^ _GetPrivileges();
    };
}
#endif // Role_h__
