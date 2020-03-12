// Declares the new analytic session class.
#ifndef NewAnalyticSession_h__
#define NewAnalyticSession_h__

namespace VxSdkNet {

    /// <summary>
    /// The NewAnalyticSession class represents a request for the creation of a new analytic session.
    /// </summary>
    public ref class NewAnalyticSession {
    public:

        /// <summary>
        /// Gets or sets the unique identifier specifying which data encoding to use as a source. This value can be used instead
        /// of <see cref="Source"/> to determine which stream to use.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ DataEncodingId;

        /// <summary>
        /// Gets or sets the unique identifier of the video data source for this analytic session. The <see cref="Source"/> should
        /// be pointing to an RTSP stream on this data source.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ DataSourceId;

        /// <summary>
        /// Gets or sets the unique identifier of the Device hosting this analytic session. The device must be of
        /// type <c>Device::Types::AnalyticServer</c>.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ DeviceId;

        /// <summary>
        /// Gets or sets the unique identifier of the analytic session. The server will generate this value if not supplied.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id;

        /// <summary>
        /// Gets or sets the RTSP URI to use as the source for the analytic session. This value can be used instead
        /// of <see cref="DataEncodingId"/> to determine which stream to use. This value takes priority over
        /// the <see cref="DataEncodingId"/> if both values are provided. Note: This field is required when sending
        /// to a <c>Device::Types::AnalyticServer</c>.
        /// </summary>
        /// <value>The source RTSP URI.</value>
        property System::String^ Source;
    };
}
#endif // NewAnalyticSession_h__
