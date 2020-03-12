// Declares the export stream clip class.
#ifndef ExportStreamClip_h__
#define ExportStreamClip_h__

#include "DataInterface.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The ExportStreamClip class represents streaming access to a single clip within an export.
    /// </summary>
    public ref class ExportStreamClip {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxExportStreamClip">The vx export stream clip.</param>
        ExportStreamClip(VxSdk::VxExportStreamClip* vxExportStreamClip) {
            AudioDataSourceId = Utils::ConvertCppString(vxExportStreamClip->audioDataSourceId);
            AudioUrl = Utils::ConvertCppString(vxExportStreamClip->audioUrl);
            EndTime = Utils::ConvertCppDateTime(vxExportStreamClip->endTime);
            RenderType = (DataInterface::RenderTypes)vxExportStreamClip->renderType;
            StartTime = Utils::ConvertCppDateTime(vxExportStreamClip->startTime);
            VideoDataSourceId = Utils::ConvertCppString(vxExportStreamClip->videoDataSourceId);
            VideoUrl = Utils::ConvertCppString(vxExportStreamClip->videoUrl);
        }

        /// <summary>
        /// Gets or sets the unique identifier of the audio data source that the exported clip came from.
        /// </summary>
        /// <value>The unique identifier of the audio data source.</value>
        property System::String^ AudioDataSourceId;

        /// <summary>
        /// Gets or sets the RTSP URL for streaming the audio data of the export.
        /// </summary>
        /// <value>The audio RTSP URL.</value>
        property System::String^ AudioUrl;

        /// <summary>
        /// Gets or sets the time at which the export media ends.
        /// </summary>
        /// <value>The end time.</value>
        property System::DateTime EndTime;

        /// <summary>
        /// Gets or sets the type of rendering required for the media data delivered by this interface. Clients
        /// can utilize this to create the correct rendering pipeline. 
        /// </summary>
        /// <value>The rendering type.</value>
        property DataInterface::RenderTypes RenderType;

        /// <summary>
        /// Gets or sets the time at which the export media begins.
        /// </summary>
        /// <value>The start time.</value>
        property System::DateTime StartTime;

        /// <summary>
        /// Gets or sets the unique identifier of the video data source that the exported clip came from.
        /// </summary>
        /// <value>The unique identifier of the video data source.</value>
        property System::String^ VideoDataSourceId;

        /// <summary>
        /// Gets or sets the RTSP URL for streaming the video data of the export.
        /// </summary>
        /// <value>The video RTSP URL.</value>
        property System::String^ VideoUrl;
    };
}
#endif // ExportStreamClip_h__
