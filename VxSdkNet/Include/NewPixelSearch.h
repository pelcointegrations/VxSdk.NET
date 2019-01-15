// Declares the new pixel search class.
#ifndef NewPixelSearch_h__
#define NewPixelSearch_h__

#include "PixelSearch.h"
#include "Rect.h"

namespace VxSdkNet {

    /// <summary>
    /// The NewPixelSearch class represents a new pixel search request. It uses a square grid composed of rows and columns
    /// with zones indicating the areas of the grid to search. The grid uses a cartesian coordinate system with 0-based indices.
    /// </summary>
    public ref class NewPixelSearch {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        NewPixelSearch() {
            Zones = gcnew System::Collections::Generic::List<Rect^>();
        }

        /// <summary>
        /// Gets or sets the number of columns in the search grid (1 to 1000).
        /// </summary>
        /// <value>The columns in the search grid.</value>
        property int Columns;

        /// <summary>
        /// Gets or sets the number of rows in the search grid (1 to 1000).
        /// </summary>
        /// <value>The rows in the search grid.</value>
        property int Rows;

        /// <summary>
        /// Gets or sets the inclusive bounds to the earliest results to retrieve. Defaults to the oldest results available.
        /// </summary>
        /// <value>The search end time.</value>
        property System::DateTime SearchEndTime;

        /// <summary>
        /// Gets or sets the inclusive bounds to the latest results to retrieve. Defaults to the most current results available.
        /// </summary>
        /// <value>The search start time.</value>
        property System::DateTime SearchStartTime;

        /// <summary>
        /// Gets or sets the rectangular areas indicating the selected zones to search (0,0 to 999,999).
        /// </summary>
        /// <value>The search zones.</value>
        property System::Collections::Generic::List<Rect^>^ Zones;
    };
}
#endif // NewPixelSearch_h__
