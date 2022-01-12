// Declares the MediaControl class.
#ifndef MediaControl_h__
#define MediaControl_h__

#include "MediaEvent.h"
#include "StreamEvent.h"
#include "PelcoDataEvent.h"
#include "Utils.h"
#include "DataSource.h"

namespace VxSdkNet {

    /// <summary>
    /// The MediaControl class creates a controller object that provides the ability to
    /// create and control video streams.
    /// </summary>
    public ref class MediaControl {
    public:

        /// <summary>
        /// Values that represent the different playback modes.
        /// </summary>
        enum class Modes {
            /// <summary>The stream is stopped.</summary>
            Stopped,

            /// <summary>The stream is playing live video.</summary>
            Live,

            /// <summary>The stream is playing recorded video.</summary>
            Playback
        };

        /// <summary>
        /// Values that represent the aspect ratio of the video stream.
        /// </summary>
        enum class AspectRatios {
            /// <summary>16:9 aspect ratio (Default).</summary>
            k16x9,

            /// <summary>4:3 aspect ratio.</summary>
            k4x3,

            /// <summary>1:1 aspect ratio.</summary>
            k1x1,

            /// <summary>3:2 aspect ratio.</summary>
            k3x2,

            /// <summary>5:49 aspect ratio.</summary>
            k5x4
        };

        /// <summary>
        /// Values that represent the different transport modes for an RTSP stream (ignored for MJPEG Pull).
        /// </summary>
        enum class RTSPNetworkTransports {
            /// <summary>Stream will be sent with UDP (default). Will be used with multicast transmissions.</summary>
            UDP,

            /// <summary>Stream will be sent with TCP network protocol if possible.</summary>
            RTPOverRTSP
        };

        /// <summary>
        /// Options for data on the video being played
        /// </summary>
        enum class VideoOverlayDataPositions {
            TopLeft,
            TopCenter,
            TopRight,
            MiddleLeft,
            MiddleCenter,
            MiddleRight,
            BottomLeft,
            BottomCenter,
            BottomRight
        };

        /// <summary>
        /// The native event callback delegate.
        /// </summary>
        /// <param name="timeEvent">The time event sent from the stream.</param>
        [System::Runtime::InteropServices::UnmanagedFunctionPointer(
            System::Runtime::InteropServices::CallingConvention::Cdecl)]
        delegate void TimestampCallbackDelegate(MediaController::TimestampEvent* timeEvent);

        /// <summary>
        /// The managed event delegate.
        /// </summary>
        /// <param name="mediaEvent">The media event sent from the stream as a managed type.</param>
        delegate void TimestampEventDelegate(MediaEvent^ mediaEvent);

        /// <summary>
        /// The native event callback delegate.
        /// </summary>
        /// <param name="streamEvent">The stream event sent from the stream.</param>
        [System::Runtime::InteropServices::UnmanagedFunctionPointer(
            System::Runtime::InteropServices::CallingConvention::Cdecl)]
        delegate void StreamCallbackDelegate(MediaController::StreamEvent* streamEvent);

        /// <summary>
        /// The managed event delegate.
        /// </summary>
        /// <param name="streamEvent">The stream event sent from the stream as a managed type.</param>
        delegate void StreamEventDelegate(StreamingEvent^ streamEvent);

        /// <summary>
        /// The native event callback delegate.
        /// </summary>
        /// <param name="pelcoDataEvent">The Pelco data event sent from the stream.</param>
        [System::Runtime::InteropServices::UnmanagedFunctionPointer(
            System::Runtime::InteropServices::CallingConvention::Cdecl)]
        delegate void PelcoDataCallbackDelegate(MediaController::PelcoDataEvent* pelcoDataEvent);

        /// <summary>
        /// The managed event delegate.
        /// </summary>
        /// <param name="pelcoDataManagedEvent">The Pelco data event sent from the stream as a managed type.</param>
        delegate void PelcoDataEventDelegate(PelcoDataManagedEvent^ pelcoDataManagedEvent);

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="videoSource">The data source to use to create the video stream.</param>
        /// <param name="videoInterface">The data interface to use to create the video stream.</param>
        /// <param name="audioSource">The data source to use to create the audio stream.</param>
        /// <param name="audioInterface">The data interface to use to create the audio stream.</param>
        MediaControl(DataSource^ videoSource, DataInterface^ videoInterface, DataSource^ audioSource, DataInterface^ audioInterface);

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="rtspVideoEndpoint">The RTSP endpoint of the video stream.</param>
        /// <param name="rtspAudioEndpoint">The RTSP endpoint of the audio stream.</param>
        MediaControl(System::String^ rtspVideoEndpoint, System::String^ rtspAudioEndpoint);

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="rtspVideoEndpoint">The RTSP endpoint of the video stream.</param>
        /// <param name="rtspAudioEndpoint">The RTSP endpoint of the audio stream.</param>
        /// <param name="username">The username for RTSP authentication.</param>
        /// <param name="password">The password for RTSP authentication.</param>
        MediaControl(System::String^ rtspVideoEndpoint, System::String^ rtspAudioEndpoint, System::String^ username, System::String^ password);

        /// <summary>
        /// Virtual destructor.
        /// </summary>
        virtual ~MediaControl() {
            this->!MediaControl();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !MediaControl();

        /// <summary>
        /// Call GoToLive on the stream.
        /// </summary>
        void GoToLive();

        /// <summary>
        /// Call Pause on the stream.
        /// </summary>
        void Pause();

        /// <summary>
        /// Call Play on the stream.
        /// </summary>
        /// <param name="speed">The playback speed.  Negative values can be used for reverse playback.</param>
        bool Play(float speed);

        /// <summary>
        /// Call Play on the stream.
        /// </summary>
        /// <param name="speed">The playback speed.  Negative values can be used for reverse playback.</param>
        /// <param name="networkTransport">Network transport to use for video stream. </param>
        bool Play(float speed, RTSPNetworkTransports networkTransport);

        /// <summary>
        /// Starts recording the current video stream to a local file.
        /// </summary>
        /// <param name="filePath">The full path to save the recorded video to.</param>
        /// <param name="fileName">The file name to use for the recorded video file.</param>
        /// <returns><c>true</c> if the recording was started successfully, otherwise <c>false</c>.</returns>
        bool StartLocalRecording(System::String^ filePath, System::String^ fileName);

        /// <summary>
        /// Starts recording the current video stream to a local file.
        /// </summary>
        /// <param name="filePath">The full path to save the recorded video to.</param>
        /// <param name="fileName">The file name to use for the recorded video file.</param>
        /// <param name="includeOverlays"><c>true</c> to include the overlays currently displayed on the stream
        /// in the recorded file, otherwise <c>false</c>.</param>
        /// <returns><c>true</c> if the recording was started successfully, otherwise <c>false</c>.</returns>
        bool StartLocalRecording(System::String^ filePath, System::String^ fileName, bool includeOverlays);

        /// <summary>
        /// Stops the current local recording in progress, if any.
        /// </summary>
        void StopLocalRecording();

        /// <summary>
        /// Takes a snapshot from the current video stream and stores it to the filename
        ///    provided
        /// </summary>
        /// <param name="filePath">The full path to save the snapshot to.</param>
        /// <param name="fileName">The file name to use for the snapshot file.</param>
        /// <returns><c>true</c> if the file stored correctly, else <c>false</c>.</returns>
        bool SnapShot(System::String^ filePath, System::String^ fileName);

        /// <summary>
        /// Call Play on the stream with the supplied start time, resulting in a playback stream.
        /// </summary>
        /// <param name="time">The start time for playback.</param>
        /// <param name="speed">The playback speed.  Negative values can be used for reverse playback.</param>
        bool Seek(System::DateTime time, float speed);

        /// <summary>
        /// Call Play on the stream with the supplied start time, resulting in a playback stream.
        /// </summary>
        /// <param name="time">The start time for playback.</param>
        /// <param name="speed">The playback speed.  Negative values can be used for reverse playback.</param>
        /// <param name="networkTransport">Network transport to use for video stream. </param>
        bool Seek(System::DateTime time, float speed, RTSPNetworkTransports networkTransport);

        /// <summary>
        /// Set the stream to a new data source.
        /// </summary>
        /// <param name="videoDataSource">The data source to use to create the video stream.</param>
        /// <param name="videoDataInterface">The data interface to use to create the video stream.</param>
        /// <param name="audioDataSource">The data source to use to create the audio stream.</param>
        /// <param name="audioDataInterface">The data interface to use to create the audio stream.</param>
        void SetDataSource(DataSource^ videoDataSource, DataInterface^ videoDataInterface, DataSource^ audioDataSource, DataInterface^ audioDataInterface);

        /// <summary>
        /// Set the stream to a new data source.
        /// </summary>
        /// <param name="rtspVideoEndpoint">The RTSP endpoint of the video stream.</param>
        /// <param name="rtspAudioEndpoint">The RTSP endpoint of the audio stream.</param>
        void SetDataSource(System::String^ rtspVideoEndpoint, System::String^ rtspAudioEndpoint);

        /// <summary>
        /// Set the display window using the given window handle.
        /// </summary>
        /// <param name="windowHandle">An <c>IntPtr</c> to the window handle.</param>
        void SetVideoWindow(System::IntPtr windowHandle);

        /// <summary>
        /// Call TearDown on the stream.
        /// </summary>
        void Stop();

        /// <summary>
        /// Get the status of the pipeline.
        /// </summary>
        /// <returns>True if pipeline is active, otherwise false.</returns>
        property bool IsPipelineActive {
            bool get() { return _control->IsPipelineActive(); }
        }

        /// <summary>
        /// Gets the current playback mode.
        /// </summary>
        /// <value>The current stream mode.</value>
        property Modes Mode {
            Modes get() { return (Modes)_control->GetMode(); }
        }

        /// <summary>
        /// Gets or sets the current aspect ratio.
        /// </summary>
        /// <value>The aspect ratio.</value>
        property AspectRatios AspectRatio {
            AspectRatios get() { return (AspectRatios)_control->GetAspectRatio(); }
            void set(AspectRatios value) { _control->SetAspectRatio((MediaController::IStream::AspectRatios)value); }
        }

        /// <summary>
        /// Gets or sets whether the rendered video should stretch to fit its display window.
        /// </summary>
        /// <value>True if the rendered video should stretch to fit its display window, otherwise false.</value>
        property bool StretchToFit {
            bool get() { return _control->GetStretchToFit(); }
            void set(bool value) { _control->SetStretchToFit(value); }
        }

        /// <summary>
        /// TimestampEvent is raised whenever a new timestamp is received from the stream.
        /// </summary>
        event TimestampEventDelegate ^ TimestampEvent {
            void add(TimestampEventDelegate ^eventDelegate);
            void remove(TimestampEventDelegate ^eventDelegate);
        }

        /// <summary>
        /// StreamEvent is raised whenever a new event is received from the stream.
        /// </summary>
        event StreamEventDelegate ^ StreamEvent {
            void add(StreamEventDelegate ^eventDelegate);
            void remove(StreamEventDelegate ^eventDelegate);
        }

        /// <summary>
        /// PelcoDataEvent is raised whenever a new event is received from the stream.
        /// </summary>
        event PelcoDataEventDelegate ^ PelcoDataEvent {
            void add(PelcoDataEventDelegate ^eventDelegate);
            void remove(PelcoDataEventDelegate ^eventDelegate);
        }

        bool AddVideoOverlayData(System::String^ overlayData, VideoOverlayDataPositions position, bool incudeDateTime);

    internal:
        MediaController::IController* _control;
        void _FireTimestampEvent(MediaController::TimestampEvent* timeEvent);
        TimestampCallbackDelegate ^ _timestampCallback;
        TimestampEventDelegate ^ _timestampEvent;
        void _FireStreamEvent(MediaController::StreamEvent* streamEvent);
        StreamCallbackDelegate ^ _streamCallback;
        StreamEventDelegate ^ _streamEvent;
        PelcoDataCallbackDelegate ^_pelcoDataCallback;
        PelcoDataEventDelegate ^_pelcoDataEvent;
        void _FirePelcoDataEvent(MediaController::PelcoDataEvent* event);
    };
}
#endif // MediaControl_h__
