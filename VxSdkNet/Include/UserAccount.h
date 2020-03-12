// Declares the user account class.
#ifndef UserAccount_h__
#define UserAccount_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ResourceLimits.h"

namespace VxSdkNet {

    /// <summary>
    /// The UserAccount class represents account information for a specific user.
    /// </summary>
    public ref class UserAccount {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxUserAccount">The vx user account.</param>
        UserAccount(VxSdk::IVxUserAccount* vxUserAccount);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~UserAccount() {
            this->!UserAccount();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !UserAccount();

        /// <summary>
        /// Update this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets or sets whether or not the user can login to the system using local credentials instead of using the
        /// LDAP authentication.
        /// </summary>
        /// <value><c>true</c> to allow using local credentials instead of LDAP, otherwise <c>false</c>.</value>
        property bool CanBypassLdap {
        public:
            bool get() { return _userAccount->canBypassLdap; }
            void set(bool value) { _userAccount->SetCanBypassLdap(value); }
        }

        /// <summary>
        /// Gets or sets whether or not this user account is enabled. A disabled account will not be able to access the
        /// system unless the account is re-enabled.
        /// </summary>
        /// <value><c>true</c> if user account is enabled, otherwise <c>false</c>.</value>
        property bool IsEnabled {
        public:
            bool get() { return _userAccount->isEnabled; }
            void set(bool value) { _userAccount->SetIsEnabled(value); }
        }

        /// <summary>
        /// Gets or sets whether or not password expiration is enabled for this user account.
        /// </summary>
        /// <value>If <c>true</c>, password expiration will be disabled for this account; <c>false</c> will use the
        /// global password expiration setting for this account.</value>
        property bool IsPasswordExpirationDisabled {
        public:
            bool get() { return _userAccount->isPasswordExpirationDisabled; }
            void set(bool value) { _userAccount->SetIsPasswordExpirationDisabled(value); }
        }

        /// <summary>
        /// Gets any limits related to this resource.
        /// </summary>
        /// <value>The limits related to this resource.</value>
        property ResourceLimits^ Limits {
        public:
            ResourceLimits^ get() { return _GetLimits(); }
        }

    internal:
        VxSdk::IVxUserAccount* _userAccount;
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // UserAccount_h__
