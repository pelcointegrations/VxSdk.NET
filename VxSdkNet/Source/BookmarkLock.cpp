/// <summary>
/// Implements the bookmark lock class.
/// </summary>
#include "BookmarkLock.h"

using namespace System::Collections::Generic;

VxSdkNet::BookmarkLock::BookmarkLock(VxSdk::IVxBookmarkLock* vxBookmarkLock) {
    _bookmarkLock = vxBookmarkLock;
}

VxSdkNet::BookmarkLock::!BookmarkLock() {
    _bookmarkLock->Delete();
    _bookmarkLock = nullptr;
}

VxSdkNet::ResourceLimits^ VxSdkNet::BookmarkLock::_GetLimits() {
    // Get the limits for this resource
    VxSdk::VxLimits* limits = nullptr;
    VxSdk::VxResult::Value result = _bookmarkLock->GetLimits(limits);

    // Return the limits if GetLimits was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew ResourceLimits(limits);

    return nullptr;
}

VxSdkNet::Results::Value VxSdkNet::BookmarkLock::Refresh() {
    return (VxSdkNet::Results::Value)_bookmarkLock->Refresh();
}
