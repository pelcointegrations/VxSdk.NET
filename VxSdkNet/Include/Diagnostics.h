// Declares the Diagnostics class.
#ifndef Diagnostics_h__
#define Diagnostics_h__

#include "VxSdk.h"
#include "Utils.h"

namespace VxSdkNet {

    /// <summary>
    /// The Diagnostics class represents a collection of device diagnostics. Each
    /// diagnostic is represented by a list of that diagnostic’s type. When multiple
    /// diagnostics exist in the list, the diagnostic identifier may be used to
    /// distinguish between them.
    /// </summary>
    public ref class Diagnostics {
    public:

        /// <summary>
        /// Values that represent the health status of a database.
        /// </summary>
        enum class  DatabaseStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The database has failed.</summary>
            Failed,

            /// <summary>The database is OK.</summary>
            Ok,

            /// <summary>The database is rebuilding.</summary>
            Rebuilding,

            /// <summary>The database is recovering.</summary>
            Recovering
        };

        /// <summary>
        /// Values that represent the health status of a drive.
        /// </summary>
        enum class  HddStatus {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>The disk has failed.</summary>
            Failed,

            /// <summary>The disk missing.</summary>
            Missing,

            /// <summary>The disk is OK.</summary>
            Ok,

            /// <summary>The disk is rebuilding.</summary>
            Rebuilding,

            /// <summary>The disk has not been configured.</summary>
            Unconfigured
        };

        /// <summary>
        /// Values that represent the type of load being referenced.
        /// </summary>
        enum class  LoadType {
            /// <summary>An error or unknown value was returned.</summary>
            Unknown,

            /// <summary>CPU load.</summary>
            Cpu,

            /// <summary>GPU load.</summary>
            Gpu,

            /// <summary>Memory load.</summary>
            Memory
        };

        /// <summary>
        /// The Assignments class represents data session information.
        /// </summary>
        ref class Assignments {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="assignments">The assignments diagnostic.</param>
            Assignments(VxSdk::VxDiagnostics::Assignments assignments)
            {
                Bitrate = assignments.bitrate;
                MaxBitrate = assignments.maxBitrate;
                DataSources = assignments.dataSources;
                MaxDataSources = assignments.maxDataSources;
            }

            /// <summary>
            /// Gets the total bitrate that is currently assigned.
            /// </summary>
            /// <value>The total bitrate.</value>
            property float Bitrate;

            /// <summary>
            /// Gets the maximum bitrate that may be assigned.
            /// </summary>
            /// <value>The maximum bitrate.</value>
            property float MaxBitrate;

            /// <summary>
            /// Gets the number of <see cref="DataSource"/> currently assigned.
            /// </summary>
            /// <value>The number of assigned <see cref="DataSource"/>.</value>
            property int DataSources;

            /// <summary>
            /// Gets the maximum number of <see cref="DataSource"/> that may be assigned.
            /// </summary>
            /// <value>The maximum number of assigned <see cref="DataSource"/>.</value>
            property int MaxDataSources;
        };

        /// <summary>
        /// The BackupPower class represents backup power diagnostic information.
        /// </summary>
        ref class BackupPower {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="backupPower">The backup power diagnostic.</param>
            BackupPower(VxSdk::VxDiagnostics::BackupPower* backupPower)
            {
                _backupPower = backupPower;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~BackupPower() {
                this->!BackupPower();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !BackupPower()
            {
                _backupPower = nullptr;
            }

            /// <summary>
            /// Gets a value indicating whether or not backup power is in use.
            /// </summary>
            /// <value><c>true</c> if currently on backup power, <c>false</c> otherwise.</value>
            property bool isEnabled {
            public:
                bool get() { return _backupPower->isEnabled; }
            }

            /// <summary>
            /// Gets the identifier of the backup power.
            /// </summary>
            /// <value>The identifier.</value>
            property System::String^ Id {
            public:
                System::String^ get() { return Utils::ConvertCppString(_backupPower->id); }
            }

            /// <summary>
            /// Gets the estimated backup time remaining (in minutes).
            /// </summary>
            /// <value>The remaining backup time (in minutes), 0 if no backup is available.</value>
            property int Remaining {
            public:
                int get() { return _backupPower->remaining; }
            }

        internal:
            VxSdk::VxDiagnostics::BackupPower* _backupPower;
        };

        /// <summary>
        /// The Database class represents database health information.
        /// </summary>
        ref class Database {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="database">The database diagnostic.</param>
            Database(VxSdk::VxDiagnostics::Database* database)
            {
                _database = database;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Database() {
                this->!Database();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Database()
            {
                _database = nullptr;
            }

            /// <summary>
            /// Gets the database health status.
            /// </summary>
            /// <value>The database health status.</value>
            property DatabaseStatus Status {
            public:
                DatabaseStatus get() { return (DatabaseStatus)_database->status; }
            }

            /// <summary>
            /// Gets the identifier of the database.
            /// </summary>
            /// <value>The identifier.</value>
            property System::String^ Id {
            public:
                System::String^ get() { return Utils::ConvertCppString(_database->id); }
            }

            /// <summary>
            /// Gets how close the current status operation is to completion (e.g. rebuilding). 
            /// </summary>
            /// <value>The progress status percentage. Defaults to 0 if no ongoing status operation is in progress.</value>
            property int StatusProgress {
            public:
                int get() { return _database->statusProgress; }
            }

        internal:
            VxSdk::VxDiagnostics::Database* _database;
        };

        /// <summary>
        /// The Eventing class represents eventing information.
        /// </summary>
        ref class Eventing {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="eventing">The eventing diagnostic.</param>
            Eventing(VxSdk::VxDiagnostics::Eventing eventing)
            {
                EventRate = eventing.eventRate;
            }

            /// <summary>
            /// Gets the average event rate (events per hour).
            /// </summary>
            /// <value>The event rate.</value>
            property int EventRate;
        };

        /// <summary>
        /// The Fan class represents fan specific diagnostic information.
        /// </summary>
        ref class Fan {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="fan">The fan diagnostic.</param>
            Fan(VxSdk::VxDiagnostics::Fan* fan)
            {
                _fan = fan;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Fan() {
                this->!Fan();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Fan()
            {
                _fan = nullptr;
            }

            /// <summary>
            /// Gets a value indicating whether or not the fan is ok.
            /// </summary>
            /// <value><c>true</c> if the fan status is ok, <c>false</c> if the fan is failed.</value>
            property bool IsOk {
            public:
                bool get() { return _fan->isOk; }
            }

            /// <summary>
            /// Gets the identifier of the fan.
            /// </summary>
            /// <value>The identifier.</value>
            property System::String^ Id {
            public:
                System::String^ get() { return Utils::ConvertCppString(_fan->id); }
            }

            /// <summary>
            /// Gets the RPM of the fan.
            /// </summary>
            /// <value>The fan RPM.</value>
            property int Rpm {
            public:
                int get() { return _fan->rpm; }
            }

        internal:
            VxSdk::VxDiagnostics::Fan* _fan;
        };

        /// <summary>
        /// The Hdd class represents hard disk drive (HDD) diagnostic information.
        /// Contains information on the health of individual hard disks.
        /// </summary>
        ref class Hdd {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="hdd">The hdd diagnostic.</param>
            Hdd(VxSdk::VxDiagnostics::Hdd* hdd)
            {
                _hdd = hdd;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Hdd() {
                this->!Hdd();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Hdd()
            {
                _hdd = nullptr;
            }

            /// <summary>
            /// Gets a value indicating whether or not the drive is ok.
            /// </summary>
            /// <value><c>true</c> if the drive status is ok, <c>false</c> if the drive is failed.</value>
            property bool IsOk {
            public:
                bool get() { return _hdd->isOk; }
            }

            /// <summary>
            /// Gets the identifier of the disk.
            /// </summary>
            /// <value>The identifier.</value>
            property System::String^ Id {
            public:
                System::String^ get() { return Utils::ConvertCppString(_hdd->id); }
            }

            /// <summary>
            /// Gets the model name of the disk.
            /// </summary>
            /// <value>The model name.</value>
            property System::String^ Model {
            public:
                System::String^ get() { return Utils::ConvertCppString(_hdd->model); }
            }

            /// <summary>
            /// Gets how close the current status operation is to completion (e.g. rebuilding). 
            /// </summary>
            /// <value>The progress status percentage. Defaults to 0 if no ongoing status operation is in progress.</value>
            property int StatusProgress {
            public:
                int get() { return _hdd->statusProgress; }
            }

            /// <summary>
            /// Gets the current drive health status.
            /// </summary>
            /// <value>The drive health status.</value>
            property HddStatus Status {
            public:
                HddStatus get() { return (HddStatus)_hdd->status; }
            }

        internal:
            VxSdk::VxDiagnostics::Hdd* _hdd;
        };

        /// <summary>
        /// The Load class represents load diagnostic information. May be used to
        /// indicate load on a CPU, application, etc. The <see cref="Type"/> will
        /// distinguish the entity being represented.
        /// </summary>
        ref class Load {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="load">The load diagnostic.</param>
            Load(VxSdk::VxDiagnostics::Load* load)
            {
                _load = load;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Load() {
                this->!Load();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Load()
            {
                _load = nullptr;
            }

            /// <summary>
            /// Gets the percentage of the resource being used.
            /// </summary>
            /// <value>The percentage used.</value>
            property int Percent {
            public:
                int get() { return _load->percent; }
            }

            /// <summary>
            /// Gets the type of load this resource is referencing.
            /// </summary>
            /// <value>The load type.</value>
            property LoadType Type {
            public:
                LoadType get() { return (LoadType)_load->type; }
            }

        internal:
            VxSdk::VxDiagnostics::Load* _load;
        };

        /// <summary>
        /// The Network class represents network diagnostic information.
        /// </summary>
        ref class Network {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="network">The network diagnostic.</param>
            Network(VxSdk::VxDiagnostics::Network* network)
            {
                _network = network;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Network() {
                this->!Network();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Network()
            {
                _network = nullptr;
            }

            /// <summary>
            /// Gets the identifier of the network.
            /// </summary>
            /// <value>The identifier.</value>
            property System::String^ Id {
            public:
                System::String^ get() { return Utils::ConvertCppString(_network->id); }
            }

            /// <summary>
            /// Gets the total amount of bandwidth available (in kbps).
            /// </summary>
            /// <value>The bandwidth in kbps.</value>
            property int BandwidthTotal {
            public:
                int get() { return _network->bandwidthTotal; }
            }

            /// <summary>
            /// Gets the amount of bandwidth in use (in kbps).
            /// </summary>
            /// <value>The bandwidth in kbps.</value>
            property int BandwidthUsed {
            public:
                int get() { return _network->bandwidthUsed; }
            }

        internal:
            VxSdk::VxDiagnostics::Network* _network;
        };

        /// <summary>
        /// The Power class represents power supply diagnostic information.
        /// </summary>
        ref class Power {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="power">The power diagnostic.</param>
            Power(VxSdk::VxDiagnostics::Power* power)
            {
                _power = power;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Power() {
                this->!Power();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Power()
            {
                _power = nullptr;
            }

            /// <summary>
            /// Gets the identifier of the power supply.
            /// </summary>
            /// <value>The identifier.</value>
            property System::String^ Id {
            public:
                System::String^ get() { return Utils::ConvertCppString(_power->id); }
            }

            /// <summary>
            /// Gets a value indicating whether or not the power supply is online.
            /// </summary>
            /// <value><c>true</c> if power supply is online, otherwise <c>false</c>.</value>
            property bool IsOk {
            public:
                bool get() { return _power->isOk; }
            }

        internal:
            VxSdk::VxDiagnostics::Power* _power;
        };

        /// <summary>
        /// The Retention class represents storage retention information.
        /// </summary>
        ref class Retention {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="retention">The retention diagnostic.</param>
            Retention(VxSdk::VxDiagnostics::Retention retention)
            {
                RetentionTime = retention.retentionTime;
            }

            /// <summary>
            /// Gets the current media storage retention time (in hours).
            /// </summary>
            /// <value>Retention time in hours.</value>
            property int RetentionTime;
        };

        /// <summary>
        /// The Storage class represents storage diagnostic information. Contains
        /// information on the capacity and usage of local storage.
        /// </summary>
        ref class Storage {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="storage">The storage diagnostic.</param>
            Storage(VxSdk::VxDiagnostics::Storage* storage)
            {
                _storage = storage;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Storage() {
                this->!Storage();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Storage()
            {
                _storage = nullptr;
            }

            /// <summary>
            /// Gets the identifier of the storage.
            /// </summary>
            /// <value>The identifier.</value>
            property System::String^ Id {
            public:
                System::String^ get() { return Utils::ConvertCppString(_storage->id); }
            }

            /// <summary>
            /// Gets a value indicating whether or not the storage is online and available.
            /// </summary>
            /// <value><c>true</c> if storage is online and available, otherwise <c>false</c>.</value>
            property bool IsOnline {
            public:
                bool get() { return _storage->isOnline; }
            }

            /// <summary>
            /// Gets the total amount of storage present (in MB).
            /// </summary>
            /// <value>Storage amount in MB.</value>
            property int Total {
            public:
                int get() { return _storage->total; }
            }

            /// <summary>
            /// Gets the amount of storage in use (in MB).
            /// </summary>
            /// <value>Storage amount in MB.</value>
            property int Used {
            public:
                int get() { return _storage->used; }
            }

        internal:
            VxSdk::VxDiagnostics::Storage* _storage;
        };

        /// <summary>
        /// The Temperature class represents temperature sensor diagnostic information.
        /// </summary>
        ref class Temperature {
        public:

            /// <summary>
            /// Constructor.
            /// </summary>
            /// <param name="temperature">The temperature diagnostic.</param>
            Temperature(VxSdk::VxDiagnostics::Temperature* temperature)
            {
                _temperature = temperature;
            }

            /// <summary>
            /// Destructor.
            /// </summary>
            virtual ~Temperature() {
                this->!Temperature();
            }

            /// <summary>
            /// Finaliser.
            /// </summary>
            !Temperature()
            {
                _temperature = nullptr;
            }

            /// <summary>
            /// Gets the identifier of the temperature.
            /// </summary>
            /// <value>The identifier.</value>
            property System::String^ Id {
            public:
                System::String^ get() { return Utils::ConvertCppString(_temperature->id); }
            }

            /// <summary>
            /// Gets the temperature reading (in Celsius).
            /// </summary>
            /// <value>The temperature.</value>
            property int Degrees {
            public:
                int get() { return _temperature->degrees; }
            }

            /// <summary>
            /// Gets the temperature threshold over which normal operating temperature is exceeded (in Celsius).
            /// </summary>
            /// <value>The temperature threshold.</value>
            property int ThresholdHigh {
            public:
                int get() { return _temperature->thresholdHigh; }
            }

            /// <summary>
            /// Gets the temperature threshold under which normal operating temperature is exceeded (in Celsius).
            /// </summary>
            /// <value>The temperature threshold.</value>
            property int ThresholdLow {
            public:
                int get() { return _temperature->thresholdLow; }
            }

        internal:
            VxSdk::VxDiagnostics::Temperature* _temperature;
        };

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxDiagnostics">The vx diagnostic.</param>
        Diagnostics(VxSdk::VxDiagnostics* vxDiagnostics)
        {
            _diagnostics = vxDiagnostics;
        }

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~Diagnostics() {
            this->!Diagnostics();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !Diagnostics() {
            _diagnostics->Clear();
            _diagnostics = nullptr;
        }

        /// <summary>
        /// Gets the assignment diagnostics.
        /// </summary>
        /// <value>The assignment diagnostics.</value>
        property Assignments^ AssignmentsInfo {
        public:
            Assignments^ get() { return gcnew Assignments(_diagnostics->assignments); }
        }

        /// <summary>
        /// Gets the backup power diagnostics.
        /// </summary>
        /// <value>The backup power diagnostics.</value>
        property System::Collections::Generic::List<BackupPower^>^ BackupPowers {
        public:
            System::Collections::Generic::List<BackupPower^>^ get() {
                System::Collections::Generic::List<BackupPower^>^ mlist = gcnew System::Collections::Generic::List<BackupPower^>();
                for (int i = 0; i < _diagnostics->backupPowerSize; i++)
                    mlist->Add(gcnew BackupPower(&_diagnostics->backupPowers[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the database diagnostics.
        /// </summary>
        /// <value>The database diagnostics.</value>
        property System::Collections::Generic::List<Database^>^ Databases {
        public:
            System::Collections::Generic::List<Database^>^ get() {
                System::Collections::Generic::List<Database^>^ mlist = gcnew System::Collections::Generic::List<Database^>();
                for (int i = 0; i < _diagnostics->databasesSize; i++)
                    mlist->Add(gcnew Database(&_diagnostics->databases[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the eventing diagnostics.
        /// </summary>
        /// <value>The eventing diagnostics.</value>
        property Eventing^ EventingInfo {
        public:
            Eventing^ get() { return gcnew Eventing(_diagnostics->eventing); }
        }

        /// <summary>
        /// Gets the fan diagnostics.
        /// </summary>
        /// <value>The fan diagnostics.</value>
        property System::Collections::Generic::List<Fan^>^ Fans {
        public:
            System::Collections::Generic::List<Fan^>^ get() {
                System::Collections::Generic::List<Fan^>^ mlist = gcnew System::Collections::Generic::List<Fan^>();
                for (int i = 0; i < _diagnostics->fansSize; i++)
                    mlist->Add(gcnew Fan(&_diagnostics->fans[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the hdd diagnostics.
        /// </summary>
        /// <value>The hdd diagnostics.</value>
        property System::Collections::Generic::List<Hdd^>^ Hdds {
        public:
            System::Collections::Generic::List<Hdd^>^ get() {
                System::Collections::Generic::List<Hdd^>^ mlist = gcnew System::Collections::Generic::List<Hdd^>();
                for (int i = 0; i < _diagnostics->hddsSize; i++)
                    mlist->Add(gcnew Hdd(&_diagnostics->hdds[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the load diagnostics.
        /// </summary>
        /// <value>The load diagnostics.</value>
        property System::Collections::Generic::List<Load^>^ Loads {
        public:
            System::Collections::Generic::List<Load^>^ get() {
                System::Collections::Generic::List<Load^>^ mlist = gcnew System::Collections::Generic::List<Load^>();
                for (int i = 0; i < _diagnostics->loadsSize; i++)
                    mlist->Add(gcnew Load(&_diagnostics->loads[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the network diagnostics.
        /// </summary>
        /// <value>The network diagnostics.</value>
        property System::Collections::Generic::List<Network^>^ Networks {
        public:
            System::Collections::Generic::List<Network^>^ get() {
                System::Collections::Generic::List<Network^>^ mlist = gcnew System::Collections::Generic::List<Network^>();
                for (int i = 0; i < _diagnostics->networksSize; i++)
                    mlist->Add(gcnew Network(&_diagnostics->networks[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the power supply diagnostics.
        /// </summary>
        /// <value>The power supply diagnostics.</value>
        property System::Collections::Generic::List<Power^>^ Powers {
        public:
            System::Collections::Generic::List<Power^>^ get() {
                System::Collections::Generic::List<Power^>^ mlist = gcnew System::Collections::Generic::List<Power^>();
                for (int i = 0; i < _diagnostics->powersSize; i++)
                    mlist->Add(gcnew Power(&_diagnostics->powers[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the retention diagnostics.
        /// </summary>
        /// <value>The retention diagnostics.</value>
        property Retention^ RetentionInfo {
        public:
            Retention^ get() { return gcnew Retention(_diagnostics->retention); }
        }

        /// <summary>
        /// Gets the storage diagnostics.
        /// </summary>
        /// <value>The storage diagnostics.</value>
        property System::Collections::Generic::List<Storage^>^ Storages {
        public:
            System::Collections::Generic::List<Storage^>^ get() {
                System::Collections::Generic::List<Storage^>^ mlist = gcnew System::Collections::Generic::List<Storage^>();
                for (int i = 0; i < _diagnostics->storagesSize; i++)
                    mlist->Add(gcnew Storage(&_diagnostics->storages[i]));

                return mlist;
            }
        }

        /// <summary>
        /// Gets the temperature diagnostics.
        /// </summary>
        /// <value>The temperature diagnostics.</value>
        property System::Collections::Generic::List<Temperature^>^ Temperatures {
        public:
            System::Collections::Generic::List<Temperature^>^ get() {
                System::Collections::Generic::List<Temperature^>^ mlist = gcnew System::Collections::Generic::List<Temperature^>();
                for (int i = 0; i < _diagnostics->temperaturesSize; i++)
                    mlist->Add(gcnew Temperature(&_diagnostics->temperatures[i]));

                return mlist;
            }
        }

        internal:
            VxSdk::VxDiagnostics* _diagnostics;
    };
}
#endif // Diagnostics_h__
