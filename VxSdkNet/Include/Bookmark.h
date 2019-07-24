// Declares the bookmark class.
#ifndef Bookmark_h__
#define Bookmark_h__

#include "VxSdk.h"
#include "DataSource.h"
#include "BookmarkLock.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Bookmark class represents a point in time of interest with reference to a particular data source.
    /// </summary>
    public ref class Bookmark {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxBookmark">The vx bookmark.</param>
        Bookmark(VxSdk::IVxBookmark* vxBookmark);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Bookmark() {
            this->!Bookmark();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Bookmark();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the data source associated with this bookmark.
        /// </summary>
        /// <value>The associated data source.</value>
        property VxSdkNet::DataSource^ DataSource {
        public:
            VxSdkNet::DataSource^ get() { return _GetDataSource(); }
        }

        /// <summary>
        /// Gets the unique identifier of the associated data source.
        /// </summary>
        /// <value>The unique identifier of the associated data source.</value>
        property System::String^ DataSourceId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_bookmark->dataSourceId); }
        }

        /// <summary>
        /// Gets or sets the friendly description of the bookmark.
        /// </summary>
        /// <value>The friendly description.</value>
        property System::String^ Description {
        public:
            System::String^ get() { return Utils::ConvertCppString(_bookmark->description); }
            void set(System::String^ value) {
                char description[255];
                VxSdk::Utilities::StrCopySafe(description, Utils::ConvertCSharpString(value).c_str());
                _bookmark->SetDescription(description);
            }
        }

        /// <summary>
        /// Gets the unique bookmark group identifier.  Typically used to identify related bookmarks (such as
        /// those bookmarking the same time on audio and video).
        /// </summary>
        /// <value>The unique bookmark group identifier.</value>
        property System::String^ GroupId {
        public:
            System::String^ get() { return Utils::ConvertCppString(_bookmark->groupId); }
        }

        /// <summary>
        /// Gets the unique bookmark identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_bookmark->id); }
        }

        /// <summary>
        /// Gets the lock configuration for this bookmark.
        /// </summary>
        /// <value>The lock configuration.</value>
        property VxSdkNet::BookmarkLock^ Lock {
        public:
            VxSdkNet::BookmarkLock^ get() { return _GetLock(); }
        }

        /// <summary>
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_bookmark->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _bookmark->SetName(name);
            }
        }

        /// <summary>
        /// Gets the date and time at which the point of interest occurred.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which the point of interest occurred.</value>
        property System::DateTime Time {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_bookmark->time); }
        }

    internal:
        VxSdk::IVxBookmark* _bookmark;
        VxSdkNet::DataSource^ _GetDataSource();
        VxSdkNet::BookmarkLock^ _GetLock();
    };
}
#endif // Bookmark_h__
