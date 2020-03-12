// Declares the configuration class.
#ifndef Configuration_h__
#define Configuration_h__

#include "VxSdk.h"
#include "Utils.h"
#include "FileRecovery.h"
#include "ResourceLimits.h"

namespace VxSdkNet {
    ref class SmtpInfo;
    ref class LdapValidationCredentials;
    ref class NewVolume;
    ref class NewVolumeGroup;
    ref class VolumeGroup;
    ref class Volume;

    /// <summary>
    /// The Configuration class represents a device configuration.
    /// </summary>
    public ref class Configuration {
    public:
        ref class Node;
        ref class Time;

        /// <summary>
        /// Values that represent SNMP v3 authentication protocols.
        /// </summary>
        enum class AuthProtocol {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>MD5 authentication protocol.</summary>
            MD5,
            /// <summary>No authentication protocol.</summary>
            None,
            /// <summary>SHA authentication protocol.</summary>
            SHA
        };

        /// <summary>
        /// Values that represent bookmark retention policies.
        /// </summary>
        enum class BookmarkRetentionPolicy {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>Unlocked bookmarks are automatically deleted after the retention limit.</summary>
            DeleteAfterLimit,
            /// <summary>
            /// Unlocked bookmarks are automatically deleted after their corresponding recordings are deleted.
            /// </summary>
            DeleteAfterRecording,
            /// <summary>Unlocked bookmarks are not automatically deleted.</summary>
            NeverDelete
        };

        /// <summary>
        /// Values that represent the current cluster configuration status.
        /// </summary>
        enum class ConfigStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>The cluster is configured.</summary>
            Configured,
            /// <summary>The cluster is being configured.</summary>
            Configuring,
            /// <summary>Cluster configuration failed.</summary>
            Failed,
            /// <summary>The cluster is unconfigured.</summary>
            Unconfigured
        };

        /// <summary>
        /// Values that represent VxMediaGateway communication configurations. The first part indicates the default
        /// communication used between a data source and the VxMediaGateway; the second part indicates the default
        /// communication between the VxMediaGateway and a client.
        /// </summary>
        enum class MgTranscast {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>Multicast between the data source and VxMG; multicast between VxMG and client.</summary>
            Multicast_Multicast,
            /// <summary>Multicast between the data source and VxMG; unicast between VxMG and client.</summary>
            Multicast_Unicast,
            /// <summary>Unicast between the data source and VxMG; multicast between VxMG and client.</summary>
            Unicast_Multicast,
            /// <summary>Unicast between the data source and VxMG; unicast between VxMG and client.</summary>
            Unicast_Unicast
        };

        /// <summary>
        /// Values that represent motion detection modes.
        /// </summary>
        enum class MotionMode {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>Camera based motion detection.</summary>
            Camera,
            /// <summary>Motion detection disabled.</summary>
            Disabled,
            /// <summary>Recorder based motion detection.</summary>
            Recorder
        };

        /// <summary>
        /// Values that represent a particular type of node.
        /// </summary>
        enum class NodeType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>Core node.</summary>
            Core,
            /// <summary>Database node.</summary>
            Database,
            /// <summary>Support node.</summary>
            Support
        };

        /// <summary>
        /// Values that represent SNMP v3 privacy protocols.
        /// </summary>
        enum class PrivacyProtocol {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>AES encryption.</summary>
            AES,
            /// <summary>DES encryption.</summary>
            DES,
            /// <summary>No encryption.</summary>
            None
        };

        /// <summary>
        /// Values that represent which version of SNMP is enabled.
        /// </summary>
        enum class SnmpVersion {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>SNMP is disabled.</summary>
            None,
            /// <summary>SNMPv2c protocol.</summary>
            SNMP2c,
            /// <summary>SNMPv3 protocol.</summary>
            SNMP3
        };

        /// <summary>
        /// Values that represent a stream source.
        /// </summary>
        enum class StreamSource {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>The 1st stream.</summary>
            Primary,
            /// <summary>The 2nd stream.</summary>
            Secondary,
            /// <summary>The 3rd stream.</summary>
            Tertiary,
            /// <summary>The 4th stream.</summary>
            Quaternary,
            /// <summary>The 5th stream.</summary>
            Quinary,
            /// <summary>The 6th stream.</summary>
            Senary,
            /// <summary>The 7th stream.</summary>
            Septenary,
            /// <summary>The 8th stream.</summary>
            Octonary,
            /// <summary>The 9th stream.</summary>
            Nonary,
            /// <summary>The 10th stream.</summary>
            Denary
        };

        /// <summary>
        /// Values that represent network communication transmission types.
        /// </summary>
        enum class TransmissionTypes {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>Multicast transmission.</summary>
            Multicast,
            /// <summary>Unicast transmission.</summary>
            Unicast
        };

        /// <summary>
        /// The Auth class represents authorization configuration.
        /// </summary>
        ref class Auth {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigAuth">The vx authentication configuration.</param>
            Auth(VxSdk::IVxConfiguration::Auth* vxConfigAuth);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Auth() {
                this->!Auth();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Auth();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets or sets whether or not password expiration is enabled for all users.
            /// </summary>
            /// <value><c>true</c> to enable password expiration, otherwise <c>false</c>.</value>
            property bool IsPasswordExpirationEnabled {
            public:
                bool get() { return _configAuth->isPasswordExpirationEnabled; }
                void set(bool value) { value ? _configAuth->EnablePasswordExpiration() : _configAuth->DisablePasswordExpiration(); }
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
            /// Gets or sets the amount of time, in days, at which a user password will expire (from when it was last set/changed).
            /// Ignored if <see cref="IsPasswordExpirationEnabled"/> is <c>false</c>.
            /// </summary>
            /// <value>The expiration time, in days.</value>
            property int PasswordExpiration {
            public:
                int get() { return _configAuth->passwordExpiration; }
                void set(int value) { _configAuth->SetPasswordExpiration(value); }
            }

        internal:
            VxSdk::IVxConfiguration::Auth* _configAuth;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The Bookmark class represents bookmark configuration.
        /// </summary>
        ref class Bookmark {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigBookmark">The vx bookmark configuration.</param>
            Bookmark(VxSdk::IVxConfiguration::Bookmark* vxConfigBookmark);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Bookmark() {
                this->!Bookmark();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Bookmark();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets or sets the number of days before automatically unlocking any locked bookmark that has a
            /// <c>BookmarkLock.EndTime</c> older than this value. A value of 0 will disable automatic unlocking.
            /// </summary>
            /// <value>The auto unlock time, in days.</value>
            property int AutoUnlock {
            public:
                int get() { return _configBookmark->autoUnlock; }
                void set(int value) { _configBookmark->SetAutoUnlock(value); }
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
            /// Gets or sets the retention limit, in days, for bookmarks; a value of 0 will disable the limit. Any
            /// bookmark that exceeds this limit will be deleted. Ignored if the <see cref="RetentionPolicy"/> is not
            /// set to <c>DeleteAfterLimit</c>.
            /// </summary>
            /// <value>The retention limit, in days.</value>
            property int RetentionLimit {
            public:
                int get() { return _configBookmark->retentionLimit; }
                void set(int value) { _configBookmark->SetRetentionLimit(value); }
            }

            /// <summary>
            /// Gets or sets the bookmark retention policy, which specifies if and when an old bookmark is
            /// automatically removed from the system.
            /// </summary>
            /// <value>The bookmark retention policy.</value>
            property BookmarkRetentionPolicy RetentionPolicy {
            public:
                BookmarkRetentionPolicy get() { return (BookmarkRetentionPolicy)_configBookmark->retentionPolicy; }
                void set(BookmarkRetentionPolicy value) { _configBookmark->SetRetentionPolicy((VxSdk::VxBookmarkRetentionPolicy::Value)value); }
            }

        internal:
            VxSdk::IVxConfiguration::Bookmark* _configBookmark;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The Cluster class represents cluster configuration attributes. This representation shall
        /// be identical within a cluster, regardless of the node it was retrieved from.
        /// </summary>
        ref class Cluster {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigCluster">The vx cluster configuration.</param>
            Cluster(VxSdk::IVxConfiguration::Cluster* vxConfigCluster);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Cluster() {
                this->!Cluster();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Cluster();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets or sets the retention limit, in days, on logged events from aggregated sources. Any aggregated
            /// events that exceed this limit shall be deleted.
            /// </summary>
            /// <value>The retention limit.</value>
            property int AggregatedEventLimit {
            public:
                int get() { return _configCluster->aggregatedEventLimit; }
                void set(int value) { _configCluster->SetAggregatedEventLimit(value); }
            }

            /// <summary>
            /// Gets or sets the virtual IP or hostname used for VideoXpert Core devices.
            /// </summary>
            /// <value>The VxCore virtual IP.</value>
            property System::String^ CoreVirtualIp {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configCluster->coreVirtualIp); }
                void set(System::String^ value) {
                    char virtualIp[256];
                    VxSdk::Utilities::StrCopySafe(virtualIp, Utils::ConvertCSharpString(value).c_str());
                    _configCluster->SetCoreVirtualIp(virtualIp);
                }
            }

            /// <summary>
            /// Gets or sets the virtual IP or hostname used for device discovery if the cluster is not governed
            /// by a VideoXpert Accessory Server. The load balancer uses this address for discovery announcements
            /// and balances responses across the cluster.
            /// </summary>
            /// <value>The discovery virtual IP.</value>
            property System::String^ DiscoveryVirtualIp {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configCluster->discoveryVirtualIp); }
                void set(System::String^ value) {
                    char virtualIp[256];
                    VxSdk::Utilities::StrCopySafe(virtualIp, Utils::ConvertCSharpString(value).c_str());
                    _configCluster->SetDiscoveryVirtualIp(virtualIp);
                }
            }

            /// <summary>
            /// Gets or sets the UNC network path to save export media to.
            /// </summary>
            /// <value>The UNC network path.</value>
            property System::String^ ExportPath {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configCluster->exportPath); }
                void set(System::String^ value) {
                    char exportPath[512];
                    VxSdk::Utilities::StrCopySafe(exportPath, Utils::ConvertCSharpString(value).c_str());
                    _configCluster->SetExportPath(exportPath);
                }
            }

            /// <summary>
            /// Sets the the export path password. If set (and <see cref="IsExportPathEnabled"/> is <c>true></c>), this
            /// password will be used to access the network resource specified in the <see cref="ExportPath"/>.
            /// </summary>
            /// <value>The password.</value>
            property System::String^ ExportPathPassword {
            public:
                void set(System::String^ value) {
                    char exportPathPassword[64];
                    VxSdk::Utilities::StrCopySafe(exportPathPassword, Utils::ConvertCSharpString(value).c_str());
                    _configCluster->SetExportPathPassword(exportPathPassword);
                }
            }

            /// <summary>
            /// Gets or sets the username used to access the network resource at the location specified by
            /// <see cref="ExportPath"/>.
            /// </summary>
            /// <value>The username.</value>
            property System::String^ ExportPathUsername {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configCluster->exportPathUsername); }
                void set(System::String^ value) {
                    char exportPathUsername[64];
                    VxSdk::Utilities::StrCopySafe(exportPathUsername, Utils::ConvertCSharpString(value).c_str());
                    _configCluster->SetExportPathUsername(exportPathUsername);
                }
            }

            /// <summary>
            /// Gets or sets whether or not the alternative export storage location is enabled.
            /// </summary>
            /// <value><c>true</c> to enable using the export path, otherwise <c>false</c>.</value>
            property bool IsExportPathEnabled {
            public:
                bool get() { return _configCluster->isExportPathEnabled; }
                void set(bool value) { value ? _configCluster->EnableExportPath() : _configCluster->DisableExportPath(); }
            }

            /// <summary>
            /// Gets or sets whether camera streams will be proxied through the VxStorage that they are assigned to or
            /// will always be pulled directly from the Media Gateway.
            /// </summary>
            /// <value><c>true</c> to enable the stream proxy, otherwise <c>false</c>.</value>
            property bool IsStreamProxyEnabled {
            public:
                bool get() { return _configCluster->isStreamProxyEnabled; }
                void set(bool value) { value ? _configCluster->EnableStreamProxy() : _configCluster->DisableStreamProxy(); }
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
            /// Gets or sets the retention limit, in days, on logged events. Any events that exceed this limit shall
            /// be deleted.
            /// </summary>
            /// <value>The retention limit.</value>
            property int LocalEventLimit {
            public:
                int get() { return _configCluster->localEventLimit; }
                void set(int value) { _configCluster->SetLocalEventLimit(value); }
            }

            /// <summary>
            /// Gets the default communication method between data sources to Media Gateways and
            /// between Media Gateways to clients.
            /// </summary>
            /// <remarks>
            /// DEPRECATED: This has been replaced by <see cref="TranscastMethod"/> and will be removed in the future.
            /// </remarks>
            /// <value>The communication method.</value>
            property System::String^ MediaGatewayTranscast {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configCluster->mediaGatewayTranscast); }
            }

            /// <summary>
            /// Gets or sets the virtual IP or hostname used for Media Gateway devices.
            /// </summary>
            /// <value>The Media Gateway virtual IP.</value>
            property System::String^ MediaGatewayVirtualIp {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configCluster->mediaGatewayVirtualIp); }
                void set(System::String^ value) {
                    char virtualIp[256];
                    VxSdk::Utilities::StrCopySafe(virtualIp, Utils::ConvertCSharpString(value).c_str());
                    _configCluster->SetMediaGatewayVirtualIp(virtualIp);
                }
            }

            /// <summary>
            /// Gets the configuration for the nodes that the cluster is composed of.
            /// </summary>
            /// <value>A <c>List</c> of node configurations.</value>
            property System::Collections::Generic::List<Node^>^ NodeConfigurations {
            public:
                System::Collections::Generic::List<Node^>^ get() { return _GetNodeConfigurations(); }
            }

            /// <summary>
            /// Gets the maximum number of allowed nodes under the current license. A license is required to expand the
            /// number of nodes that can be added to this cluster beyond this number. Set to -1 if there is no limit.
            /// </summary>
            /// <value>The retention limit.</value>
            property int NodeLicenseLimit {
            public:
                int get() { return _configCluster->nodeLicenseLimit; }
            }

            /// <summary>
            /// Gets the current configuration status of the entire cluster.
            /// </summary>
            /// <value>The configuration status.</value>
            property ConfigStatus Status {
            public:
                ConfigStatus get() { return (ConfigStatus)_configCluster->status; }
            }

            /// <summary>
            /// Gets the current configuration status code.
            /// </summary>
            /// <value>The status code.</value>
            property int StatusCode {
            public:
                int get() { return _configCluster->statusCode; }
            }

            /// <summary>
            /// Gets the current configuration status description.
            /// </summary>
            /// <value>The status description.</value>
            property System::String^ StatusDescription {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configCluster->statusDescription); }
            }

            /// <summary>
            /// Gets the time configuration for the cluster.
            /// </summary>
            /// <value>The time configuration.</value>
            property Time^ TimeConfig {
            public:
                Time^ get() { return _GetTimeConfig(); }
            }

            /// <summary>
            /// Gets or sets the default communication method between data sources to Media Gateways and
            /// between Media Gateways to clients.
            /// </summary>
            /// <value>The communication method.</value>
            property MgTranscast TranscastMethod {
            public:
                MgTranscast get() { return (MgTranscast)_configCluster->transcastMethod; }
                void set(MgTranscast value) { _configCluster->SetTranscastMethod((VxSdk::VxMgTranscast::Value)value); }
            }

        internal:
            VxSdk::IVxConfiguration::Cluster* _configCluster;
            VxSdkNet::ResourceLimits^ _GetLimits();
            System::Collections::Generic::List<Node^>^ _GetNodeConfigurations();
            Time^ _GetTimeConfig();
        };

        /// <summary>
        /// The Ldap class represents the LDAP configuration available.
        /// </summary>
        ref class Ldap {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigLdap">The vx LDAP configuration.</param>
            Ldap(VxSdk::IVxConfiguration::Ldap* vxConfigLdap);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Ldap() {
                this->!Ldap();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Ldap();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Validates the given credentials on the specified LDAP server.
            /// </summary>
            /// <param name="ldapCredentials">The LDAP credentials to validate.</param>
            /// <returns><c>true</c> if the config and credentials are valid, otherwise <c>false</c>.</returns>
            bool ValidateLdapCredentials(LdapValidationCredentials^ ldapCredentials);

            /// <summary>
            /// Gets or sets the location in the LDAP database that will be used to search for and authenticate user entries.
            /// </summary>
            /// <value>The LDAP database location.</value>
            property System::String^ BaseDn {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configLdap->baseDn); }
                void set(System::String^ value) {
                    char baseDn[1024];
                    VxSdk::Utilities::StrCopySafe(baseDn, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetBaseDn(baseDn);
                }
            }

            /// <summary>
            /// Gets or sets whether or not LDAP username/password authentication is enabled.
            /// </summary>
            /// <value><c>true</c> to enable LDAP authentication, otherwise <c>false</c>.</value>
            property bool IsEnabled {
            public:
                bool get() { return _configLdap->isEnabled; }
                void set(bool value) { value ? _configLdap->EnableLdap() : _configLdap->DisableLdap(); }
            }

            /// <summary>
            /// Gets or sets whether or not SSL/TLS security is enabled for the LDAP server.
            /// </summary>
            /// <value><c>true</c> to enable SSL/TLS security, otherwise <c>false</c>.</value>
            property bool IsServerTlsEnabled {
            public:
                bool get() { return _configLdap->isServerTlsEnabled; }
                void set(bool value) { value ? _configLdap->EnableServerTls() : _configLdap->DisableServerTls(); }
            }

            /// <summary>
            /// Gets or sets whether or not single sign-on is enabled.
            /// </summary>
            /// <value><c>true</c> to enable single sign-on, otherwise <c>false</c>.</value>
            property bool IsSsoEnabled {
            public:
                bool get() { return _configLdap->isSsoEnabled; }
                void set(bool value) { value ? _configLdap->EnableSso() : _configLdap->DisableSso(); }
            }

            /// <summary>
            /// Gets or sets whether or not two stage binding authentication is enabled.
            /// </summary>
            /// <value><c>true</c> to enable two stage binding authentication, otherwise <c>false</c>.</value>
            property bool IsTwoStageBindingEnabled {
            public:
                bool get() { return _configLdap->isTwoStageBindingEnabled; }
                void set(bool value) { value ? _configLdap->EnableTwoStageBinding() : _configLdap->DisableTwoStageBinding(); }
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
            /// Gets or sets the LDAP object classes to search for users.
            /// </summary>
            /// <value>The LDAP object classes.</value>
            property System::String^ ObjectClasses {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configLdap->objectClasses); }
                void set(System::String^ value) {
                    char objectClasses[1024];
                    VxSdk::Utilities::StrCopySafe(objectClasses, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetObjectClasses(objectClasses);
                }
            }

            /// <summary>
            /// Gets or sets the attributes against which to match the user’s identity/name.
            /// </summary>
            /// <value>The attributes.</value>
            property System::String^ SearchAttributes {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configLdap->searchAttributes); }
                void set(System::String^ value) {
                    char searchAttributes[1024];
                    VxSdk::Utilities::StrCopySafe(searchAttributes, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetSearchAttributes(searchAttributes);
                }
            }

            /// <summary>
            /// Gets or sets the superuser DN account in the LDAP directory to use for performing searches there.
            /// </summary>
            /// <value>The superuser DN account.</value>
            property System::String^ SearchDnAccount {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configLdap->searchDnAccount); }
                void set(System::String^ value) {
                    char searchDnAccount[1024];
                    VxSdk::Utilities::StrCopySafe(searchDnAccount, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetSearchDnAccount(searchDnAccount);
                }
            }

            /// <summary>
            /// Sets the password for the search DN account.
            /// </summary>
            /// <value>The superuser DN password.</value>
            property System::String^ SearchDnPassword {
            public:
                void set(System::String^ value) {
                    char searchDnPassword[64];
                    VxSdk::Utilities::StrCopySafe(searchDnPassword, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetSearchDnPassword(searchDnPassword);
                }
            }

            /// <summary>
            /// Gets or sets the hostname or IP address of the LDAP server.
            /// </summary>
            /// <value>The hostname or IP address.</value>
            property System::String^ ServerName {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configLdap->serverName); }
                void set(System::String^ value) {
                    char serverName[256];
                    VxSdk::Utilities::StrCopySafe(serverName, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetServerName(serverName);
                }
            }

            /// <summary>
            /// Gets or sets the port number of the LDAP server.
            /// </summary>
            /// <value>The port number.</value>
            property int ServerPort {
            public:
                int get() { return _configLdap->serverPort; }
                void set(int value) { _configLdap->SetServerPort(value); }
            }

            /// <summary>
            /// Gets or sets the Active Directory/Kerberos domain used for single sign-on.
            /// </summary>
            /// <value>The Active Directory/Kerberos domain.</value>
            property System::String^ SsoDomain {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configLdap->ssoDomain); }
                void set(System::String^ value) {
                    char ssoDomain[1024];
                    VxSdk::Utilities::StrCopySafe(ssoDomain, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetSsoDomain(ssoDomain);
                }
            }

            /// <summary>
            /// Gets or sets whether or not LDAP will be used to manage users and roles.
            /// </summary>
            /// <value><c>true</c> to use LDAP for managing users and roles, <c>false</c> to use the VideoXpert system (default).</value>
            property bool UseLdapUsersAndRoles {
            public:
                bool get() { return _configLdap->useLdapUsersAndRoles; }
                void set(bool value) { value ? _configLdap->EnableLdapUsersAndRoles() : _configLdap->DisableLdapUsersAndRoles(); }
            }

            /// <summary>
            /// Gets or sets the LDAP container under which VideoXpert system information for all sites is stored; this should be the
            /// same for all sites.
            /// </summary>
            /// <value>The root LDAP container.</value>
            property System::String^ VxRootDn {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configLdap->vxRootDn); }
                void set(System::String^ value) {
                    char vxRootDn[1024];
                    VxSdk::Utilities::StrCopySafe(vxRootDn, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetVxRootDn(vxRootDn);
                }
            }

            /// <summary>
            /// Gets or sets the site specific LDAP container; unique per VideoXpert site. This DN should contain the
            /// <see cref="VxRootDn"/> (which is a suffix of this full DN).
            /// </summary>
            /// <value>The site specific LDAP container.</value>
            property System::String^ VxSystemDn {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configLdap->vxSystemDn); }
                void set(System::String^ value) {
                    char vxSystemDn[1024];
                    VxSdk::Utilities::StrCopySafe(vxSystemDn, Utils::ConvertCSharpString(value).c_str());
                    _configLdap->SetVxSystemDn(vxSystemDn);
                }
            }

        internal:
            VxSdk::IVxConfiguration::Ldap* _configLdap;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The Motion class represents a motion detection configuration.
        /// </summary>
        ref class Motion {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigMotion">The vx motion configuration.</param>
            Motion(VxSdk::IVxConfiguration::Motion* vxConfigMotion);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Motion() {
                this->!Motion();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Motion();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets any limits related to this resource.
            /// </summary>
            /// <value>The limits related to this resource.</value>
            property ResourceLimits^ Limits {
            public:
                ResourceLimits^ get() { return _GetLimits(); }
            }

            /// <summary>
            /// Gets or sets the motion detection mode.
            /// </summary>
            /// <value>The motion detection mode.</value>
            property MotionMode Mode {
            public:
                MotionMode get() { return (MotionMode)_configMotion->mode; }
                void set(MotionMode value) { _configMotion->SetMode((VxSdk::VxMotionMode::Value)value); }
            }

            /// <summary>
            /// Gets or sets the amount of change that needs to occur in order to qualify as motion. Higher values increase
            /// sensitivity (less change required to trigger motion).
            /// </summary>
            /// <value>The motion sensitivity level.</value>
            property int Sensitivity {
            public:
                int get() { return _configMotion->sensitivity; }
                void set(int value) { _configMotion->SetSensitivity(value); }
            }

            /// <summary>
            /// Gets or sets the amount of area that needs to occur in order to qualify as motion. Higher values increase
            /// sensitivity (less area required to trigger motion).
            /// </summary>
            /// <value>The motion threshold level.</value>
            property int Threshold {
            public:
                int get() { return _configMotion->threshold; }
                void set(int value) { _configMotion->SetThreshold(value); }
            }

        internal:
            VxSdk::IVxConfiguration::Motion* _configMotion;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The Node class represents an individual host machine (a "node") within a cluster.
        /// </summary>
        ref class Node {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigNode">The vx node configuration.</param>
            Node(VxSdk::IVxConfiguration::Node* vxConfigNode);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Node() {
                this->!Node();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Node();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets the host alias for the arbiter node.
            /// </summary>
            /// <value>The host alias.</value>
            property System::String^ ArbiterAlias {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configNode->arbiterAlias); }
            }

            /// <summary>
            /// Gets the port number that the arbiter node uses.
            /// </summary>
            /// <value>The port number.</value>
            property int ArbiterPort {
            public:
                int get() { return _configNode->arbiterPort; }
            }

            /// <summary>
            /// Gets the host address.
            /// </summary>
            /// <value>The host address.</value>
            property System::String^ HostAddress {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configNode->hostAddress); }
            }

            /// <summary>
            /// Gets whether or not this node is an arbiter.
            /// </summary>
            /// <value><c>true</c> if this node is an arbiter, otherwise <c>false</c>.</value>
            property bool IsArbiter {
            public:
                bool get() { return _configNode->isArbiter; }
            }

            /// <summary>
            /// Gets the current configuration status of this node.
            /// </summary>
            /// <value>The configuration status.</value>
            property ConfigStatus Status {
            public:
                ConfigStatus get() { return (ConfigStatus)_configNode->status; }
            }


            /// <summary>
            /// Gets the particular type of node this is.
            /// </summary>
            /// <value>The node type.</value>
            property NodeType Type {
            public:
                NodeType get() { return (NodeType)_configNode->type; }
            }

        internal:
            VxSdk::IVxConfiguration::Node* _configNode;
        };

        /// <summary>
        /// The Server class represents general server configuration.
        /// </summary>
        ref class Server {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigServer">The vx server configuration.</param>
            Server(VxSdk::IVxConfiguration::Server* vxConfigServer);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Server() {
                this->!Server();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Server();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Restarts the server; generally required after any port changes to have them take effect.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of restarting the server.</returns>
            Results::Value Restart();

            /// <summary>
            /// Gets or sets the HTTP port number.
            /// </summary>
            /// <value>The HTTP port number.</value>
            property int HttpPort {
            public:
                int get() { return _configServer->httpPort; }
                void set(int value) { _configServer->SetHttpPort(value); }
            }

            /// <summary>
            /// Gets or sets the HTTPS port number.
            /// </summary>
            /// <value>The HTTPS port number.</value>
            property int HttpsPort {
            public:
                int get() { return _configServer->httpsPort; }
                void set(int value) { _configServer->SetHttpsPort(value); }
            }

            /// <summary>
            /// Gets or sets whether or not hostname lookup from IP is enabled.
            /// </summary>
            /// <value><c>true</c> to enable hostname lookup, otherwise <c>false</c>.</value>
            property bool IsReverseDnsLookupEnabled {
            public:
                bool get() { return _configServer->isReverseDnsLookupEnabled; }
                void set(bool value) { value ? _configServer->EnableReverseDnsLookup() : _configServer->DisableReverseDnsLookup(); }
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
            /// Gets or sets the RTSP port number.
            /// </summary>
            /// <value>The RTSP port number.</value>
            property int RtspPort {
            public:
                int get() { return _configServer->rtspPort; }
                void set(int value) { _configServer->SetRtspPort(value); }
            }

        internal:
            VxSdk::IVxConfiguration::Server* _configServer;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The Smtp class represents the SMTP configuration.
        /// </summary>
        ref class Smtp {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigSmtp">The vx SMTP configuration.</param>
            Smtp(VxSdk::IVxConfiguration::Smtp* vxConfigSmtp);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Smtp() {
                this->!Smtp();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Smtp();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Validate the given SMTP information by attempting to use it to send a test email.
            /// </summary>
            /// <param name="smtpInfo">The SMTP information to validate.</param>
            /// <returns><c>true</c> if sending the test email was successful, otherwise <c>false</c>.</returns>
            bool ValidateSmtpInfo(SmtpInfo^ smtpInfo);

            /// <summary>
            /// Gets or sets the "Mail From" email address.
            /// </summary>
            /// <value>The "Mail From" email address.</value>
            property System::String^ FromAddress {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configSmtp->fromAddress); }
                void set(System::String^ value) {
                    char fromAddress[256];
                    VxSdk::Utilities::StrCopySafe(fromAddress, Utils::ConvertCSharpString(value).c_str());
                    _configSmtp->SetFromAddress(fromAddress);
                }
            }

            /// <summary>
            /// Gets or sets the SMTP host.
            /// </summary>
            /// <value>The SMTP host.</value>
            property System::String^ Host {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configSmtp->host); }
                void set(System::String^ value) {
                    char host[256];
                    VxSdk::Utilities::StrCopySafe(host, Utils::ConvertCSharpString(value).c_str());
                    _configSmtp->SetHost(host);
                }
            }

            /// <summary>
            /// Gets or sets whether or not validation of the servers certificate is enforced.
            /// </summary>
            /// <value><c>true</c> to enable certificate validation, otherwise <c>false</c>.</value>
            property bool IsValidateCertEnabled {
            public:
                bool get() { return _configSmtp->isValidateCertEnabled; }
                void set(bool value) { value ? _configSmtp->EnableCertValidation() : _configSmtp->DisableCertValidation(); }
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
            /// Sets the password for SMTP access.
            /// </summary>
            /// <value>The password.</value>
            property System::String^ Password {
            public:
                void set(System::String^ value) {
                    char password[64];
                    VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(value).c_str());
                    _configSmtp->SetPassword(password);
                }
            }

            /// <summary>
            /// Gets or sets the SMTP port.
            /// </summary>
            /// <value>The SMTP port.</value>
            property int SmtpPort {
            public:
                int get() { return _configSmtp->smtpPort; }
                void set(int value) { _configSmtp->SetSmtpPort(value); }
            }

            /// <summary>
            /// Gets or sets the timeout in milliseconds.
            /// </summary>
            /// <value>The timeout in milliseconds.</value>
            property int Timeout {
            public:
                int get() { return _configSmtp->timeout; }
                void set(int value) { _configSmtp->SetTimeout(value); }
            }

            /// <summary>
            /// Gets or sets the username for SMTP access.
            /// </summary>
            /// <value>The username.</value>
            property System::String^ Username {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configSmtp->username); }
                void set(System::String^ value) {
                    char username[64];
                    VxSdk::Utilities::StrCopySafe(username, Utils::ConvertCSharpString(value).c_str());
                    _configSmtp->SetUsername(username);
                }
            }

            /// <summary>
            /// Gets or sets whether SMTPS should be used instead of SMTP.
            /// </summary>
            /// <value><c>true</c> to use SMTPS, <c>false</c> to use SMTP.</value>
            property bool UseSmtps {
            public:
                bool get() { return _configSmtp->useSmtps; }
                void set(bool value) { value ? _configSmtp->EnableSmtps() : _configSmtp->DisableSmtps(); }
            }

        internal:
            VxSdk::IVxConfiguration::Smtp* _configSmtp;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The Snmp class represents the SNMP agent configuration.
        /// </summary>
        ref class Snmp {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigSnmp">The vx SNMP configuration.</param>
            Snmp(VxSdk::IVxConfiguration::Snmp* vxConfigSnmp);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Snmp() {
                this->!Snmp();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Snmp();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets any limits related to this resource.
            /// </summary>
            /// <value>The limits related to this resource.</value>
            property ResourceLimits^ Limits {
            public:
                ResourceLimits^ get() { return _GetLimits(); }
            }

            /// <summary>
            /// Gets or sets the port on which to provide access to SNMP.
            /// </summary>
            /// <value>The port.</value>
            property int SnmpPort {
            public:
                int get() { return _configSnmp->snmpPort; }
                void set(int value) { _configSnmp->SetSnmpPort(value); }
            }

            /// <summary>
            /// Gets or sets the SNMP v2c community string.
            /// </summary>
            /// <value>The community string.</value>
            property System::String^ V2cReadCommunityString {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configSnmp->v2cReadCommunityString); }
                void set(System::String^ value) {
                    char v2cReadCommunityString[256];
                    VxSdk::Utilities::StrCopySafe(v2cReadCommunityString, Utils::ConvertCSharpString(value).c_str());
                    _configSnmp->SetV2cReadCommunityString(v2cReadCommunityString);
                }
            }

            /// <summary>
            /// Gets or sets the SNMP v3 authentication protocol.
            /// </summary>
            /// <value>The authentication protocol.</value>
            property AuthProtocol V3AuthProtocol {
            public:
                AuthProtocol get() { return (AuthProtocol)_configSnmp->v3AuthProtocol; }
                void set(AuthProtocol value) { _configSnmp->SetV3AuthProtocol((VxSdk::VxAuthProtocol::Value)value); }
            }

            /// <summary>
            /// Gets or sets the SNMP v3 privacy protocol.
            /// </summary>
            /// <value>The privacy protocol.</value>
            property PrivacyProtocol V3PrivacyProtocol {
            public:
                PrivacyProtocol get() { return (PrivacyProtocol)_configSnmp->v3PrivacyProtocol; }
                void set(PrivacyProtocol value) { _configSnmp->SetV3PrivacyProtocol((VxSdk::VxPrivacyProtocol::Value)value); }
            }

            /// <summary>
            /// Gets or sets the SNMP v3 read auth password.
            /// </summary>
            /// <value>The read auth password.</value>
            property System::String^ V3ReadAuthPassword {
            public:
                void set(System::String^ value) {
                    char password[64];
                    VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(value).c_str());
                    _configSnmp->SetV3ReadAuthPassword(password);
                }
            }

            /// <summary>
            /// Sets the SNMP v3 read privacy password.
            /// </summary>
            /// <value>The read privacy password.</value>
            property System::String^ V3ReadPrivacyPassword {
            public:
                void set(System::String^ value) {
                    char password[64];
                    VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(value).c_str());
                    _configSnmp->SetV3ReadPrivacyPassword(password);
                }
            }

            /// <summary>
            /// Gets or sets the SNMP v3 read username.
            /// </summary>
            /// <value>The read username.</value>
            property System::String^ V3ReadUsername {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configSnmp->v3ReadUsername); }
                void set(System::String^ value) {
                    char v3ReadUsername[256];
                    VxSdk::Utilities::StrCopySafe(v3ReadUsername, Utils::ConvertCSharpString(value).c_str());
                    _configSnmp->SetV3ReadUsername(v3ReadUsername);
                }
            }

            /// <summary>
            /// Gets or sets which version of SNMP is enabled.
            /// </summary>
            /// <value>The SNMP version to enable.</value>
            property SnmpVersion Version {
            public:
                SnmpVersion get() { return (SnmpVersion)_configSnmp->version; }
                void set(SnmpVersion value) { _configSnmp->SetVersion((VxSdk::VxSnmpVersion::Value)value); }
            }

        internal:
            VxSdk::IVxConfiguration::Snmp* _configSnmp;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The Storage class represents a VxStorage-specific configuration.
        /// </summary>
        ref class Storage {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigStorage">The vx storage configuration.</param>
            Storage(VxSdk::IVxConfiguration::Storage* vxConfigStorage);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Storage() {
                this->!Storage();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Storage();

            /// <summary>
            /// Creates a new volume on the storage.
            /// </summary>
            /// <param name="newVolume">The new volume to be created.</param>
            /// <returns>The <see cref="Results::Value">Result</see> of creating the volume.</returns>
            Results::Value CreateVolume(NewVolume^ newVolume);

            /// <summary>
            /// Creates a new volume group on the storage.
            /// </summary>
            /// <param name="newVolumeGroup">The new volume group to be created.</param>
            /// <returns>The <see cref="Results::Value">Result</see> of creating the volume group.</returns>
            Results::Value CreateVolumeGroup(NewVolumeGroup^ newVolumeGroup);

            /// <summary>
            /// Delete a volume from the storage.
            /// </summary>
            /// <param name="volume">The volume to be deleted from the storage.</param>
            /// <returns>The <see cref="Results::Value">Result</see> of deleting the volume.</returns>
            Results::Value DeleteVolume(Volume^ volume);

            /// <summary>
            /// Delete a volume group from the storage.
            /// </summary>
            /// <param name="volumeGroup">The volume group to be deleted from the storage.</param>
            /// <returns>The <see cref="Results::Value">Result</see> of deleting the volume group.</returns>
            Results::Value DeleteVolumeGroup(VolumeGroup^ volumeGroup);

            /// <summary>
            /// Get the volume groups for this storage using an optional collection filter.
            /// <para>Available filters: Archive, Id, ModifiedSince, Name.</para>
            /// </summary>
            /// <param name="filters">The collection filters to be used in the request.</param>
            /// <returns>A <c>List</c> containing the volume groups.</returns>
            System::Collections::Generic::List<VolumeGroup^>^ GetVolumeGroups(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

            /// <summary>
            /// Get the volumes for this storage using an optional collection filter.
            /// <para>Available filters: Id, ModifiedSince.</para>
            /// </summary>
            /// <param name="filters">The collection filters to be used in the request.</param>
            /// <returns>A <c>List</c> containing the volumes.</returns>
            System::Collections::Generic::List<Volume^>^ GetVolumes(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

            /// <summary>
            /// Rebuilds the database. Has no effect if the database is already rebuilding.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of starting the database rebuild.</returns>
            Results::Value RebuildDatabase();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets a list of device IDs belonging to this VxStorage failover group (including itself).
            /// </summary>
            /// <value>The list of device IDs.</value>
            property System::Collections::Generic::List<System::String^>^ FailoverGroup {
            public:
                System::Collections::Generic::List<System::String^>^ get() { return _GetFailoverGroup(); }
            }

            /// <summary>
            /// Gets or sets the maximum recording bitrate for this VxStorage when enabled as a failover unit (in Mbps).
            /// </summary>
            /// <value>The bitrate.</value>
            property int FailoverMaxRecordingBitrate {
            public:
                int get() { return _configStorage->failoverMaxRecordingBitrate; }
                void set(int value) { _configStorage->SetFailoverMaxRecordingBitrate(value); }
            }

            /// <summary>
            /// Gets the file recovery control and monitor resource for this VxStorage.
            /// </summary>
            /// <value>The file recovery resource.</value>
            property FileRecovery^ FileRecoveryResource {
            public:
                FileRecovery^ get() { return _GetFileRecovery(); }
            }

            /// <summary>
            /// Gets or sets the maximum number of attempts to fill a gap before giving up.
            /// </summary>
            /// <value>The number of attempts.</value>
            property int GapFillerAttempts {
            public:
                int get() { return _configStorage->gapFillerAttempts; }
                void set(int value) { _configStorage->SetGapFillerAttempts(value); }
            }

            /// <summary>
            /// Gets or sets the maximum number of concurrent downloads.
            /// </summary>
            /// <value>The number of concurrent downloads.</value>
            property int GapFillerDownloads {
            public:
                int get() { return _configStorage->gapFillerDownloads; }
                void set(int value) { _configStorage->SetGapFillerDownloads(value); }
            }

            /// <summary>
            /// Gets or sets the interval, in seconds, to reattempt to automatically fill a gap.
            /// </summary>
            /// <value>The interval in seconds.</value>
            property int GapFillerInterval {
            public:
                int get() { return _configStorage->gapFillerInterval; }
                void set(int value) { _configStorage->SetGapFillerInterval(value); }
            }

            /// <summary>
            /// Gets or sets whether or not this VxStorage is designated as a failover unit.
            /// </summary>
            /// <value><c>true</c> to designate this as a failover unit, otherwise <c>false</c>.</value>
            property bool IsFailoverEnabled {
            public:
                bool get() { return _configStorage->isFailoverEnabled; }
                void set(bool value) { value ? _configStorage->EnableFailover() : _configStorage->DisableFailover(); }
            }

            /// <summary>
            /// Gets or sets whether or not automatic gap filling is enabled.
            /// </summary>
            /// <value><c>true</c> to enable automatic gap filling, otherwise <c>false</c>.</value>
            property bool IsGapFillerEnabled {
            public:
                bool get() { return _configStorage->isGapFillerEnabled; }
                void set(bool value) { value ? _configStorage->EnableGapFiller() : _configStorage->DisableGapFiller(); }
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
            /// Gets or sets the amount of time, in seconds, to allow a manual recording to be active.
            /// </summary>
            /// <value>The timeout in seconds.</value>
            property int ManualRecordingTimeout {
            public:
                int get() { return _configStorage->manualRecordingTimeout; }
                void set(int value) { _configStorage->SetManualRecordingTimeout(value); }
            }

            /// <summary>
            /// Gets or sets the maximum outbound bitrate for this VxStorage (in Mbps).
            /// </summary>
            /// <value>The bitrate in Mbps.</value>
            property int MaxOutboundBitrate {
            public:
                int get() { return _configStorage->maxOutboundBitrate; }
                void set(int value) { _configStorage->SetMaxOutboundBitrate(value); }
            }

            /// <summary>
            /// Gets or sets a list of device IDs being monitored for failover.
            /// </summary>
            /// <value>The list of device IDs.</value>
            property System::Collections::Generic::List<System::String^>^ MonitoredDeviceIds {
            public:
                System::Collections::Generic::List<System::String^>^ get() { return _GetMonitoredDeviceIds(); }
                void set(System::Collections::Generic::List<System::String^>^ value) { _SetMonitoredDeviceIds(value); }
            }

            /// <summary>
            /// Gets or sets the retention limit, in hours, on recorded data.
            /// </summary>
            /// <value>The retention limit.</value>
            property int RetentionLimit {
            public:
                int get() { return _configStorage->retentionLimit; }
                void set(int value) { _configStorage->SetRetentionLimit(value); }
            }

            /// <summary>
            /// Gets or sets network communication transmission type preference.
            /// </summary>
            /// <value>The transmission type preference.</value>
            property TransmissionTypes TransmissionPreference {
            public:
                TransmissionTypes get() { return (TransmissionTypes)_configStorage->transmissionPreference; }
                void set(TransmissionTypes value) { _configStorage->SetTransmissionPreference((VxSdk::VxTransmissionType::Value)value); }
            }

            /// <summary>
            /// Gets the network communication transmission type preference.
            /// </summary>
            /// <remarks>
            /// DEPRECATED: This has been replaced by <see cref="TransmissionPreference"/> and will be removed in
            /// the future.
            /// </remarks>
            /// <value>The transmission type.</value>
            property System::String^ TransmissionType {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configStorage->transmissionType); }
            }

            /// <summary>
            /// Gets or sets the stream to record from for all assigned data sources (when scheduled to record).
            /// </summary>
            /// <value>The stream to record.</value>
            property StreamSource VideoStreamRecordingSource {
            public:
                StreamSource get() { return (StreamSource)_configStorage->videoStreamRecordingSource; }
                void set(StreamSource value) { _configStorage->SetVideoStreamRecordingSource((VxSdk::VxStreamSource::Value)value); }
            }

            /// <summary>
            /// Gets the volume groups for this storage.
            /// </summary>
            /// <value>A <c>List</c> of volume groups.</value>
            property System::Collections::Generic::List<VolumeGroup^>^ VolumeGroups {
            public:
                System::Collections::Generic::List<VolumeGroup^>^ get() { return GetVolumeGroups(nullptr); }
            }

            /// <summary>
            /// Gets the volumes for this storage.
            /// </summary>
            /// <value>A <c>List</c> of volumes.</value>
            property System::Collections::Generic::List<Volume^>^ Volumes {
            public:
                System::Collections::Generic::List<Volume^>^ get() { return GetVolumes(nullptr); }
            }

        internal:
            VxSdk::IVxConfiguration::Storage* _configStorage;
            System::Collections::Generic::List<System::String^>^ _GetFailoverGroup();
            FileRecovery^ _GetFileRecovery();
            VxSdkNet::ResourceLimits^ _GetLimits();
            System::Collections::Generic::List<System::String^>^ _GetMonitoredDeviceIds();
            void _SetMonitoredDeviceIds(System::Collections::Generic::List<System::String^>^ deviceIds);
        };

        /// <summary>
        /// The Time class represents a time configuration.
        /// </summary>
        ref class Time {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigTime">The vx time configuration.</param>
            Time(VxSdk::IVxConfiguration::Time* vxConfigTime);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Time() {
                this->!Time();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Time();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets a value indicating whether or not the external time server is enabled.
            /// </summary>
            /// <value><c>true</c> if the external time server is enabled, <c>false</c> if disabled.</value>
            property bool IsTimeServerEnabled {
            public:
                bool get() { return _configTime->isTimeServerEnabled; }
            }

            /// <summary>
            /// Gets the current internal system time.
            /// </summary>
            /// <value>The current internal system time.</value>
            property System::DateTime CurrentTime {
            public:
                System::DateTime get() {
                    char time[64];
                    _configTime->GetTime(time);
                    return Utils::ConvertCppDateTime(time);
                }
            }

            /// <summary>
            /// Gets the host address of the external time server.
            /// </summary>
            /// <value>The external time server host address.</value>
            property System::String^ TimeServerAddress {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configTime->timeServerAddress); }
            }

        internal:
            VxSdk::IVxConfiguration::Time* _configTime;
        };

        /// <summary>
        /// The Twilio class represents Twilio (twilio.com) SMS account configuration.
        /// </summary>
        ref class Twilio {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigTwilio">The vx Twilio configuration.</param>
            Twilio(VxSdk::IVxConfiguration::Twilio* vxConfigTwilio);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Twilio() {
                this->!Twilio();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Twilio();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Validates the given Twilio info by attempting to use it to send a test SMS.
            /// </summary>
            /// <param name="accountSid">A Twilio account SID.</param>
            /// <param name="authToken">A Twilio account authorization token.</param>
            /// <param name="fromNumber">A Twilio phone number capable of sending SMS (e.g., +15595551234).</param>
            /// <param name="toNumber">A phone number capable of receiving SMS to send messages to (e.g., +15595551234).</param>
            /// <returns><c>true</c> if sending the test SMS was successful, otherwise <c>false</c>.</returns>
            bool ValidateTwilioInfo(System::String^ accountSid, System::String^ authToken, System::String^ fromNumber, System::String^ toNumber);

            /// <summary>
            /// Gets or sets the Twilio account SID.
            /// </summary>
            /// <value>The Twilio account SID.</value>
            property System::String^ AccountSid {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configTwilio->accountSid); }
                void set(System::String^ value) {
                    char accountSid[256];
                    VxSdk::Utilities::StrCopySafe(accountSid, Utils::ConvertCSharpString(value).c_str());
                    _configTwilio->SetAccountSid(accountSid);
                }
            }

            /// <summary>
            /// Sets the Twilio account authorization token.
            /// </summary>
            /// <value>The Twilio account authorization token.</value>
            property System::String^ AuthToken {
            public:
                void set(System::String^ value) {
                    char authToken[512];
                    VxSdk::Utilities::StrCopySafe(authToken, Utils::ConvertCSharpString(value).c_str());
                    _configTwilio->SetAuthToken(authToken);
                }
            }

            /// <summary>
            /// Gets or sets a Twilio phone number capable of sending SMS (e.g., +15595551234).
            /// </summary>
            /// <value>A Twilio phone number.</value>
            property System::String^ FromNumber {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configTwilio->fromNumber); }
                void set(System::String^ value) {
                    char fromNumber[64];
                    VxSdk::Utilities::StrCopySafe(fromNumber, Utils::ConvertCSharpString(value).c_str());
                    _configTwilio->SetFromNumber(fromNumber);
                }
            }

            /// <summary>
            /// Gets or sets whether or not SMS messaging via Twilio is enabled.
            /// </summary>
            /// <value><c>true</c> to enable SMS messaging via Twilio, otherwise <c>false</c>.</value>
            property bool IsEnabled {
            public:
                bool get() { return _configTwilio->isEnabled; }
                void set(bool value) { value ? _configTwilio->Enable() : _configTwilio->Disable(); }
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
            VxSdk::IVxConfiguration::Twilio* _configTwilio;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

    internal:
        Configuration() { };
    };
}
#endif // Configuration_h__
