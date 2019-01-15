/// <summary>
/// Implements the bookmark class.
/// </summary>
#include "Bookmark.h"

using namespace System::Collections::Generic;

VxSdkNet::Bookmark::Bookmark(VxSdk::IVxBookmark* vxBookmark) {
    _bookmark = vxBookmark;
}

VxSdkNet::Bookmark::!Bookmark() {
    _bookmark->Delete();
    _bookmark = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Bookmark::Refresh() {
    return (VxSdkNet::Results::Value)_bookmark->Refresh();
}

VxSdkNet::DataSource^ VxSdkNet::Bookmark::_GetDataSource() {
    // Get the data source
    VxSdk::IVxDataSource* dataSource = nullptr;
    VxSdk::VxResult::Value result = _bookmark->GetDataSource(dataSource);

    // Return the data source if GetDataSource was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataSource(dataSource);

    return nullptr;
}

VxSdkNet::BookmarkLock^ VxSdkNet::Bookmark::_GetLock() {
    // Get the bookmark lock
    VxSdk::IVxBookmarkLock* bookmarkLock = nullptr;
    VxSdk::VxResult::Value result = _bookmark->GetLock(bookmarkLock);

    // Return the bookmark lock if GetLock was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::BookmarkLock(bookmarkLock);

    return nullptr;
}
