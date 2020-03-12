/// <summary>
/// Implements the VX System class.
/// </summary>
#include "AnalyticSession.h"
#include "VxSystem.h"
#include "VxSdk.h"
#include "NewAnalyticSession.h"

namespace {
    /// <summary>
    /// Converts a data source type to it'string representation.
    /// </summary>
    /// <param name="type">The datasource type to convert</param>
    /// <returns>The string representation of the data source type</returns>
    const char* ConvertDataSourceTypeToString(VxSdkNet::DataSource::Types type)
    {
        switch (type)
        {
        case VxSdkNet::DataSource::Types::Audio:
            return "audio";
        case VxSdkNet::DataSource::Types::Metadata:
            return "metadata";
        case VxSdkNet::DataSource::Types::Video:
            return "video";
        default:
            return "";
        }
    }
}

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

VxSdkNet::VXSystem::VXSystem(String^ ip, String^ licenseKey) : _loginInfo(new VxSdk::VxLoginInfo()) {
    // Enter the VideoXpert IP information
    VxSdk::Utilities::StrCopySafe(_loginInfo->ipAddress, Utils::ConvertCSharpString(ip).c_str());
    VxSdk::Utilities::StrCopySafe(_loginInfo->licenseKey, Utils::ConvertCSharpString(licenseKey).c_str());
}

VxSdkNet::VXSystem::VXSystem(String^ ip, int port, bool useSSL, String^ licenseKey) : _loginInfo(new VxSdk::VxLoginInfo()) {
    // Enter the VideoXpert IP information
    VxSdk::Utilities::StrCopySafe(_loginInfo->ipAddress, Utils::ConvertCSharpString(ip).c_str());
    VxSdk::Utilities::StrCopySafe(_loginInfo->licenseKey, Utils::ConvertCSharpString(licenseKey).c_str());
    _loginInfo->port = port;
    _loginInfo->useSsl = useSSL;
}

VxSdkNet::VXSystem::!VXSystem() {
    // Delete system object
    if (_system != nullptr) {
        // Unsubscribe to the system events
        _system->StopNotifications();
        _system->StopInternalNotifications();
        delete _callback;
        _system->Delete();
        _system = nullptr;
    }

    // Delete loginInfo object
    if (_loginInfo != nullptr) {
        delete _loginInfo;
    }
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddAnalyticSession(NewAnalyticSession^ newAnalyticSession) {
    VxSdk::VxNewAnalyticSession vxNewAnalyticSession;
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.dataEncodingId, Utils::ConvertCSharpString(newAnalyticSession->DataEncodingId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.dataSourceId, Utils::ConvertCSharpString(newAnalyticSession->DataSourceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.deviceId, Utils::ConvertCSharpString(newAnalyticSession->DeviceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.id, Utils::ConvertCSharpString(newAnalyticSession->Id).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewAnalyticSession.source, Utils::ConvertCSharpString(newAnalyticSession->Source).c_str());

    // Attempt to add the analytic session
    return VxSdkNet::Results::Value(_system->AddAnalyticSession(vxNewAnalyticSession));
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddBookmark(VxSdkNet::NewBookmark^ newBookmark) {
    // Create a bookmark object and populate its fields using newBookmark
    VxSdk::VxNewBookmark vxBookmark;
    VxSdk::Utilities::StrCopySafe(vxBookmark.dataSourceId, Utils::ConvertCSharpString(newBookmark->DataSourceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxBookmark.description, Utils::ConvertCSharpString(newBookmark->Description).c_str());
    VxSdk::Utilities::StrCopySafe(vxBookmark.groupId, Utils::ConvertCSharpString(newBookmark->GroupId).c_str());
    VxSdk::Utilities::StrCopySafe(vxBookmark.lockEndTime, Utils::ConvertCSharpDateTime(newBookmark->LockEndTime).c_str());
    VxSdk::Utilities::StrCopySafe(vxBookmark.lockStartTime, Utils::ConvertCSharpDateTime(newBookmark->LockStartTime).c_str());
    VxSdk::Utilities::StrCopySafe(vxBookmark.name, Utils::ConvertCSharpString(newBookmark->Name).c_str());
    VxSdk::Utilities::StrCopySafe(vxBookmark.time, Utils::ConvertCSharpDateTime(newBookmark->Time).c_str());
    vxBookmark.isLocked = newBookmark->IsLocked;

    // Make the call to add the bookmark into VideoXpert
    VxSdk::VxResult::Value result = _system->AddBookmark(vxBookmark);
    // Unless there was an issue creating the bookmark the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddDataObject(VxSdkNet::NewDataObject^ newDataObject) {
    // Create a new data object and populate its fields using newDataObject
    VxSdk::VxNewDataObject vxDataObject;
    VxSdk::Utilities::StrCopySafe(vxDataObject.clientType, Utils::ConvertCSharpString(newDataObject->ClientType).c_str());
    std::string val = Utils::ConvertCSharpString(newDataObject->Data);
    vxDataObject.data = (char*)val.c_str();
    vxDataObject.isPrivate = newDataObject->IsPrivate;

    // Make the call to add the data object into VideoXpert
    VxSdk::VxResult::Value result = _system->AddDataObject(vxDataObject);
    // Unless there was an issue creating the data object the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddDevice(VxSdkNet::NewDevice^ newDevice) {
    VxSdk::VxNewDevice vxNewDevice;
    vxNewDevice.shouldAutoCommission = newDevice->ShouldAutoCommission;
    VxSdk::Utilities::StrCopySafe(vxNewDevice.driverType, Utils::ConvertCSharpString(newDevice->DriverType).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.id, Utils::ConvertCSharpString(newDevice->Id).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.ip, Utils::ConvertCSharpString(newDevice->Ip).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.host, Utils::ConvertCSharpString(newDevice->Host).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.model, Utils::ConvertCSharpString(newDevice->Model).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.name, Utils::ConvertCSharpString(newDevice->Name).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.password, Utils::ConvertCSharpString(newDevice->Password).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.serial, Utils::ConvertCSharpString(newDevice->Serial).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.username, Utils::ConvertCSharpString(newDevice->Username).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.vendor, Utils::ConvertCSharpString(newDevice->Vendor).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewDevice.version, Utils::ConvertCSharpString(newDevice->Version).c_str());
    vxNewDevice.type = VxSdk::VxDeviceType::Value(newDevice->Type);
    vxNewDevice.port = newDevice->Port;
    vxNewDevice.endpointsSize = static_cast<int>(newDevice->Endpoints->Count);
    if (vxNewDevice.endpointsSize > 0) {
        vxNewDevice.endpoints = new char* [vxNewDevice.endpointsSize];
        for (int i = 0; i < vxNewDevice.endpointsSize; i++) {
            int endpointLength = newDevice->Endpoints[i]->Length + 1;
            vxNewDevice.endpoints[i] = new char[endpointLength];
            VxSdk::Utilities::StrCopySafe(vxNewDevice.endpoints[i], Utils::ConvertCSharpString(newDevice->Endpoints[i]).c_str(), endpointLength);
        }
    }

    // Make the call to add the device into VideoXpert
    VxSdk::VxResult::Value result = _system->AddDevice(vxNewDevice);
    // Unless there was an issue creating the device the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddDrawing(System::String^ drawingName) {
    VxSdk::VxNewDrawing vxDrawing;
    VxSdk::Utilities::StrCopySafe(vxDrawing.name, Utils::ConvertCSharpString(drawingName).c_str());

    // Make the call to add the drawing into VideoXpert
    VxSdk::VxResult::Value result = _system->AddDrawing(vxDrawing);
    // Unless there was an issue creating the drawing the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Export^ VxSdkNet::VXSystem::AddExport(VxSdkNet::NewExport^ newExport) {
    // Create a VxNewExport object using the settings contained in newExport and the VxNewExportClip that
    // was just created.
    VxSdk::VxNewExport vxExport;
    vxExport.clipSize = newExport->Clips->Count;
    if (vxExport.clipSize > 0) {
        // Create new VxNewExportClip objects using the clip info contained in newExport
        vxExport.clips = new VxSdk::VxNewExportClip[vxExport.clipSize];
        for (int i = 0; i < vxExport.clipSize; i++) {
            VxSdk::Utilities::StrCopySafe(vxExport.clips[i].dataSourceId, Utils::ConvertCSharpString(newExport->Clips[i]->DataSourceId).c_str());
            VxSdk::Utilities::StrCopySafe(vxExport.clips[i].startTime, Utils::ConvertCSharpDateTime(newExport->Clips[i]->StartTime).c_str());
            VxSdk::Utilities::StrCopySafe(vxExport.clips[i].endTime, Utils::ConvertCSharpDateTime(newExport->Clips[i]->EndTime).c_str());
        }
    }

    vxExport.format = (VxSdk::VxExportFormat::Value)newExport->Format;
    VxSdk::Utilities::StrCopySafe(vxExport.name, Utils::ConvertCSharpString(newExport->Name).c_str());
    // If the password field has a password set then the export will be password protected, if the password is not
    // set, the export will be public
    VxSdk::Utilities::StrCopySafe(vxExport.password, Utils::ConvertCSharpString(newExport->Password).c_str());

    VxSdkNet::Export^ retExport = nullptr;
    // Attempt to create the export
    VxSdk::IVxExport* exportItem = nullptr;
    VxSdk::VxResult::Value result = _system->CreateExport(vxExport, exportItem);

    // Unless there was an issue initiating the export the result should be VxSdk::VxResult::kOK
    if (result == VxSdk::VxResult::kOK) {
        // The exportItem returned from the system is the export initiated on the server and contains a lot of
        // helpful information about the export.
        retExport = gcnew VxSdkNet::Export(exportItem);
    }

    delete[] vxExport.clips;
    vxExport.clips = nullptr;

    return retExport;
}

VxSdkNet::ManualRecording^ VxSdkNet::VXSystem::AddManualRecording(VxSdkNet::NewManualRecording^ newManualRecording) {
    VxSdk::VxNewManualRecording vxNewManualRecording;
    VxSdk::Utilities::StrCopySafe(vxNewManualRecording.dataSourceId, Utils::ConvertCSharpString(newManualRecording->DataSourceId).c_str());
    vxNewManualRecording.postRecord = newManualRecording->PostRecord;
    vxNewManualRecording.preRecord = newManualRecording->PreRecord;

    VxSdkNet::ManualRecording^ retManualRecording = nullptr;
    // Make the call to add the manual recording into VideoXpert
    VxSdk::IVxManualRecording* manualRecordingItem = nullptr;
    VxSdk::VxResult::Value result = _system->AddManualRecording(vxNewManualRecording, manualRecordingItem);

    // Unless there was an issue adding the manual recording the result should be VxSdk::VxResult::kOK
    if (result == VxSdk::VxResult::kOK) {
        retManualRecording = gcnew VxSdkNet::ManualRecording(manualRecordingItem);
    }
    return retManualRecording;
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddMember(NewMember^ newMember) {
    // Create a new member object and populate its fields using newMember
    VxSdk::VxNewMember vxNewMember;
    VxSdk::Utilities::StrCopySafe(vxNewMember.host, Utils::ConvertCSharpString(newMember->Host).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewMember.username, Utils::ConvertCSharpString(newMember->Username).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewMember.password, Utils::ConvertCSharpString(newMember->Password).c_str());
    vxNewMember.bandwidth = newMember->Bandwidth;
    vxNewMember.port = newMember->Port;
    vxNewMember.rtspCapability = (VxSdk::VxRtspCapability::Value)newMember->RtspCapabilities;

    // Make the call to add the member into VideoXpert
    VxSdk::VxResult::Value result = _system->AddMember(vxNewMember);
    // Unless there was an issue adding the member the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddMonitorWall(System::String^ monitorWallName) {
    // Make the call to add the monitor wall into VideoXpert
    VxSdk::VxResult::Value result = _system->CreateMonitorWall(Utils::ConvertCSharpString(monitorWallName).c_str());
    // Unless there was an issue creating the monitor wall the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddRole(System::String^ roleName) {
    // Make the call to add the role into VideoXpert
    VxSdk::VxResult::Value result = _system->AddRole(Utils::ConvertCSharpString(roleName).c_str());
    // Unless there was an issue creating the role the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddRule(VxSdkNet::NewRule^ newRule) {
    // Create a new rule and populate its fields using newRule
    VxSdk::VxNewRule vxNewRule;
    VxSdk::Utilities::StrCopySafe(vxNewRule.name, Utils::ConvertCSharpString(newRule->Name).c_str());
    std::string val = Utils::ConvertCSharpString(newRule->Script);
    vxNewRule.script = (char*)val.c_str();
    vxNewRule.isEnabled = newRule->IsEnabled;
    vxNewRule.triggerSize = newRule->RuleTriggers->Count;
    if (vxNewRule.triggerSize > 0)  {
        vxNewRule.triggers = new VxSdk::VxRuleTrigger[vxNewRule.triggerSize];
        for (int i = 0; i < vxNewRule.triggerSize; i++) {
            VxSdk::Utilities::StrCopySafe(vxNewRule.triggers[i].situationType, Utils::ConvertCSharpString(newRule->RuleTriggers[i]->SituationType).c_str());
            vxNewRule.triggers[i].sourceRefSize = newRule->RuleTriggers[i]->ResourceRefs->Count;
            vxNewRule.triggers[i].sourceRef = new VxSdk::VxResourceRef[vxNewRule.triggers[i].sourceRefSize];
            for (int ii = 0; ii < vxNewRule.triggers[i].sourceRefSize; ii++) {
                VxSdk::Utilities::StrCopySafe(vxNewRule.triggers[i].sourceRef[ii].id, Utils::ConvertCSharpString(newRule->RuleTriggers[i]->ResourceRefs[ii]->Id).c_str());
                vxNewRule.triggers[i].sourceRef[ii].type = (VxSdk::VxResourceType::Value)newRule->RuleTriggers[i]->ResourceRefs[ii]->Type;
            }
        }
    }

    vxNewRule.timeTableIdSize = static_cast<int>(newRule->TimeTables->Count);
    if (vxNewRule.timeTableIdSize > 0) {
        vxNewRule.timeTableIds = new char*[vxNewRule.timeTableIdSize];
        for (int i = 0; i < vxNewRule.timeTableIdSize; i++) {
            int idLength = newRule->TimeTables[i]->Id->Length + 1;
            vxNewRule.timeTableIds[i] = new char[idLength];
            VxSdk::Utilities::StrCopySafe(vxNewRule.timeTableIds[i], Utils::ConvertCSharpString(newRule->TimeTables[i]->Id).c_str(), idLength);
        }
    }

    // Make the call to add the rule into VideoXpert
    VxSdk::VxResult::Value result = _system->AddRule(vxNewRule);

    for (int i = 0; i < vxNewRule.timeTableIdSize; i++)
        delete[] vxNewRule.timeTableIds[i];

    delete[] vxNewRule.timeTableIds;
    delete[] vxNewRule.triggers;

    // Unless there was an issue creating the rule the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddSchedule(VxSdkNet::NewSchedule^ newSchedule) {
    // Create a schedule object and populate its fields using newSchedule
    VxSdk::VxNewSchedule vxSchedule;
    VxSdk::Utilities::StrCopySafe(vxSchedule.id, Utils::ConvertCSharpString(newSchedule->Id).c_str());
    VxSdk::Utilities::StrCopySafe(vxSchedule.name, Utils::ConvertCSharpString(newSchedule->Name).c_str());
    vxSchedule.action = (VxSdk::VxScheduleAction::Value)newSchedule->Action;
    vxSchedule.useAllDataSources = newSchedule->UseAllDataSources;

    // Create new VxNewScheduleTrigger objects using the ScheduleTrigger info contained in newSchedule
    vxSchedule.scheduleTriggerSize = newSchedule->ScheduleTriggers->Count;
    if (vxSchedule.scheduleTriggerSize > 0) {
        vxSchedule.scheduleTriggers = new VxSdk::VxNewScheduleTrigger[vxSchedule.scheduleTriggerSize];
        for (int i = 0; i < vxSchedule.scheduleTriggerSize; i++) {
            VxSdk::Utilities::StrCopySafe(vxSchedule.scheduleTriggers[i].id, Utils::ConvertCSharpString(newSchedule->ScheduleTriggers[i]->Id).c_str());
            VxSdk::Utilities::StrCopySafe(vxSchedule.scheduleTriggers[i].eventSituationType, Utils::ConvertCSharpString(newSchedule->ScheduleTriggers[i]->EventSituationType).c_str());
            vxSchedule.scheduleTriggers[i].postTrigger = newSchedule->ScheduleTriggers[i]->PostTrigger;
            vxSchedule.scheduleTriggers[i].preTrigger = newSchedule->ScheduleTriggers[i]->PreTrigger;
            vxSchedule.scheduleTriggers[i].timeout = newSchedule->ScheduleTriggers[i]->Timeout;
            vxSchedule.scheduleTriggers[i].framerate = VxSdk::VxRecordingFramerate::Value(newSchedule->ScheduleTriggers[i]->Framerate);

            // Add any event properties to the new schedule trigger
            vxSchedule.scheduleTriggers[i].eventPropertySize = newSchedule->ScheduleTriggers[i]->EventProperties->Count;
            if (vxSchedule.scheduleTriggers[i].eventPropertySize > 0) {
                vxSchedule.scheduleTriggers[i].eventProperties = new VxSdk::VxKvObject[vxSchedule.scheduleTriggers[i].eventPropertySize];
                for (int ii = 0; ii < vxSchedule.scheduleTriggers[i].eventPropertySize; ii++) {
                    VxSdk::Utilities::StrCopySafe(vxSchedule.scheduleTriggers[i].eventProperties[ii].key,
                        Utils::ConvertCSharpString(newSchedule->ScheduleTriggers[i]->EventProperties[ii].Key).c_str());
                    VxSdk::Utilities::StrCopySafe(vxSchedule.scheduleTriggers[i].eventProperties[ii].value,
                        Utils::ConvertCSharpString(newSchedule->ScheduleTriggers[i]->EventProperties[ii].Value).c_str());
                }
            }
        }
    }

    // Make the call to add the schedule into VideoXpert
    VxSdk::VxResult::Value result = _system->AddSchedule(vxSchedule);

    // Unless there was an issue adding the schedule the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddSituation(VxSdkNet::NewSituation^ newSituation) {
    // Create a situation object and populate its fields using newSituation
    VxSdk::VxNewSituation vxSituation;
    VxSdk::Utilities::StrCopySafe(vxSituation.name, Utils::ConvertCSharpString(newSituation->Name).c_str());
    VxSdk::Utilities::StrCopySafe(vxSituation.sourceDeviceId, Utils::ConvertCSharpString(newSituation->SourceDeviceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxSituation.type, Utils::ConvertCSharpString(newSituation->Type).c_str());
    vxSituation.isAckNeeded = newSituation->IsAckNeeded;
    vxSituation.audibleLoopDelay = newSituation->AudibleLoopDelay;
    vxSituation.audiblePlayCount = newSituation->AudiblePlayCount;
    vxSituation.autoAcknowledge = newSituation->AutoAcknowledge;
    vxSituation.shouldAudiblyNotify = newSituation->ShouldAudiblyNotify;
    vxSituation.shouldExpandBanner = newSituation->ShouldExpandBanner;
    vxSituation.shouldLog = newSituation->ShouldLog;
    vxSituation.shouldNotify = newSituation->ShouldNotify;
    vxSituation.shouldPopupBanner = newSituation->ShouldPopupBanner;
    vxSituation.severity = newSituation->Severity;
    vxSituation.snoozeIntervalSize = newSituation->SnoozeIntervals->Count;
    if (vxSituation.snoozeIntervalSize > 0) {
        vxSituation.snoozeIntervals = new int[vxSituation.snoozeIntervalSize];
        for (int i = 0; i < vxSituation.snoozeIntervalSize; i++) {
            vxSituation.snoozeIntervals[i] = newSituation->SnoozeIntervals[i];
        }
    }

    // Make the call to add the situation into VideoXpert
    VxSdk::VxResult::Value result = _system->AddSituation(vxSituation);

    // Remove the memory we previously allocated
    delete[] vxSituation.snoozeIntervals;

    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddTag(VxSdkNet::NewTag^ newTag) {
    // Create a new tag object and populate its fields using newTag
    VxSdk::VxNewTag vxTag;
    VxSdk::Utilities::StrCopySafe(vxTag.name, Utils::ConvertCSharpString(newTag->Name).c_str());
    VxSdk::Utilities::StrCopySafe(vxTag.parentId, Utils::ConvertCSharpString(newTag->ParentId).c_str());
    vxTag.isFolder = newTag->IsFolder;
    vxTag.isPublic = newTag->IsPublic;

    // Make the call to add the tag into VideoXpert
    VxSdk::VxResult::Value result = _system->AddTag(vxTag);
    // Unless there was an issue creating the tag the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddTimeTable(VxSdkNet::NewTimeTable^ newTimeTable) {
    // Create a new time table object and populate its fields using newTimeTable
    VxSdk::VxNewTimeTable vxNewTimeTable;
    VxSdk::Utilities::StrCopySafe(vxNewTimeTable.name, Utils::ConvertCSharpString(newTimeTable->Name).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewTimeTable.id, Utils::ConvertCSharpString(newTimeTable->Id).c_str());

    if (newTimeTable->EndDate != System::DateTime::MinValue)
        VxSdk::Utilities::StrCopySafe(vxNewTimeTable.endDate, Utils::ConvertCSharpDateTime(newTimeTable->EndDate).c_str());
    else
        VxSdk::Utilities::StrCopySafe(vxNewTimeTable.endDate, new char[64]);

    if (newTimeTable->StartDate != System::DateTime::MinValue)
        VxSdk::Utilities::StrCopySafe(vxNewTimeTable.startDate, Utils::ConvertCSharpDateTime(newTimeTable->StartDate).c_str());
    else
        VxSdk::Utilities::StrCopySafe(vxNewTimeTable.startDate, new char[64]);

    vxNewTimeTable.weeklyTimeRangeSize = newTimeTable->WeeklyTimeRanges->Count;
    if (vxNewTimeTable.weeklyTimeRangeSize > 0) {
        vxNewTimeTable.weeklyTimeRanges = new VxSdk::VxTimeRange[vxNewTimeTable.weeklyTimeRangeSize];
        for (int i = 0; i < vxNewTimeTable.weeklyTimeRangeSize; i++) {
            vxNewTimeTable.weeklyTimeRanges[i].day = (VxSdk::VxDayOfWeek::Value)newTimeTable->WeeklyTimeRanges[i]->Day;
            VxSdk::Utilities::StrCopySafe(vxNewTimeTable.weeklyTimeRanges[i].endTime, Utils::ConvertCSharpTime(newTimeTable->WeeklyTimeRanges[i]->EndTime).c_str());
            VxSdk::Utilities::StrCopySafe(vxNewTimeTable.weeklyTimeRanges[i].startTime, Utils::ConvertCSharpTime(newTimeTable->WeeklyTimeRanges[i]->StartTime).c_str());
        }
    }

    // Make the call to add the time table into VideoXpert
    VxSdk::VxResult::Value result = _system->AddTimeTable(vxNewTimeTable);

    delete[] vxNewTimeTable.weeklyTimeRanges;
    vxNewTimeTable.weeklyTimeRanges = nullptr;

    // Unless there was an issue creating the time table the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddUser(VxSdkNet::NewUser^ newUser) {
    // Create a new user object and populate its fields using newUser
    VxSdk::VxNewUser vxNewUser;
    VxSdk::Utilities::StrCopySafe(vxNewUser.domain, Utils::ConvertCSharpString(newUser->Domain).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.email, Utils::ConvertCSharpString(newUser->Email).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.employeeId, Utils::ConvertCSharpString(newUser->EmployeeId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.firstName, Utils::ConvertCSharpString(newUser->FirstName).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.lastName, Utils::ConvertCSharpString(newUser->LastName).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.name, Utils::ConvertCSharpString(newUser->Name).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.note, Utils::ConvertCSharpString(newUser->Note).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewUser.password, Utils::ConvertCSharpString(newUser->Password).c_str());
    vxNewUser.mustChangePassword = newUser->MustChangePassword;
    vxNewUser.canBypassLdap = newUser->CanBypassLdap;
    vxNewUser.isPasswordExpirationDisabled = newUser->IsPasswordExpirationDisabled;
    vxNewUser.phoneNumberSize = newUser->PhoneNumbers->Count;
    if (vxNewUser.phoneNumberSize > 0) {
        vxNewUser.phoneNumbers = new VxSdk::VxPhoneNumber[vxNewUser.phoneNumberSize];
        for (int i = 0; i < vxNewUser.phoneNumberSize; i++) {
            vxNewUser.phoneNumbers[i].type = (VxSdk::VxPhoneType::Value)newUser->PhoneNumbers[i].Key;
            VxSdk::Utilities::StrCopySafe(vxNewUser.phoneNumbers[i].number, Utils::ConvertCSharpString(newUser->PhoneNumbers[i].Value).c_str());
        }
    }

    // Make the call to add the user into VideoXpert
    VxSdk::VxResult::Value result = _system->AddUser(vxNewUser);

    delete[] vxNewUser.phoneNumbers;
    vxNewUser.phoneNumbers = nullptr;

    // Unless there was an issue creating the user the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::AddVxMonitor(NewMonitor^ newMonitor) {
    // Create a new monitor object and populate its fields using newMonitor
    VxSdk::VxNewMonitor vxNewMonitor;
    VxSdk::Utilities::StrCopySafe(vxNewMonitor.hostDeviceId, Utils::ConvertCSharpString(newMonitor->HostDeviceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxNewMonitor.name, Utils::ConvertCSharpString(newMonitor->Name).c_str());
    vxNewMonitor.layout = (VxSdk::VxCellLayout::Value)newMonitor->Layout;
    vxNewMonitor.number = newMonitor->Number;

    // Make the call to add the monitor into VideoXpert
    VxSdk::VxResult::Value result = _system->CreateMonitor(vxNewMonitor);
    // Unless there was an issue creating the monitor the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::CommissionDevice(VxSdkNet::Device^ device) {
    // Get the license object
    VxSdk::IVxLicense* license = nullptr;
    VxSdk::VxResult::Value result = _system->GetLicense(license);
    if (license == nullptr)
        return (VxSdkNet::Results::Value)result;

    if (result == VxSdk::VxResult::kOK )
        result = license->CommissionDevice(*device->_device);

    license->Delete();
    license = nullptr;

    return (VxSdkNet::Results::Value)result;
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DecommissionDevice(VxSdkNet::Device^ device) {
    // Get the license object
    VxSdk::IVxLicense* license = nullptr;
    VxSdk::VxResult::Value result = _system->GetLicense(license);
    if (license == nullptr)
        return (VxSdkNet::Results::Value)result;

    if (result == VxSdk::VxResult::kOK )
        result = license->DecommissionDevice(*device->_device);

    license->Delete();
    license = nullptr;

    return (VxSdkNet::Results::Value)result;
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteAnalyticSession(AnalyticSession^ analyticSession) {
    // Create aa analytic session object
    VxSdk::IVxAnalyticSession* delAnalyticSession = analyticSession->_analyticSession;

    // To delete an analytic session simply make a DeleteAnalyticSession call
    VxSdk::VxResult::Value result = delAnalyticSession->DeleteAnalyticSession();
    // Unless there was an issue deleting the analytic session the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteBookmark(VxSdkNet::Bookmark^ bookmarkItem) {
    // To delete a bookmark simply make a DeleteBookmark call
    VxSdk::VxResult::Value result = bookmarkItem->_bookmark->DeleteBookmark();
    // Unless there was an issue deleting the bookmark the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteDataObject(VxSdkNet::DataObject^ dataObjectItem) {
    // To delete a data object simply make a DeleteTag call
    VxSdk::VxResult::Value result = dataObjectItem->_dataObject->DeleteDataObject();
    // Unless there was an issue deleting the data object the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteDevice(VxSdkNet::Device^ device) {
    // To delete a device simply make a DeleteDevice call
    VxSdk::VxResult::Value result = device->_device->DeleteDevice();
    // Unless there was an issue deleting the device the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteDrawing(VxSdkNet::Drawing^ drawingItem) {
    // To delete a drawing simply make a DeleteDrawing call
    VxSdk::VxResult::Value result = drawingItem->_drawing->DeleteDrawing();
    // Unless there was an issue deleting the drawing the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteExport(VxSdkNet::Export^ exportItem) {
    // To delete an export simply make a DeleteExport call
    VxSdk::VxResult::Value result = exportItem->_export->DeleteExport();
    // Unless there was an issue deleting the export the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteManualRecording(VxSdkNet::ManualRecording^ manualRecordingItem) {
    // To delete a manual recording simply make a DeleteManualRecording call
    VxSdk::VxResult::Value result = manualRecordingItem->_manualRecording->DeleteManualRecording();
    // Unless there was an issue deleting the manual recording the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteMonitorWall(VxSdkNet::MonitorWall^ monitorWallItem) {
    // To delete a monitor wall simply make a DeleteMonitorWall call
    VxSdk::VxResult::Value result = monitorWallItem->_monitorWall->DeleteMonitorWall();
    // Unless there was an issue deleting the monitor wall the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteRole(VxSdkNet::Role^ roleItem) {
    // To delete a role simply make a DeleteRole call
    VxSdk::VxResult::Value result = roleItem->_role->DeleteRole();
    // Unless there was an issue deleting the role the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteRule(VxSdkNet::Rule^ ruleItem) {
    // To delete a rule simply make a DeleteRule call
    VxSdk::VxResult::Value result = ruleItem->_rule->DeleteRule();
    // Unless there was an issue deleting the rule the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteSchedule(VxSdkNet::Schedule^ scheduleItem) {
    // To delete a schedule simply make a DeleteSchedule call
    VxSdk::VxResult::Value result = scheduleItem->_schedule->DeleteSchedule();
    // Unless there was an issue deleting the schedule the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteSituation(VxSdkNet::Situation^ situationItem) {
    // To delete a situation simply make a DeleteSituation call
    VxSdk::VxResult::Value result = situationItem->_situation->DeleteSituation();
    // Unless there was an issue deleting the situation the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteTag(VxSdkNet::Tag^ tagItem) {
    // To delete a tag simply make a DeleteTag call
    VxSdk::VxResult::Value result = tagItem->_tag->DeleteTag();
    // Unless there was an issue deleting the tag the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteTimeTable(VxSdkNet::TimeTable^ timeTableItem) {
    // To delete a time table simply make a DeleteTimeTable call
    VxSdk::VxResult::Value result = timeTableItem->_timeTable->DeleteTimeTable();
    // Unless there was an issue deleting the time table the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteUser(VxSdkNet::User^ userItem) {
    // To delete a user simply make a DeleteUser call
    VxSdk::VxResult::Value result = userItem->_user->DeleteUser();
    // Unless there was an issue deleting the user the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::DeleteVxMonitor(VxSdkNet::Monitor^ monitorItem) {
    // To delete a monitor simply make a RemoveMonitor call
    VxSdk::VxResult::Value result = monitorItem->_monitor->RemoveMonitor();
    // Unless there was an issue deleting the monitor the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

List<VxSdkNet::AccessPoint^>^ VxSdkNet::VXSystem::GetAccessPoints(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed access point objects
    List<AccessPoint^>^ mlist = gcnew List<AccessPoint^>();
    // Create a collection of unmanaged access point objects
    VxSdk::VxCollection<VxSdk::IVxAccessPoint**> accessPoints;

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
        accessPoints.filterSize = filters->Count;
        accessPoints.filters = collFilters;
    }

    // Make the GetAccessPoints call, which will return with the total count of access points, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetAccessPoints(accessPoints);
    // Unless there are no access points on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetAccessPoints call
        accessPoints.collection = new VxSdk::IVxAccessPoint * [accessPoints.collectionSize];
        result = _system->GetAccessPoints(accessPoints);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < accessPoints.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AccessPoint(accessPoints.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] accessPoints.collection;
    }
    return mlist;
}

List<VxSdkNet::AlarmInput^>^ VxSdkNet::VXSystem::GetAlarmInputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed alarm input objects
    List<AlarmInput^>^ mlist = gcnew List<AlarmInput^>();
    // Create a collection of unmanaged alarm input objects
    VxSdk::VxCollection<VxSdk::IVxAlarmInput**> alarmInputs;

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
        alarmInputs.filterSize = filters->Count;
        alarmInputs.filters = collFilters;
    }

    // Make the GetAlarmInputs call, which will return with the total count of alarm inputs, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetAlarmInputs(alarmInputs);
    // Unless there are no alarm inputs on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetAlarmInputs call
        alarmInputs.collection = new VxSdk::IVxAlarmInput*[alarmInputs.collectionSize];
        result = _system->GetAlarmInputs(alarmInputs);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < alarmInputs.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AlarmInput(alarmInputs.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] alarmInputs.collection;
    }
    return mlist;
}

List<VxSdkNet::AnalyticSession^>^ VxSdkNet::VXSystem::GetAnalyticSessions(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed analytic sessions
    List<AnalyticSession^>^ mlist = gcnew List<AnalyticSession^>();
    // Create a collection of unmanaged analytic sessions
    VxSdk::VxCollection<VxSdk::IVxAnalyticSession**> analyticSessions;

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
        analyticSessions.filterSize = filters->Count;
        analyticSessions.filters = collFilters;
    }

    // Make the GetAnalyticSessions call, which will return with the total analytic session count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetAnalyticSessions(analyticSessions);
    // As long as there are analytic sessions for this datasource the result should be VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxAnalyticSession collection
        analyticSessions.collection = new VxSdk::IVxAnalyticSession * [analyticSessions.collectionSize];
        result = _system->GetAnalyticSessions(analyticSessions);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < analyticSessions.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::AnalyticSession(analyticSessions.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] analyticSessions.collection;
    }
    return mlist;
}

List<VxSdkNet::Bookmark^>^ VxSdkNet::VXSystem::GetBookmarks(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed bookmark objects
    List<VxSdkNet::Bookmark^>^ mlist = gcnew List<VxSdkNet::Bookmark^>();
    // Create a collection of unmanaged bookmark objects
    VxSdk::VxCollection<VxSdk::IVxBookmark**> bookmarks;

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
        bookmarks.filterSize = filters->Count;
        bookmarks.filters = collFilters;
    }

    // Make the GetBookmarks call, which will return with the total bookmark count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetBookmarks(bookmarks);
    // The result should be kInsufficientSize if the number of bookmarks on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxBookmark collection
        bookmarks.collection = new VxSdk::IVxBookmark*[bookmarks.collectionSize];
        result = _system->GetBookmarks(bookmarks);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < bookmarks.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Bookmark(bookmarks.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] bookmarks.collection;
    }
    return mlist;
}

List<VxSdkNet::DataObject^>^ VxSdkNet::VXSystem::GetDataObjects(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data objects
    List<VxSdkNet::DataObject^>^ mlist = gcnew List<VxSdkNet::DataObject^>();
    // Create a collection of unmanaged data objects
    VxSdk::VxCollection<VxSdk::IVxDataObject**> dataObjects;
    
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
        dataObjects.filterSize = filters->Count;
        dataObjects.filters = collFilters;
    }

    // Make the GetDataObjects call, which will return with the total data object count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetDataObjects(dataObjects);
    // The result should be kInsufficientSize if the number of data objects on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataObject collection
        dataObjects.collection = new VxSdk::IVxDataObject*[dataObjects.collectionSize];
        result = _system->GetDataObjects(dataObjects);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataObjects.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::DataObject(dataObjects.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataObjects.collection;
    }
    return mlist;
}

Collections::Generic::List<VxSdkNet::DataSource^>^ VxSdkNet::VXSystem::GetDataSources(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data source objects
    List<VxSdkNet::DataSource^>^ mlist = gcnew List<VxSdkNet::DataSource^>();
    // Create a collection of unmanaged data source objects
    VxSdk::VxCollection<VxSdk::IVxDataSource**> dataSources;
    
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
        dataSources.filterSize = filters->Count;
        dataSources.filters = collFilters;
    }

    // Make the GetDataSources call, which will return with the total data source count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetDataSources(dataSources);
    // Unless there are no data sources on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataSource collection
        dataSources.collection = new VxSdk::IVxDataSource*[dataSources.collectionSize];
        result = _system->GetDataSources(dataSources);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataSources.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::DataSource(dataSources.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataSources.collection;
    }
    return mlist;
}

List<VxSdkNet::DataStorage^>^ VxSdkNet::VXSystem::GetDataStorages(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed data storage objects
    List<VxSdkNet::DataStorage^>^ mlist = gcnew List<VxSdkNet::DataStorage^>();
    // Create a collection of unmanaged data storage objects
    VxSdk::VxCollection<VxSdk::IVxDataStorage**> dataStorages;
    
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
        dataStorages.filterSize = filters->Count;
        dataStorages.filters = collFilters;
    }

    // Make the GetDataStorages call, which will return with the total storage count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetDataStorages(dataStorages);
    // The result should be kInsufficientSize if the number of data storages on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDataStorage collection
        dataStorages.collection = new VxSdk::IVxDataStorage*[dataStorages.collectionSize];
        result = _system->GetDataStorages(dataStorages);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < dataStorages.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::DataStorage(dataStorages.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] dataStorages.collection;
    }
    return mlist;
}

List<VxSdkNet::DeviceAssignment^>^ VxSdkNet::VXSystem::GetDeviceAssignments(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed device assignment objects
    List<DeviceAssignment^>^ mlist = gcnew List<DeviceAssignment^>();
    // Create a collection of unmanaged device assignment objects
    VxSdk::VxCollection<VxSdk::IVxDeviceAssignment**> deviceAssignments;
    
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
        deviceAssignments.filterSize = filters->Count;
        deviceAssignments.filters = collFilters;
    }

    // Make the GetDeviceAssignments call, which will return with the total count of device assignments, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetDeviceAssignments(deviceAssignments);
    // Unless there are no device assignments on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetDeviceAssignments call
        deviceAssignments.collection = new VxSdk::IVxDeviceAssignment*[deviceAssignments.collectionSize];
        result = _system->GetDeviceAssignments(deviceAssignments);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < deviceAssignments.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::DeviceAssignment(deviceAssignments.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] deviceAssignments.collection;
    }
    return mlist;
}

Collections::Generic::List<VxSdkNet::Device^>^ VxSdkNet::VXSystem::GetDevices(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed device objects
    List<VxSdkNet::Device^>^ mlist = gcnew List<VxSdkNet::Device^>();
    // Create a collection of unmanaged device objects
    VxSdk::VxCollection<VxSdk::IVxDevice**> devices;
    
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
        devices.filterSize = filters->Count;
        devices.filters = collFilters;
    }

    // Make the GetDevices call, which will return with the total device count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetDevices(devices);
    // Unless there are no devices on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDevice collection
        devices.collection = new VxSdk::IVxDevice*[devices.collectionSize];
        result = _system->GetDevices(devices);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < devices.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Device(devices.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] devices.collection;
    }
    return mlist;
}

Collections::Generic::List<VxSdkNet::ManualRecording^>^ VxSdkNet::VXSystem::GetManualRecordings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed manual recording objects
    List<VxSdkNet::ManualRecording^>^ mlist = gcnew List<VxSdkNet::ManualRecording^>();
    // Create a collection of unmanaged manual recording objects
    VxSdk::VxCollection<VxSdk::IVxManualRecording**> manualRecordings;
    
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
        manualRecordings.filterSize = filters->Count;
        manualRecordings.filters = collFilters;
    }

    // Make the GetManualRecordings call, which will return with the total manual recording count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetManualRecordings(manualRecordings);
    // Unless there are no manual recordings on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxManualRecording collection
        manualRecordings.collection = new VxSdk::IVxManualRecording*[manualRecordings.collectionSize];
        result = _system->GetManualRecordings(manualRecordings);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < manualRecordings.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::ManualRecording(manualRecordings.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] manualRecordings.collection;
    }
    return mlist;
}

Collections::Generic::List<VxSdkNet::Member^>^ VxSdkNet::VXSystem::GetMembers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed member objects
    List<VxSdkNet::Member^>^ mlist = gcnew List<VxSdkNet::Member^>();
    // Create a collection of unmanaged member objects
    VxSdk::VxCollection<VxSdk::IVxMember**> members;

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
        members.filterSize = filters->Count;
        members.filters = collFilters;
    }

    // Make the GetMembers call, which will return with the total member count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetMembers(members);
    // Unless there are no members on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxMember collection
        members.collection = new VxSdk::IVxMember*[members.collectionSize];
        result = _system->GetMembers(members);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < members.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Member(members.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] members.collection;
    }
    return mlist;
}

List<VxSdkNet::Monitor^>^ VxSdkNet::VXSystem::GetMonitors(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed monitor objects
    List<VxSdkNet::Monitor^>^ mlist = gcnew List<VxSdkNet::Monitor^>();
    // Create a collection of unmanaged monitor objects
    VxSdk::VxCollection<VxSdk::IVxMonitor**> monitors;

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
        monitors.filterSize = filters->Count;
        monitors.filters = collFilters;
    }

    // Make the GetExports call, which will return with the total export count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetMonitors(monitors);
    // Unless there are no exports on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxExport collection
        monitors.collection = new VxSdk::IVxMonitor*[monitors.collectionSize];
        result = _system->GetMonitors(monitors);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < monitors.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Monitor(monitors.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] monitors.collection;
    }
    return mlist;
}

List<VxSdkNet::MonitorWall^>^ VxSdkNet::VXSystem::GetMonitorWalls(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed monitor objects
    List<VxSdkNet::MonitorWall^>^ mlist = gcnew List<VxSdkNet::MonitorWall^>();
    // Create a collection of unmanaged monitor objects
    VxSdk::VxCollection<VxSdk::IVxMonitorWall**> monitorWalls;
    
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
        monitorWalls.filterSize = filters->Count;
        monitorWalls.filters = collFilters;
    }

    // Make the GetExports call, which will return with the total export count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetMonitorWalls(monitorWalls);
    // Unless there are no exports on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxExport collection
        monitorWalls.collection = new VxSdk::IVxMonitorWall*[monitorWalls.collectionSize];
        result = _system->GetMonitorWalls(monitorWalls);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < monitorWalls.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::MonitorWall(monitorWalls.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] monitorWalls.collection;
    }
    return mlist;
}

List<VxSdkNet::Drawing^>^ VxSdkNet::VXSystem::GetDrawings(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed drawing objects
    List<VxSdkNet::Drawing^>^ mlist = gcnew List<VxSdkNet::Drawing^>();
    // Create a collection of unmanaged drawing objects
    VxSdk::VxCollection<VxSdk::IVxDrawing**> drawings;
    
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
        drawings.filterSize = filters->Count;
        drawings.filters = collFilters;
    }

    // Make the GetDrawings call, which will return with the total drawing count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetDrawings(drawings);
    // The result should be kInsufficientSize if the number of drawings on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDrawing collection
        drawings.collection = new VxSdk::IVxDrawing*[drawings.collectionSize];
        result = _system->GetDrawings(drawings);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < drawings.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Drawing(drawings.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] drawings.collection;
    }
    return mlist;
}

List<VxSdkNet::Driver^>^ VxSdkNet::VXSystem::GetDrivers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed driver objects
    List<VxSdkNet::Driver^>^ mlist = gcnew List<VxSdkNet::Driver^>();
    // Create a collection of unmanaged driver objects
    VxSdk::VxCollection<VxSdk::IVxDriver**> drivers;
    
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
        drivers.filterSize = filters->Count;
        drivers.filters = collFilters;
    }

    // Make the GetDrivers call, which will return with the total driver count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetDrivers(drivers);
    // The result should be kInsufficientSize if the number of drivers on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxDriver collection
        drivers.collection = new VxSdk::IVxDriver*[drivers.collectionSize];
        result = _system->GetDrivers(drivers);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < drivers.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Driver(drivers.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] drivers.collection;
    }
    return mlist;
}

List<VxSdkNet::Event^>^ VxSdkNet::VXSystem::GetEvents(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed event objects
    List<VxSdkNet::Event^>^ mlist = gcnew List<VxSdkNet::Event^>();
    // Create a collection of unmanaged event objects
    VxSdk::VxCollection<VxSdk::IVxEvent**> events;
    
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
        events.filterSize = filters->Count;
        events.filters = collFilters;
    }

    // Make the GetEvents call, which will return with the total event count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetEvents(events);
    // The result should be kInsufficientSize if the number of events on the system are greater than 0 (always)
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxEvent collection
        events.collection = new VxSdk::IVxEvent*[events.collectionSize];
        result = _system->GetEvents(events);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < events.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Event(events.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] events.collection;
    }
    return mlist;
}

List<VxSdkNet::Export^>^ VxSdkNet::VXSystem::GetExports(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed export objects
    List<VxSdkNet::Export^>^ mlist = gcnew List<VxSdkNet::Export^>();
    // Create a collection of unmanaged export objects
    VxSdk::VxCollection<VxSdk::IVxExport**> exports;
    
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
        exports.filterSize = filters->Count;
        exports.filters = collFilters;
    }

    // Make the GetExports call, which will return with the total export count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetExports(exports);
    // Unless there are no exports on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxExport collection
        exports.collection = new VxSdk::IVxExport*[exports.collectionSize];
        result = _system->GetExports(exports);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < exports.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Export(exports.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] exports.collection;
    }
    return mlist;
}

VxSdkNet::License^ VxSdkNet::VXSystem::GetLicense() {
    // Get the license object
    VxSdk::IVxLicense* license = nullptr;
    VxSdk::VxResult::Value result = _system->GetLicense(license);

    // Return the license if GetLicense was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::License(license);

    return nullptr;
}

List<VxSdkNet::RelayOutput^>^ VxSdkNet::VXSystem::GetRelayOutputs(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed relay output objects
    List<RelayOutput^>^ mlist = gcnew List<RelayOutput^>();
    // Create a collection of unmanaged relay output objects
    VxSdk::VxCollection<VxSdk::IVxRelayOutput**> relayOutputs;
        
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
        relayOutputs.filterSize = filters->Count;
        relayOutputs.filters = collFilters;
    }

    // Make the GetRelayOutputs call, which will return with the total count of relay outputs, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetRelayOutputs(relayOutputs);
    // Unless there are no relay outputs on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetRelayOutputs call
        relayOutputs.collection = new VxSdk::IVxRelayOutput*[relayOutputs.collectionSize];
        result = _system->GetRelayOutputs(relayOutputs);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < relayOutputs.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::RelayOutput(relayOutputs.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] relayOutputs.collection;
    }
    return mlist;
}

List<VxSdkNet::Role^>^ VxSdkNet::VXSystem::GetRoles(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed role objects
    List<VxSdkNet::Role^>^ mlist = gcnew List<VxSdkNet::Role^>();
    // Create a collection of unmanaged role objects
    VxSdk::VxCollection<VxSdk::IVxRole**> roles;
        
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
        roles.filterSize = filters->Count;
        roles.filters = collFilters;
    }

    // Make the GetRoles call, which will return with the total role count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetRoles(roles);
    // The result should be kInsufficientSize if the number of roles on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxRole collection
        roles.collection = new VxSdk::IVxRole*[roles.collectionSize];
        result = _system->GetRoles(roles);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < roles.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Role(roles.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] roles.collection;
    }
    return mlist;
}

System::Collections::Generic::List<VxSdkNet::Rule^>^ VxSdkNet::VXSystem::GetRules(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed rule objects
    List<VxSdkNet::Rule^>^ mlist = gcnew List<VxSdkNet::Rule^>();
    // Create a collection of unmanaged rule objects
    VxSdk::VxCollection<VxSdk::IVxRule**> rules;
        
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
        rules.filterSize = filters->Count;
        rules.filters = collFilters;
    }

    // Make the GetRules call, which will return with the total rule count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetRules(rules);
    // The result should be kInsufficientSize if the number of rules on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxRule collection
        rules.collection = new VxSdk::IVxRule*[rules.collectionSize];
        result = _system->GetRules(rules);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < rules.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Rule(rules.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] rules.collection;
    }
    return mlist;
}

List<VxSdkNet::Schedule^>^ VxSdkNet::VXSystem::GetSchedules(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed schedule objects
    List<VxSdkNet::Schedule^>^ mlist = gcnew List<VxSdkNet::Schedule^>();
    // Create a collection of unmanaged schedule objects
    VxSdk::VxCollection<VxSdk::IVxSchedule**> schedules;
        
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
        schedules.filterSize = filters->Count;
        schedules.filters = collFilters;
    }

    // Make the GetSchedules call, which will return with the total schedule count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetSchedules(schedules);
    // The result should be kInsufficientSize if the number of schedules on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxSchedule collection
        schedules.collection = new VxSdk::IVxSchedule*[schedules.collectionSize];
        result = _system->GetSchedules(schedules);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < schedules.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Schedule(schedules.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] schedules.collection;
    }
    return mlist;
}

List<VxSdkNet::Situation^>^ VxSdkNet::VXSystem::GetSituations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed situation objects
    List<VxSdkNet::Situation^>^ mlist = gcnew List<VxSdkNet::Situation^>();
    // Create a collection of unmanaged situation objects
    VxSdk::VxCollection<VxSdk::IVxSituation**> situations;
        
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
        situations.filterSize = filters->Count;
        situations.filters = collFilters;
    }

    // Make the GetSituations call, which will return with the total situation count, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _system->GetSituations(situations);
    // The result should be kInsufficientSize if the number of situations on the system are greater than 0 (always)
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxSituation collection
        situations.collection = new VxSdk::IVxSituation*[situations.collectionSize];
        result = _system->GetSituations(situations);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < situations.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Situation(situations.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] situations.collection;
    }
    return mlist;
}

List<VxSdkNet::Tag^>^ VxSdkNet::VXSystem::GetTags(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed tag objects
    List<VxSdkNet::Tag^>^ mlist = gcnew List<VxSdkNet::Tag^>();
    // Create a collection of unmanaged tag objects
    VxSdk::VxCollection<VxSdk::IVxTag**> tags;
        
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
        tags.filterSize = filters->Count;
        tags.filters = collFilters;
    }

    // Make the GetTags call, which will return with the total tag count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetTags(tags);
    // The result should be kInsufficientSize if the number of tags on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxTag collection
        tags.collection = new VxSdk::IVxTag*[tags.collectionSize];
        result = _system->GetTags(tags);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < tags.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::Tag(tags.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] tags.collection;
    }
    return mlist;
}

System::Collections::Generic::List< VxSdkNet::TimeTable^>^ VxSdkNet::VXSystem::GetTimeTables(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed time table objects
    List<VxSdkNet::TimeTable^>^ mlist = gcnew List<VxSdkNet::TimeTable^>();
    // Create a collection of unmanaged time table objects
    VxSdk::VxCollection<VxSdk::IVxTimeTable**> timeTables;
        
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
        timeTables.filterSize = filters->Count;
        timeTables.filters = collFilters;
    }

    // Make the GetTimeTables call, which will return with the total time tables count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetTimeTables(timeTables);
    // The result should be kInsufficientSize if the number of time tables on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxTimeTable collection
        timeTables.collection = new VxSdk::IVxTimeTable*[timeTables.collectionSize];
        result = _system->GetTimeTables(timeTables);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < timeTables.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::TimeTable(timeTables.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] timeTables.collection;
    }
    return mlist;
}

List<VxSdkNet::User^>^ VxSdkNet::VXSystem::GetUsers(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters) {
    // Create a list of managed tag objects
    List<VxSdkNet::User^>^ mlist = gcnew List<VxSdkNet::User^>();
    // Create a collection of unmanaged tag objects
    VxSdk::VxCollection<VxSdk::IVxUser**> users;
        
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
        users.filterSize = filters->Count;
        users.filters = collFilters;
    }

    // Make the GetTags call, which will return with the total tag count, this allows the client to allocate memory
    VxSdk::VxResult::Value result = _system->GetUsers(users);
    // The result should be kInsufficientSize if the number of tags on the system are greater than 0
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // Allocate enough space for the IVxTag collection
        users.collection = new VxSdk::IVxUser*[users.collectionSize];
        result = _system->GetUsers(users);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < users.collectionSize; i++) {
                mlist->Add(gcnew VxSdkNet::User(users.collection[i]));
            }
        }
        // Remove the memory we previously allocated to the collection
        delete[] users.collection;
    }
    return mlist;
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::InjectEvent(VxSdkNet::NewEvent^ newEvent) {
    // Create a new VxNewEvent object using the information contained in newEvent
    VxSdk::VxNewEvent vxEvent;
    VxSdk::Utilities::StrCopySafe(vxEvent.generatorDeviceId, Utils::ConvertCSharpString(newEvent->GeneratorDeviceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxEvent.situationType, Utils::ConvertCSharpString(newEvent->SituationType).c_str());
    VxSdk::Utilities::StrCopySafe(vxEvent.sourceDeviceId, Utils::ConvertCSharpString(newEvent->SourceDeviceId).c_str());
    VxSdk::Utilities::StrCopySafe(vxEvent.time, Utils::ConvertCSharpDateTime(newEvent->Time).c_str());
    vxEvent.propertySize = newEvent->Properties->Count;
    if (vxEvent.propertySize > 0) {
        vxEvent.properties =  new VxSdk::VxKvObject[vxEvent.propertySize];
        for (int i = 0; i < vxEvent.propertySize; i++) {
            VxSdk::Utilities::StrCopySafe(vxEvent.properties[i].key, Utils::ConvertCSharpString(newEvent->Properties[i].Key).c_str());
            VxSdk::Utilities::StrCopySafe(vxEvent.properties[i].value, Utils::ConvertCSharpString(newEvent->Properties[i].Value).c_str());
        }
    }

    // Make the call to insert the event into VideoXpert
    VxSdk::VxResult::Value result = _system->InsertEvent(vxEvent);

    delete[] vxEvent.properties;
    vxEvent.properties = nullptr;

    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::Login(String^ username, String^ password) {
    // Enter the VideoXpert login information
    VxSdk::Utilities::StrCopySafe(_loginInfo->username, Utils::ConvertCSharpString(username).c_str());
    VxSdk::Utilities::StrCopySafe(_loginInfo->password, Utils::ConvertCSharpString(password).c_str());
    const int kSslPort = 443;
    _loginInfo->port = _loginInfo->port == 0 ? kSslPort : _loginInfo->port;
    _loginInfo->useSsl = true;

    // Attempt to login to the system
    VxSdk::IVxSystem* system = nullptr;
    VxSdk::VxResult::Value result = VxSdk::VxSystemLogin(*_loginInfo, system);
    if (result == VxSdk::VxResult::kOK || result == VxSdk::VxResult::kSdkLicenseGracePeriodActive) {
        _system = system;
        // Create a new callback delegate
        _callback = gcnew EventCallbackDelegate(&_FireEvent);
        _internalCallback = gcnew InternalEventCallbackDelegate(&_FireInternalEvent);
    }
    else if (system != nullptr) {
        system->Delete();
        system = nullptr;
    }

    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::Login(String^ authToken) {
    VxSdk::Utilities::StrCopySafe(_loginInfo->authToken, Utils::ConvertCSharpString(authToken).c_str());
    const int kSslPort = 443;
    _loginInfo->port = _loginInfo->port == 0 ? kSslPort : _loginInfo->port;
    _loginInfo->useSsl = true;

    VxSdk::IVxSystem* system = nullptr;
    VxSdk::VxResult::Value result = VxSdk::VxSystemLogin(*_loginInfo, system);
    if (result == VxSdk::VxResult::kOK || result == VxSdk::VxResult::kSdkLicenseGracePeriodActive) {
        _system = system;
        // Create a new callback delegate
        _callback = gcnew EventCallbackDelegate(&_FireEvent);
        _internalCallback = gcnew InternalEventCallbackDelegate(&_FireInternalEvent);
    }
    else if (system != nullptr) {
        system->Delete();
        system = nullptr;
    }

    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::Refresh() {
    return (VxSdkNet::Results::Value)_system->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::RemoveMember(Member^ memberItem) {
    // To delete a member simply make a RemoveMember call
    VxSdk::VxResult::Value result = memberItem->_member->RemoveMember();
    // Unless there was an issue removing the member the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::SubscribeToEventsByType(VxSdkNet::VXSystem::EventDelegate^ eventDelegate, List<Situation^>^ situations) {
    VxSdkNet::Results::Value result = SubscribeToEventsByType(eventDelegate, situations, false);
    return result;
}

VxSdkNet::Results::Value VxSdkNet::VXSystem::SubscribeToEventsByType(VxSdkNet::VXSystem::EventDelegate^ eventDelegate, List<Situation^>^ situations, bool userNotification) {
    VxSdk::VxCollection<VxSdk::IVxSituation**> situationCollection;
    situationCollection.collectionSize = situations->Count;
    if (situationCollection.collectionSize > 0) {
        situationCollection.collection = new VxSdk::IVxSituation*[situationCollection.collectionSize];
        // Add the situations to subscribe to
        for (int i = 0; i < situations->Count; i++)
            situationCollection.collection[i] = situations[i]->_situation;
    }

    // Subscribe to the system events using the situation types
    VxSdk::VxResult::Value result = _system->StartNotifications(
        VxSdk::VxEventCallback(Marshal::GetFunctionPointerForDelegate(_callback).ToPointer()), situationCollection, userNotification);

    // Add a new subscription to the EventDelegate
    _systemEvent += eventDelegate;

    delete[] situationCollection.collection;

    // Unless there was an issue subscribing the result should be VxSdk::VxResult::kOK
    return VxSdkNet::Results::Value(result);
}

bool VxSdkNet::VXSystem::ValidateMember(System::String^ host, int port, System::String^ username, System::String^ password) {
    bool result;
    _system->ValidateMember(result, Utils::ConvertCSharpString(host).c_str(), port, Utils::ConvertCSharpString(username).c_str(), Utils::ConvertCSharpString(password).c_str());
    return result;
}

void VxSdkNet::VXSystem::_FireEvent(VxSdk::IVxEvent* vxEvent) {
    // Fire the notification if there is a subscription to the system events
    if (_systemEvent != nullptr)
        return _systemEvent(gcnew Event(vxEvent));
}

void VxSdkNet::VXSystem::_FireInternalEvent(VxSdk::VxInternalEvent* vxInternalEvent) {
    // Fire the notification if there is a subscription to the internal events
    if (_sdkEvent != nullptr)
        return _sdkEvent(gcnew VxSdkNet::InternalEvent(vxInternalEvent));
}

VxSdkNet::Configuration::Auth^ VxSdkNet::VXSystem::_GetAuthConfig() {
    // Get the auth configuration
    VxSdk::IVxConfiguration::Auth* authConfig = nullptr;
    VxSdk::VxResult::Value result = _system->GetAuthenticationConfiguration(authConfig);

    // Return the auth configuration if GetAuthenticationConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Auth(authConfig);
    }
    else if (authConfig != nullptr) {
        authConfig->Delete();
        authConfig = nullptr;
    }

    return nullptr;
}

VxSdkNet::Configuration::Bookmark^ VxSdkNet::VXSystem::_GetBookmarkConfig() {
    // Get the bookmark configuration
    VxSdk::IVxConfiguration::Bookmark* bookmarkConfig = nullptr;
    VxSdk::VxResult::Value result = _system->GetBookmarkConfiguration(bookmarkConfig);

    // Return the bookmark configuration if GetBookmarkConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Bookmark(bookmarkConfig);
    }
    else if (bookmarkConfig != nullptr) {
        bookmarkConfig->Delete();
        bookmarkConfig = nullptr;
    }

    return nullptr;
}

VxSdkNet::Configuration::Cluster^ VxSdkNet::VXSystem::_GetClusterConfig() {
    // Get the cluster configuration
    VxSdk::IVxConfiguration::Cluster* cluster = nullptr;
    VxSdk::VxResult::Value result = _system->GetClusterConfiguration(cluster);

    // Return the cluster configuration if GetClusterConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Cluster(cluster);
    }
    else if (cluster != nullptr) {
        cluster->Delete();
        cluster = nullptr;
    }

    return nullptr;
}

VxSdkNet::User^ VxSdkNet::VXSystem::_GetCurrentUser() {
    // Get the user object
    VxSdk::IVxUser* user = nullptr;
    VxSdk::VxResult::Value result = _system->GetCurrentUser(user);

    // Return the user if GetCurrentUser was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew VxSdkNet::User(user);
    }
    else if (user != nullptr) {
        user->Delete();
        user = nullptr;
    }

    return nullptr;
}

VxSdkNet::Device^ VxSdkNet::VXSystem::_GetHostDevice() {
    // Get the device which hosts this system
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _system->GetHostDevice(device);

    // Return the device if GetHostDevice was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Device(device);
    }
    else if (device != nullptr) {
        device->Delete();
        device = nullptr;
    }

    return nullptr;
}

VxSdkNet::Configuration::Ldap^ VxSdkNet::VXSystem::_GetLdapConfig() {
    // Get the LDAP configuration
    VxSdk::IVxConfiguration::Ldap* ldapConfig = nullptr;
    VxSdk::VxResult::Value result = _system->GetLdapConfiguration(ldapConfig);

    // Return the LDAP configuration if GetLdapConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Ldap(ldapConfig);
    }
    else if (ldapConfig != nullptr) {
        ldapConfig->Delete();
        ldapConfig = nullptr;
    }

    return nullptr;
}

VxSdkNet::Configuration::Server^ VxSdkNet::VXSystem::_GetServerConfig() {
    // Get the  server configuration
    VxSdk::IVxConfiguration::Server* serverConfig = nullptr;
    VxSdk::VxResult::Value result = _system->GetServerConfiguration(serverConfig);

    // Return the  server configuration if GetServerConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Server(serverConfig);
    }
    else if (serverConfig != nullptr) {
        serverConfig->Delete();
        serverConfig = nullptr;
    }

    return nullptr;
}

VxSdkNet::Configuration::Smtp^ VxSdkNet::VXSystem::_GetSmtpConfig() {
    // Get the SMTP configuration
    VxSdk::IVxConfiguration::Smtp* smtpConfig = nullptr;
    VxSdk::VxResult::Value result = _system->GetSmtpConfiguration(smtpConfig);

    // Return the SMTP configuration if GetSmtpConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Smtp(smtpConfig);
    }
    else if (smtpConfig != nullptr) {
        smtpConfig->Delete();
        smtpConfig = nullptr;
    }

    return nullptr;
}

VxSdkNet::Configuration::Snmp^ VxSdkNet::VXSystem::_GetSnmpConfig() {
    // Get the SNMP configuration
    VxSdk::IVxConfiguration::Snmp* snmpConfig = nullptr;
    VxSdk::VxResult::Value result = _system->GetSnmpConfiguration(snmpConfig);

    // Return the SNMP configuration if GetSnmpConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Snmp(snmpConfig);
    }
    else if (snmpConfig != nullptr) {
        snmpConfig->Delete();
        snmpConfig = nullptr;
    }

    return nullptr;
}

VxSdkNet::Configuration::Twilio^ VxSdkNet::VXSystem::_GetTwilioConfig() {
    // Get the Twilio configuration
    VxSdk::IVxConfiguration::Twilio* twilioConfig = nullptr;
    VxSdk::VxResult::Value result = _system->GetTwilioConfiguration(twilioConfig);

    // Return the Twilio configuration if GetTwilioConfiguration was successful
    if (result == VxSdk::VxResult::kOK) {
        return gcnew Configuration::Twilio(twilioConfig);
    }
    else if (twilioConfig != nullptr) {
        twilioConfig->Delete();
        twilioConfig = nullptr;
    }

    return nullptr;
}

void VxSdkNet::VXSystem::SystemEvent::add(EventDelegate ^eventDelegate) {
    // Subscribe to the system events
    _system->StartNotifications(VxSdk::VxEventCallback(Marshal::GetFunctionPointerForDelegate(_callback).ToPointer()));
    // Add a new subscription to the EventDelegate
    _systemEvent += eventDelegate;
};

void VxSdkNet::VXSystem::SystemEvent::remove(EventDelegate ^eventDelegate) {
    // Unsubscribe to the system events
    _system->StopNotifications();
    // Remove the EventDelegate subscription
    _systemEvent -= eventDelegate;
};

void VxSdkNet::VXSystem::InternalEvent::add(InternalEventDelegate ^sdkEventDelegate) {
    // Subscribe to the internal events
    _system->StartInternalNotifications(VxSdk::VxInternalEventCallback(Marshal::GetFunctionPointerForDelegate(_internalCallback).ToPointer()));
    // Add a new subscription to the InternalEventDelegate
    _sdkEvent += sdkEventDelegate;
};

void VxSdkNet::VXSystem::InternalEvent::remove(InternalEventDelegate ^sdkEventDelegate) {
    // Unsubscribe to the internal events
    _system->StopInternalNotifications();
    // Remove the InternalEventDelegate subscription
    _sdkEvent -= sdkEventDelegate;
};
