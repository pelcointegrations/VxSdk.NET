// Declares the license sup event class.
#ifndef LicenseSupEvent_h__
#define LicenseSupEvent_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The LicenseSupEvent class represents a specific event that occurred for a software upgrade plan.
    /// </summary>
    public ref class LicenseSupEvent {
    public:

        /// <summary>
        /// Values that represent software upgrade plan licensing event types.
        /// </summary>
        enum class SupEventType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,
            /// <summary>A license commissioned event.</summary>
            Commissioned,
            /// <summary>A license decommissioned event.</summary>
            Decommissioned,
            /// <summary>A 1-year license expired event.</summary>
            ExpiredSup1,
            /// <summary>A 3-year license expired event.</summary>
            ExpiredSup3,
            /// <summary>A license extended event.</summary>
            ExtendedSup,
            /// <summary>A 1-year license installed event.</summary>
            InstalledSup1,
            /// <summary>A 3-year license installed event.</summary>
            InstalledSup3,
            /// <summary>A license tampered event.</summary>
            Tampered
        };

        /// <summary>
        /// Default constructor.
        /// </summary>
        LicenseSupEvent() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxLicenseSupEvent">The vx license sup event.</param>
        LicenseSupEvent(VxSdk::VxLicenseSupEvent vxLicenseSupEvent){
            CurrentBalance = vxLicenseSupEvent.currentBalance;
            ExpirationTime = Utils::ConvertCppDateTime(vxLicenseSupEvent.expirationTime);
            Time = Utils::ConvertCppDateTime(vxLicenseSupEvent.time);
            Type = (SupEventType)vxLicenseSupEvent.type;
            Value = vxLicenseSupEvent.value;
        }

        /// <summary>
        /// Gets the current number of channel-years available (at the time of this event).
        /// </summary>
        /// <value>The number of channel-years available.</value>
        property float CurrentBalance;

        /// <summary>
        /// Gets the projected expiration of the software upgrade plan (at the time of this event).
        /// </summary>
        /// <value>The projected expiration time.</value>
        property System::DateTime ExpirationTime;

        /// <summary>
        /// Gets the time at which this event occurred.
        /// </summary>
        /// <value>The event time.</value>
        property System::DateTime Time;

        /// <summary>
        /// Gets the type of software upgrade plan event.
        /// </summary>
        /// <value>The event type.</value>
        property SupEventType Type;

        /// <summary>
        /// Gets a numerical value that provides additional data related to the type of event this is.
        /// </summary>
        /// <value>The additional data numerical value.</value>
        property float Value;
    };
}
#endif // LicenseSupEvent_h__
