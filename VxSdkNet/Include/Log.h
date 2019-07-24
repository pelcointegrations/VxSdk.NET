// Declares the log class.
#ifndef Log_h__
#define Log_h__

#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Log class represents a log file or set of log files.
    /// </summary>
    public ref class Log {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxLog">The vx log.</param>
        Log(VxSdk::IVxLog* vxLog);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Log() {
            this->!Log();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Log();

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the date and time at which the log was completed.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which the log was completed.</value>
        property System::DateTime Completed {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_log->completed); }
        }

        /// <summary>
        /// Gets the unique identifier of the log.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_log->id); }
        }

        /// <summary>
        /// Gets the date and time at which the log was requested.
        /// </summary>
        /// <value>A default <c>DateTime</c> if it fails, else the <c>DateTime</c> at which the log was requested.</value>
        property System::DateTime Initiated {
        public:
            System::DateTime get() { return Utils::ConvertCppDateTime(_log->initiated); }
        }

        /// <summary>
        /// Gets the URI to the download location of the actual log data. May be presented in whatever format is suitable
        /// to the server. This endpoint will only be present if the log data is complete and available for download.
        /// </summary>
        /// <returns>The log endpoint, if available.</returns>
        property System::String^ LogEndpoint {
        public:
            System::String^ get() { return _GetLogEndpoint(); }
        }

    internal:
        VxSdk::IVxLog* _log;
        System::String^ _GetLogEndpoint();
    };
}
#endif // Log_h__
