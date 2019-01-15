// Declares the new data object class.
#ifndef NewDataObject_h__
#define NewDataObject_h__

#include "DataObject.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewDataObject class represents a new data object.
    /// </summary>
    public ref class NewDataObject {
    public:

        /// <summary>
        /// Gets or sets the client identifier. Recommend using the Java package naming convention: com.&gt;company&lt;.&gt;project&lt;.&gt;client_name&lt;.
        /// </summary>
        /// <value>The unique friendly name.</value>
        property System::String^ ClientType;

        /// <summary>
        /// Gets or sets the serialized data (e.g.: JSON, XML, CSV, etc). The maximum allowable size of this field is 1MB.
        /// </summary>
        /// <value>The serialized data.</value>
        property System::String^ Data;

        /// <summary>
        /// Gets or sets whether the new data object will not be owned (public) or will be owned by the user
        /// submitting the request (private).
        /// </summary>
        /// <value><c>true</c> if the data object will be public, <c>false</c> if private.</value>
        property bool IsPrivate;
    };
}
#endif // NewDataObject_h__
