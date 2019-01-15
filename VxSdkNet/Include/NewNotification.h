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
        }

        /// <summary>
        /// Gets or sets the roles that should receive this notification.
        /// </summary>
        /// <value>A <c>List</c> of role ids.</value>
        property System::Collections::Generic::List<Role^>^ Roles;
    };
}
#endif // NewNotification_h__
