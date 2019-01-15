// Declares the new user class.
#ifndef NewUser_h__
#define NewUser_h__

#include "User.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewUser class represents a new user.
    /// </summary>
    public ref class NewUser {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewUser() {
            PhoneNumbers = gcnew System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<User::PhoneType, System::String^>>();
        }

        /// <summary>
        /// Gets or sets the network domain for this user.
        /// </summary>
        /// <value>The network domain.</value>
        property System::String^ Domain;

        /// <summary>
        /// Gets or sets the email address of the user.
        /// </summary>
        /// <value>The email address.</value>
        property System::String^ Email;

        /// <summary>
        /// Gets or sets the employee identifier associated with the user.
        /// </summary>
        /// <value>The employee identifier.</value>
        property System::String^ EmployeeId;

        /// <summary>
        /// Gets or sets the first name of user.
        /// </summary>
        /// <value>The first name of user.</value>
        property System::String^ FirstName;

        /// <summary>
        /// Gets or sets the last name of user.
        /// </summary>
        /// <value>The last name of user.</value>
        property System::String^ LastName;

        /// <summary>
        /// Gets or sets whether the new user will be forced to change their password the first time they log in.
        /// </summary>
        /// <value><c>true</c> if the user must change its password, <c>false</c> if if not.</value>
        property bool MustChangePassword;

        /// <summary>
        /// Gets or sets the unique users friendly name.
        /// </summary>
        /// <value>The unique friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets supplemental information about the user.
        /// </summary>
        /// <value>Information about the user.</value>
        property System::String^ Note;

        /// <summary>
        /// Gets or sets the user password.
        /// </summary>
        /// <value>The user password.</value>
        property System::String^ Password;

        /// <summary>
        /// Gets or sets the telephone number(s) for the user.
        /// </summary>
        /// <value>The telephone number(s) for the user.</value>
        property System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<User::PhoneType, System::String^>>^ PhoneNumbers;
    };
}
#endif // NewUser_h__
