// Declares the database backups class.
#ifndef DbBackups_h__
#define DbBackups_h__

#include "VxSdk.h"
#include "Utils.h"
#include "DbBackup.h"
#include "ResourceLimits.h"

namespace VxSdkNet {

    /// <summary>
    /// The DbBackups class represents a collection of database backups and provides database backup and control.
    /// </summary>
    public ref class DbBackups {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDbBackups">The vx database backups.</param>
        DbBackups(VxSdk::IVxDbBackups* vxDbBackups);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~DbBackups() {
            this->!DbBackups();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !DbBackups();

        /// <summary>
        /// Delete a database backup. If the backup is in progress, it shall be halted first.
        /// </summary>
        /// <param name="dbBackupItem">The database backup to be deleted.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the database backup.</returns>
        Results::Value DeleteDatabaseBackup(DbBackup^ dbBackupItem);

        /// <summary>
        /// Initiates a new unscheduled database backup.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of initiating the backup.</returns>
        Results::Value TriggerBackup();

        /// <summary>
        /// Gets a value indicating whether a network storage path is available and valid as a backup storage.
        /// </summary>
        /// <param name="backupPath">The UNC network storage path.</param>
        /// <param name="backupPathUsername">The username for access to the backup path, if any.</param>
        /// <param name="backupPathPassword">The password for access to the backup path, if any.</param>
        /// <returns><c>true</c> if valid, otherwise <c>false</c>.</returns>
        bool ValidateBackupPath(System::String^ backupPath, System::String^ backupPathUsername, System::String^ backupPathPassword);

        /// <summary>
        /// Gets or sets the number of days between automatic database backups.
        /// </summary>
        /// <value>The number of days between automatic database backups.</value>
        property int BackupInterval {
        public:
            int get() { return _dbBackups->backupInterval; }
            void set(int value) { _dbBackups->SetBackupInterval(value); }
        }

        /// <summary>
        /// Gets or sets the optional UNC network path to use for alternate backup storage (instead of the server default location).
        /// </summary>
        /// <value>The UNC network path.</value>
        property System::String^ BackupPath {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dbBackups->backupPath); }
            void set(System::String^ value) {
                char backupPath[512];
                VxSdk::Utilities::StrCopySafe(backupPath, Utils::ConvertCSharpString(value).c_str());
                _dbBackups->SetBackupPath(backupPath);
            }
        }

        /// <summary>
        /// Sets the password used to access the backup storage location path.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ BackupPathPassword {
        public:
            void set(System::String^ value) {
                char backupPathPassword[64];
                VxSdk::Utilities::StrCopySafe(backupPathPassword, Utils::ConvertCSharpString(value).c_str());
                _dbBackups->SetBackupPathPassword(backupPathPassword);
            }
        }

        /// <summary>
        /// Gets or sets the username used to access the backup storage location path.
        /// </summary>
        /// <value>The username.</value>
        property System::String^ BackupPathUsername {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dbBackups->backupPathUsername); }
            void set(System::String^ value) {
                char backupPathUsername[64];
                VxSdk::Utilities::StrCopySafe(backupPathUsername, Utils::ConvertCSharpString(value).c_str());
                _dbBackups->SetBackupPathUsername(backupPathUsername);
            }
        }

        /// <summary>
        /// Gets or sets the time at which daily automatic database backups will begin.
        /// </summary>
        /// <value>The time to run daily backups, from 00:00:00 to 23:59:59.</value>
        property System::DateTime BackupTime {
        public:
            System::DateTime get() { return Utils::ConvertCppTime(_dbBackups->backupTime); }
            void set(System::DateTime value) {
                char backupTime[9];
                VxSdk::Utilities::StrCopySafe(backupTime, Utils::ConvertCSharpTime(value).c_str());
                _dbBackups->SetBackupTime(backupTime);
            }
        }

        /// <summary>
        /// Gets the current collection of database backups.
        /// </summary>
        /// <value>A <c>List</c> of database backups.</value>
        property System::Collections::Generic::List<DbBackup^>^ DatabaseBackups {
        public:
            System::Collections::Generic::List<DbBackup^>^ get() { return _GetDatabaseBackups(); }
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
        /// Gets or sets the maximum number of backups to keep in the backup directory before overwriting the oldest.
        /// </summary>
        /// <value>The maximum number of backups to keep.</value>
        property int MaxBackupsToKeep {
        public:
            int get() { return _dbBackups->maxBackupsToKeep; }
            void set(int value) { _dbBackups->SetMaxBackupsToKeep(value); }
        }

    internal:
        VxSdk::IVxDbBackups* _dbBackups;
        System::Collections::Generic::List<DbBackup^>^ _GetDatabaseBackups();
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // DbBackups_h__
