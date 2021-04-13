// Declares the video encoding option class.
#ifndef VideoEncodingOption_h__
#define VideoEncodingOption_h__

#include "VxSdk.h"

namespace VxSdkNet {

    /// <summary>
    /// The VideoEncodingOption class represents the valid video encoding options/limits for the specified format.
    /// </summary>
    public ref class VideoEncodingOption {
    public:
        /// <summary>
        /// Values that represent the profile used by an encoder to select the features used.
        /// </summary>
        enum class EncoderProfile {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>MPEG4 Advanced Simple profile.</summary>
            AdvancedSimple,
            /// <summary>H264 Baseline profile.</summary>
            Baseline,
            /// <summary>H264 Extended profile.</summary>
            Extended,
            /// <summary>H264 High profile.</summary>
            High,
            /// <summary>H264/H265 Main profile.</summary>
            Main,
            /// <summary>H265 Main10 profile.</summary>
            Main10,
            /// <summary>MPEG4 Simple profile.</summary>
            Simple
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        VideoEncodingOption() {
            Framerates = gcnew System::Collections::Generic::List<float>();
            Profiles = gcnew System::Collections::Generic::List<EncoderProfile>();
			RateControls = gcnew System::Collections::Generic::List<System::String^>();
            Resolutions = gcnew System::Collections::Generic::List<Resolution^>();
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxVideoEncodingOption">The vx video encoding option.</param>
        VideoEncodingOption(VxSdk::VxVideoEncodingOption* vxVideoEncodingOption) {
            Format = (DataInterface::StreamFormats)vxVideoEncodingOption->format;
            HasOptions = vxVideoEncodingOption->hasOptions;
            MaxBitrate = vxVideoEncodingOption->maxBitrate;
            MinBitrate = vxVideoEncodingOption->minBitrate;
            MaxGop = vxVideoEncodingOption->maxGop;
            MinGop = vxVideoEncodingOption->minGop;

            Framerates = gcnew System::Collections::Generic::List<float>();
            for (int i = 0; i < vxVideoEncodingOption->frameratesSize; i++) {
                Framerates->Add(vxVideoEncodingOption->framerates[i]);
            }

            Profiles = gcnew System::Collections::Generic::List<EncoderProfile>();
            for (int i = 0; i < vxVideoEncodingOption->profilesSize; i++) {
                Profiles->Add((EncoderProfile)vxVideoEncodingOption->profiles[i]);
            }
			
			RateControls = gcnew System::Collections::Generic::List<System::String^>();
            for (int i = 0; i < vxVideoEncodingOption->rateControlsSize; i++) {
				RateControls->Add(Utils::ConvertCppString(vxVideoEncodingOption->rateControls[i]));
            }

            Resolutions = gcnew System::Collections::Generic::List<Resolution^>();
            for (int i = 0; i < vxVideoEncodingOption->resolutionsSize; i++) {
                Resolutions->Add(gcnew Resolution(&vxVideoEncodingOption->resolutions[i]));
            }
        }

        /// <summary>
        /// Gets or sets the media stream encoding format that these options/limits apply to.
        /// </summary>
        /// <value>The media stream encoding format.</value>
        property DataInterface::StreamFormats Format;

        /// <summary>
        /// Gets or sets the list of valid framerates.
        /// </summary>
        /// <value>A <c>List</c> of valid framerates.</value>
        property System::Collections::Generic::List<float>^ Framerates;

        /// <summary>
        /// Gets or sets whether there are any video encoding options available. If <c>true</c> you must first switch to
        /// the <see cref="Format"/> to determine them.
        /// </summary>
        /// <value><c>true</c> if there are options available, otherwise <c>false</c>.</value>
        property bool HasOptions;

        /// <summary>
        /// Gets or sets the maximum bitrate that can be set for the stream (in bps).
        /// </summary>
        /// <value>The maximum bitrate (in bps).</value>
        property int MaxBitrate;

        /// <summary>
        /// Gets or sets the maximum GOP size that can be set for the stream.
        /// </summary>
        /// <value>The maximum GOP size.</value>
        property int MaxGop;

        /// <summary>
        /// Gets or sets the minimum bitrate that can be set for the stream (in bps).
        /// </summary>
        /// <value>The minimum bitrate (in bps).</value>
        property int MinBitrate;

        /// <summary>
        /// Gets or sets the minimum GOP size that can be set for the stream.
        /// </summary>
        /// <value>The minimum GOP size.</value>
        property int MinGop;

        /// <summary>
        /// Gets or sets the list of encoding profiles that are available for the stream.
        /// </summary>
        /// <value>A <c>List</c> of encoding profiles.</value>
        property System::Collections::Generic::List<EncoderProfile>^ Profiles;
		
        /// <summary>
        /// Gets or sets the list of available methods that control the bitrate of the stream.
        /// </summary>
        /// <value>A <c>List</c> of rate control methods.</value>
        property System::Collections::Generic::List<System::String^>^ RateControls;

        /// <summary>
        /// Gets or sets the list of resolutions that are available for the stream.
        /// </summary>
        /// <value>A <c>List</c> of resolutions.</value>
        property System::Collections::Generic::List<Resolution^>^ Resolutions;

    };
}
#endif // VideoEncodingOption_h__