// Declares the monitor class.
#ifndef MonitorWall_h__
#define MonitorWall_h__

#include "VxSdk.h"
#include "Utils.h"
#include "MonitorPosition.h"
#include "Monitor.h"

namespace VxSdkNet {
    /// <summary>
    /// The MonitorWall class represents a group of monitors.
    /// </summary>
    public ref class MonitorWall {
    public:

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="vxMonitorWall">The vx monitor wall.</param>
        MonitorWall(VxSdk::IVxMonitorWall* vxMonitorWall);

        /// <summary>
        /// Destructor.
        /// </summary>
        virtual ~MonitorWall() {
            this->!MonitorWall();
        }

        /// <summary>
        /// Finaliser.
        /// </summary>
        !MonitorWall();

        /// <summary>
        /// Get the monitors associated with this monitor wall using an optional collection filter.
        /// <para>Available filters: AdvancedQuery, Id, ModifiedSince, Name, Number.</para>
        /// </summary>
        /// <param name="filters">The collection filters to be used in the request.</param>
        /// <returns>A <c>List</c> of associated monitors.</returns>
        System::Collections::Generic::List<Monitor^>^ GetMonitors(System::Collections::Generic::Dictionary<Filters::Value, System::String^>^ filters);

        /// <summary>
        /// Refreshes this instances properties.
        /// </summary>
        /// <returns>The <see cref="Results::Value">Result</see> of updating the properties.</returns>
        Results::Value Refresh();

        /// <summary>
        /// Gets the unique monitor wall identifier.
        /// </summary>
        /// <value>The unique identifier.</value>
        property System::String^ Id {
        public:
            System::String^ get() { return Utils::ConvertCppString(_monitorWall->id); }
        }

        /// <summary>
        /// Gets or sets the monitor positions for this monitor wall.
        /// </summary>
        /// <value>A <c>List</c> of monitor positions.</value>
        property System::Collections::Generic::List<MonitorPosition^>^ MonitorPositions {
        public:
            System::Collections::Generic::List<MonitorPosition^>^ get() {
                _monitorWall->Refresh();
                System::Collections::Generic::List<MonitorPosition^>^ mList = gcnew System::Collections::Generic::List<MonitorPosition^>();
                for (int i = 0; i < _monitorWall->monitorPositionsSize; i++)
                {
                    mList->Add(gcnew MonitorPosition(&_monitorWall->monitorPositions[i]));
                }

                return mList;
            }
            void set(System::Collections::Generic::List<MonitorPosition^>^ value) {
                int size = value->Count;
                VxSdk::VxMonitorPosition* positions = new VxSdk::VxMonitorPosition[size];
                for (int i = 0; i < size; i++) {
                    VxSdk::Utilities::StrCopySafe(positions[i].monitorId, Utils::ConvertCSharpString(value[i]->MonitorId).c_str());
                    positions[i].position.height = value[i]->Position->Height;
                    positions[i].position.left = value[i]->Position->Left;
                    positions[i].position.top = value[i]->Position->Top;
                    positions[i].position.width = value[i]->Position->Width;
                }

                _monitorWall->SetMonitorPositions(positions, size);
                delete[] positions;
                positions = nullptr;
                _monitorWall->Refresh();
            }
        }

        /// <summary>
        /// Gets the monitors associated with this monitor wall.
        /// </summary>
        /// <value>A <c>List</c> of associated monitors.</value>
        property System::Collections::Generic::List<Monitor^>^ Monitors {
        public:
            System::Collections::Generic::List<Monitor^>^ get() { return GetMonitors(nullptr); }
        }

        /// <summary>
        /// Gets or sets the friendly name of this monitor wall.
        /// </summary>
        /// <value>The friendly name.</value>
        property System::String^ Name {
        public:
            System::String^ get() { return Utils::ConvertCppString(_monitorWall->name); }
            void set(System::String^ value) {
                char name[64];
                VxSdk::Utilities::StrCopySafe(name, Utils::ConvertCSharpString(value).c_str());
                _monitorWall->SetName(name);
            }
        }

    internal:
        VxSdk::IVxMonitorWall* _monitorWall;
    };
}
#endif // MonitorWall_h__
