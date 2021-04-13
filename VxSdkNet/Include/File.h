// Declares the file class.
#ifndef File_h__
#define File_h__

#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The File class represents a file (e.g. camera firmware).
    /// </summary>
    public ref class File {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxFile">The vx file.</param>
        File(VxSdk::IVxFile* vxFile);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~File() {
            this->!File();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !File();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the URI to the download location of the actual file data.
        /// </summary>
        /// <returns>The file endpoint, if available.</returns>
        property System::String^ FileEndpoint {
        public:
            System::String^ get() { return _GetFileEndpoint(); }
        }

        /// <summary>
        /// Gets the filename of the associated file data.
        /// </summary>
        /// <value>The filename.</value>
        property System::String^ Filename {
        public:
            System::String^ get() { return Utils::ConvertCppString(_file->filename); }
        }

        /// <summary>
        /// Gets the unique identifier of the file.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_file->id); }
        }

    internal:
        VxSdk::IVxFile* _file;
        System::String^ _GetFileEndpoint();
    };
}
#endif // File_h__
