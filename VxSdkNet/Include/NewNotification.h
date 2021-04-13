// Declares the new notification class.
#ifndef NewNotification_h__
#define NewNotification_h__

#include "Notification.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewNotification class represents a new notification.
    /// </summary>
    public ref class NewNotification {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewNotification() {
            Roles = gcnew System::Collections::Generic::List<Role^>();
            Users = gcnew System::Collections::Generic::List<User^>();
        }

        /// <summary>
        /// Gets or sets the roles that should receive this notification.
        /// </summary>
        /// <value>A <c>List</c> of roles.</value>
        property System::Collections::Generic::List<Role^>^ Roles;

        /// <summary>
        /// Gets or sets the users that should receive this notification.
        /// </summary>
        /// <value>A <c>List</c> of users.</value>
        property System::Collections::Generic::List<User^>^ Users;
    };
}
#endif // NewNotification_h__
