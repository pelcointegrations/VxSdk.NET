// Declares the analytic session class.
#ifndef AnalyticSession_h__
#define AnalyticSession_h__

#include "VxSdk.h"
#include "Device.h"
#include "Utils.h"

namespace VxSdkNet {
    ref class AnalyticConfig;

    /// <summary>
    /// The AnalyticSession class represents an analytic session for a single video data source on an analytic server.
    /// </summary>
    public ref class AnalyticSession {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxAnalyticSession">The vx analytic session.</param>
        AnalyticSession(VxSdk::IVxAnalyticSession* vxAnalyticSession);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~AnalyticSession() {
            this->!AnalyticSession();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !AnalyticSession();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the analytic configuration for this session.
        /// </summary>
        /// <value>The analytic configuration.</value>
        property VxSdkNet::AnalyticConfig^ AnalyticConfig {
        public:
            VxSdkNet::AnalyticConfig^ get() { return _GetAnalyticConfig(); }
        }

        /// <summary>
        /// Gets or sets the unique identifier specifying which data encoding to use as a source. This value
        /// can be used instead of <see cref="Source"/> to determine which stream to use.
        /// </summary>
        /// <value>The data encoding unique identifier.</value>
        property System::String^ DataEncodingId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_analyticSession->dataEncodingId); }
            void set(System::String^ value) {
                char dataEncodingId[64];
                VxSdk::Utilities::StrCopySafe(dataEncodingId, Utils::ConvertCSharpString(value).c_str());
                _analyticSession->SetDataEncodingId(dataEncodingId);
            }
        }

        /// <summary>
        /// Gets the associated video data source.
        /// </summary>
        /// <value>The associated video data source.</value>
        property VxSdkNet::DataSource^ DataSource {
        public:
            VxSdkNet::DataSource^ get() { return _GetDataSource(); }
        }

        /// <summary>
        /// Gets the device that hosts this analytic session.
        /// </summary>
        /// <value>The host device.</value>
        property Device^ HostDevice {
        public:
            Device^ get() { return _GetHostDevice(); }
        }

        /// <summary>
        /// Gets the unique analytic session identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_analyticSession->id); }
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
        /// Gets or sets the RTSP URI to use as the source for the analytic session.
        /// </summary>
        /// <value>The RTSP URI.</value>
        property System::String^ Source {
        public:
            System::String^ get() { return Utils::ConvertCppString(_analyticSession->source); }
            void set(System::String^ value) {
                char source[1024];
                VxSdk::Utilities::StrCopySafe(source, Utils::ConvertCSharpString(value).c_str());
                _analyticSession->SetSource(source);
            }
        }

    internal:
        VxSdk::IVxAnalyticSession* _analyticSession;
        VxSdkNet::AnalyticConfig^ _GetAnalyticConfig();
        VxSdkNet::DataSource^ _GetDataSource();
        VxSdkNet::Device^ _GetHostDevice();
        VxSdkNet::ResourceLimits^ _GetLimits();
    };
}
#endif // AnalyticSession_h__
