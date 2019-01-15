// Declares the new tag class.
#ifndef NewTag_h__
#define NewTag_h__

#include "Tag.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewTag class represents a new tag.
    /// </summary>
    public ref class NewTag {
    public:

        /// <summary>
        /// Gets or sets whether the new tag will be a folder tag.
        /// </summary>
        /// <value><c>true</c> if the tag will be a folder, otherwise <c>false</c>.</value>
        property bool IsFolder;

        /// <summary>
        /// Gets or sets whether the new tag will not be owned (public) or will be owned by the user
        /// submitting the request (private). Not applicable if this is a folder tag.
        /// </summary>
        /// <value><c>true</c> if the tag will be public, <c>false</c> if private.</value>
        property bool IsPublic;

        /// <summary>
        /// Gets or sets the unique tag friendly name.
        /// </summary>
        /// <remarks>Note: Commas are invalid characters for this field and MUST NOT be used.</remarks>
        /// <value>The unique friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the unique identifier of the tag that is the parent of this tag. If this is provided on a
        /// non-folder tag, it will be ignored.
        /// </summary>
        /// <value>The unique identifier of the parent tag.</value>
        property System::String^ ParentId;
    };
}
#endif // NewTag_h__
