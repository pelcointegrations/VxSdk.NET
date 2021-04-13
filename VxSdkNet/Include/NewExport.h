// Declares the  new export class.
#ifndef NewExport_h__
#define NewExport_h__

#include "NewExportClip.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewExport class represents a new export.
    /// </summary>
    public ref class NewExport {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewExport() {
            AlternateLocation = gcnew NetworkStorageInfo();
            Clips = gcnew System::Collections::Generic::List<NewExportClip^>();
        }

        /// <summary>
        /// Gets or sets the alternate network location to export the file to, if any.
        /// </summary>
        /// <value>The alternate export location, if any.</value>
        property NetworkStorageInfo^ AlternateLocation;

        /// <summary>
        /// Gets the clips that shall be included in this export when triggered.
        /// </summary>
        /// <value>A <c>List</c> of clips included in the export.</value>
        property System::Collections::Generic::List<NewExportClip^>^ Clips;

        /// <summary>
        /// Gets or sets the export format to use.
        /// </summary>
        /// <value>The export <see cref="Export::Formats">Format</see>.</value>
        property Export::Formats Format;

        /// <summary>
        /// Gets or sets the friendly name of the export.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name;

        /// <summary>
        /// Gets or sets the password for the Export. If set, the export data will be signed and encrypted. This password
        /// will be required to decrypt the export data. If not set, the export data will not be signed or encrypted.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ Password;
    };
}
#endif // NewExport_h__
