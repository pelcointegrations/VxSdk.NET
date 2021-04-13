// Declares the discovery request class.
#ifndef DiscoveryRequest_h__
#define DiscoveryRequest_h__

#include "DeviceSearch.h"

namespace VxSdkNet {

    /// <summary>
    /// The DiscoveryRequest class represents a request to discover new devices.
    /// </summary>
    public ref class DiscoveryRequest {
    public:

        /// <summary>
        /// Values that represent protocols to use for discovery.
        /// </summary>
        enum class DiscoveryProtocol {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>SSDP discovery.</summary>
            Ssdp,

            /// <summary>WS-Discovery.</summary>
            kWsDiscovery
        };

        /// <summary>
        /// Default constructor.
        /// </summary>
        DiscoveryRequest() {
            Protocols = gcnew System::Collections::Generic::List<DiscoveryProtocol>();
            SearchAt = gcnew System::Collections::Generic::List<DeviceSearch^>();
        }

        /// <summary>
        /// Gets or sets whether this request should extend the previous discovery (this will maintain the existing
        /// initiated and number counters) or begin a new discovery (new initiated and reset number counters). Ignored
        /// if discovery is currently in progress (discovery is always extended in this case).  Defaults to <c>true</c>
        /// if discovery was initiated is within the past 12 hours.
        /// </summary>
        /// <value><c>true</c> to extend the previous discovery; <c>false</c> to begin a new discovery.</value>
        property bool ShouldExtend;

        /// <summary>
        /// Gets or sets the list of protocols to use for the discovery; if omitted, all available protocols are used.
        /// </summary>
        /// <value>The list of protocols.</value>
        property System::Collections::Generic::List<DiscoveryProtocol>^ Protocols;

        /// <summary>
        /// Gets or sets the specific devices to discover.
        /// </summary>
        /// <value>The specific devices to discover.</value>
        property System::Collections::Generic::List<DeviceSearch^>^ SearchAt;

    };
}
#endif // DiscoveryRequest_h__
