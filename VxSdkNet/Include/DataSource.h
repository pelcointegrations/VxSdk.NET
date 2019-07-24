// Declares the data source class.
#ifndef DataSource_h__
#define DataSource_h__

#include "Configuration.h"
#include "Clip.h"
#include "DataSession.h"
#include "NewPixelSearch.h"
#include "PtzController.h"

namespace VxSdkNet {
    ref class Bookmark;
    ref class DataStorage;
    ref class Device;
    ref class Gap;
    ref class ResourceRel;
    ref class UserInfo;
    ref class Tag;

    /// <summary>
    /// The DataSource class represents a data producer in the system hosted by a device. Each
    /// DataSource provides a list of DataInterface, each of which provides a particular protocol
    /// used to transmit and control the data produced by this DataSource.
    /// </summary>
    public ref class DataSource {
    public:

        /// <summary>
        /// Values that represent the particular type of a data source.
        /// </summary>
        enum class Types {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>A video data source.</summary>
            Video,

            /// <summary>An audio data source.</summary>
            Audio,

            /// <summary>A metadata data source.</summary>
            Metadata
        };

        /// <summary>
        /// Values that represent the operational state of a device.
        /// </summary>
        enum class States {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The device is offline.</summary>
            Offline,

            /// <summary>The device is online.</summary>
            Online
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDataSource">The vx data source.</param>
        DataSource(VxSdk::IVxDataSource* vxDataSource);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~DataSource() {
            this->!DataSource();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !DataSource();

        /// <summary>
        /// Create a new MJPEG stream.
        /// </summary>
        /// <returns><c>nullptr</c> if it fails, else the new MJPEG streams <see cref="DataSession"/>.</returns>
        VxSdkNet::DataSession^ CreateMjpegStream();

        /// <summary>
        /// Create a new pixel search for this data source.
        /// </summary>
        /// <param name="newPixelSearch">The new pixel search to be created.</param>
        /// <returns><c>nullptr</c> if it fails, else the new pixel search result.</returns>
        VxSdkNet::PixelSearch^ CreatePixelSearch(VxSdkNet::NewPixelSearch^ newPixelSearch);

         /// <summary>
        /// Delete a pixel search result.
        /// </summary>
        /// <param name="pixelSearchItem">The pixel search to be deleted.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of deleting the pixel search.</returns>
        Results::Value DeletePixelSearch(VxSdkNet::PixelSearch^ pixelSearchItem);

        /// <summary>
        /// Get all data storages associated with this data source; includes edge and failover data storages using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Commissioned, Id, ModifiedSince, Name, Type.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of all associated data storages.</returns>
        System::Collections::Generic::List<DataStorage^>^ GetAllDataStorages(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get all possible audio resource relations for this data source (both linked and non-linked) using an optional collection filter.
        /// Each linked resource shall be considered to be associated to this data source while non-linked resources
        /// shall not be (they are available to be associated).
        /// <para>Available filters: AdvancedQuery, AllTags, AllPrivateTags, Linked.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of related audio resources.</returns>
        System::Collections::Generic::List<ResourceRel^>^ GetAudioRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the bookmarks associated with this data source using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, DataSourceId, DataSourceType, Description, GroupId, Id, Locked, ModifiedSince, Name, SearchEndTime, SearchStartTime, Time.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of all associated bookmarks.</returns>
        System::Collections::Generic::List<Bookmark^>^ GetBookmarks(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the clips associated with this data source using an optional collection filter.
        /// <para>Available filters: DataSourceId, EndTime, Event, Framerate, SearchEndTime, SearchStartTime, StartTime.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of the associated clips.</returns>
        System::Collections::Generic::List<Clip^>^ GetClips(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the data storages that this data source is associated with using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Commissioned, Id, ModifiedSince, Name, Type.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of the associated data storages.</returns>
        System::Collections::Generic::List<DataStorage^>^ GetDataStorages(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the edge clips associated with this data source using an optional collection filter; may take a long time (minutes).
        /// <para>Available filters: DataSourceId, EndTime, Event, Framerate, SearchEndTime, SearchStartTime, StartTime.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of the associated edge clips.</returns>
        System::Collections::Generic::List<Clip^>^ GetEdgeClips(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the gaps for this data source using an optional collection filter.
        /// <para>Available filters: DataStorageId, SearchEndTime, SearchStartTime, StartTime.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of gaps for this data source.</returns>
        System::Collections::Generic::List<Gap^>^ GetGaps(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get all possible metadata resource relations for this data source (both linked and non-linked) using an optional collection filter.
        /// Each linked resource shall be considered to be associated to this data source while non-linked resources
        /// shall not be (they are available to be associated).
        /// <para>Available filters: AdvancedQuery, AllTags, AllPrivateTags, Linked.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of related audio resources.</returns>
        System::Collections::Generic::List<ResourceRel^>^ GetMetadataRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get the tags associated with this data source using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Folder, Id, ModifiedSince, Name, Owned, Owner, ParentId, ResourceId, ResourceType.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of the associated tags.</returns>
        System::Collections::Generic::List<Tag^>^ GetTags(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Get all possible video resource relations for this data source (both linked and non-linked) using an optional collection filter.
        /// Each linked resource shall be considered to be associated to this data source while non-linked resources
        /// shall not be (they are available to be associated).
        /// <para>Available filters: AdvancedQuery, AllTags, AllPrivateTags, Linked.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of related video resources.</returns>
        System::Collections::Generic::List<ResourceRel^>^ GetVideoRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets all data storages associated with this data source; includes edge and failover data storages.
        /// </summary>
        /// <value>A <c>List</c> of all associated data storages.</value>
        property System::Collections::Generic::List<DataStorage^>^ AllDataStorages {
        public:
            System::Collections::Generic::List<DataStorage^>^ get() { return GetAllDataStorages(nullptr); }
        }

        /// <summary>
        /// Gets all possible audio resource relations for this data source (both linked and non-linked).
        /// Each linked resource shall be considered to be associated to this data source while non-linked resources
        /// shall not be (they are available to be associated).
        /// </summary>
        /// <value>A <c>List</c> of related audio resources.</value>
        property System::Collections::Generic::List<ResourceRel^>^ AudioRelations {
        public:
            System::Collections::Generic::List<ResourceRel^>^ get() { return GetAudioRelations(nullptr); }
        }

        /// <summary>
        /// Gets the bookmarks associated with this data source.
        /// </summary>
        /// <value>A <c>List</c> of all associated bookmarks.</value>
        property System::Collections::Generic::List<Bookmark^>^ Bookmarks {
        public:
            System::Collections::Generic::List<Bookmark^>^ get() { return GetBookmarks(nullptr); }
        }

        /// <summary>
        /// Gets a value indicating whether pixel search is available for this data source.
        /// </summary>
        /// <value><c>true</c> if pixel search is available, <c>false</c> if not.</value>
        property bool CanPixelSearch {
        public:
            bool get() { return _CanPixelSearch(); }
        }

        /// <summary>
        /// Gets the clips associated with this data source.
        /// </summary>
        /// <value>A <c>List</c> of the associated clips.</value>
        property System::Collections::Generic::List<Clip^>^ Clips {
        public:
            System::Collections::Generic::List<Clip^>^ get() { return GetClips(nullptr); }
        }

        /// <summary>
        /// Gets all interfaces available for retrieval of data from this data source.
        /// </summary>
        /// <value>A <c>List</c> of the data interfaces.</value>
        property System::Collections::Generic::List<DataInterface^>^ DataInterfaces {
        public:
            System::Collections::Generic::List<DataInterface^>^ get() { return _GetDataInterfaces(); }
        }

        /// <summary>
        /// Gets the data storages that this data source is associated with.
        /// </summary>
        /// <value>A <c>List</c> of the associated data storages.</value>
        property System::Collections::Generic::List<DataStorage^>^ DataStorages {
        public:
            System::Collections::Generic::List<DataStorage^>^ get() { return GetDataStorages(nullptr); }
        }

        /// <summary>
        /// Gets the edge clips associated with this data source; may take a long time (minutes).
        /// </summary>
        /// <value>A <c>List</c> of the associated edge clips.</value>
        property System::Collections::Generic::List<Clip^>^ EdgeClips {
        public:
            System::Collections::Generic::List<Clip^>^ get() { return GetEdgeClips(nullptr); }
        }

        /// <summary>
        /// Gets the encoding mime type.
        /// </summary>
        property System::String^ Encoding {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dataSource->encoding); }
        }

        /// <summary>
        /// Gets the gaps for this data source.
        /// </summary>
        /// <value>A <c>List</c> of gaps for this data source.</value>
        property System::Collections::Generic::List<Gap^>^ Gaps {
        public:
            System::Collections::Generic::List<Gap^>^ get() { return GetGaps(nullptr); }
        }

        /// <summary>
        /// Gets a value indicating whether the live stream is available.
        /// </summary>
        /// <value><c>true</c> if live is available, <c>false</c> if not.</value>
        property bool HasLiveStream {
        public:
            bool get() { return _dataSource->hasLive; }
        }

        /// <summary>
        /// Gets a value indicating whether the recorded video is available.
        /// </summary>
        /// <value><c>true</c> if recorded video is available, <c>false</c> if not.</value>
        property bool HasRecordedVideo {
        public:
            bool get() { return _dataSource->hasRecorded; }
        }

        /// <summary>
        /// Gets the device that hosts this data source.
        /// </summary>
        /// <value>The host device.</value>
        property VxSdkNet::Device^ HostDevice {
        public:
            VxSdkNet::Device^ get() { return _GetHostDevice(); }
        }

        /// <summary>
        /// Gets the unique identifier for this data source.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dataSource->id); }
        }

        /// <summary>
        /// Gets the zero-based index (per host device) indicating the "position" of the data source (per data source type)
        /// within the host device.
        /// </summary>
        /// <value>The data source index.</value>
        property int Index {
        public:
            int get() { return _dataSource->index; }
        }

        /// <summary>
        /// Gets the IP.
        /// </summary>
        /// <value>The IP.</value>
        property System::String^ Ip {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dataSource->ip); }
        }

        /// <summary>
        /// Gets a value indicating whether this data source is currently being captured by a recorder.
        /// </summary>
        /// <value><c>true</c> if capturing, <c>false</c> if not.</value>
        property bool IsCapturing {
        public:
            bool get() { return _dataSource->isCapturing; }
        }

        /// <summary>
        /// Gets a value indicating whether the data source is currently being manually recorded (by one
        /// or more data storage).
        /// </summary>
        /// <value><c>true</c> if manually recording, <c>false</c> if not.</value>
        property bool IsManuallyRecording {
        public:
            bool get() { return _dataSource->isManuallyRecording; }
        }

        /// <summary>
        /// Gets a value indicating whether the data source is currently recording.
        /// </summary>
        /// <value><c>true</c> if recording, <c>false</c> if not.</value>
        property bool IsRecording {
        public:
            bool get() { return _dataSource->isRecording; }
        }

        /// <summary>
        /// Gets a value indicating whether PTZ is enabled.
        /// </summary>
        /// <value><c>true</c> if PTZ is enabled, <c>false</c> if not.</value>
        property bool IsPTZ {
        public:
            bool get() { return _CanPtz(); }
        }

        /// <summary>
        /// Gets a value indicating whether the data source is currently recording.
        /// </summary>
        /// <value><c>true</c> if recording, <c>false</c> if not.</value>
        property bool IsEnabled {
        public:
            bool get() { return _dataSource->isEnabled; }
            void set(bool value) {
                if (value)
                    _dataSource->Enable();
                else
                    _dataSource->Disable();
            }
        }

        /// <summary>
        /// Gets the currently linked audio resource relation for this data source, if any.
        /// </summary>
        /// <value>The linked audio resource if available, otherwise <c>nullptr</c>.</value>
        property ResourceRel^ LinkedAudioRelation {
        public:
            ResourceRel^ get() {
                System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filter = gcnew System::Collections::Generic::Dictionary<Filters::Value, System::String^>();
                filter->Add(Filters::Value::Linked, "true");
                System::Collections::Generic::List<ResourceRel^>^ audioRels = GetAudioRelations(filter);
                return audioRels->Count > 0 ? audioRels[0] : nullptr;
            }
        }

        /// <summary>
        /// Gets the currently linked metadata resource relations for this data source, if any.
        /// </summary>
        /// <value>A <c>List</c> of linked metadata resource relations.</value>
        property System::Collections::Generic::List<ResourceRel^>^ LinkedMetadataRelations {
        public:
            System::Collections::Generic::List<ResourceRel^>^ get() {
                System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filter = gcnew System::Collections::Generic::Dictionary<Filters::Value, System::String^>();
                filter->Add(Filters::Value::Linked, "true");
                return GetMetadataRelations(filter);
            }
        }

        /// <summary>
        /// Gets all possible metadata resource relations for this data source (both linked and non-linked).
        /// Each linked resource shall be considered to be associated to this data source while non-linked resources
        /// shall not be (they are available to be associated).
        /// </summary>
        /// <value>A <c>List</c> of related audio resources.</value>
        property System::Collections::Generic::List<ResourceRel^>^ MetadataRelations {
        public:
            System::Collections::Generic::List<ResourceRel^>^ get() { return GetMetadataRelations(nullptr); }
        }

        /// <summary>
        /// Gets the motion detection configuration for this data source, if supported.
        /// </summary>
        /// <value>The motion configuration if supported by this data source, otherwise <c>nullptr</c>.</value>
        property VxSdkNet::Configuration::Motion^ MotionConfiguration {
        public:
            VxSdkNet::Configuration::Motion^ get() { return _GetMotionConfig(); }
        }

        /// <summary>
        /// Gets the multiple viewer information for this data source.  This information contains details on the
        /// current viewers of this data source.
        /// </summary>
        /// <value>A <c>List</c> of user information for all viewers of this data source.</value>
        property System::Collections::Generic::List<UserInfo^>^ MultiviewInfo {
        public:
            System::Collections::Generic::List<UserInfo^>^ get() { return _GetMultiviewInfo(); }
        }

        /// <summary>
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dataSource->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _dataSource->SetName(name);
            }
        }

        /// <summary>
        /// Gets or sets the number used to designate the data source.
        /// </summary>
        /// <value>The data source number.</value>
        property int Number {
        public:
            int get() { return _dataSource->number; }
            void set(int value) { _dataSource->SetNumber(value); }
        }

        /// <summary>
        /// Gets the <see cref="PtzController"/> associated with this data source.
        /// </summary>
        /// <value><c>nullptr</c> if PTZ is not supported on the device, else the <see cref="PtzController"/>.</value>
        property PtzController^ PTZController {
        public:
            PtzController^ get() { return _GetPtzController(); }
        }

        /// <summary>
        /// Gets or sets the maximum retention (in hours) that the system will keep recorded data for this data
        /// source. Any recorded data that exceeds this limit will be deleted. If <see cref="Configuration::Storage::RetentionLimit"/>
        /// is also set, the lowest non-zero value will be used. A value of 0 means no retention limit will be used.
        /// </summary>
        /// <value>The retention limit (in hours).</value>
        property int RetentionLimit {
        public:
            int get() { return _dataSource->retentionLimit; }
            void set(int value) { _dataSource->SetRetentionLimit(value); }
        }

        /// <summary>
        /// Gets the RTSP stream endpoint URI.
        /// </summary>
        /// <value>The RTSP endpoint.</value>
        property System::String^ RtspEndpoint {
        public:
            System::String^ get() { return _GetRtspEndpoint(); }
        }

        /// <summary>
        /// Gets the URI to retrieve the current live frame.
        /// </summary>
        /// <value>The JPEG URI.</value>
        property System::String^ SnapshotUri {
        public:
            System::String^ get() { return Utils::ConvertCppString(_dataSource->snapshotUri); }
        }

        /// <summary>
        /// Gets the current operational state of the associated device.
        /// </summary>
        /// <value>The current device state.</value>
        property States State {
        public:
            States get() { return States(_dataSource->state); }
        }

        /// <summary>
        /// Gets the tags associated with this data source.
        /// </summary>
        /// <value>A <c>List</c> of the associated tags.</value>
        property System::Collections::Generic::List<Tag^>^ Tags {
        public:
            System::Collections::Generic::List<Tag^>^ get() { return GetTags(nullptr); }
        }

        /// <summary>
        /// Gets the type of media this data source contains.
        /// </summary>
        /// <value>The media type.</value>
        property Types Type {
        public:
            Types get() { return Types(_dataSource->type); }
        }

        /// <summary>
        /// Gets all possible video resource relations for this data source (both linked and non-linked).
        /// Each linked resource shall be considered to be associated to this data source while non-linked resources
        /// shall not be (they are available to be associated).
        /// </summary>
        /// <value>A <c>List</c> of related video resources.</value>
        property System::Collections::Generic::List<ResourceRel^>^ VideoRelations {
        public:
            System::Collections::Generic::List<ResourceRel^>^ get() { return GetVideoRelations(nullptr); }
        }

    internal:
        VxSdk::IVxDataSource* _dataSource;
        bool _CanPixelSearch();
        bool _CanPtz();
        System::Collections::Generic::List<DataInterface^>^ _GetDataInterfaces();
        VxSdkNet::Device^ _GetHostDevice();
        VxSdkNet::Configuration::Motion^ _GetMotionConfig();
        System::Collections::Generic::List<UserInfo^>^ _GetMultiviewInfo();
        PtzController^ _GetPtzController();
        System::String^ _GetRtspEndpoint();
    };
}
#endif // DataSource_h__
