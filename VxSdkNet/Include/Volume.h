// Declares the volume class.
#ifndef Volume_h__
#define Volume_h__

#include "VxSdk.h"
#include "Utils.h"
#include "VolumeGroup.h"

namespace VxSdkNet {

    /// <summary>
    /// The Volume class represents a storage volume.
    /// </summary>
    public ref class Volume {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxVolume">The vx volume.</param>
        Volume(VxSdk::IVxVolume* vxVolume);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Volume() {
            this->!Volume();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Volume();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets or sets the percentage of the volume to keep free.
        /// </summary>
        /// <value>The buffer percentage (0 - 1).</value>
        property float Buffer {
        public:
            float get() { return _volume->buffer; }
            void set(float value) { _volume->SetBuffer(value); }
        }

        /// <summary>
        /// Gets or sets the domain for the volume network path. Note: Ignored if the <see cref="Path"/> is not a UNC path.
        /// </summary>
        /// <value>The domain name.</value>
        property System::String^ Domain {
        public:
            System::String^ get() { return Utils::ConvertCppString(_volume->domain); }
            void set(System::String^ value) {
                char domain[64];
                VxSdk::Utilities::StrCopySafe(domain, Utils::ConvertCSharpString(value).c_str());
                _volume->SetDomain(domain);
            }
        }

        /// <summary>
        /// Gets the unique volume identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_volume->id); }
        }

        /// <summary>
        /// Gets or sets whether or not this is a NAS volume that shares bandwidth with data streams (bandwidth will be
        /// reserved for NAS operations).
        /// </summary>
        /// <value><c>true</c> to share bandwidth with data streams, otherwise <c>false</c>.</value>
        property bool IsBandwidthReserved {
        public:
            bool get() { return _volume->isBandwidthReserved; }
            void set(bool value) { _volume->SetIsBandwidthReserved(value); }
        }

        /// <summary>
        /// Gets whether or not the storage is online and available.
        /// </summary>
        /// <value><c>true</c> if online, otherwise <c>false</c>.</value>
        property bool IsOnline {
        public:
            bool get() { return _volume->isOnline; }
        }

        /// <summary>
        /// Gets any limits related to this resource.
        /// </summary>
        /// <value>The limits related to this resource.</value>
        property ResourceLimits^ Limits {
        public:
            ResourceLimits^ get() { return _GetLimits(); }
        }

        /// <summary>
        /// Sets the password for access to the network path. Note: Ignored if the <see cref="Path"/> is not a UNC path.
        /// </summary>
        /// <value>The password.</value>
        property System::String^ Password {
        public:
            void set(System::String^ value) {
                char password[64];
                VxSdk::Utilities::StrCopySafe(password, Utils::ConvertCSharpString(value).c_str());
                _volume->SetPassword(password);
            }
        }

        /// <summary>
        /// Gets or sets the fully qualified Windows directory path.
        /// </summary>
        /// <value>The directory path.</value>
        property System::String^ Path {
        public:
            System::String^ get() { return Utils::ConvertCppString(_volume->path); }
            void set(System::String^ value) {
                char path[512];
                VxSdk::Utilities::StrCopySafe(path, Utils::ConvertCSharpString(value).c_str());
                _volume->SetPath(path);
            }
        }

        /// <summary>
        /// Gets the total amount of storage present (in MB).
        /// </summary>
        /// <value>The total amount of storage present (in MB).</value>
        property int Total {
        public:
            int get() { return _volume->total; }
        }

        /// <summary>
        /// Gets the amount of storage in use (in MB).
        /// </summary>
        /// <value>The amount of storage in use (in MB).</value>
        property int Used {
        public:
            int get() { return _volume->used; }
        }

        /// <summary>
        /// Gets or sets the username for access to the network path. Note: Ignored if the <see cref="Path"/> is not a UNC path.
        /// </summary>
        /// <value>The username.</value>
        property System::String^ Username {
        public:
            System::String^ get() { return Utils::ConvertCppString(_volume->username); }
            void set(System::String^ value) {
                char username[64];
                VxSdk::Utilities::StrCopySafe(username, Utils::ConvertCSharpString(value).c_str());
                _volume->SetUsername(username);
            }
        }

        /// <summary>
        /// Gets the volume group that this volume is in, if any.
        /// </summary>
        /// <value>The volume group if present, otherwise <c>nullptr</c>.</value>
        property VxSdkNet::VolumeGroup^ VolumeGroup {
        public:
            VxSdkNet::VolumeGroup^ get() { return _GetVolumeGroup(); }
        }

    internal:
        VxSdk::IVxVolume* _volume;
        VxSdkNet::ResourceLimits^ _GetLimits();
        VxSdkNet::VolumeGroup^ _GetVolumeGroup();
    };
}
#endif // Volume_h__
