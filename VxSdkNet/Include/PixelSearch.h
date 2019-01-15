// Declares the pixel search class.
#ifndef PixelSearch_h__
#define PixelSearch_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {
    ref class Clip;

    /// <summary>
    /// The PixelSearch class represents a pixel search.
    /// </summary>
    public ref class PixelSearch {
    public:

        /// <summary>
        /// Values that represent the status of a search.
        /// </summary>
        enum class SearchStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>The search has completed.</summary>
            Complete,
            /// <summary>The search is in progress.</summary>
            InProgress
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxPixelSearch">The vx pixel search.</param>
        PixelSearch(VxSdk::IVxPixelSearch* vxPixelSearch);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~PixelSearch() {
            this->!PixelSearch();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !PixelSearch();

        /// <summary>
        /// Get the clips that were found as a result of the pixel search using an optional collection filter. New clips may continue to be available
        /// while the search is in progress.
        /// <para>Available filters: DataSourceId, EndTime, Event, Framerate, SearchEndTime, SearchStartTime, StartTime.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of clips.</returns>
        System::Collections::Generic::List<Clip^>^ GetClips(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Gets the clips that were found as a result of the pixel search. New clips may continue to be available
        /// while the search is in progress.
        /// </summary>
        /// <value>A <c>List</c> of clips found.</value>
        property System::Collections::Generic::List<Clip^>^ Clips {
        public:
            System::Collections::Generic::List<Clip^>^ get() { return GetClips(nullptr); }
        }

        /// <summary>
        /// Gets the current status of the pixel search.
        /// </summary>
        /// <value>A the current status of the pixel search.</value>
        property SearchStatus Status {
        public:
            SearchStatus get() { return _GetStatus(); }
        }

    internal:
        VxSdk::IVxPixelSearch* _pixelSearch;
        SearchStatus _GetStatus();
    };
}
#endif // PixelSearch_h__
