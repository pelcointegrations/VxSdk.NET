/// <summary>
/// Implements the data interface class.
/// </summary>
#include "DataInterface.h"

VxSdkNet::DataInterface::DataInterface(VxSdk::IVxDataInterface* vxDataInterface) {
    _dataInterface = vxDataInterface;
}
