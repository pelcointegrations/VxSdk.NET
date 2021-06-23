/// <summary>
/// Implements the configuration class.
/// </summary>
#include "Configuration.h"
#include "LdapValidationCredentials.h"
#include "NewUser.h"
#include "NewVolume.h"
#include "NewVolumeGroup.h"
#include "SmtpInfo.h"
#include "Volume.h"
#include "VolumeGroup.h"

using namespace System::Collections::Generic;

// ====================================================================================================================
// VxSdkNet::Configuration::Auth
// ====================================================================================================================

VxSdkNet::Configuration::Auth::Auth(VxSdk::IVxConfiguration::Auth* vxConfigAuth) {
    _configAuth = vxConfigAuth;
}

VxSdkNet::Configuration::Auth::!Auth() {
    _configAuth->Delete();
    _configAuth = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Auth::Refresh() {
    return (VxSdkNet::Results::Value)_configAuth->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Auth::SetPassword(System::String^ newPassword, bool mustChangePassword) {
    char password[1024];
    VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(newPassword).c_str());
    VxSdk::VxResult::Value result = _configAuth->SetPassword(password, mustChangePassword);

    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Auth::SetUser(NewUser^ user) {
    // Create a new user object and populate its fields using user
    VxSdk::VxNewUser vxNewUser;
    VxSdk::Utilities::StrCopySafe(vxNewUser.domain, Utils::ConvertCSharpString(user->Domain).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.email, Utils::ConvertCSharpString(user->Email).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.employeeId, Utils::ConvertCSharpString(user->EmployeeId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.firstName, Utils::ConvertCSharpString(user->FirstName).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.lastName, Utils::ConvertCSharpString(user->LastName).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.name, Utils::ConvertCSharpString(user->Name).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.note, Utils::ConvertCSharpString(user->Note).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.password, Utils::ConvertCSharpString(user->Password).c_str());
    vxNewUser.mustChangePassword = user->MustChangePassword;
    vxNewUser.canBypassLdap = user->CanBypassLdap;
    vxNewUser.isPasswordExpirationDisabled = user->IsPasswordExpirationDisabled;
    vxNewUser.phoneNumberSize = user->PhoneNumbers->Count;
    if (vxNewUser.phoneNumberSize > 0) {
        vxNewUser.phoneNumbers = new VxSdk::VxPhoneNumber[vxNewUser.phoneNumberSize];
        for (int i = 0; i < vxNewUser.phoneNumberSize; i++) {
            vxNewUser.phoneNumbers[i].type = (VxSdk::VxPhoneType::Value)user->PhoneNumbers[i].Key;
            VxSdk::Utilities::StrCopySafe(vxNewUser.phoneNumbers[i].number, Utils::ConvertCSharpString(user->PhoneNumbers[i].Value).c_str());
        }
    }

    // Make the call to set the user
    VxSdk::VxResult::Value result = _configAuth->SetUser(vxNewUser);

    return VxSdkNet::Results::Value(result);
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Auth::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configAuth->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Bookmark
// ====================================================================================================================

VxSdkNet::Configuration::Bookmark::Bookmark(VxSdk::IVxConfiguration::Bookmark* vxConfigBookmark) {
    _configBookmark = vxConfigBookmark;
}

VxSdkNet::Configuration::Bookmark::!Bookmark() {
    _configBookmark->Delete();
    _configBookmark = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Bookmark::Refresh() {
    return (VxSdkNet::Results::Value)_configBookmark->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Bookmark::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configBookmark->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Cluster
// ====================================================================================================================

VxSdkNet::Configuration::Cluster::Cluster(VxSdk::IVxConfiguration::Cluster* vxConfigCluster) {
    _configCluster = vxConfigCluster;
}

VxSdkNet::Configuration::Cluster::!Cluster() {
    _configCluster->Delete();
    _configCluster = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Cluster::Refresh() {
    return (VxSdkNet::Results::Value)_configCluster->Refresh();
}

bool VxSdkNet::Configuration::Cluster::ValidateExportPath(NetworkStorageInfo^ exportStorageInfo) {   
    // Create a new network storage info object and populate its fields using exportStorageInfo
    VxSdk::VxNetworkStorageInfo vxNetworkStorageInfo;
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.password, Utils::ConvertCSharpString(exportStorageInfo->Password).c_str());
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.path, Utils::ConvertCSharpString(exportStorageInfo->Path).c_str());
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.username, Utils::ConvertCSharpString(exportStorageInfo->Username).c_str());

    bool result;
    // Make the call to validate the export path
    _configCluster->ValidateExportPath(result, vxNetworkStorageInfo);

    return result;
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Cluster::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configCluster->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

System::Collections::Generic::List<VxSdkNet::Configuration::Node^>^ VxSdkNet::Configuration::Cluster::_GetNodeConfigurations() {
    // Create a list of managed node objects
    List<Node^>^ mlist = gcnew List<Node^>();
    // Create a collection of unmanaged node objects
    VxSdk::VxCollection<VxSdk::IVxConfiguration::Node**> nodes;

    // Make the GetNodeConfigurations call, which will return with the total count of nodes, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _configCluster->GetNodeConfigurations(nodes);
    // Unless there are no nodes on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetNodeConfigurations call
        nodes.collection = new VxSdk::IVxConfiguration::Node*[nodes.collectionSize];
        result = _configCluster->GetNodeConfigurations(nodes);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < nodes.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Configuration::Node(nodes.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] nodes.collection;
    }
    return mlist;
}

VxSdkNet::Configuration::Time^ VxSdkNet::Configuration::Cluster::_GetTimeConfig() {
    // Get the time config for the cluster
    VxSdk::IVxConfiguration::Time* time = nullptr;
    VxSdk::VxResult::Value result = _configCluster->GetTimeConfig(time);

    // Return the time config if GetTimeConfig was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Configuration::Time(time);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Event
// ====================================================================================================================

VxSdkNet::Configuration::Event::Event(VxSdk::IVxConfiguration::Event* vxConfigEvent) {
    _configEvent = vxConfigEvent;
}

VxSdkNet::Configuration::Event::!Event() {
    _configEvent->Delete();
    _configEvent = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Event::Refresh() {
    return (VxSdkNet::Results::Value)_configEvent->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Event::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configEvent->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Export
// ====================================================================================================================

VxSdkNet::Configuration::Export::Export(VxSdk::IVxConfiguration::Export* vxConfigExport) {
    _configExport = vxConfigExport;
}

VxSdkNet::Configuration::Export::!Export() {
    _configExport->Delete();
    _configExport = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Export::Refresh() {
    return (VxSdkNet::Results::Value)_configExport->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Export::SetProtectPassword(System::String^ globalPassword) {
    char password[1024];
    VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(globalPassword).c_str());

    return (VxSdkNet::Results::Value)_configExport->SetProtectPassword(password);
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Export::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configExport->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Ldap
// ====================================================================================================================

VxSdkNet::Configuration::Ldap::Ldap(VxSdk::IVxConfiguration::Ldap* vxConfigLdap) {
    _configLdap = vxConfigLdap;
}

VxSdkNet::Configuration::Ldap::!Ldap() {
    _configLdap->Delete();
    _configLdap = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Ldap::Refresh() {
    return (VxSdkNet::Results::Value)_configLdap->Refresh();
}

bool VxSdkNet::Configuration::Ldap::ValidateLdapCredentials(LdapValidationCredentials^ ldapCredentials) {
    bool isValid = false;
    VxSdk::VxLdapValidationCredentials vxLdapValidationCredentials;
    vxLdapValidationCredentials.isServerTlsEnabled = ldapCredentials->IsServerTlsEnabled;
    vxLdapValidationCredentials.isSsoEnabled = ldapCredentials->IsSsoEnabled;
    vxLdapValidationCredentials.isTwoStageBindingEnabled = ldapCredentials->IsTwoStageBindingEnabled;
    vxLdapValidationCredentials.serverPort = ldapCredentials->ServerPort;
    vxLdapValidationCredentials.useLdapUsersAndRoles = ldapCredentials->UseLdapUsersAndRoles;
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.baseDn, Utils::ConvertCSharpString(ldapCredentials->BaseDn).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.objectClasses, Utils::ConvertCSharpString(ldapCredentials->ObjectClasses).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.password, Utils::ConvertCSharpString(ldapCredentials->Password).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.searchAttributes, Utils::ConvertCSharpString(ldapCredentials->SearchAttributes).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.searchDnAccount, Utils::ConvertCSharpString(ldapCredentials->SearchDnAccount).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.searchDnPassword, Utils::ConvertCSharpString(ldapCredentials->SearchDnPassword).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.serverName, Utils::ConvertCSharpString(ldapCredentials->ServerName).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.ssoDomain, Utils::ConvertCSharpString(ldapCredentials->SsoDomain).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.username, Utils::ConvertCSharpString(ldapCredentials->Username).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.vxRootDn, Utils::ConvertCSharpString(ldapCredentials->VxRootDn).c_str());
    VxSdk::Utilities::StrCopySafe(vxLdapValidationCredentials.vxSystemDn, Utils::ConvertCSharpString(ldapCredentials->VxSystemDn).c_str());
    _configLdap->ValidateLdapCredentials(isValid, vxLdapValidationCredentials);

    return isValid;
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Ldap::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configLdap->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Motion
// ====================================================================================================================

VxSdkNet::Configuration::Motion::Motion(VxSdk::IVxConfiguration::Motion* vxConfigMotion) {
    _configMotion = vxConfigMotion;
}

VxSdkNet::Configuration::Motion::!Motion() {
    _configMotion->Delete();
    _configMotion = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Motion::Refresh() {
    return (VxSdkNet::Results::Value)_configMotion->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Motion::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configMotion->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Node
// ====================================================================================================================

VxSdkNet::Configuration::Node::Node(VxSdk::IVxConfiguration::Node* vxConfigNode) {
    _configNode = vxConfigNode;
}

VxSdkNet::Configuration::Node::!Node() {
    _configNode->Delete();
    _configNode = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Node::Refresh() {
    return (VxSdkNet::Results::Value)_configNode->Refresh();
}

// ====================================================================================================================
// VxSdkNet::Configuration::Report
// ====================================================================================================================

VxSdkNet::Configuration::Report::Report(VxSdk::IVxConfiguration::Report* vxConfigReport) {
    _configReport = vxConfigReport;
}

VxSdkNet::Configuration::Report::!Report() {
    _configReport->Delete();
    _configReport = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Report::Refresh() {
    return (VxSdkNet::Results::Value)_configReport->Refresh();
}

void VxSdkNet::Configuration::Report::_SetStorageLocation(VxSdkNet::NetworkStorageInfo^ storageInfo) {
    VxSdk::VxNetworkStorageInfo vxNetworkStorageInfo;
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.password, Utils::ConvertCSharpString(storageInfo->Password).c_str());
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.path, Utils::ConvertCSharpString(storageInfo->Path).c_str());
    VxSdk::Utilities::StrCopySafe(vxNetworkStorageInfo.username, Utils::ConvertCSharpString(storageInfo->Username).c_str());
    _configReport->SetStorageLocation(vxNetworkStorageInfo);
}

// ====================================================================================================================
// VxSdkNet::Configuration::Server
// ====================================================================================================================

VxSdkNet::Configuration::Server::Server(VxSdk::IVxConfiguration::Server* vxConfigServer) {
    _configServer = vxConfigServer;
}

VxSdkNet::Configuration::Server::!Server() {
    _configServer->Delete();
    _configServer = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Server::Refresh() {
    return (VxSdkNet::Results::Value)_configServer->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Server::Restart() {
    return (VxSdkNet::Results::Value)_configServer->Restart();
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Server::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configServer->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Smtp
// ====================================================================================================================

VxSdkNet::Configuration::Smtp::Smtp(VxSdk::IVxConfiguration::Smtp* vxConfigSmtp) {
    _configSmtp = vxConfigSmtp;
}

VxSdkNet::Configuration::Smtp::!Smtp() {
    _configSmtp->Delete();
    _configSmtp = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Smtp::Refresh() {
    return (VxSdkNet::Results::Value)_configSmtp->Refresh();
}

bool VxSdkNet::Configuration::Smtp::ValidateSmtpInfo(SmtpInfo^ smtpInfo) {
    bool isValid = false;
    VxSdk::VxSmtpInfo vxSmtpInfo;
    vxSmtpInfo.smtpPort = smtpInfo->SmtpPort;
    vxSmtpInfo.timeout = smtpInfo->Timeout;
    vxSmtpInfo.useSmtps = smtpInfo->UseSmtps;
    VxSdk::Utilities::StrCopySafe(vxSmtpInfo.fromAddress, Utils::ConvertCSharpString(smtpInfo->FromAddress).c_str());
    VxSdk::Utilities::StrCopySafe(vxSmtpInfo.host, Utils::ConvertCSharpString(smtpInfo->Host).c_str());
    VxSdk::Utilities::StrCopySafe(vxSmtpInfo.password, Utils::ConvertCSharpString(smtpInfo->Password).c_str());
    VxSdk::Utilities::StrCopySafe(vxSmtpInfo.username, Utils::ConvertCSharpString(smtpInfo->Username).c_str());
    VxSdk::Utilities::StrCopySafe(vxSmtpInfo.toAddress, Utils::ConvertCSharpString(smtpInfo->ToAddress).c_str());
    _configSmtp->ValidateSmtpInfo(isValid, vxSmtpInfo);

    return isValid;
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Smtp::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configSmtp->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Snmp
// ====================================================================================================================

VxSdkNet::Configuration::Snmp::Snmp(VxSdk::IVxConfiguration::Snmp* vxConfigSnmp) {
    _configSnmp = vxConfigSnmp;
}

VxSdkNet::Configuration::Snmp::!Snmp() {
    _configSnmp->Delete();
    _configSnmp = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Snmp::Refresh() {
    return (VxSdkNet::Results::Value)_configSnmp->Refresh();
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Snmp::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configSnmp->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Storage
// ====================================================================================================================

VxSdkNet::Configuration::Storage::Storage(VxSdk::IVxConfiguration::Storage* vxConfigStorage) {
    _configStorage = vxConfigStorage;
}

VxSdkNet::Configuration::Storage::!Storage() {
    _configStorage->Delete();
    _configStorage = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Storage::CreateVolume(NewVolume^ newVolume) {
    // Create a new volume object and populate its fields using newVolume
    VxSdk::VxNewVolume vxNewVolume;
    VxSdk::Utilities::StrCopySafe(vxNewVolume.domain, Utils::ConvertCSharpString(newVolume->Domain).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewVolume.password, Utils::ConvertCSharpString(newVolume->Password).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewVolume.path, Utils::ConvertCSharpString(newVolume->Path).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewVolume.username, Utils::ConvertCSharpString(newVolume->Username).c_str());
    vxNewVolume.isBandwidthReserved = newVolume->IsBandwidthReserved;
    vxNewVolume.buffer = newVolume->Buffer;

    // Make the call to add the volume to the storage
    VxSdk::VxResult::Value result = _configStorage->CreateVolume(vxNewVolume);

    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Storage::CreateVolumeGroup(NewVolumeGroup^ newVolumeGroup) {
    // Create a new volume group object and populate its fields using newVolumeGroup
    VxSdk::VxNewVolumeGroup vxNewVolumeGroup;
    VxSdk::Utilities::StrCopySafe(vxNewVolumeGroup.name, Utils::ConvertCSharpString(newVolumeGroup->Name).c_str());
    vxNewVolumeGroup.isArchiveGroup = newVolumeGroup->IsArchiveGroup;

    // Make the call to add the volume group to the storage
    VxSdk::VxResult::Value result = _configStorage->CreateVolumeGroup(vxNewVolumeGroup);

    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Storage::DeleteVolume(Volume^ volumeItem) {
    // To delete a volume simply make a DeleteVolume call
    VxSdk::VxResult::Value result = volumeItem->_volume->DeleteVolume();
    // Unless there was an issue deleting the volume the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Storage::DeleteVolumeGroup(VolumeGroup^ volumeGroupItem) {
    // To delete a volume group simply make a DeleteVolumeGroup call
    VxSdk::VxResult::Value result = volumeGroupItem->_volumeGroup->DeleteVolumeGroup();
    // Unless there was an issue deleting the volume group the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Storage::RebuildDatabase() {
    return (VxSdkNet::Results::Value)_configStorage->RebuildDatabase();
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Storage::Refresh() {
    return (VxSdkNet::Results::Value)_configStorage->Refresh();
}

List<VxSdkNet::VolumeGroup^>^ VxSdkNet::Configuration::Storage::GetVolumeGroups(Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed volume group objects
    List<VolumeGroup^>^ mlist = gcnew List<VolumeGroup^>();
    // Create a collection of unmanaged volume group objects
    VxSdk::VxCollection<VxSdk::IVxVolumeGroup**> volumeGroups;

    if (filters != nullptr && filters->Count > 0) {
        // Create our filter
        VxSdk::VxCollectionFilter* collFilters = new VxSdk::VxCollectionFilter[filters->Count];
        int i = 0;
        for each (KeyValuePair<Filters::Value, System::String^>^ kvp in filters)
        {
            collFilters[i].key = static_cast<VxSdk::VxCollectionFilterItem::Value>(kvp->Key);
            VxSdk::Utilities::StrCopySafe(collFilters[i++].value, Utils::ConvertCSharpString(kvp->Value).c_str());
        }

        // Add the filters to the collection 
        volumeGroups.filterSize = filters->Count;
        volumeGroups.filters = collFilters;
    }

    // Make the GetVolumeGroups call, which will return with the total volume group count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _configStorage->GetVolumeGroups(volumeGroups);
    // Unless there are no volume groups on the storage, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxVolumeGroup collection
        volumeGroups.collection = new VxSdk::IVxVolumeGroup * [volumeGroups.collectionSize];
        result = _configStorage->GetVolumeGroups(volumeGroups);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < volumeGroups.collectionSize; i++)
                mlist->Add(gcnew VolumeGroup(volumeGroups.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] volumeGroups.collection;
    }
    return mlist;
}

List<VxSdkNet::Volume^>^ VxSdkNet::Configuration::Storage::GetVolumes(Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed volume objects
    List<Volume^>^ mlist = gcnew List<Volume^>();
    // Create a collection of unmanaged volume objects
    VxSdk::VxCollection<VxSdk::IVxVolume**> volumes;

    if (filters != nullptr && filters->Count > 0) {
        // Create our filter
        VxSdk::VxCollectionFilter* collFilters = new VxSdk::VxCollectionFilter[filters->Count];
        int i = 0;
        for each (KeyValuePair<Filters::Value, System::String^>^ kvp in filters)
        {
            collFilters[i].key = static_cast<VxSdk::VxCollectionFilterItem::Value>(kvp->Key);
            VxSdk::Utilities::StrCopySafe(collFilters[i++].value, Utils::ConvertCSharpString(kvp->Value).c_str());
        }

        // Add the filters to the collection 
        volumes.filterSize = filters->Count;
        volumes.filters = collFilters;
    }

    // Make the GetVolumes call, which will return with the total volume count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _configStorage->GetVolumes(volumes);
    // Unless there are no volumes on the storage, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxVolume collection
        volumes.collection = new VxSdk::IVxVolume * [volumes.collectionSize];
        result = _configStorage->GetVolumes(volumes);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < volumes.collectionSize; i++)
                mlist->Add(gcnew Volume(volumes.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] volumes.collection;
    }
    return mlist;
}

System::Collections::Generic::List<System::String^>^ VxSdkNet::Configuration::Storage::_GetFailoverGroup() {
    // Create a list of strings
    List<System::String^>^ mlist = gcnew List<System::String^>();
    // Add each device id in the failover group to the string list
    for (int i = 0; i < _configStorage->failoverGroupSize; i++)
        mlist->Add(Utils::ConvertCppString(_configStorage->failoverGroup[i]));

    return mlist;
}

VxSdkNet::VxFileRecovery^ VxSdkNet::Configuration::Storage::_GetFileRecovery() {
    // Get the file recovery resource for the recorder
    VxSdk::IVxFileRecovery* fileRecovery = nullptr;
    VxSdk::VxResult::Value result = _configStorage->GetFileRecovery(fileRecovery);

    // Return the file recovery resource if GetFileRecovery was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::VxFileRecovery(fileRecovery);

    return nullptr;
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Storage::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configStorage->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

System::Collections::Generic::List<System::String^>^ VxSdkNet::Configuration::Storage::_GetMonitoredDeviceIds() {
    // Create a list of strings
    List<System::String^>^ mlist = gcnew List<System::String^>();
    // Add each monitored device id to the string list
    for (int i = 0; i < _configStorage->monitoredDeviceIdsSize; i++)
        mlist->Add(Utils::ConvertCppString(_configStorage->monitoredDeviceIds[i]));

    return mlist;
}

void VxSdkNet::Configuration::Storage::_SetMonitoredDeviceIds(List<System::String^>^ deviceIds) {
    int size = deviceIds->Count;
    char** monitoredDeviceIds = new char* [size];
    for (int i = 0; i < size; i++) {
        int idLength = deviceIds[i]->Length + 1;
        monitoredDeviceIds[i] = new char[idLength];
        VxSdk::Utilities::StrCopySafe(monitoredDeviceIds[i], Utils::ConvertCSharpString(deviceIds[i]).c_str(), idLength);
    }

    _configStorage->SetMonitoredDeviceIds(monitoredDeviceIds, size);
    for (int i = 0; i < size; i++) {
        delete monitoredDeviceIds[i];
        monitoredDeviceIds[i] = nullptr;
    }

    delete[] monitoredDeviceIds;
    monitoredDeviceIds = nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::ThermalEtd
// ====================================================================================================================

VxSdkNet::Configuration::ThermalEtd::ThermalEtd(VxSdk::IVxConfiguration::ThermalEtd* vxConfigThermalEtd) {
    _configThermalEtd = vxConfigThermalEtd;
}

VxSdkNet::Configuration::ThermalEtd::!ThermalEtd() {
    _configThermalEtd->Delete();
    _configThermalEtd = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::ThermalEtd::Refresh() {
    return (VxSdkNet::Results::Value)_configThermalEtd->Refresh();
}

// ====================================================================================================================
// VxSdkNet::Configuration::Time
// ====================================================================================================================

VxSdkNet::Configuration::Time::Time(VxSdk::IVxConfiguration::Time* vxConfigTime) {
    _configTime = vxConfigTime;
}

VxSdkNet::Configuration::Time::!Time() {
    _configTime->Delete();
    _configTime = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Time::Refresh() {
    return (VxSdkNet::Results::Value)_configTime->Refresh();
}

System::Collections::Generic::List<System::String^>^ VxSdkNet::Configuration::Time::_GetExternalTimeServers() {
    // Create a list of strings
    List<System::String^>^ mlist = gcnew List<System::String^>();
    // Add each external time server to the string list
    for (int i = 0; i < _configTime->externalTimeServersSize; i++)
        mlist->Add(Utils::ConvertCppString(_configTime->externalTimeServers[i]));

    return mlist;
}

void VxSdkNet::Configuration::Time::_SetExternalTimeServers(List<System::String^>^ timeServers) {
    int size = timeServers->Count;
    char** externalTimeServers = new char* [size];
    for (int i = 0; i < size; i++) {
        int serversLength = timeServers[i]->Length + 1;
        externalTimeServers[i] = new char[serversLength];
        VxSdk::Utilities::StrCopySafe(externalTimeServers[i], Utils::ConvertCSharpString(timeServers[i]).c_str(), serversLength);
    }

    _configTime->SetExternalTimeServers(externalTimeServers, size);
    for (int i = 0; i < size; i++) {
        delete externalTimeServers[i];
        externalTimeServers[i] = nullptr;
    }

    delete[] externalTimeServers;
    externalTimeServers = nullptr;
}

// ====================================================================================================================
// VxSdkNet::Configuration::Twilio
// ====================================================================================================================

VxSdkNet::Configuration::Twilio::Twilio(VxSdk::IVxConfiguration::Twilio* vxConfigTwilio) {
    _configTwilio = vxConfigTwilio;
}

VxSdkNet::Configuration::Twilio::!Twilio() {
    _configTwilio->Delete();
    _configTwilio = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Twilio::Refresh() {
    return (VxSdkNet::Results::Value)_configTwilio->Refresh();
}

bool VxSdkNet::Configuration::Twilio::ValidateTwilioInfo(System::String^ accountSid, System::String^ authToken, System::String^ fromNumber, System::String^ toNumber) {
    bool result;
    _configTwilio->ValidateTwilioInfo(result, Utils::ConvertCSharpString(accountSid).c_str(),
                                      Utils::ConvertCSharpString(authToken).c_str(),
                                      Utils::ConvertCSharpString(fromNumber).c_str(),
                                      Utils::ConvertCSharpString(toNumber).c_str());

    return result;
}

VxSdkNet::ResourceLimits^ VxSdkNet::Configuration::Twilio::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _configTwilio->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}