// Declares the volume group class.
#ifndef VolumeGroup_h__
#define VolumeGroup_h__

#include "VxSdk.h"
#include "Utils.h"
#include "ResourceRel.h"
#include "ResourceLimits.h"

namespace VxSdkNet {
    ref class Volume;

    /// <summary>
    /// The VolumeGroup class represents a group of volumes that can be used together as a storage pool.
    /// </summary>
    public ref class VolumeGroup {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxVolumeGroup">The vx volume group.</param>
        VolumeGroup(VxSdk::IVxVolumeGroup* vxVolumeGroup);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~VolumeGroup() {
            this->!VolumeGroup();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !VolumeGroup();

        /// <summary>
        /// Get all possible volume relations for this volume group (both linked and non-linked). Each linked volume
        /// shall be included in the volume group while each non-linked volume shall be excluded. Note that a volume
        /// may only be linked to 1 volume group.
        /// <para>Available filters: AdvancedQuery, AllTags, AllPrivateTags, Linked.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of related volume resources.</returns>
        System::Collections::Generic::List<ResourceRel^>^ GetVolumeRelations(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the unique volume group identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_volumeGroup->id); }
        }

        /// <summary>
        /// Gets or sets whether or not this volume group is an "archive volume group", which will act as storage for the
        /// oldest available data.
        /// </summary>
        /// <value><c>true</c> to set this volume group as an "archive volume group", otherwise <c>false</c>.</value>
        property bool IsArchiveGroup {
        public:
            bool get() { return _volumeGroup->isArchiveGroup; }
            void set(bool value) { _volumeGroup->SetIsArchiveGroup(value); }
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
        /// Gets or sets the friendly name.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_volumeGroup->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _volumeGroup->SetName(name);
            }
        }

        /// <summary>
        /// Gets the volumes that constitute this volume group.
        /// </summary>
        /// <value>A <c>List</c> of volumes.</value>
        property System::Collections::Generic::List<Volume^>^ Volumes {
        public:
            System::Collections::Generic::List<Volume^>^ get() { return _GetVolumes(); }
        }

    internal:
        VxSdk::IVxVolumeGroup* _volumeGroup;
        VxSdkNet::ResourceLimits^ _GetLimits();
        System::Collections::Generic::List<Volume^>^ _GetVolumes();
    };
}
#endif // VolumeGroup_h__
