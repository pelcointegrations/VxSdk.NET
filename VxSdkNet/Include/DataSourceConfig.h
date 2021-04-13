// Declares the data source config class.
#ifndef DataSourceConfig_h__
#define DataSourceConfig_h__

#include "Configuration.h"
#include "DataInterface.h"
#include "VxSdk.h"
#include "Utils.h"
#include "Resolution.h"
#include "ResourceLimits.h"
#include "VideoEncodingOption.h"

namespace VxSdkNet {
    /// <summary>
    /// The DataSourceConfig class represents the configuration of a data source.
    /// </summary>
    public ref class DataSourceConfig {
    public:
        /// <summary>
        /// Values that represent PTZ control protocols used by encoders to control analog PTZ cameras.
        /// </summary>
        enum class PtzControlProtocol {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>Coaxitron protocol.</summary>
            Coaxitron,
            /// <summary>D protocol.</summary>
            ProtocolD,
            /// <summary>PTZ control disabled.</summary>
            Disabled,
            /// <summary>Extended coaxitron protocol.</summary>
            ExtendedCoaxitron,
            /// <summary>P protocol.</summary>
            ProtocolP
        };

        /// <summary>
        /// Values that represent Smart Compression levels, which offer a trade-off between image quality and compression efficiency.
        /// </summary>
        enum class SmartCompressionLevel {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>Smart Compression is disabled.</summary>
            Disabled,
            /// <summary>Allows a lot of distortion in order to achieve greater compression efficiency gains.</summary>
            High,
            /// <summary>Allows a little distortion in order to achieve small compression efficiency gains.</summary>
            Low,
            /// <summary>Allows some distortion in order to achieve medium compression efficiency gains.</summary>
            Medium
        };

        /// <summary>
        /// The Motion class represents a motion detection configuration.
        /// </summary>
        ref class Motion {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigMotion">The vx motion configuration.</param>
            Motion(VxSdk::IVxDataSourceConfig::Motion* vxConfigMotion);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Motion() {
                this->!Motion();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Motion();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets any limits related to this resource.
            /// </summary>
            /// <value>The limits related to this resource.</value>
            property ResourceLimits^ Limits {
            public:
                ResourceLimits^ get() { return _GetLimits(); }
            }

            /// <summary>
            /// Gets or sets the motion detection mode.
            /// </summary>
            /// <value>The motion detection mode.</value>
            property Configuration::MotionMode Mode {
            public:
                Configuration::MotionMode get() { return (Configuration::MotionMode)_configMotion->mode; }
                void set(Configuration::MotionMode value) { _configMotion->SetMode((VxSdk::VxMotionMode::Value)value); }
            }

            /// <summary>
            /// Gets or sets the amount of change that needs to occur in order to qualify as motion. Higher values increase
            /// sensitivity (less change required to trigger motion).
            /// </summary>
            /// <value>The motion sensitivity level.</value>
            property int Sensitivity {
            public:
                int get() { return _configMotion->sensitivity; }
                void set(int value) { _configMotion->SetSensitivity(value); }
            }

            /// <summary>
            /// Gets or sets the amount of area that needs to occur in order to qualify as motion. Higher values increase
            /// sensitivity (less area required to trigger motion).
            /// </summary>
            /// <value>The motion threshold level.</value>
            property int Threshold {
            public:
                int get() { return _configMotion->threshold; }
                void set(int value) { _configMotion->SetThreshold(value); }
            }

        internal:
            VxSdk::IVxDataSourceConfig::Motion* _configMotion;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The Ptz class represents a configuration of PTZ for a particular video data source.
        /// </summary>
        ref class Ptz {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigPtz">The vx PTZ configuration.</param>
            Ptz(VxSdk::IVxDataSourceConfig::Ptz* vxConfigPtz);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Ptz() {
                this->!Ptz();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Ptz();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets or sets the protocol used by the encoder device to PTZ this channel.
            /// </summary>
            /// <value>The PTZ protocol.</value>
            property PtzControlProtocol Protocol {
            public:
                PtzControlProtocol get() { return (PtzControlProtocol)_configPtz->protocol; }
                void set(PtzControlProtocol value) { _configPtz->SetProtocol((VxSdk::VxPtzControlProtocol::Value)value); }
            }

        internal:
            VxSdk::IVxDataSourceConfig::Ptz* _configPtz;
        };

        /// <summary>
        /// The SmartCompression class represents a configuration of Smart Compression for a particular video data source.
        /// </summary>
        ref class SmartCompression {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigSmartCompression">The vx smart compression configuration.</param>
            SmartCompression(VxSdk::IVxDataSourceConfig::SmartCompression* vxConfigSmartCompression);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~SmartCompression() {
                this->!SmartCompression();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !SmartCompression();

            /// <summary>
            /// Refreshes this instances properties.
            /// </summary>
            /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
            Results::Value Refresh();

            /// <summary>
            /// Gets or sets the dynamic GOP for the denary (10th) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int DenaryDynamicGop {
            public:
                int get() { return _configSmartCompression->denaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetDenaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the smart compression level, which offers a trade-off between image quality and
            /// compression efficiency.  When not disabled, dynamic GOP can be enabled for each stream.
            /// </summary>
            /// <value>The smart compression level.</value>
            property SmartCompressionLevel Level {
            public:
                SmartCompressionLevel get() { return (SmartCompressionLevel)_configSmartCompression->level; }
                void set(SmartCompressionLevel value) { _configSmartCompression->SetLevel((VxSdk::VxSmartCompressionLevel::Value)value); }
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
            /// Gets or sets the dynamic GOP for the nonary (9th) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int NonaryDynamicGop {
            public:
                int get() { return _configSmartCompression->nonaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetNonaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the dynamic GOP for the octonary (8th) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int OctonaryDynamicGop {
            public:
                int get() { return _configSmartCompression->octonaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetOctonaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the dynamic GOP for the primary (1st) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int PrimaryDynamicGop {
            public:
                int get() { return _configSmartCompression->primaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetPrimaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the dynamic GOP for the quaternary (4th) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int QuaternaryDynamicGop {
            public:
                int get() { return _configSmartCompression->quaternaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetQuaternaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the dynamic GOP for the quinary (5th) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int QuinaryDynamicGop {
            public:
                int get() { return _configSmartCompression->quinaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetQuinaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the dynamic GOP for the secondary (2nd) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int SecondaryDynamicGop {
            public:
                int get() { return _configSmartCompression->secondaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetSecondaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the dynamic GOP for the senary (6th) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int SenaryDynamicGop {
            public:
                int get() { return _configSmartCompression->senaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetSenaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the dynamic GOP for the septenary (7th) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int SeptenaryDynamicGop {
            public:
                int get() { return _configSmartCompression->septenaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetSeptenaryDynamicGop(value); }
            }

            /// <summary>
            /// Gets or sets the dynamic GOP for the tertiary (3rd) stream. If 0, dynamic GOP is disabled for this stream.
            /// </summary>
            /// <value>The maximum number of frames between I-frames.</value>
            property int TertiaryDynamicGop {
            public:
                int get() { return _configSmartCompression->tertiaryDynamicGop; }
                void set(int value) { _configSmartCompression->SetTertiaryDynamicGop(value); }
            }

        internal:
            VxSdk::IVxDataSourceConfig::SmartCompression* _configSmartCompression;
            VxSdkNet::ResourceLimits^ _GetLimits();
        };

        /// <summary>
        /// The VideoEncoding class represents a configuration of a video encoding.
        /// </summary>
        ref class VideoEncoding {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="vxConfigVideoEncoding">The vx video encoding configuration.</param>
            VideoEncoding(VxSdk::IVxDataSourceConfig::VideoEncoding* vxConfigVideoEncoding);

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~VideoEncoding() {
                this->!VideoEncoding();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !VideoEncoding();

            /// <summary>
            /// Gets or sets the bitrate of the stream (in bps).
            /// </summary>
            /// <value>The bitrate (in bps).</value>
            property int Bitrate {
            public:
                int get() { return _configVideoEncoding->bitrate; }
                void set(int value) { _configVideoEncoding->SetBitrate(value); }
            }

            /// <summary>
            /// Gets the list of valid video encoding options for each format. If the format does not contain any options
            /// you must first switch to that format to determine them.
            /// </summary>
            /// <value>A <c>List</c> of video encoding options.</value>
            property System::Collections::Generic::List<VideoEncodingOption^>^ ConfigurationOptions {
            public:
                System::Collections::Generic::List<VideoEncodingOption^>^ get() { return _GetConfigurationOptions(); }
            }

            /// <summary>
            /// Gets or sets the media stream encoding format.
            /// </summary>
            /// <value>The media stream encoding format.</value>
            property DataInterface::StreamFormats Format {
            public:
                DataInterface::StreamFormats get() { return (DataInterface::StreamFormats)_configVideoEncoding->format; }
                void set(DataInterface::StreamFormats value) { _configVideoEncoding->SetFormat((VxSdk::VxStreamFormat::Value)value); }
            }

            /// <summary>
            /// Gets or sets the framerate of the stream.
            /// </summary>
            /// <value>The framerate.</value>
            property float Framerate {
            public:
                float get() { return _configVideoEncoding->framerate; }
                void set(float value) { _configVideoEncoding->SetFramerate(value); }
            }

            /// <summary>
            /// Gets or sets the GOP size of the stream.
            /// </summary>
            /// <value>The GOP size.</value>
            property int Gop {
            public:
                int get() { return _configVideoEncoding->gop; }
                void set(int value) { _configVideoEncoding->SetGop(value); }
            }

            /// <summary>
            /// Gets or sets the IP used for multicast streaming.
            /// </summary>
            /// <value>The multicast IP.</value>
            property System::String^ MulticastIp {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configVideoEncoding->multicastIp); }
                void set(System::String^ value) {
                    char multicastIp[64];
                    VxSdk::Utilities::StrCopySafe(multicastIp, Utils::ConvertCSharpString(value).c_str());
                    _configVideoEncoding->SetMulticastIp(multicastIp);
                }
            }

            /// <summary>
            /// Gets or sets the port used for multicast streaming.
            /// </summary>
            /// <value>The multicast port.</value>
            property int MulticastPort {
            public:
                int get() { return _configVideoEncoding->multicastPort; }
                void set(int value) { _configVideoEncoding->SetMulticastPort(value); }
            }

            /// <summary>
            /// Gets or sets the friendly name for this stream.
            /// </summary>
            /// <value>The friendly name.</value>
            property System::String^ Name {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configVideoEncoding->name); }
                void set(System::String^ value) {
                    char name[64];
                    VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                    _configVideoEncoding->SetName(name);
                }
            }

            /// <summary>
            /// Gets or sets the encoding profile for the format.
            /// </summary>
            /// <value>The encoding profile.</value>
            property VideoEncodingOption::EncoderProfile Profile {
            public:
                VideoEncodingOption::EncoderProfile get() { return (VideoEncodingOption::EncoderProfile)_configVideoEncoding->profile; }
                void set(VideoEncodingOption::EncoderProfile value) { _configVideoEncoding->SetProfile((VxSdk::VxEncoderProfile::Value)value); }
            }

            /// <summary>
            /// Gets or sets the method used to control the bitrate of the stream.
            /// </summary>
            /// <value>The rate control method.</value>
            property System::String^ RateControl {
            public:
                System::String^ get() { return Utils::ConvertCppString(_configVideoEncoding->rateControl); }
                void set(System::String^ value) {
                    char rateControl[64];
                    VxSdk::Utilities::StrCopySafe(rateControl, Utils::ConvertCSharpString(value).c_str());
                    _configVideoEncoding->SetRateControl(rateControl);
                }
            }

            /// <summary>
            /// Gets the ordinal source of the stream: primary, secondary, tertiary, etc.
            /// </summary>
            /// <value>The ordinal source of the stream.</value>
            property Configuration::StreamSource Stream {
            public:
                Configuration::StreamSource get() { return (Configuration::StreamSource)_configVideoEncoding->stream; }
            }

            /// <summary>
            /// Specifies the resolution of the stream.
            /// </summary>
            /// <value>The resolution.</value>
            property Resolution^ StreamResolution {
            public:
                Resolution^ get() { return gcnew Resolution(&_configVideoEncoding->resolution); }
                void set(Resolution^ value) { _SetResolution(value); }
            }

        internal:
            VxSdk::IVxDataSourceConfig::VideoEncoding* _configVideoEncoding;
            void _SetResolution(Resolution^ value);
            System::Collections::Generic::List<VideoEncodingOption^>^ _GetConfigurationOptions();
        };

    internal:
        DataSourceConfig() { };
    };
}
#endif // DataSourceConfig_h__
