/// <summary>
/// Implements the database backups class.
/// </summary>
#include "DbBackups.h"

using namespace System::Collections::Generic;

VxSdkNet::DbBackups::DbBackups(VxSdk::IVxDbBackups* vxDbBackups) {
    _dbBackups = vxDbBackups;
}

VxSdkNet::DbBackups::!DbBackups() {
    _dbBackups->Delete();
    _dbBackups = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::DbBackups::DeleteDatabaseBackup(DbBackup^ dbBackupItem) {
    // Create a database backup object
    VxSdk::IVxDbBackup* delDbBackupItem = dbBackupItem->_dbBackup;

    // To delete a database backup simply make a DeleteBackup call
    VxSdk::VxResult::Value result = delDbBackupItem->DeleteBackup();
    // Unless there was an issue deleting the database backup the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::DbBackups::TriggerBackup() {
    return (Results::Value)_dbBackups->TriggerBackup();
}

bool VxSdkNet::DbBackups::ValidateBackupPath(System::String^ backupPath, System::String^ backupPathUsername, System::String^ backupPathPassword) {
    bool result;
    _dbBackups->ValidateBackupPath(result, Utils::ConvertCSharpString(backupPath).c_str(), Utils::ConvertCSharpString(backupPathUsername).c_str(), Utils::ConvertCSharpString(backupPathPassword).c_str());
    return result;
}

List<VxSdkNet::DbBackup^>^ VxSdkNet::DbBackups::_GetDatabaseBackups() {
    // Create a list of managed database backups
    List<DbBackup^>^ mlist = gcnew List<DbBackup^>();
    // Create a collection of unmanaged database backups
    VxSdk::VxCollection<VxSdk::IVxDbBackup**> databaseBackups;

    // Make the GetDatabaseBackups call, which will return with the total database backup count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _dbBackups->GetDatabaseBackups(databaseBackups);
    // As long as there are database backups the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDbBackup collection
        databaseBackups.collection = new VxSdk::IVxDbBackup*[databaseBackups.collectionSize];
        result = _dbBackups->GetDatabaseBackups(databaseBackups);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < databaseBackups.collectionSize; i++)
                mlist->Add(gcnew DbBackup(databaseBackups.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] databaseBackups.collection;
    }
    return mlist;
}

VxSdkNet::ResourceLimits^ VxSdkNet::DbBackups::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _dbBackups->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

