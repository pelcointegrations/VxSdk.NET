// Declares the discovery class.
#ifndef Discovery_h__
#define Discovery_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {
    ref class DiscoveryRequest;

    /// <summary>
    /// The Discovery class represents the current status of device discovery.
    /// </summary>
    public ref class Discovery {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDiscovery">The vx discovery.</param>
        Discovery(VxSdk::IVxDiscovery* vxDiscovery);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Discovery() {
            this->!Discovery();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Discovery();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Begins discovery and initialization.
        /// </summary>
        /// <param name="discoveryRequest">The discovery request to trigger.</param>
        /// <returns>The <see cref="Results::Value">Result</see> of triggering device discovery.</returns>
        Results::Value TriggerDiscovery(DiscoveryRequest^ discoveryRequest);

        /// <summary>
        /// Gets the number of devices that were successfully discovered in the most recent discovery attempt.
        /// </summary>
        /// <value>The number of devices that were successfully discovered.</value>
        property int Discovered {
        public:
            int get() { return _discovery->numDiscovered; }
        }

        /// <summary>
        /// Gets the number of devices that failed to initialize in the most recent discovery attempt.
        /// </summary>
        /// <value>The number of devices that failed to initialize.</value>
        property int InitializationErrors {
        public:
            int get() { return _discovery->numInitializationErrors; }
        }

        /// <summary>
        /// Gets the number of devices that were successfully initialized in the most recent discovery attempt.
        /// </summary>
        /// <value>The number of devices that were successfully initialized.</value>
        property int Initialized {
        public:
            int get() { return _discovery->numInitialized; }
        }

        /// <summary>
        /// Gets the date and time at which the current discovery attempt was triggered.
        /// </summary>
        /// <value>
        /// A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which the current discovery attempt was
        /// triggered.
        /// </value>
        property System::DateTime Initiated {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_discovery->initiated); }
        }

        /// <summary>
        /// Gets whether the system is currently discovering devices.
        /// </summary>
        /// <value><c>true</c> if the system is currently discovering devices, otherwise <c>false</c>.</value>
        property bool IsDiscovering {
        public:
            bool get() { return _discovery->isDiscovering; }
        }

        /// <summary>
        /// Gets whether the system is currently initializing devices.
        /// </summary>
        /// <value><c>true</c> if the system is currently initializing devices, otherwise <c>false</c>.</value>
        property bool IsInitializing {
        public:
            bool get() { return _discovery->isInitializing; }
        }

    internal:
        VxSdk::IVxDiscovery* _discovery;
    };
}
#endif // Discovery_h__
