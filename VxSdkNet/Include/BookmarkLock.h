// Declares the bookmark lock class.
#ifndef BookmarkLock_h__
#define BookmarkLock_h__

#include "VxSdk.h"
#include "DataSource.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The BookmarkLock class represents the lock configuration of a bookmark. An enabled lock will prevent
    /// the media it locks from being garbage collected on recorders.
    /// </summary>
    public ref class BookmarkLock {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxBookmarkLock">The vx bookmark lock.</param>
        BookmarkLock(VxSdk::IVxBookmarkLock* vxBookmarkLock);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~BookmarkLock() {
            this->!BookmarkLock();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !BookmarkLock();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets or sets the time at which the bookmark lock ends. Must be after <see cref="StartTime">StartTime</see>.
        /// </summary>
        /// <value>The time at which the bookmark lock ends.</value>
        property System::DateTime EndTime {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_bookmarkLock->endTime); }
            void set(System::DateTime value) { 
                std::string val = Utils::ConvertCSharpDateTime(value);
                _bookmarkLock->SetEndTime((char*)val.c_str());
            }
        }

        /// <summary>
        /// Gets or sets whether or not this bookmark lock is enabled.
        /// </summary>
        /// <value><c>true</c> if locked, otherwise <c>false</c>.</value>
        property bool IsEnabled {
        public:
            bool get() { return _bookmarkLock->isEnabled; }
            void set(bool value) { _bookmarkLock->SetIsEnabled(value); }
        }

        /// <summary>
        /// Gets or sets the time at which the bookmark lock begins. Must be after <see cref="EndTime">EndTime</see>.
        /// </summary>
        /// <value>The time at which the bookmark lock begins.</value>
        property System::DateTime StartTime {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_bookmarkLock->startTime); }
            void set(System::DateTime value) { 
                std::string val = Utils::ConvertCSharpDateTime(value);
                _bookmarkLock->SetStartTime((char*)val.c_str()); 
            }
        }

    internal:
        VxSdk::IVxBookmarkLock* _bookmarkLock;
    };
}
#endif // BookmarkLock_h__
