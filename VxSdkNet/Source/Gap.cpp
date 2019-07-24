/// <summary>
/// Implements the gap class.
/// </summary>

#include "Gap.h"

using namespace System::Collections::Generic;

VxSdkNet::Gap::Gap(VxSdk::IVxGap* vxGap) {
    _gap = vxGap;
}

VxSdkNet::Gap::!Gap() {
    _gap->Delete();
    _gap = nullptr;
}

VxSdkNet::DataSource^ VxSdkNet::Gap::_GetDataSource() {
    // Get the data source
    VxSdk::IVxDataSource* dataSource = nullptr;
    VxSdk::VxResult::Value result = _gap->GetDataSource(dataSource);

    // Return the data source if GetDataSource was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataSource(dataSource);

    return nullptr;
}

VxSdkNet::DataStorage^ VxSdkNet::Gap::_GetDataStorage() {
    // Get the data storage
    VxSdk::IVxDataStorage* dataStorage = nullptr;
    VxSdk::VxResult::Value result = _gap->GetDataStorage(dataStorage);

    // Return the data storage if GetDataStorage was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::DataStorage(dataStorage);

    return nullptr;
}

System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ VxSdkNet::Gap::_GetReasonData() {
    // Create a list of key value pair objects
    System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ mList =
        gcnew System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>();

    // Populate the list with the reason data
    for (int i = 0; i < _gap->reasonDataSize; i++) {
        System::Collections::Generic::KeyValuePair<System::String^, System::String^> kvPair(Utils::ConvertCppString(_gap->reasonData[i]->key),
            Utils::ConvertCppString(_gap->reasonData[i]->value));

        mList->Add(kvPair);
    }

    return mList;
}
