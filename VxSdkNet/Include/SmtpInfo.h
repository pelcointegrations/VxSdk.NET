// Declares the SMTP info class.
#ifndef SmtpInfo_h__
#define SmtpInfo_h__

namespace VxSdkNet {

    /// <summary>
    /// The SmtpInfo class represents the SMTP information needed to send an email.
    /// </summary>
    public ref class SmtpInfo {
    public:

        /// <summary>
        /// Gets or sets the "Mail From" email address.
        /// </summary>
        /// <value>The "Mail From" email address.</value>
        property System::String^ FromAddress;

        /// <summary>
        /// Gets or sets the SMTP host.
        /// </summary>
        /// <value>The SMTP host.</value>
        property System::String^ Host;

        /// <summary>
        /// Gets or sets the password for SMTP access.
        /// </summary>
        /// <value>The password for SMTP access.</value>
        property System::String^ Password;

        /// <summary>
        /// Gets or sets the SMTP port.
        /// </summary>
        /// <value>The SMTP port.</value>
        property int SmtpPort;

        /// <summary>
        /// Gets or sets the timeout in milliseconds.
        /// </summary>
        /// <value>The timeout in milliseconds.</value>
        property int Timeout;

        /// <summary>
        /// Gets or sets the "Mail To" email address.
        /// </summary>
        /// <value>The "Mail To" email address.</value>
        property System::String^ ToAddress;

        /// <summary>
        /// Gets or sets the username for SMTP access.
        /// </summary>
        /// <value>The username for SMTP access.</value>
        property System::String^ Username;

        /// <summary>
        /// Gets or sets whether SMTPS should be used instead of SMTP.
        /// </summary>
        /// <value><c>true</c> to use SMTPS, <c>false</c> to use SMTP.</value>
        property bool UseSmtps;
    };
}
#endif // SmtpInfo_h__
