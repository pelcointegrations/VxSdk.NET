/// <summary>
/// Implements the driver class.
/// </summary>
#include "Driver.h"
#include "DataStorage.h"

using namespace System::Collections::Generic;

VxSdkNet::Driver::Driver(VxSdk::IVxDriver* vxDriver) {
    _driver = vxDriver;
}

VxSdkNet::Driver::!Driver() {
    _driver->Delete();
    _driver = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Driver::Refresh() {
    return (VxSdkNet::Results::Value)_driver->Refresh();
}
