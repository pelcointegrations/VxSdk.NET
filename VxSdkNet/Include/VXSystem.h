// Declares the VX System class.
#ifndef VXSystem_h__
#define VXSystem_h__

#undef AddMonitor
#undef DeleteMonitor

#include <map>

#include "AlarmInput.h"
#include "Device.h"
#include "DataStorage.h"
#include "Discovery.h"
#include "Drawing.h"
#include "ExportEstimate.h"
#include "VxFile.h"
#include "InternalEvent.h"
#include "License.h"
#include "Monitor.h"
#include "MonitorWall.h"
#include "NewBookmark.h"
#include "NewDataObject.h"
#include "NewDevice.h"
#include "NewEvent.h"
#include "NewExport.h"
#include "NewManualRecording.h"
#include "NewMember.h"
#include "NewMonitor.h"
#include "NewNotification.h"
#include "NewRecording.h"
#include "NewReport.h"
#include "NewReportTemplate.h"
#include "NewRule.h"
#include "NewSchedule.h"
#include "NewSituation.h"
#include "NewTag.h"
#include "NewTimeTable.h"
#include "NewUser.h"
#include "PermissionSchema.h"
#include "RelayOutput.h"
#include "Report.h"

namespace VxSdkNet {

    /// <summary>
    /// The VXSystem class represents a VideoXpert system.  It is the entry point of the VideoXpert SDK
    /// and allows the user to manage the system and devices.
    /// </summary>
    public ref class VXSystem {
    public:

        /// <summary>
        /// The native event callback delegate.
        /// </summary>
        /// <param name="vxEvent">The event sent from system.</param>
        [System::Runtime::InteropServices::UnmanagedFunctionPointer(
            System::Runtime::InteropServices::CallingConvention::Cdecl)]
        delegate void EventCallbackDelegate(VxSdk::IVxEvent* vxEvent);

        /// <summary>
        /// The native internal event callback delegate.
        /// </summary>
        /// <param name="vxInternalEvent">The internal event sent from the VxSDK.</param>
        [System::Runtime::InteropServices::UnmanagedFunctionPointer(
            System::Runtime::InteropServices::CallingConvention::Cdecl)]
        delegate void InternalEventCallbackDelegate(VxSdk::VxInternalEvent* vxInternalEvent);

        /// <summary>
        /// The managed event delegate.
        /// </summary>
        /// <param name="vxEvent">The event sent from the system as a managed type.</param>
        delegate void EventDelegate(Event^ vxEvent);

        /// <summary>
        /// The managed internal event delegate.
        /// </summary>
        /// <param name="sdkEvent">The internal event sent from the VxSDK as a managed type.</param>
        delegate void InternalEventDelegate(InternalEvent^ sdkEvent);

        /// <summary>
        /// Constructor that takes an IP and license key as parameters.
        /// </summary>
        /// <param name="ip">The IP address of the VideoXpert system.</param>
        /// <param name="licenseKey">The license key.</param>
        VXSystem(System::String^ ip, System::String^ licenseKey);

        /// <summary>
        /// Constructor that allows the port and SSL encryption parameters to be set.
        /// </summary>
        /// <param name="ip">The IP address of the VideoXpert system.</param>
        /// <param name="port">The port used by the VideoXpert system.</param>
        /// <param name="useSSL">Whether or not to use SSL encryption</param>
        /// <param name="licenseKey">The license key.</param>
        VXSystem(System::String^ ip, int port, bool useSSL, System::String^ licenseKey); 

        /// <summary>
        /// Virtual destructor.
        /// </summary>
        virtual ~VXSystem() {
            this->!VXSystem();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !VXSystem();

        /// <summary>
        /// Acknowledge all events.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of acknowledging all events.</returns>
        Results::Value AcknowledgeAllEvents() { return (Results::Value)_system->AcknowledgeAllEvents(); }

        /// <summary>
        /// Add a new analytic session to the VideoXpert system.
        /// </summary>
        /// <param name="newAnalyticSession">The new analytic session to be added.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the analytic session.</returns>
        Results::Value AddAnalyticSession(NewAnalyticSession^ newAnalyticSession);

        /// <summary>
        /// Add a new bookmark on the VideoXpert system.
        /// </summary>
        /// <param name="newBookmark">The new bookmark to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the bookmark.</returns>
        Results::Value AddBookmark(NewBookmark^ newBookmark);

        /// <summary>
        /// Add a new data object on the VideoXpert system.
        /// </summary>
        /// <param name="newDataObject">The new data object to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the data object.</returns>
        Results::Value AddDataObject(NewDataObject^ newDataObject);

        /// <summary>
        /// Add a device to the VideoXpert system.
        /// </summary>
        /// <param name="newDevice">The new device to be added.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of the request.</returns>
        Results::Value AddDevice(NewDevice^ newDevice);

        /// <summary>
        /// Add a new drawing on the VideoXpert system.
        /// </summary>
        /// <param name="drawingName">The name of the new drawing to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the drawing.</returns>
        Results::Value AddDrawing(System::String^ drawingName);

        /// <summary>
        /// Add a new export on the VideoXpert system.
        /// </summary>
        /// <param name="newExport">The new export to be added to the system.</param>
        /// <returns><c>nullptr</c> if it fails, else the new export.</returns>
        Export^ AddExport(NewExport^ newExport);

        /// <summary>
        /// Add a new file to the VideoXpert system.
        /// </summary>
        /// <param name="filePath">The local path to the file.</param>
        /// <param name="filename">The filename of the associated file data.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the file.</returns>
        Results::Value AddFile(System::String^ filePath, System::String^ filename);

        /// <summary>
        /// Add a new manual recording to the VideoXpert system.
        /// </summary>
        /// <param name="newManualRecording">The new manual recording to be added.</param>
        /// <returns><c>nullptr</c> if it fails, else the new manual recording.</returns>
        ManualRecording^ AddManualRecording(NewManualRecording^ newManualRecording);

        /// <summary>
        /// Add a new member system to be aggregated.
        /// </summary>
        /// <param name="newMember">The new member system to be aggregated.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the member.</returns>
        Results::Value AddMember(NewMember^ newMember);

        /// <summary>
        /// Add a new monitor wall on the VideoXpert system.
        /// </summary>
        /// <param name="monitorWallName">The name of the new monitor wall to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of creating the monitor wall.</returns>
        Results::Value AddMonitorWall(System::String^ monitorWallName);

        /// <summary>
        /// Add a new recording to the VideoXpert system.
        /// </summary>
        /// <param name="newRecording">The new recording to be added.</param>
        /// <returns><c>nullptr</c> if it fails, else the new recording.</returns>
        Recording^ AddRecording(NewRecording^ newRecording);

        /// <summary>
        /// Requests a new report to be generated on the VideoXpert system.
        /// </summary>
        /// <param name="newReport">The new report to be generated to the system.</param>
        /// <returns><c>nullptr</c> if it fails, else the new report template.</returns>
        Report^ AddReport(NewReport^ newReport);

        /// <summary>
        /// Add a new report template to the VideoXpert system.
        /// </summary>
        /// <param name="newReportTemplate">The new report template to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the report template.</returns>
        Results::Value AddReportTemplate(NewReportTemplate^ newReportTemplate);

        /// <summary>
        /// Add a new role on the VideoXpert system.
        /// </summary>
        /// <param name="roleName">The name of new role to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the role.</returns>
        Results::Value AddRole(System::String^ roleName);

        /// <summary>
        /// Add a new rule on the VideoXpert system.
        /// </summary>
        /// <param name="newRule">The new rule to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the schedule.</returns>
        Results::Value AddRule(NewRule^ newRule);

        /// <summary>
        /// Add a new schedule on the VideoXpert system.
        /// </summary>
        /// <param name="newSchedule">The new schedule to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the schedule.</returns>
        Results::Value AddSchedule(NewSchedule^ newSchedule);

        /// <summary>
        /// Add a new situation to the system.
        /// </summary>
        /// <param name="newSituation">The new situation to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the situation.</returns>
        Results::Value AddSituation(NewSituation^ newSituation);

        /// <summary>
        /// Add a new tag on the VideoXpert system.
        /// </summary>
        /// <param name="newTag">The new tag to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the tag.</returns>
        Results::Value AddTag(NewTag^ newTag);

        /// <summary>
        /// Add a new time table on the VideoXpert system.
        /// </summary>
        /// <param name="newTimeTable">The new time table to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the schedule.</returns>
        Results::Value AddTimeTable(NewTimeTable^ newTimeTable);

        /// <summary>
        /// Add a new user on the VideoXpert system.
        /// </summary>
        /// <param name="newUser">The new user to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of adding the user.</returns>
        Results::Value AddUser(NewUser^ newUser);

        /// <summary>
        /// Add a new monitor on the VideoXpert system.
        /// </summary>
        /// <param name="newMonitor">The new monitor to be added to the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of creating the monitor.</returns>
        Results::Value AddVxMonitor(NewMonitor^ newMonitor);

        /// <summary>
        /// Commissions a device for use within the VideoXpert system.
        /// </summary>
        /// <param name="device">The device to commission.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of commissioning the device.</returns>
        Results::Value CommissionDevice(Device^ device);

        /// <summary>
        /// Decommissions a device on the VideoXpert system.
        /// </summary>
        /// <param name="device">The device to decommission.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of decommissioning the device.</returns>
        Results::Value DecommissionDevice(Device^ device);

        /// <summary>
        /// Delete an analytic session from the VideoXpert system.
        /// </summary>
        /// <param name="analyticSession">The analytic session to be deleted from the VideoXpert system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the analytic session.</returns>
        Results::Value DeleteAnalyticSession(AnalyticSession^ analyticSession);

        /// <summary>
        /// Delete a bookmark from the VideoXpert system.
        /// </summary>
        /// <param name="bookmarkItem">The bookmark to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the bookmark.</returns>
        Results::Value DeleteBookmark(Bookmark^ bookmarkItem);

        /// <summary>
        /// Delete a data object from the VideoXpert system.
        /// </summary>
        /// <param name="dataObject">The data object to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the data object.</returns>
        Results::Value DeleteDataObject(DataObject^ dataObject);

        /// <summary>
        /// Delete a device and its hosted data sources and data storages from the VideoXpert system.
        /// If the device is assigned to a datastorage, it shall be unassigned.
        /// </summary>
        /// <param name="device">The device to be deleted.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the device.</returns>
        Results::Value DeleteDevice(Device^ device);

        /// <summary>
        /// Delete a drawing from the VideoXpert system.
        /// </summary>
        /// <param name="drawingItem">The drawing to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the drawing.</returns>
        Results::Value DeleteDrawing(Drawing^ drawingItem);

        /// <summary>
        /// Delete an export from the VideoXpert system.
        /// </summary>
        /// <param name="exportItem">The export to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the export.</returns>
        Results::Value DeleteExport(Export^ exportItem);

        /// <summary>
        /// Delete a file from the VideoXpert system.
        /// </summary>
        /// <param name="fileItem">The file to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the file.</returns>
        Results::Value DeleteFile(VxFile^ fileItem);

        /// <summary>
        /// Delete a manual recording from the VideoXpert system.
        /// </summary>
        /// <param name="manualRecordingItem">The manual recording to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the manual recording.</returns>
        Results::Value DeleteManualRecording(ManualRecording^ manualRecordingItem);

        /// <summary>
        /// Delete a monitor wall from the VideoXpert system.
        /// </summary>
        /// <param name="monitorWallItem">The monitor wall to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the monitor wall.</returns>
        Results::Value DeleteMonitorWall(MonitorWall^ monitorWallItem);

        /// <summary>
        /// Delete a recording from the VideoXpert system.
        /// </summary>
        /// <param name="recordingItem">The recording to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the recording.</returns>
        Results::Value DeleteRecording(Recording^ recordingItem);

        /// <summary>
        /// Delete a report from the VideoXpert system.
        /// </summary>
        /// <param name="reportItem">The report to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the report.</returns>
        Results::Value DeleteReport(Report^ reportItem);

        /// <summary>
        /// Delete a report template from the VideoXpert system.
        /// </summary>
        /// <param name="reportTemplate">The report template to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the report template.</returns>
        Results::Value DeleteReportTemplate(ReportTemplate^ reportTemplate);

        /// <summary>
        /// Delete a role from the VideoXpert system.
        /// </summary>
        /// <param name="roleItem">The role to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the role.</returns>
        Results::Value DeleteRole(Role^ roleItem);

        /// <summary>
        /// Delete a rule from the VideoXpert system.
        /// </summary>
        /// <param name="ruleItem">The rule to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the rule.</returns>
        Results::Value DeleteRule(Rule^ ruleItem);

        /// <summary>
        /// Delete a schedule from the VideoXpert system.
        /// </summary>
        /// <param name="scheduleItem">The schedule to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the schedule.</returns>
        Results::Value DeleteSchedule(Schedule^ scheduleItem);

        /// <summary>
        /// Delete an existing situation from the system.
        /// </summary>
        /// <param name="situationItem">The situation to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the situation.</returns>
        Results::Value DeleteSituation(Situation^ situationItem);

        /// <summary>
        /// Delete a tag from the VideoXpert system.
        /// </summary>
        /// <param name="tagItem">The tag to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the tag.</returns>
        Results::Value DeleteTag(Tag^ tagItem);

        /// <summary>
        /// Delete a time table from the VideoXpert system.
        /// </summary>
        /// <param name="timeTableItem">The time table to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the time table.</returns>
        Results::Value DeleteTimeTable(TimeTable^ timeTableItem);

        /// <summary>
        /// Delete a user from the VideoXpert system.
        /// </summary>
        /// <param name="user">The user to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the user.</returns>
        Results::Value DeleteUser(User^ user);

        /// <summary>
        /// Delete a monitor from the VideoXpert system.
        /// </summary>
        /// <param name="monitorItem">The monitor to be deleted from the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the monitor.</returns>
        Results::Value DeleteVxMonitor(Monitor^ monitorItem);

        /// <summary>
        /// Gets the access points from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: kAdvancedQuery, kHasStatus, kId, kModifiedSince, kName, kState, kType.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the access points on the system.</returns>
        System::Collections::Generic::List<AccessPoint^>^ GetAccessPoints(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the alarm inputs from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name, State.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the alarm inputs on the system.</returns>
        System::Collections::Generic::List<AlarmInput^>^ GetAlarmInputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Gets the analytic sessions from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, DataSourceId, DeviceId, Id, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the analytic sessions on the system.</returns>
        System::Collections::Generic::List<AnalyticSession^>^ GetAnalyticSessions(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the bookmarks from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, DataSourceId, DataSourceType, Description, GroupId, Id, Locked, ModifiedSince, Name, SearchEndTime, SearchStartTime, Time.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the bookmarks on the system.</returns>
        System::Collections::Generic::List<Bookmark^>^ GetBookmarks(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the data objects from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: ClientType, ModifiedSince, Owned, Owner.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the data objects on the system.</returns>
        System::Collections::Generic::List<DataObject^>^ GetDataObjects(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the data sources from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, AllTags, Capturing, Commissioned, Enabled, Encoding, HasFolderTags, Id, Ip, ManualRecording, ModifiedSince, Name, Number, Recording, State, Type, Unassigned.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the data sources on the system.</returns>
        System::Collections::Generic::List<DataSource^>^ GetDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the data storages residing on the system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Commissioned, Id, ModifiedSince, Name, Type.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the data storages.</returns>
        System::Collections::Generic::List<DataStorage^>^ GetDataStorages(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the device assignments residing on the system using an optional collection filter.
        /// <para>Available filters: DataSourceId, DataStorageId, DeviceId, ModifiedSince.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the device assignments.</returns>
        System::Collections::Generic::List<DeviceAssignment^>^ GetDeviceAssignments(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the devices from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Commissioned, Discovered, DriverType, HasStatus, Id, Ip, Model, ModifiedSince, Name, Serial, State, Type, Vendor, Version.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the devices on the system.</returns>
        System::Collections::Generic::List<Device^>^ GetDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the drawings from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ImageType, ModifiedSince, Name, Provider.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the drawings on the system.</returns>
        System::Collections::Generic::List<Drawing^>^ GetDrawings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Gets the drivers provided by this system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince, Name, Vendor, Version.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the drivers on the system.</returns>
        System::Collections::Generic::List<VxSdkNet::Driver^>^ VxSdkNet::VXSystem::GetDrivers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get events from the system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, AckState, AckUser, GeneratorDeviceId, Id, ModifiedSince, Notifies, SearchEndTime, SearchStartTime, Severity, SituationType, SourceDeviceId, SourceUserName, Time.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing matching events on the system.</returns>
        System::Collections::Generic::List<Event^>^ GetEvents(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Gets the estimate information for a given set of export criteria. This does not perform an actual export operation.
        /// </summary>
        /// <param name="newExport">The new export to request an estimate for.</param>
        /// <returns><c>nullptr</c> if it fails, else the export estimate.</returns>
        ExportEstimate^ GetExportEstimate(NewExport^ newExport);

        /// <summary>
        /// Get the exports residing on the system using an optional collection filter.
        /// <para>Available filters: DataSourceAllTags, DataSourceAllPrivateTags, DataSourceName, DataSourceNumber, ModifiedSince, Name, Owner, PercentComplete, Size, Status, Trashed.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the exports on the system.</returns>
        System::Collections::Generic::List<Export^>^ GetExports(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the files residing on the system using an optional collection filter.
        /// <para>Available filters: Id, FileName.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the files on the system.</returns>
        System::Collections::Generic::List<VxFile^>^ GetFiles(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the license from the system.
        /// </summary>
        /// <returns>The system license.</returns>
        License^ GetLicense();

        /// <summary>
        /// Gets the manual recordings residing on the system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, DataSourceId, Id, ModifiedSince, Owner.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the manual recordings on the system.</returns>
        System::Collections::Generic::List<ManualRecording^>^ GetManualRecordings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Gets the member systems that this system is aggregating using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Host, Id, ModifiedSince, Name, State.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the member systems.</returns>
        System::Collections::Generic::List<Member^>^ GetMembers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the monitors residing on the system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name, Number.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the monitors on the system.</returns>
        System::Collections::Generic::List<Monitor^>^ GetMonitors(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the monitor walls residing on the system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the monitor walls on the system.</returns>
        System::Collections::Generic::List<MonitorWall^>^ GetMonitorWalls(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Gets the recordings residing on the system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, DataSourceId, Id, ModifiedSince, Name, Owner, RecordType.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the recordings on the system.</returns>
        System::Collections::Generic::List<Recording^>^ GetRecordings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the relay outputs from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Enabled, Id, ModifiedSince, Name, State.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the relay outputs on the system.</returns>
        System::Collections::Generic::List<RelayOutput^>^ GetRelayOutputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the reports from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name, Owner.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the reports on the system.</returns>
        System::Collections::Generic::List<Report^>^ GetReports(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the report templates from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name, Owner.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the report templates on the system.</returns>
        System::Collections::Generic::List<ReportTemplate^>^ GetReportTemplates(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the roles from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, Internal, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the roles on the system.</returns>
        System::Collections::Generic::List<Role^>^ GetRoles(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the rules from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name, Number.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the rules on the system.</returns>
        System::Collections::Generic::List<Rule^>^ GetRules(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the schedules from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, DataSourceId, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the schedules on the system.</returns>
        System::Collections::Generic::List<Schedule^>^ GetSchedules(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the situations residing on the system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, AudibleNotify, HasProperty, Log, ModifiedSince, Name, Notify, ServicePropertyId, Severity, SourceDeviceId, Type.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the situations on the system.</returns>
        System::Collections::Generic::List<Situation^>^ GetSituations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the tags from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Folder, Id, ModifiedSince, Name, Owned, Owner, ParentId, ResourceId, ResourceType.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the tags on the system.</returns>
        System::Collections::Generic::List<Tag^>^ GetTags(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the time tables from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the time tables on the system.</returns>
        System::Collections::Generic::List<TimeTable^>^ GetTimeTables(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the users from the VideoXpert system using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, FirstName, LastName, ModifiedSince, Name.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> containing the users on the system.</returns>
        System::Collections::Generic::List<User^>^ GetUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Insert a new event into the system.
        /// </summary>
        /// <param name="newEvent">The new event to be injected into the system.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of injecting the event.</returns>
        Results::Value InjectEvent(NewEvent^ newEvent);

        /// <summary>
        /// Log in to the VideoXpert system.
        /// </summary>
        /// <param name="username">The user name to log in with.</param>
        /// <param name="password">The password to log in with.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of the log in process.</returns>
        Results::Value Login(System::String^ username, System::String^ password);

        /// <summary>
        /// Log in to the VideoXpert system.
        /// </summary>
        /// <param name="authToken">The auth token</param>
        /// <returns>The <see cref="Results::Value">Result</see> of the log in process.</returns>
        Results::Value Login(System::String^ authToken);

        /// <summary>
        /// Update this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Remove the member system; it will no longer be aggregated.
        /// </summary>
        /// <param name="memberItem">The member system to be removed.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of removing the member system.</returns>
        Results::Value RemoveMember(Member^ memberItem);

        /// <summary>
        /// Subscribe to system events by situation type, regardless of its notification setting.
        /// </summary>
        /// <param name="eventDelegate">The event delegate to be used when an event is received.</param>
        /// <param name="situations">A <c>List</c> of situations to subscribe to.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of subscribing.</returns>
        Results::Value SubscribeToEventsByType(EventDelegate^ eventDelegate, System::Collections::Generic::List<Situation^>^ situations);

        /// <summary>
        /// Subscribe to system events by situation type, regardless of its notification setting.
        /// </summary>
        /// <param name="eventDelegate">The event delegate to be used when an event is received.</param>
        /// <param name="situations">A <c>List</c> of situations to subscribe to.</param>
        /// <param name="userNotification"><c>true</c> to receive user role notifications, otherwise <c>false</c>.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of subscribing.</returns>
        Results::Value SubscribeToEventsByType(EventDelegate^ eventDelegate, System::Collections::Generic::List<Situation^>^ situations, bool userNotification);

        /// <summary>
        /// Unsubscribes to system events that were subscribed to by type.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of unsubscribing.</returns>
        Results::Value UnsubscribeToEvents();

        /// <summary>
        /// Gets a value indicating whether or not the member administrator credentials provided are valid.
        /// </summary>
        /// <param name="host">The host address.</param>
        /// <param name="port">The host port.</param>
        /// <param name="username">The username for access to the member.</param>
        /// <param name="password">The password for access to the member.</param>
        /// <returns><c>true</c> if the administrator credentials are determined to be valid, otherwise <c>false</c>.</returns>
        bool ValidateMember(System::String^ host, int port, System::String^ username, System::String^ password);

        /// <summary>
        /// Gets the access points from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the access points on the system.</value>
        property System::Collections::Generic::List<AccessPoint^>^ AccessPoints {
        public:
            System::Collections::Generic::List<AccessPoint^>^ get() { return GetAccessPoints(nullptr); }
        }

        /// <summary>
        /// Gets the alarm inputs from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the alarm inputs on the system.</value>
        property System::Collections::Generic::List<AlarmInput^>^ AlarmInputs {
            System::Collections::Generic::List<AlarmInput^>^ get() { return GetAlarmInputs(nullptr); }
        }

        /// <summary>
        /// Gets all of the analytic sessions from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> of analytic sessions.</value>
        property System::Collections::Generic::List<AnalyticSession^>^ AnalyticSessions {
        public:
            System::Collections::Generic::List<AnalyticSession^>^ get() { return GetAnalyticSessions(nullptr); }
        }

        /// <summary>
        /// Gets the authorization configuration.
        /// </summary>
        /// <value>The authorization configuration.</value>
        property VxSdkNet::Configuration::Auth^ AuthConfig {
        public:
            VxSdkNet::Configuration::Auth^ get() { return _GetAuthConfig(); }
        }

        /// <summary>
        /// Gets the available report templates representing the default template for each report type. These defaults
        /// act as a schema for each report type, providing all available fields and filters that may be used in the
        /// report template for that report type.
        /// </summary>
        /// <value>A <c>List</c> of the available default report templates.</value>
        property System::Collections::Generic::List<NewReportTemplate^>^ AvailableReportTemplates {
        public:
            System::Collections::Generic::List<NewReportTemplate^>^ get() { return _GetAvailableReportTemplates(); }
        }

        /// <summary>
        /// Gets the list of available event types that may be used within a schedule trigger.
        /// </summary>
        /// <value>A <c>List</c> of the available situation types.</value>
        property System::Collections::Generic::List<System::String^>^ AvailableScheduleTriggerEvents {
        public:
            System::Collections::Generic::List<System::String^>^ get() { return _GetAvailableScheduleTriggerEvents(); }
        }

        /// <summary>
        /// Gets or sets the current bookmark automatic unlock time value.
        /// </summary>
        /// <value>The bookmark auto-unlock time (in days).</value>
        property int BookmarkAutoUnlockTime {
            int get() {
                int autoUnlockTime;
                VxSdk::VxResult::Value result = _system->GetBookmarkAutoUnlockTime(autoUnlockTime);
                return autoUnlockTime;
            }
            void set(int value) { _system->SetBookmarkAutoUnlockTime(value); }
        }

        /// <summary>
        /// Gets the bookmark configuration.
        /// </summary>
        /// <value>The bookmark configuration.</value>
        property VxSdkNet::Configuration::Bookmark^ BookmarkConfig {
        public:
            VxSdkNet::Configuration::Bookmark^ get() { return _GetBookmarkConfig(); }
        }

        /// <summary>
        /// Gets the bookmarks from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the bookmarks on the system.</value>
        property System::Collections::Generic::List<Bookmark^>^ Bookmarks {
            System::Collections::Generic::List<Bookmark^>^ get() { return GetBookmarks(nullptr); }
        }

        /// <summary>
        /// Gets the cluster configuration from the VideoXpert system.
        /// </summary>
        /// <value>The cluster configuration.</value>
        property Configuration::Cluster^ ClusterConfig {
            Configuration::Cluster^ get() { return _GetClusterConfig(); }
        }

        /// <summary>
        /// Gets the user currently accessing the VideoXpert system.
        /// </summary>
        /// <value>The current user.</value>
        property User^ Currentuser {
            User^ get() { return _GetCurrentUser(); }
        }
        
        /// <summary>
        /// Gets the data objects from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the data objects on the system.</value>
        property System::Collections::Generic::List<DataObject^>^ DataObjects {
            System::Collections::Generic::List<DataObject^>^ get() { return GetDataObjects(nullptr); }
        }
        
        /// <summary>
        /// Gets the data sources from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the data sources on the system.</value>
        property System::Collections::Generic::List<DataSource^>^ DataSources {
            System::Collections::Generic::List<DataSource^>^ get() { return GetDataSources(nullptr); }
        }
        
        /// <summary>
        /// Gets the data storages from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the data storages on the system.</value>
        property System::Collections::Generic::List<DataStorage^>^ DataStorages {
            System::Collections::Generic::List<DataStorage^>^ get() { return GetDataStorages(nullptr); }
        }
        
        /// <summary>
        /// Gets the device assignments from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the device assignments on the system.</value>
        property System::Collections::Generic::List<DeviceAssignment^>^ DeviceAssignments {
            System::Collections::Generic::List<DeviceAssignment^>^ get() { return GetDeviceAssignments(nullptr); }
        }
        
        /// <summary>
        /// Gets the devices from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the devices on the system.</value>
        property System::Collections::Generic::List<Device^>^ Devices {
            System::Collections::Generic::List<Device^>^ get() { return GetDevices(nullptr); }
        }

        /// <summary>
        /// Gets the current discovery status.
        /// </summary>
        /// <value>The current discovery status.</value>
        property Discovery^ DiscoveryStatus {
            Discovery^ get() { return _GetDiscoveryStatus(); }
        }
        
        /// <summary>
        /// Gets the drawings from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the drawings on the system.</value>
        property System::Collections::Generic::List<Drawing^>^ Drawings {
            System::Collections::Generic::List<Drawing^>^ get() { return GetDrawings(nullptr); }
        }
        
        /// <summary>
        /// Gets the drivers from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the drivers on the system.</value>
        property System::Collections::Generic::List<Driver^>^ Drivers {
            System::Collections::Generic::List<Driver^>^ get() { return GetDrivers(nullptr); }
        }

        /// <summary>
        /// Gets the event configuration.
        /// </summary>
        /// <value>The event configuration.</value>
        property VxSdkNet::Configuration::Event^ EventConfig {
        public:
            VxSdkNet::Configuration::Event^ get() { return _GetEventConfig(); }
        }
        
        /// <summary>
        /// Gets the events from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the events on the system.</value>
        property System::Collections::Generic::List<Event^>^ Events {
            System::Collections::Generic::List<Event^>^ get() { return GetEvents(nullptr); }
        }

        /// <summary>
        /// Gets the export configuration.
        /// </summary>
        /// <value>The export configuration.</value>
        property VxSdkNet::Configuration::Export^ ExportConfig {
        public:
            VxSdkNet::Configuration::Export^ get() { return _GetExportConfig(); }
        }
        
        /// <summary>
        /// Gets the exports from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the exports on the system.</value>
        property System::Collections::Generic::List<Export^>^ Exports {
            System::Collections::Generic::List<Export^>^ get() { return GetExports(nullptr); }
        }

        /// <summary>
        /// Gets the files from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the files on the system.</value>
        property System::Collections::Generic::List<VxFile^>^ Files {
            System::Collections::Generic::List<VxFile^>^ get() { return GetFiles(nullptr); }
        }

        /// <summary>
        /// Gets the grace license expiration date time (if applicable).
        /// </summary>
        /// <value>The grace license expiration time.</value>
        property System::DateTime GraceLicenseExpirationTime {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_system->graceLicenseExpirationTime); }
        }

        /// <summary>
        /// Gets the device that hosts this system.
        /// </summary>
        /// <value>The host device.</value>
        property VxSdkNet::Device^ HostDevice {
        public:
            VxSdkNet::Device^ get() { return _GetHostDevice(); }
        }

        /// <summary>
        /// Gets the unique identifier of the VideoXpert system.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
            System::String^ get() { return Utils::ConvertCppString(_system->id); }
        }

        /// <summary>
        /// Gets the LDAP configuration.
        /// </summary>
        /// <value>The LDAP configuration.</value>
        property VxSdkNet::Configuration::Ldap^ LdapConfig {
        public:
            VxSdkNet::Configuration::Ldap^ get() { return _GetLdapConfig(); }
        }
        
        /// <summary>
        /// Gets the manual recordings from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the manual recordings on the system.</value>
        property System::Collections::Generic::List<ManualRecording^>^ ManualRecordings {
            System::Collections::Generic::List<ManualRecording^>^ get() { return GetManualRecordings(nullptr); }
        }

        /// <summary>
        /// Gets the member systems that this system is aggregating.
        /// </summary>
        /// <value>A <c>List</c> containing the member systems.</value>
        property System::Collections::Generic::List<Member^>^ Members {
            System::Collections::Generic::List<Member^>^ get() { return GetMembers(nullptr); }
        }
        
        /// <summary>
        /// Gets the monitors from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the monitors on the system.</value>
        property System::Collections::Generic::List<Monitor^>^ Monitors {
            System::Collections::Generic::List<Monitor^>^ get() { return GetMonitors(nullptr); }
        }
        
        /// <summary>
        /// Gets the monitor walls from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the monitor walls on the system.</value>
        property System::Collections::Generic::List<MonitorWall^>^ MonitorWalls {
            System::Collections::Generic::List<MonitorWall^>^ get() { return GetMonitorWalls(nullptr); }
        }

        /// <summary>
        /// Gets the friendly name of the VideoXpert system.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
            System::String^ get() { return Utils::ConvertCppString(_system->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _system->SetName(name);
            }
        }

        /// <summary>
        /// Gets the recordings from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the recordings on the system.</value>
        property System::Collections::Generic::List<Recording^>^ Recordings {
            System::Collections::Generic::List<Recording^>^ get() { return GetRecordings(nullptr); }
        }
        
        /// <summary>
        /// Gets the relay outputs from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the relay outputs on the system.</value>
        property System::Collections::Generic::List<RelayOutput^>^ RelayOutputs {
            System::Collections::Generic::List<RelayOutput^>^ get() { return GetRelayOutputs(nullptr); }
        }

        /// <summary>
        /// Gets the report configuration.
        /// </summary>
        /// <value>The report configuration.</value>
        property VxSdkNet::Configuration::Report^ ReportConfig {
        public:
            VxSdkNet::Configuration::Report^ get() { return _GetReportConfig(); }
        }

        /// <summary>
        /// Gets the reports from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the reports on the system.</value>
        property System::Collections::Generic::List<Report^>^ Reports {
            System::Collections::Generic::List<Report^>^ get() { return GetReports(nullptr); }
        }

        /// <summary>
        /// Gets the report templates from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the report templates on the system.</value>
        property System::Collections::Generic::List<ReportTemplate^>^ ReportTemplates {
            System::Collections::Generic::List<ReportTemplate^>^ get() { return GetReportTemplates(nullptr); }
        }

        /// <summary>
        /// Gets the roles from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the roles on the system.</value>
        property System::Collections::Generic::List<Role^>^ Roles {
            System::Collections::Generic::List<Role^>^ get() { return GetRoles(nullptr); }
        }

        /// <summary>
        /// Gets the ordered permission schema information for roles.
        /// </summary>
        /// <value>The permission schema.</value>
        property PermissionSchema^ RolePermissionSchema {
            PermissionSchema^ get() { return _GetPermissionSchema(); }
        }
        
        /// <summary>
        /// Gets the rules from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the rules on the system.</value>
        property System::Collections::Generic::List<Rule^>^ Rules {
            System::Collections::Generic::List<Rule^>^ get() { return GetRules(nullptr); }
        }
        
        /// <summary>
        /// Gets the schedules from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the schedules on the system.</value>
        property System::Collections::Generic::List<Schedule^>^ Schedules {
            System::Collections::Generic::List<Schedule^>^ get() { return GetSchedules(nullptr); }
        }

        /// <summary>
        /// Gets the server configuration.
        /// </summary>
        /// <value>The server configuration.</value>
        property VxSdkNet::Configuration::Server^ ServerConfig {
        public:
            VxSdkNet::Configuration::Server^ get() { return _GetServerConfig(); }
        }
        
        /// <summary>
        /// Gets the situations from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the situations on the system.</value>
        property System::Collections::Generic::List<Situation^>^ Situations {
            System::Collections::Generic::List<Situation^>^ get() { return GetSituations(nullptr); }
        }

        /// <summary>
        /// Gets the SMTP configuration.
        /// </summary>
        /// <value>The SMTP configuration.</value>
        property VxSdkNet::Configuration::Smtp^ SmtpConfig {
        public:
            VxSdkNet::Configuration::Smtp^ get() { return _GetSmtpConfig(); }
        }

        /// <summary>
        /// Gets the SNMP agent configuration.
        /// </summary>
        /// <value>The SNMP agent configuration.</value>
        property VxSdkNet::Configuration::Snmp^ SnmpConfig {
        public:
            VxSdkNet::Configuration::Snmp^ get() { return _GetSnmpConfig(); }
        }

        /// <summary>
        /// Gets the current system time (UTC).
        /// </summary>
        /// <value>The current system time (UTC).</value>
        property System::DateTime SystemTime {
        public:
            System::DateTime get() {
                char time[64];
                _system->GetSystemTime(time);
                return Utils::ConvertCppDateTime(time);
            }
        }

        /// <summary>
        /// Gets the tags from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the tags on the system.</value>
        property System::Collections::Generic::List<Tag^>^ Tags {
            System::Collections::Generic::List<Tag^>^ get() { return GetTags(nullptr); }
        }

        /// <summary>
        /// Gets the time configuration.
        /// </summary>
        /// <value>The time configuration.</value>
        property VxSdkNet::Configuration::Time^ TimeConfig {
        public:
            VxSdkNet::Configuration::Time^ get() { return _GetTimeConfig(); }
        }
        
        /// <summary>
        /// Gets the time tables from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the time tables on the system.</value>
        property System::Collections::Generic::List<TimeTable^>^ TimeTables {
            System::Collections::Generic::List<TimeTable^>^ get() { return GetTimeTables(nullptr); }
        }



        /// <summary>
        /// Gets the Twilio SMS account configuration.
        /// </summary>
        /// <value>The Twilio SMS account configuration.</value>
        property VxSdkNet::Configuration::Twilio^ TwilioConfig {
        public:
            VxSdkNet::Configuration::Twilio^ get() { return _GetTwilioConfig(); }
        }
        
        /// <summary>
        /// Gets the users from the VideoXpert system.
        /// </summary>
        /// <value>A <c>List</c> containing the users on the system.</value>
        property System::Collections::Generic::List<User^>^ Users {
            System::Collections::Generic::List<User^>^ get() { return GetUsers(nullptr); }
        }

        /// <summary>
        /// SystemEvent is raised whenever a new event is created on the system.
        /// </summary>
        event EventDelegate ^ SystemEvent {
            void add(EventDelegate ^eventDelegate);
            void remove(EventDelegate ^eventDelegate);
        }

        /// <summary>
        /// InternalEvent is raised whenever a new internal event is sent from the VxSDK.
        /// </summary>
        event InternalEventDelegate ^ InternalEvent {
            void add(InternalEventDelegate ^sdkEventDelegate);
            void remove(InternalEventDelegate ^sdkEventDelegate);
        }

    internal:
        VxSdk::IVxSystem* _system;
        EventCallbackDelegate ^ _callback;
        InternalEventCallbackDelegate ^ _internalCallback;
        VxSdk::VxLoginInfo* _loginInfo;
        static EventDelegate ^ _systemEvent;
        static InternalEventDelegate ^ _sdkEvent;
        EventDelegate^ _eventDelegate;
        static void _FireEvent(VxSdk::IVxEvent* vxEvent);
        static void _FireInternalEvent(VxSdk::VxInternalEvent* vxInternalEvent);
        Configuration::Auth^ _GetAuthConfig();
        System::Collections::Generic::List<NewReportTemplate^>^ _GetAvailableReportTemplates();
        System::Collections::Generic::List<System::String^>^ _GetAvailableScheduleTriggerEvents();
        Configuration::Bookmark^ _GetBookmarkConfig();
        Configuration::Cluster^ _GetClusterConfig();
        VxSdkNet::User^ _GetCurrentUser();
        Discovery^ _GetDiscoveryStatus();
        Configuration::Event^ _GetEventConfig();
        Configuration::Export^ _GetExportConfig();
        VxSdkNet::Device^ _GetHostDevice();
        Configuration::Ldap^ _GetLdapConfig();
        PermissionSchema^ _GetPermissionSchema();
        Configuration::Report^ _GetReportConfig();
        Configuration::Server^ _GetServerConfig();
        Configuration::Smtp^ _GetSmtpConfig();
        Configuration::Snmp^ _GetSnmpConfig();
        Configuration::Time^ _GetTimeConfig();
        Configuration::Twilio^ _GetTwilioConfig();
    };
}
#endif // VXSystem_h__
