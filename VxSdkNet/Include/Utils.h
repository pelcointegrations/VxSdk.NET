// Declares the utilities class.
#ifndef Utils_h__
#define Utils_h__

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <string>
#include "VxSdk.h"

namespace VxSdkNet {

    /// <summary>
    /// The Results class is a helper class that contains the <see cref="Results::Value">Results</see> enum.
    /// </summary>
    public ref class Results {
    public:

        /// <summary>
        /// Values that represent the result of calls to the VideoXpert system.
        /// </summary>
        enum class Value {
            /// <summary>An error or unknown value was returned.</summary>
            UnknownError,

            /// <summary>The action was successful.</summary>
            OK,

            /// <summary>The VideoXpert system version is not supported.</summary>
            UnsupportedVersion,

            /// <summary>The size value was not sufficient enough to allocate the collection.</summary>
            InsufficientSize,

            /// <summary>The login credentials were invalid.</summary>
            InvalidLoginInfo,

            /// <summary>The attempted action is unsupported by the system.</summary>
            ActionUnavailable,

            /// <summary>A parameter was invalid.</summary>
            InvalidParameters,

            /// <summary>There was an error communicating to the device.</summary>
            CommunicationError,

            /// <summary>No valid license was found on the VideoXpert system.</summary>
            InvalidLicense,

            /// <summary>Camera is unavailable, data cannot be retrieved at this time.</summary>
            CameraUnavailable,

            /// <summary>
            /// No further stream data is currently available (the edge of a currently recording clip has been reached); more data will
            /// be available shortly.
            /// </summary>
            EdgeOfStream,

            /// <summary>
            /// No further stream data is available (the end of all recorded data has been reached; no further data is currently be recorded).
            /// </summary>
            EndOfStream,

            /// <summary>The server is unable to initiate any new stream sessions due to having reached its stream count capacity.</summary>
            NoAvailableStreams,

            /// <summary>Storage is unavailable, data cannot be retrieved at this time.</summary>
            StorageUnavailable,

            /// <summary>The data needed to perform the export operation can not be retrieved.</summary>
            ExportDataUnretrievable,

            /// <summary>The export storage location does not have enough free space to store the export.</summary>
            ExportStorageFull,

            /// <summary> The export storage location is not accessible due to invalid credentials.</summary>
            ExportStorageUnauthenticated,

            /// <summary>
            /// The export storage location is not accessible; this may be due to an invalid location, network issue, or storage issue.
            /// </summary>
            ExportStorageUnavailable,

            /// <summary>
            /// The requested operation is not possible due to a conflict with the resource. Typically this is due to a violation of a
            /// uniqueness property on one of the resource’s fields.
            /// </summary>
            Conflict,

            /// <summary>The server has insufficient resources to satisfy the request.</summary>
            InsufficientResources,

            /// <summary>
            /// The server is not in an appropriate state to be able to service this request. The server requires intervention in order
            /// to resolve this.
            /// </summary>
            NotReady,

            /// <summary>
            /// The server is not in an appropriate state to be able to service this request due to an authentication issue between it
            /// and another entity. The server requires intervention in order to resolve this.
            /// </summary>
            NotReadyUnauthenticated,

            /// <summary>
            /// The server is not in an appropriate state to be able to service this request due to an authorization issue between it
            /// and another entity. The server requires intervention in order to resolve this.
            /// </summary>
            NotReadyUnauthorized,

            /// <summary>The requested operation failed.</summary>
            OperationFailed,

            /// <summary>
            /// The server is incapable of handling the client request due to the size of the resulting response.What constitutes
            /// ’too large’ is entirely up to the server.
            /// </summary>
            ResponseTooLarge,

            /// <summary>The license that was supplied has an activation conflict with an existing license(e.g.duplicate activation IDs).</summary>
            ActivationConflict,

            /// <summary>The activation failed due to communication error with the FNO licensing server.</summary>
            ActivationHostNotFound,

            /// <summary>The activation failed.</summary>
            ActivationFailed,

            /// <summary>The license that was supplied is not compatible with the device and/or system that it is being applied to.</summary>
            IncompatibleLicense,

            /// <summary>A valid license is available but the available count on that license is fully utilized.</summary>
            LicenseCountExceeded,

            /// <summary>A valid license is required to utilize this method on the resource; no valid license found.</summary>
            LicenseRequired,

            /// <summary>Unable to apply the license; valid LDAP administrator credentials are required.</summary>
            LicenseReqLdapAdmin,

            /// <summary>Unable to commission (or float) a feature because no valid license is available for it.</summary>
            NoLicense,

            /// <summary>Camera is in use (or the usage dwell time is active) by same or higher authority user.</summary>
            CameraInUse,

            /// <summary>Camera is locked by same or higher authority user.</summary>
            CameraLocked,

            /// <summary>Locked by lower authority user, may override.</summary>
            NeedOverride,

            /// <summary>
            /// An attempt to set an invalid value on a writable field was made. The value may be invalid due to being out of range, unavailable, etc.
            /// </summary>
            InvalidValue,

            /// <summary>An attempt to set a new port number failed because the port number is already in use.</summary>
            PortInUse,

            /// <summary>An attempt to edit a read-only field was made.</summary>
            ReadOnlyField,

            /// <summary>An attempt to edit a locked resource was made by a user that does not own the IVxResourceLock.</summary>
            ResourceLocked,

            /// <summary>A request was made using expired authentication credentials.</summary>
            AuthExpired,

            /// <summary>A password with an insufficient number of digits was supplied in an attempt to create a new user password.</summary>
            PasswordReqMoreDigits,

            /// <summary>A password with an insufficient number of lowercase letters was supplied in an attempt to create a new user password.</summary>
            PasswordReqMoreLower,

            /// <summary>A password with an insufficient number of special characters was supplied in an attempt to create a new user password.</summary>
            PasswordReqMoreSpecial,

            /// <summary>A password with an insufficient number of uppercase letters was supplied in an attempt to create a new user password.</summary>
            PasswordReqMoreUpper,

            /// <summary>A password of insufficient length was supplied in an attempt to create a new user password.</summary>
            PasswordTooShort,

            /// <summary>A password too similar to a previous password was supplied in an attempt to create a new user password.</summary>
            PasswordTooSimilar,

            /// <summary>
            /// The requested operation is not possible due to a permission conflict with the resource. Typically this is due to a violation
            /// of permission hierarchy (e.g. a nested permission is being assigned without its parent permission already assigned).
            /// </summary>
            PermissionConflict,

            /// <summary>An unauthenticated request was made (i.e. invalid username and/or password).</summary>
            Unauthenticated,

            /// <summary>An unauthorized request was made (i.e. user does not have permission to access the resource).</summary>
            Unauthorized,

            /// <summary>The SDK license key is empty.</summary>
            SdkLicenseKeyEmpty,

            /// <summary>The SDK license key data is invalid.</summary>
            SdkLicenseKeyInvalid,

            /// <summary>The license on the server does not support this version of the SDK.</summary>
            SdkLicenseVersionInvalid,

            /// <summary>The license on the server has expired.</summary>
            SdkLicenseExpired,

            /// <summary>The license associated with the license key was not found on the server, but the license grace period is active.</summary>
            SdkLicenseGracePeriodActive,

            /// <summary>The license associated with the license key was not found on the server and the license grace period has expired.</summary>
            SdkLicenseGracePeriodExpired
        };
    };

    public ref class Filters {
    public:
        enum class Value {
            /// <summary>No filter.</summary>
            None,

            /// <summary>The maximum number of items to return per page.</summary>
            Count,

            /// <summary>Filter by data source id.</summary>
            DataSourceId,

            /// <summary>Filter by start time.</summary>
            SearchStartTime,

            /// <summary>Filter by end time.</summary>
            SearchEndTime,

            /// <summary>Filter by name.</summary>
            Name,

            /// <summary>Filter by id.</summary>
            Id,

            /// <summary>The start index.</summary>
            Start,

            /// <summary>Filter by type.</summary>
            Type,

            /// <summary>Filter by situation type.</summary>
            SituationType,

            /// <summary>True to return only items that are not assigned.</summary>
            Unassigned,

            /// <summary>Filter by data source number.</summary>
            DataSourceNumber,

            /// <summary>Filter by the description value.</summary>
            Description,

            /// <summary>Return items that have been modified since the given time.</summary>
            ModifiedSince,

            /// <summary>Filter by the time value.</summary>
            Time,

            /// <summary>Filter by the end time value.</summary>
            EndTime,

            /// <summary>Filter by the start time value.</summary>
            StartTime,

            /// <summary>Filter by the event value.</summary>
            Event,

            /// <summary>Filter by the framerate value.</summary>
            Framerate,

            /// <summary>Filter by the client type value.</summary>
            ClientType,

            /// <summary>True to return only owned items.</summary>
            Owned,

            /// <summary>Filter by owner.</summary>
            Owner,

            /// <summary>Filter by the username value.</summary>
            Username,

            /// <summary>Filter by comma-separated list of tag names.</summary>
            AllTags,

            /// <summary>True to return only items that are capturing.</summary>
            Capturing,

            /// <summary>Filter by IP.</summary>
            Ip,

            /// <summary>Filter by number.</summary>
            Number,

            /// <summary>True to return only items that are recording.</summary>
            Recording,

            /// <summary>Filter by the state value.</summary>
            State,

            /// <summary>True to return only items that are commissioned.</summary>
            Commissioned,

            /// <summary>Filter by model.</summary>
            Model,

            /// <summary>Filter by serial.</summary>
            Serial,

            /// <summary>Filter by vendor.</summary>
            Vendor,

            /// <summary>Filter by version.</summary>
            Version,

            /// <summary>Filter by the ack state value.</summary>
            AckState,

            /// <summary>Filter by the ack user value.</summary>
            AckUser,

            /// <summary>Filter by generator device id.</summary>
            GeneratorDeviceId,

            /// <summary>True to return items that were sent to the client.</summary>
            Notifies,

            /// <summary>Filter by severity.</summary>
            Severity,

            /// <summary>Filter by source device id.</summary>
            SourceDeviceId,

            /// <summary>Filter by source username.</summary>
            SourceUserName,

            /// <summary>Filter by the percent complete value.</summary>
            PercentComplete,

            /// <summary>Filter by the size value.</summary>
            Size,

            /// <summary>Filter by status.</summary>
            Status,

            /// <summary>Filter by resource id.</summary>
            ResourceId,

            /// <summary>True to return items that are internal to the server and read-only</summary>
            Internal,

            /// <summary>Filter by the audible notification value.</summary>
            AudibleNotify,

            /// <summary>Filter by the log value.</summary>
            Log,

            /// <summary>Filter by the notify value.</summary>
            Notify,

            /// <summary>Filter by resource type.</summary>
            ResourceType,

            /// <summary>True to return only items that are linked.</summary>
            Linked,

            /// <summary>Filter by comma-separated list of tag names owned by the current user.</summary>
            AllPrivateTags,

            /// <summary>True to return items that are currently being manually recorded.</summary>
            ManualRecording,

            /// <summary>Filter by first name.</summary>
            FirstName,

            /// <summary>Filter by last name.</summary>
            LastName,

            /// <summary>Filter by items that have a specific property defined.</summary>
            HasProperty,

            /// <summary>Filter by items that have a specific status.</summary>
            HasStatus,

            /// <summary>Filter by comma-separated list of tag names.</summary>
            DataSourceAllTags,

            /// <summary>Filter by comma-separated list of tag names owned by the current user.</summary>
            DataSourceAllPrivateTags,

            /// <summary>Filter by data source name.</summary>
            DataSourceName,

            /// <summary>Filter by the name of the key in the properties map corresponding to the service identifier.</summary>
            ServicePropertyId,

            /// <summary>Filter by a image type, useful when filtering Drawings.</summary>
            ImageType,

            /// <summary>Filter by advanced query.</summary>
            AdvancedQuery,

            /// <summary>Filter by all public and private tags (tags_all).</summary>
            TagsAll,

            /// <summary>True to return only items that are enabled.</summary>
            Enabled,

            /// <summary>Filter by the intiated time value.</summary>
            Initiated,

            /// <summary>Filter by data storage id.</summary>
            DataStorageId,

            /// <summary>True to return only items that have been trashed.</summary>
            Trashed,

            /// <summary>Filter by data source type.</summary>
            DataSourceType,

            /// <summary>Filter by device id.</summary>
            DeviceId,

            /// <summary>Filter by driver type.</summary>
            DriverType,

            /// <summary>Filter by encoding type.</summary>
            Encoding,

            /// <summary>True to return only items that are folders.</summary>
            Folder,

            /// <summary>Filter by group id.</summary>
            GroupId,

            /// <summary>True to return only items that have folder tags.</summary>
            HasFolderTags,

            /// <summary>Filter by layer name.</summary>
            LayerName,

            /// <summary>True to return only items that require a license.</summary>
            LicenseRequired,

            /// <summary>True to return only items that are locked.</summary>
            Locked,

            /// <summary>Filter by parent id.</summary>
            ParentId,

            /// <summary>Filter by provider type.</summary>
            Provider,

            /// <summary>Filter by recording type.</summary>
            RecordType
        };
    };

    /// <summary>
    /// The LogLevel class is a helper class that contains the logging severity <see cref="LogLevel::Value">Values</see> enum.
    /// </summary>
    public ref class LogLevel {
    public:

        /// <summary>
        /// Values that represent the logging severity levels.
        /// </summary>
        enum class Value {
            Trace,
            Debug,
            Info,
            Warning,
            Error,
            Fatal,
            None
        };
    };

    /// <summary>
    /// Provides commonly used methods.
    /// </summary>
    private class Utils {
    public:
        /// <summary>
        /// Convert a std string to a system string.
        /// </summary>
        /// <param name="stdString">The string source</param>
        /// <returns>Null if it fails, else the converted string.</returns>
        static System::String^ ConvertCppString(std::string &stdString) {
            const char *strChars = stdString.c_str();
            return ConvertCppString(strChars);
        }

        /// <summary>
        /// Convert a pointer to const char to a system string.
        /// </summary>
        /// <param name="charString">The string source</param>
        /// <returns>Null if it fails, else the converted string.</returns>
        static System::String^ ConvertCppString(const char *charString) {
            System::String^ str = System::String::Empty;
            if (charString == nullptr) return str;

            int strLen = strlen(charString);
            if (strLen == 0) return str;

            array<byte> ^bytes = gcnew array<byte>(strLen);
            pin_ptr<byte> pinnedBytes = &bytes[0];
            strcpy_s((char*)pinnedBytes, strLen + 1, charString);
            return System::Text::Encoding::UTF8->GetString(bytes);
        }

        /// <summary>
        /// Convert a system string to a standard string.
        /// </summary>
        /// <param name="sysString">The system string.</param>
        /// <returns>Null if it fails, else the converted string.</returns>
        static std::string ConvertCSharpString(System::String^ sysString) {
            std::string stdString;
            if (System::String::IsNullOrWhiteSpace(sysString)) return stdString;

            array<byte> ^bytes = System::Text::Encoding::UTF8->GetBytes(sysString);
            pin_ptr<byte> pinnedBytes = &bytes[0];
            stdString = std::string((char*)pinnedBytes);
            return stdString;
        }

        /// <summary>
        /// Convert a char to a DateTime.
        /// </summary>
        /// <param name="charString">The date string.</param>
        /// <returns>Default DateTime if it fails, else the parsed DateTime.</returns>
        static System::DateTime ConvertCppDateTime(const char* charString) {
            System::DateTime parsedTime;
            System::String^ value = Utils::ConvertCppString(charString);
            if (System::String::IsNullOrWhiteSpace(value)) return parsedTime;

            array<System::String^>^ formats = gcnew array<System::String^>(2);
            formats[0] = Utils::ConvertCppString("yyyy-MM-dd'T'HH:mm:ss.fff'Z'");
            formats[1] = Utils::ConvertCppString("yyyy-MM-dd'T'HH:mm:ss'Z'");

            System::Globalization::CultureInfo^ culture = System::Globalization::CultureInfo::InvariantCulture;
            System::DateTime::TryParseExact(value, formats, culture, System::Globalization::DateTimeStyles::None, parsedTime);
            parsedTime = System::DateTime::SpecifyKind(parsedTime, System::DateTimeKind::Utc);
            return parsedTime;
        }

        /// <summary>
        /// Convert a DateTime to a string.
        /// </summary>
        /// <param name="dateTime">The DateTime.</param>
        /// <returns>The DateTime as a string.</returns>
        static std::string ConvertCSharpDateTime(System::DateTime dateTime) {
            dateTime = dateTime.ToUniversalTime();
            System::String^ timeString = dateTime.ToString(Utils::ConvertCppString("yyyy-MM-dd'T'HH:mm:ss.fff'Z'"));
            return Utils::ConvertCSharpString(timeString);
        }

        /// <summary>
        /// Convert a DateTime to a string in TimeOfDay format.
        /// </summary>
        /// <param name="dateTime">The DateTime.</param>
        /// <returns>The DateTime as a string in TimeOfDay format.</returns>
        static std::string ConvertCSharpTime(System::DateTime dateTime) {
            System::String^ timeString = dateTime.ToString(Utils::ConvertCppString("HH:mm:ss"));
            return Utils::ConvertCSharpString(timeString);
        }

        /// <summary>
        /// Convert a char to a DateTime using TimeOfDay format.
        /// </summary>
        /// <param name="charString">The time string.</param>
        /// <returns>Default DateTime if it fails, else the parsed DateTime.</returns>
        static System::DateTime ConvertCppTime(const char* charString) {
            System::DateTime parsedTime;
            System::String^ value = Utils::ConvertCppString(charString);
            if (System::String::IsNullOrWhiteSpace(value)) return parsedTime;

            array<System::String^>^ formats = gcnew array<System::String^>(2);
            formats[0] = Utils::ConvertCppString("HH:mm:ss");
            formats[1] = Utils::ConvertCppString("HH:mm:ss.fff");
            System::DateTime::TryParseExact(value, formats, System::Globalization::CultureInfo::InvariantCulture, System::Globalization::DateTimeStyles::None, parsedTime);
            return parsedTime;
        }
    };

    /// <summary>
    /// Provides global VxSDK methods.
    /// </summary>
    public ref class VxGlobal{
    public:
        /// <summary>
        /// Sets the minimum severity level of messages to log.
        /// </summary>
        /// <param name="logLevel">The logging severity <see cref="LogLevel">level</see>.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the configuration.</returns>
        static VxSdkNet::Results::Value SetLogLevel(VxSdkNet::LogLevel::Value logLevel) {
            // Set the log level
            VxSdk::VxResult::Value result = VxSdk::VxSetLogLevel((VxSdk::VxLogLevel::Value)logLevel);

            return VxSdkNet::Results::Value(result);
        }

        /// <summary>
        /// Sets the output path for log files.
        /// </summary>
        /// <param name="logPath">The directory to store the generated log files.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of setting the configuration.</returns>
        static VxSdkNet::Results::Value SetLogPath(System::String^ logPath) {
            // Set the log path
            VxSdk::VxResult::Value result = VxSdk::VxSetLogPath(VxSdkNet::Utils::ConvertCSharpString(logPath).c_str());

            return VxSdkNet::Results::Value(result);
        }
    };
}
#endif // Utils_h__
