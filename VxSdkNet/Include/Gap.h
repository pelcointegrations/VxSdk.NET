// Declares the gap class.
#ifndef Gap_h__
#define Gap_h__

#include "VxSdk.h"
#include "DataStorage.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Gap class represents a span of time that a clip should exist for a particular data source on a particular data storage but
    /// for some reason the clip does not exist. Not all instances of gaps may be detectable by the system and thus may not be reported.
    /// </summary>
    public ref class Gap {
    public:

        /// <summary>
        /// Values that represent the reason for a gap.
        /// </summary>
        enum class GapReasons {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>Camera offline.</summary>
            CameraOffline,

            /// <summary>Not supported.</summary>
            NotSupported,

            /// <summary>Storage device offline.</summary>
            StorageOffline,

            /// <summary>Stream loss.</summary>
            StreamLoss,

            /// <summary>Stream source changed.</summary>
            StreamSourceChanged,

            /// <summary>Time jump.</summary>
            TimeJump,

            /// <summary>Transport changed.</summary>
            TransportChanged,

            /// <summary>Write error.</summary>
            WriteError
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxGap">The vx gap.</param>
        Gap(VxSdk::IVxGap* vxGap);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Gap() {
            this->!Gap();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Gap();

        /// <summary>
        /// Gets the data source associated with this gap.
        /// </summary>
        /// <value>The associated data source.</value>
        property VxSdkNet::DataSource^ DataSource {
        public:
            VxSdkNet::DataSource^ get() { return _GetDataSource(); }
        }

        /// <summary>
        /// Gets the data storage with the gap.
        /// </summary>
        /// <value>The data storage with the gap.</value>
        property VxSdkNet::DataStorage^ DataStorage {
        public:
            VxSdkNet::DataStorage^ get() { return _GetDataStorage(); }
        }

        /// <summary>
        /// Gets the unique identifier of the gapped data source.
        /// </summary>
        /// <value>The unique identifier of the gapped data source.</value>
        property System::String^ DataSourceId {
        public:
            System::String^ get() { return gcnew System::String(_gap->dataSourceId); }
        }

        /// <summary>
        /// Gets the unique identifier of the data storage with the gap.
        /// </summary>
        /// <value>The unique identifier of the data storage with the gap.</value>
        property System::String^ DataStorageId {
        public:
            System::String^ get() { return gcnew System::String(_gap->dataStorageId); }
        }

        /// <summary>
        /// Gets the end time of the gap.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> of the end of the gap.</value>
        property System::DateTime EndTime {
        public:
            System::DateTime get() { return Utils::ConvertCharToDateTime(_gap->endTime); }
        }

        /// <summary>
        /// Gets the reason for this gap.
        /// </summary>
        /// <value>The reason for this gap.</value>
        property GapReasons Reason {
        public:
            GapReasons get() { return GapReasons(_gap->reason); }
        }

        /// <summary>
        /// Gets a list of additional reason data, if any.
        /// </summary>
        /// <value>Additional reason data.</value>
        property System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ ReasonData {
        public:
            System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ get() {
                return _GetReasonData();
            }
        }

        /// <summary>
        /// Gets the start time of the gap.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> of the start of the gap.</value>
        property System::DateTime StartTime {
        public:
            System::DateTime get() { return Utils::ConvertCharToDateTime(_gap->startTime); }
        }

    internal:
        VxSdk::IVxGap* _gap;
        VxSdkNet::DataSource^ _GetDataSource();
        VxSdkNet::DataStorage^ _GetDataStorage();
        System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ _GetReasonData();
    };
}
#endif // Gap_h__
