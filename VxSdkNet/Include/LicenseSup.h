// Declares the license sup class.
#ifndef LicenseSup_h__
#define LicenseSup_h__

#include "VxSdk.h"
#include "Utils.h"
#include "LicenseSupEvent.h"

namespace VxSdkNet {

    /// <summary>
    /// The LicenseSup class represents software upgrade plan licensing information.
    /// </summary>
    public ref class LicenseSup {
    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        LicenseSup() { }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxLicenseSup">The vx license sup.</param>
        LicenseSup(VxSdk::VxLicenseSup vxLicenseSup){
            CatchUpCount = vxLicenseSup.catchUpCount;
            CurrentBalance = vxLicenseSup.currentBalance;
            ExpirationTime = Utils::ConvertCppDateTime(vxLicenseSup.expirationTime);
            ExtensionYearCount = vxLicenseSup.extensionYearCount;
            Events = gcnew System::Collections::Generic::List<LicenseSupEvent^>();
            for (int i = 0; i < vxLicenseSup.eventsSize; i++)
                Events->Add(gcnew LicenseSupEvent(vxLicenseSup.events[i]));
        }

        /// <summary>
        /// Gets the number of channel-years needed to bring the software upgrade plan license up-to-date today.
        /// </summary>
        /// <value>The channel-years needed.</value>
        property int CatchUpCount;

        /// <summary>
        /// Gets the current number of channel-years remaining.
        /// </summary>
        /// <value>The number of channel-years remaining.</value>
        property float CurrentBalance;

        /// <summary>
        /// Gets the events that are related to this license software upgrade plan; an audit trail.
        /// </summary>
        /// <value>A <c>List</c> of related events.</value>
        property System::Collections::Generic::List<LicenseSupEvent^>^ Events;

        /// <summary>
        /// Gets the expiration time of the software upgrade plan.
        /// </summary>
        /// <value>The expiration time.</value>
        property System::DateTime ExpirationTime;

        /// <summary>
        /// Gets the number of channel-years needed to extend the software upgrade plan license for 1 year.
        /// </summary>
        /// <value>The channel-years needed.</value>
        property int ExtensionYearCount;
    };
}
#endif // LicenseSup_h__
