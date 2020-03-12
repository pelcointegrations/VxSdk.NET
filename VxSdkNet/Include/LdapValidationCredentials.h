// Declares the LDAP validation credentials class.
#ifndef LdapValidationCredentials_h__
#define LdapValidationCredentials_h__

namespace VxSdkNet {

    /// <summary>
    /// The LdapValidationCredentials class represents credentials that are used to verify the connection to the LDAP
    ///  server. The information will not be stored.
    /// </summary>
    public ref class LdapValidationCredentials {
    public:

        /// <summary>
        /// Gets or sets the location in the LDAP database that will be used to search for and authenticate user entries.
        /// </summary>
        /// <value>The location in the LDAP database.</value>
        property System::String^ BaseDn;

        /// <summary>
        /// Gets or sets whether or not SSL/TLS security is enabled for the LDAP server.
        /// </summary>
        /// <value><c>true</c> to enable SSL/TLS security, otherwise <c>false</c>.</value>
        property bool IsServerTlsEnabled;

        /// <summary>
        /// Gets or sets whether or not single sign-on is enabled.
        /// </summary>
        /// <value><c>true</c> to enable single sign-on, otherwise <c>false</c>.</value>
        property bool IsSsoEnabled;

        /// <summary>
        /// Gets or sets whether or not two stage binding authentication is enabled.
        /// </summary>
        /// <value><c>true</c> to enable two stage binding authentication, otherwise <c>false</c>.</value>
        property bool IsTwoStageBindingEnabled;

        /// <summary>
        /// Gets or sets the LDAP object classes to search for users.
        /// </summary>
        /// <value>The LDAP object classes.</value>
        property System::String^ ObjectClasses;

        /// <summary>
        /// Gets or sets the user password.
        /// </summary>
        /// <value>The user password.</value>
        property System::String^ Password;

        /// <summary>
        /// Gets or sets the attributes against which to match the user’s identity/name.
        /// </summary>
        /// <value>The attributes.</value>
        property System::String^ SearchAttributes;

        /// <summary>
        /// Gets or sets the superuser DN account in the LDAP directory to use for performing searches there.
        /// </summary>
        /// <value>The superuser DN account.</value>
        property System::String^ SearchDnAccount;

        /// <summary>
        /// Gets or sets the password for the superuser DN account in the LDAP directory that performs searches.
        /// </summary>
        /// <value>The password for the superuser DN account.</value>
        property System::String^ SearchDnPassword;

        /// <summary>
        /// Gets or sets the hostname or IP address of the LDAP server.
        /// </summary>
        /// <value>The the hostname or IP address.</value>
        property System::String^ ServerName;

        /// <summary>
        /// Gets or sets the port number of the LDAP server.
        /// </summary>
        /// <value>The port number.</value>
        property int ServerPort;

        /// <summary>
        /// Gets or sets the Active Directory/Kerberos domain used for single sign-on.
        /// </summary>
        /// <value>The single sign-on domain.</value>
        property System::String^ SsoDomain;

        /// <summary>
        /// Gets or sets whether or not LDAP will be used to manage users and roles.
        /// </summary>
        /// <value><c>true</c> to use LDAP user and role management, <c>false</c> to use the VideoXpert system.</value>
        property bool UseLdapUsersAndRoles;

        /// <summary>
        /// Gets or sets the user login name.
        /// </summary>
        /// <value>The user login name.</value>
        property System::String^ Username;

        /// <summary>
        /// Gets or sets the LDAP container under which VideoXpert system information for all sites is stored; this
        /// should be the same for all sites.
        /// </summary>
        /// <value>The LDAP container.</value>
        property System::String^ VxRootDn;

        /// <summary>
        /// Gets or sets the site specific LDAP container; unique per VideoXpert site.
        /// </summary>
        /// <value>The site specific LDAP container.</value>
        property System::String^ VxSystemDn;
    };
}
#endif // LdapValidationCredentials_h__
