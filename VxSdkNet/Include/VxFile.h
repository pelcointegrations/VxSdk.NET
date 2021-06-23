// Declares the vx file class.
#ifndef VxFile_h__
#define VxFile_h__

#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The VxFile class represents a file (e.g. camera firmware).
    /// </summary>
    public ref class VxFile {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxFile">The vx file.</param>
        VxFile(VxSdk::IVxFile* vxFile);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~VxFile() {
            this->!VxFile();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !VxFile();

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
            System::String^ get() { return Utils::ConvertCppString(_vxFile->filename); }
        }

        /// <summary>
        /// Gets the unique identifier of the file.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_vxFile->id); }
        }

    internal:
        VxSdk::IVxFile* _vxFile;
        System::String^ _GetFileEndpoint();
    };
}
#endif // VxFile_h__
