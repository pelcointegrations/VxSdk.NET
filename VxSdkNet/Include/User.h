// Declares the user class.
#ifndef User_h__
#define User_h__

#include "VxSdk.h"
#include "Utils.h"
#include "DataObject.h"
#include "Role.h"
#include "Tag.h"
#include "UserAccount.h"

namespace VxSdkNet {

    /// <summary>
    /// The User class represents information about a system user.
    /// </summary>
    public ref class User {
    public:

        /// <summary>
        /// Values that represent the type of a phone number.
        /// </summary>
        enum class PhoneType {
            /// <summary>Home number.</summary>
            Home,

            /// <summary>Home fax number.</summary>
            HomeFax,

            /// <summary>Mobile number.</summary>
            Mobile,

            /// <summary>Other number.</summary>
            Other,

            /// <summary>Pager number.</summary>
            Pager,

            /// <summary>Work number.</summary>
            Work,

            /// <summary>Work fax number.</summary>
            WorkFax
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxUser">The vx user.</param>
        User(VxSdk::IVxUser* vxUser);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~User() {
            this->!User();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !User();

        /// <summary>
        /// Add this user to a role.
        /// </summary>
        /// <param name="role">The role to add this user to.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the user.</returns>
        VxSdkNet::Results::Value AddToRole(VxSdkNet::Role^ role);

        /// <summary>
        /// Gets all private data objects owned by this user and all public data objects using an optional collection filter. Other user’s private data
        /// objects will not be returned.
        /// <para>Available filters: ClientType, ModifiedSince, Owned, Owner.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of data objects.</returns>
        System::Collections::Generic::List<DataObject^>^ GetDataObjects(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Gets the roles currently assigned to this user using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, Internal, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of assigned roles.</returns>
        System::Collections::Generic::List<Role^>^ GetRoles(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Gets the tags currently assigned to this user using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Folder, Id, ModifiedSince, Name, Owned, Owner, ParentId, ResourceId, ResourceType.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <value>A <c>List</c> of assigned tags.</value>
        System::Collections::Generic::List<Tag^>^ GetTags(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Update this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Remove this user from a role.
        /// </summary>
        /// <param name="role">The role to remove this user from.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the user.</returns>
        VxSdkNet::Results::Value RemoveFromRole(VxSdkNet::Role^ role);

        /// <summary>
        /// Submit a request for a password change.
        /// </summary>
        /// <param name="newPassword">The new password.</param>
        /// <param name="mustChangePassword">If <c>True</c>, the password will immediately be expired the first time it is used to login.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the password.</returns>
        VxSdkNet::Results::Value SetPassword(System::String^ newPassword, bool mustChangePassword);

        /// <summary>
        /// Gets the user account configuration for this user.
        /// </summary>
        /// <value>The user account.</value>
        property UserAccount^ Account {
            UserAccount^ get() { return _GetUserAccount(); }
        }

        /// <summary>
        /// Gets or sets the state of the user account, either enabled or disabled.
        /// </summary>
        /// <value>The state of the user account.</value>
        property bool AccountState {
        public:
            bool get() { return _GetAccountState(); }
            void set(bool value) { _user->SetAccountState(value); }
        }

        /// <summary>
        /// Gets all private data objects owned by this user and all public data objects. Other user’s private data
        /// objects will not be returned.
        /// </summary>
        /// <value>A <c>List</c> of data objects.</value>
        property System::Collections::Generic::List<DataObject^>^ DataObjects {
            System::Collections::Generic::List<DataObject^>^ get() { return GetDataObjects(nullptr); }
        }

        /// <summary>
        /// Gets or sets the network domain for this user.
        /// </summary>
        /// <value>The network domain.</value>
        property System::String^ Domain {
        public:
            System::String^ get() { return Utils::ConvertCppString(_user->domain); }
            void set(System::String^ value) {
                char domain[64];
                VxSdk::Utilities::StrCopySafe(domain, Utils::ConvertCSharpString(value).c_str());
                _user->SetDomain(domain);
            }
        }

        /// <summary>
        /// Gets or sets the email address of the user.
        /// </summary>
        /// <value>The email address.</value>
        property System::String^ Email {
        public:
            System::String^ get() { return Utils::ConvertCppString(_user->email); }
            void set(System::String^ value) {
                char email[256];
                VxSdk::Utilities::StrCopySafe(email, Utils::ConvertCSharpString(value).c_str());
                _user->SetEmail(email);
            }
        }

        /// <summary>
        /// Gets or sets the employee identifier associated with the user.
        /// </summary>
        /// <value>The employee identifier.</value>
        property System::String^ EmployeeId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_user->employeeId); }
            void set(System::String^ value) {
                char employeeId[64];
                VxSdk::Utilities::StrCopySafe(employeeId, Utils::ConvertCSharpString(value).c_str());
                _user->SetEmployeeId(employeeId);
            }
        }

        /// <summary>
        /// Gets or sets the first name of user.
        /// </summary>
        /// <value>The first name of user.</value>
        property System::String^ FirstName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_user->firstName); }
            void set(System::String^ value) {
                char firstName[64];
                VxSdk::Utilities::StrCopySafe(firstName, Utils::ConvertCSharpString(value).c_str());
                _user->SetFirstName(firstName);
            }
        }

        /// <summary>
        /// Gets the unique identifier of the user.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_user->id); }
        }

        /// <summary>
        /// Gets or sets the last name of user.
        /// </summary>
        /// <value>The last name of user.</value>
        property System::String^ LastName {
        public:
            System::String^ get() { return Utils::ConvertCppString(_user->lastName); }
            void set(System::String^ value) {
                char lastName[64];
                VxSdk::Utilities::StrCopySafe(lastName, Utils::ConvertCSharpString(value).c_str());
                _user->SetLastName(lastName);
            }
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
        /// Gets or sets the friendly name, within the domain, of the user.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_user->name); }
        }

        /// <summary>
        /// Gets or sets supplemental information about the user.
        /// </summary>
        /// <value>Information about the user.</value>
        property System::String^ Note {
        public:
            System::String^ get() { return Utils::ConvertCppString(_user->note); }
            void set(System::String^ value) {
                char note[1024];
                VxSdk::Utilities::StrCopySafe(note, Utils::ConvertCSharpString(value).c_str());
                _user->SetNote(note);
            }
        }

        /// <summary>
        /// Gets the time at which the user’s password will expire.
        /// </summary>
        /// <value>The password experation date.</value>
        property System::DateTime PasswordExpiration {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_user->passwordExpiration); }
        }

        /// <summary>
        /// Gets or sets the telephone number(s) for the user.
        /// </summary>
        /// <value>The telephone number(s) for the user.</value>
        property System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<User::PhoneType, System::String^>>^ PhoneNumbers {
        public:
            System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<User::PhoneType, System::String^>>^ get() {
                System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<User::PhoneType, System::String^>>^ mList =
                    gcnew System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<User::PhoneType, System::String^>>();

                for (int i = 0; i < _user->phoneNumberSize; i++)
                {
                    System::Collections::Generic::KeyValuePair<User::PhoneType, System::String^> kvPair((User::PhoneType)_user->phoneNumbers[i]->type,
                        Utils::ConvertCppString(_user->phoneNumbers[i]->number));

                    mList->Add(kvPair);
                }

                return mList;
            }
            void set(System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<User::PhoneType, System::String^>>^ value) {
                int size = value->Count;
                VxSdk::VxPhoneNumber** numbers = new VxSdk::VxPhoneNumber*[size];
                for (int i = 0; i < size; i++) {
                    numbers[i] = new VxSdk::VxPhoneNumber();
                    numbers[i]->type = (VxSdk::VxPhoneType::Value)value[i].Key;
                    VxSdk::Utilities::StrCopySafe(numbers[i]->number, Utils::ConvertCSharpString(value[i].Value).c_str());
                }

                _user->SetPhoneNumbers(numbers, size);
                for (int i = 0; i < size; i++) {
                    delete numbers[i];
                    numbers[i] = nullptr;
                }

                delete[] numbers;
                numbers = nullptr;
            }
        }

        /// <summary>
        /// Gets the roles currently assigned to this user.
        /// </summary>
        /// <value>A <c>List</c> of assigned roles.</value>
        property System::Collections::Generic::List<Role^>^ Roles {
            System::Collections::Generic::List<Role^>^ get() { return GetRoles(nullptr); }
        }

        /// <summary>
        /// Gets the tags currently assigned to this user.
        /// </summary>
        /// <value>A <c>List</c> of assigned tags.</value>
        property System::Collections::Generic::List<Tag^>^ Tags {
            System::Collections::Generic::List<Tag^>^ get() { return GetTags(nullptr); }
        }

    internal:
        VxSdk::IVxUser* _user;
        bool _GetAccountState();
        VxSdkNet::ResourceLimits^ _GetLimits();
        UserAccount^ _GetUserAccount();
    };
}
#endif // User_h__
