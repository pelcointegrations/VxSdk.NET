// Declares the new bookmark class.
#ifndef NewBookmark_h__
#define NewBookmark_h__

#include "Bookmark.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewBookmark class represents a new bookmark.
    /// </summary>
    public ref class NewBookmark {
    public:

        /// <summary>
        /// Gets or sets the unique identifier of the data source to associate with the bookmark.
        /// </summary>
        /// <value>The unique identifier of the associated data source.</value>
        property System::String^ DataSourceId;

        /// <summary>
        /// Gets or sets the description of the bookmark.
        /// </summary>
        /// <value>The bookmark description.</value>
        property System::String^ Description;

        /// <summary>
        /// Gets or sets the unique identifier of the associated bookmark group.  Typically used to identify related bookmarks (such as those
        /// bookmarking the same time on audio and video).
        /// </summary>
        /// <value>The unique identifier of the bookmark group.</value>
        property System::String^ GroupId;

        /// <summary>
        /// Gets or sets whether this bookmark will be locked, which will prevent the media it locks from being garbage collected on recorders.
        /// </summary>
        /// <value><c>true</c> if locked, otherwise <c>false</c>.</value>
        property bool IsLocked;

        /// <summary>
        /// Gets or sets the end time of the media to lock.
        /// </summary>
        /// <value>The lock end time.</value>
        property System::DateTime LockEndTime;

        /// <summary>
        /// Gets or sets the start time of the media to lock.
        /// </summary>
        /// <value>The lock start time.</value>
        property System::DateTime LockStartTime;

        /// <summary>
        /// Gets or sets the friendly name of the bookmark.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the time at which the point of interest occurred.
        /// </summary>
        /// <value>The time at which the point of interest occurred.</value>
        property System::DateTime Time;
    };
}
#endif // NewBookmark_h__
