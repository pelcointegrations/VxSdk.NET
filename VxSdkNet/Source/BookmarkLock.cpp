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

VxSdkNet::Results::Value VxSdkNet::BookmarkLock::Refresh() {
    return (VxSdkNet::Results::Value)_bookmarkLock->Refresh();
}
