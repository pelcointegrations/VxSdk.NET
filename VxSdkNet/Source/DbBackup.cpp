/// <summary>
/// Implements the database backup class.
/// </summary>
#include "DbBackup.h"

using namespace System::Collections::Generic;

VxSdkNet::DbBackup::DbBackup(VxSdk::IVxDbBackup* vxDbBackup) {
    _dbBackup = vxDbBackup;
}

VxSdkNet::DbBackup::!DbBackup() {
    _dbBackup->Delete();
    _dbBackup = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::DbBackup::Halt() {
    // Call Halt and return the result
    return (Results::Value)_dbBackup->Halt();
}

VxSdkNet::Results::Value VxSdkNet::DbBackup::Refresh() {
    return (Results::Value)_dbBackup->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::DbBackup::Restore() {
    // Call Halt and return the result
    return (Results::Value)_dbBackup->Restore();
}
