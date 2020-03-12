// Declares the database backup class.
#ifndef DbBackup_h__
#define DbBackup_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The DbBackup class represents a database backup.
    /// </summary>
    public ref class DbBackup {
    public:

        /// <summary>
        /// Values that represent the status of a backup.
        /// </summary>
        enum class BackupStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Backup has failed.</summary>
            Failed,

            /// <summary>Backup was halted.</summary>
            Halted,

            /// <summary>Backup is in progress.</summary>
            InProgress,

            /// <summary>Backup was successful.</summary>
            Successful
        };

        /// <summary>
        /// Values that represent the reason for the current status of a backup.
        /// </summary>
        enum class BackupStatusReason {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Backup storage is full.</summary>
            BackupStorageFull,

            /// <summary>Backup storage unauthenticated.</summary>
            BackupStorageUnauthenticated,

            /// <summary>Backup storage is unavailable.</summary>
            BackupStorageUnavailable,

            /// <summary>Shadow copy creation failed.</summary>
            ShadowCopyCreationFailure,

            /// <summary>Shadow copy mount failed.</summary>
            ShadowCopyMountFailure
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDbBackup">The vx database backup.</param>
        DbBackup(VxSdk::IVxDbBackup* vxDbBackup);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~DbBackup() {
            this->!DbBackup();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !DbBackup();

        /// <summary>
        /// Halts the current backup operation that is in progress, if any.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of halting the backup.</returns>
        Results::Value Halt();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Restore this backup to the database.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of restoring the backup.</returns>
        Results::Value Restore();

        /// <summary>
        /// Gets the date and time at which this backup completed.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which this backup completed.</value>
        property System::DateTime Completed {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_dbBackup->completed); }
        }

        /// <summary>
        /// Gets the unique identifier of this database backup.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dbBackup->id); }
        }

        /// <summary>
        /// Gets the date and time at which this backup was initiated.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which this backup was initiated.</value>
        property System::DateTime Initiated {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_dbBackup->initiated); }
        }

        /// <summary>
        /// Gets the current status of this backup.
        /// </summary>
        /// <value>The backup status.</value>
        property BackupStatus Status {
        public:
            BackupStatus get() { return (BackupStatus)_dbBackup->status; }
        }

        /// <summary>
        /// Gets the optional reason for the current status of this backup; typically used to express the reason
        /// for a failure.
        /// </summary>
        /// <value>The status reason.</value>
        property BackupStatusReason StatusReason {
        public:
            BackupStatusReason get() { return (BackupStatusReason)_dbBackup->statusReason; }
        }

    internal:
        VxSdk::IVxDbBackup* _dbBackup;
    };
}
#endif // DbBackup_h__
