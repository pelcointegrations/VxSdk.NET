// Declares the report field class.
#ifndef ReportField_h__
#define ReportField_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The ReportField class represents a field or field group within a report.
    /// </summary>
    public ref class ReportField {
    public:

        enum class ReportFieldType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The alarm input id report field.</summary>
            AlarmInputId,

            /// <summary>The alarm input name report field.</summary>
            AlarmInputName,

            /// <summary>The camera stream bitrate report field.</summary>
            CameraStreamBitrate,

            /// <summary>The camera stream encoding id report field.</summary>
            CameraStreamEncodingId,

            /// <summary>The camera stream format report field.</summary>
            CameraStreamFormat,

            /// <summary>The camera stream framerate report field.</summary>
            CameraStreamFramerate,

            /// <summary>The camera stream resolution report field.</summary>
            CameraStreamResolution,

            /// <summary>The configured max retention report field.</summary>
            ConfiguredMaxRetention,

            /// <summary>The data source id report field.</summary>
            DatasourceId,

            /// <summary>The data source ip report field.</summary>
            DatasourceIp,

            /// <summary>The data source name report field.</summary>
            DatasourceName,

            /// <summary>The data source number report field.</summary>
            DatasourceNumber,

            /// <summary>The data source recording report field.</summary>
            DatasourceRecording,

            /// <summary>The data source state report field.</summary>
            DatasourceState,

            /// <summary>The data source type report field.</summary>
            DatasourceType,

            /// <summary>The data storage failover report field.</summary>
            DatastorageFailover,

            /// <summary>The data storage id report field.</summary>
            DatastorageId,

            /// <summary>The data storage name report field.</summary>
            DatastorageName,

            /// <summary>The data storage retention report field.</summary>
            DatastorageRetention,

            /// <summary>The data storage type report field.</summary>
            DatastorageType,

            /// <summary>The device commissioned report field.</summary>
            DeviceCommissioned,

            /// <summary>The device hostname report field.</summary>
            DeviceHostname,

            /// <summary>The device id report field.</summary>
            DeviceId,

            /// <summary>The device ip report field.</summary>
            DeviceIp,

            /// <summary>The device model report field.</summary>
            DeviceModel,

            /// <summary>The device name report field.</summary>
            DeviceName,

            /// <summary>The device port report field.</summary>
            DevicePort,

            /// <summary>The device serial report field.</summary>
            DeviceSerial,

            /// <summary>The device state report field.</summary>
            DeviceState,

            /// <summary>The device type report field.</summary>
            DeviceType,

            /// <summary>The device vendor report field.</summary>
            DeviceVendor,

            /// <summary>The device version report field.</summary>
            DeviceVersion,

            /// <summary>The event ack client id report field.</summary>
            EventAckClientId,

            /// <summary>The event ack client name report field.</summary>
            EventAckClientName,

            /// <summary>The event ack state report field.</summary>
            EventAckState,

            /// <summary>The event ack time report field.</summary>
            EventAckTime,

            /// <summary>The event ack user report field.</summary>
            EventAckUser,

            /// <summary>The event id report field.</summary>
            EventId,

            /// <summary>The event severity report field.</summary>
            EventSeverity,

            /// <summary>The event situation type report field.</summary>
            EventSituationType,

            /// <summary>The event source client id report field.</summary>
            EventSourceClientId,

            /// <summary>The event source device id report field.</summary>
            EventSourceDeviceId,

            /// <summary>The event source device name report field.</summary>
            EventSourceDeviceName,

            /// <summary>The event source user name report field.</summary>
            EventSourceUserName,

            /// <summary>The event time report field.</summary>
            EventTime,

            /// <summary>The field group report field.</summary>
            FieldGroup,

            /// <summary>The field group camera assignments report field.</summary>
            FieldGroupCameraAssignments,

            /// <summary>The field group privileges report field.</summary>
            FieldGroupPrivileges,

            /// <summary>The field group stream configuration report field.</summary>
            FieldGroupStreamConfiguration,

            /// <summary>The gap end report field.</summary>
            GapEnd,

            /// <summary>The gap filler status report field.</summary>
            GapFillerStatus,

            /// <summary>The gap reason report field.</summary>
            GapReason,

            /// <summary>The gap start report field.</summary>
            GapStart,

            /// <summary>The line counter count report field.</summary>
            LineCounterCount,

            /// <summary>The line counter count correction report field.</summary>
            LineCounterCountCorrection,

            /// <summary>The line counter end time report field.</summary>
            LineCounterEndTime,

            /// <summary>The line counter in count report field.</summary>
            LineCounterInCount,

            /// <summary>The line counter in count correction report field.</summary>
            LineCounterInCountCorrection,

            /// <summary>The line counter name report field.</summary>
            LineCounterName,

            /// <summary>The line counter out count report field.</summary>
            LineCounterOutCount,

            /// <summary>The line counter out count correction report field.</summary>
            LineCounterOutCountCorrection,

            /// <summary>The line counter start time report field.</summary>
            LineCounterStartTime,

            /// <summary>The line counter type report field.</summary>
            LineCounterType,

            /// <summary>The permission dev settings report field.</summary>
            PermissionDevSettings,

            /// <summary>The permission invest clips report field.</summary>
            PermissionInvestClips,

            /// <summary>The permission invest clips marks report field.</summary>
            PermissionInvestClipsMarks,

            /// <summary>The permission invest clips marks locks report field.</summary>
            PermissionInvestClipsMarksLocks,

            /// <summary>The permission super ptz presets report field.</summary>
            PermissionSuperPtzpresets,

            /// <summary>The permission surveillance video report field.</summary>
            PermissionSurveilVideo,

            /// <summary>The permission surveillance video ptz report field.</summary>
            PermissionSurveilVideoPtz,

            /// <summary>The permission surveillance video ptz lock report field.</summary>
            PermissionSurveilVideoPtzLock,

            /// <summary>The permission surveillance video record report field.</summary>
            PermissionSurveilVideoRecord,

            /// <summary>The permission system recording report field.</summary>
            PermissionSysRecording,

            /// <summary>The privilege permission report field.</summary>
            PrivilegePermission,

            /// <summary>The privilege priority report field.</summary>
            PrivilegePriority,

            /// <summary>The privilege restricted report field.</summary>
            PrivilegeRestricted,

            /// <summary>The property ids report field.</summary>
            PropertyIds,

            /// <summary>The property mods report field.</summary>
            PropertyMods,

            /// <summary>The property other report field.</summary>
            PropertyOther,

            /// <summary>The role id report field.</summary>
            RoleId,

            /// <summary>The role name report field.</summary>
            RoleName,

            /// <summary>The situation name report field.</summary>
            SituationName,

            /// <summary>The status http report field.</summary>
            StatusHttp,

            /// <summary>The status rtsp report field.</summary>
            StatusRtsp,

            /// <summary>The status service state report field.</summary>
            StatusServiceState,

            /// <summary>The system id report field.</summary>
            SystemId,

            /// <summary>The system name report field.</summary>
            SystemName,

            /// <summary>The system num audio data sources report field.</summary>
            SystemNumAudioDatasources,

            /// <summary>The system num data storages report field.</summary>
            SystemNumDatastorages,

            /// <summary>The system num devices report field.</summary>
            SystemNumDevices,

            /// <summary>The system num users report field.</summary>
            SystemNumUsers,

            /// <summary>The system num video data sources report field.</summary>
            SystemNumVideoDatasources,

            /// <summary>The user employee id report field.</summary>
            UserEmployeeId,

            /// <summary>The user first name report field.</summary>
            UserFirstName,

            /// <summary>The user id report field.</summary>
            UserId,

            /// <summary>The user last name report field.</summary>
            UserLastName,

            /// <summary>The user name report field.</summary>
            UserName,

            /// <summary>The user note report field.</summary>
            UserNote,

            /// <summary>The user password expiration report field.</summary>
            UserPasswordExpiration,

            /// <summary>The user phone number report field.</summary>
            UserPhoneNumber,

            /// <summary>The user role names report field.</summary>
            UserRoleNames
        };

        /// <summary>
        /// Default constructor.
        /// </summary>
        ReportField()
        {
            Subfields = gcnew System::Collections::Generic::List<ReportField^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxReportField">The vx report field.</param>
        ReportField(VxSdk::VxReportField* vxReportField){
            IsEnabled = vxReportField->isEnabled;
            Name = Utils::ConvertCppString(vxReportField->name);
            Type = (ReportFieldType)vxReportField->type;
            Subfields = gcnew System::Collections::Generic::List<ReportField^>();
            for (int i = 0; i < vxReportField->subfieldSize; i++) {
                Subfields->Add(gcnew ReportField(&vxReportField->subfields[i]));
            }
        }

        /// <summary>
        /// Gets or sets whether or not to include this field in the report.
        /// </summary>
        /// <value><c>true</c> to include this field in the report; <c>false</c> to omit it.</value>
        property bool IsEnabled;

        /// <summary>
        /// Gets or sets the friendly name of this field or field group.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the list of report field subfields. If not empty, indicates that this is a field group.
        /// </summary>
        /// <value>The list of report field subfields, if any.</value>
        property System::Collections::Generic::List<ReportField^>^ Subfields;;

        /// <summary>
        /// Gets or sets the report field type of this field or field group.
        /// </summary>
        /// <value>The report field type.</value>
        property ReportFieldType Type;
    };
}
#endif // ReportField_h__
