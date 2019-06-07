/// <summary>
/// Implements the MediaControl class.
/// </summary>
#include "MediaControl.h"

using namespace System::Runtime::InteropServices;

VxSdkNet::MediaControl::MediaControl(DataSource^ videoSource, DataInterface^ videoInterface, DataSource^ audioSource, DataInterface^ audioInterface) {
    // Create a new MediaRequest object
    MediaController::MediaRequest request;
    if (videoSource != nullptr) {
        request.dataSource = videoSource->_dataSource;
        request.dataInterface = *videoInterface->_dataInterface;
    }
    
    if (audioSource != nullptr) {
        request.audioDataSource = audioSource->_dataSource;
        request.audioDataInterface = *audioInterface->_dataInterface;
    }

    // Get the MediaController which allows the client to control streams
    MediaController::IController* control = nullptr;
    MediaController::GetController(&request, &control);

    // Set the callback for timestamp events
    _timestampCallback = gcnew TimestampCallbackDelegate(this, &VxSdkNet::MediaControl::_FireTimestampEvent);
    control->AddObserver(MediaController::TimestampEventCallback(Marshal::GetFunctionPointerForDelegate(_timestampCallback).ToPointer()));

    // Set the callback for stream events
    _streamCallback = gcnew StreamCallbackDelegate(this, &VxSdkNet::MediaControl::_FireStreamEvent);
    control->AddStreamObserver(MediaController::StreamEventCallback(Marshal::GetFunctionPointerForDelegate(_streamCallback).ToPointer()));

     // Set the callback for PelcoData events
     _pelcoDataCallback = gcnew PelcoDataCallbackDelegate(this, &VxSdkNet::MediaControl::_FirePelcoDataEvent);
     control->AddPelcoDataObserver(MediaController::PelcoDataEventCallback(Marshal::GetFunctionPointerForDelegate(_pelcoDataCallback).ToPointer()));

    _control = control;
    _currentdataSource = videoSource;
}

VxSdkNet::MediaControl::!MediaControl() {
    // Clear all subscriptions to the timestamp events
    if (_control != nullptr) {
        _control->ClearObservers();
        delete _control;
        _control = nullptr;
    }
}

void VxSdkNet::MediaControl::GoToLive() {
    _control->GoToLive();
}

void VxSdkNet::MediaControl::Pause() {
    _control->Pause();
}

bool VxSdkNet::MediaControl::Play(float speed) {
    return _control->Play(speed);
}

bool VxSdkNet::MediaControl::StartLocalRecording(System::String^ filePath, System::String^ fileName) {
    return _control->StartLocalRecording(Utils::ConvertSysStringNonConst(filePath), Utils::ConvertSysStringNonConst(fileName));
}

void VxSdkNet::MediaControl::StopLocalRecording() {
    _control->StopLocalRecording();
}

bool VxSdkNet::MediaControl::SnapShot(System::String^ filePath, System::String^ fileName) {
    return _control->SnapShot(Utils::ConvertSysStringNonConst(filePath), Utils::ConvertSysStringNonConst(fileName));
}

bool VxSdkNet::MediaControl::Seek(System::DateTime time, float speed) {
    // Convert the seek time from a DateTime format to unix time format
    System::TimeSpan ts = (time - System::DateTime(1970, 1, 1, 0, 0, 0));
    unsigned int seekTime = safe_cast<unsigned int>(ts.TotalSeconds);

    return _control->Play(speed, seekTime);
}

void VxSdkNet::MediaControl::SetDataSource(DataSource^ videoSource, DataInterface^ videoInterface, DataSource^ audioSource, DataInterface^ audioInterface) {
    // Create a new MediaRequest object
    MediaController::MediaRequest request;
    if (videoSource != nullptr) {
        request.dataSource = videoSource->_dataSource;
        request.dataInterface = *videoInterface->_dataInterface;
    }

    if (audioSource != nullptr) {
        request.audioDataSource = audioSource->_dataSource;
        request.audioDataInterface = *audioInterface->_dataInterface;
    }

    // Update the stream settings for the MediaController using the MediaRequest
    _control->NewRequest(request);
    _currentdataSource = videoSource;
}

void VxSdkNet::MediaControl::SetVideoWindow(System::IntPtr windowHandle) {
    // Set the display for the MediaController using windowHandle
    HWND VideoWindow = static_cast<HWND>(windowHandle.ToPointer());
    _control->SetWindow(VideoWindow);
}

void VxSdkNet::MediaControl::Stop() {
    _control->Stop();
}

void VxSdkNet::MediaControl::TimestampEvent::add(TimestampEventDelegate ^eventDelegate) {
    // Add a new subscription to the TimestampEventDelegate
    _timestampEvent += eventDelegate;
};

void VxSdkNet::MediaControl::TimestampEvent::remove(TimestampEventDelegate ^eventDelegate) {
    // Remove the TimestampEventDelegate subscription
    _timestampEvent -= eventDelegate;
};

void VxSdkNet::MediaControl::_FireTimestampEvent(MediaController::TimestampEvent* timeEvent) {
    // Fire the notification if there is a subscription to the timestamp events
    if (_timestampEvent != nullptr)
        return _timestampEvent(gcnew MediaEvent(timeEvent));
}

void VxSdkNet::MediaControl::StreamEvent::add(StreamEventDelegate ^eventDelegate) {
    // Add a new subscription to the TimestampEventDelegate
    _streamEvent += eventDelegate;
};

void VxSdkNet::MediaControl::StreamEvent::remove(StreamEventDelegate ^eventDelegate) {
    // Remove the TimestampEventDelegate subscription
    _streamEvent -= eventDelegate;
};

void VxSdkNet::MediaControl::_FireStreamEvent(MediaController::StreamEvent* streamEvent) {
    // Fire the notification if there is a subscription to the stream events
    if (_streamEvent != nullptr)
        return _streamEvent(gcnew StreamingEvent(streamEvent));
}

void VxSdkNet::MediaControl::PelcoDataEvent::add(PelcoDataEventDelegate ^eventDelegate) {
    // Add a new subscription to the PelcoDataEventDelegate
    _pelcoDataEvent += eventDelegate;
};

void VxSdkNet::MediaControl::PelcoDataEvent::remove(PelcoDataEventDelegate ^eventDelegate) {
    // Remove the PelcoDataEventDelegate subscription
    _pelcoDataEvent -= eventDelegate;
};

void VxSdkNet::MediaControl::_FirePelcoDataEvent(MediaController::PelcoDataEvent* event) {
    // Fire the notification if there is a subscription to the Pelco data events
    if (_pelcoDataEvent != nullptr)
        return _pelcoDataEvent(gcnew PelcoDataManagedEvent(event));
}