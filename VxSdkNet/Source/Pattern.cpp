/// <summary>
/// Implements the pattern class.
/// </summary>
#include "Pattern.h"

VxSdkNet::Pattern::Pattern(VxSdk::IVxPattern* vxPattern) {
    _pattern = vxPattern;
}

VxSdkNet::Pattern::!Pattern() {
    _pattern->Delete();
    _pattern = nullptr;
}
