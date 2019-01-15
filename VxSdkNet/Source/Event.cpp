/// <summary>
/// Implements the bookmark class.
/// </summary>
#include "Event.h"
#include <iterator>
#include <map>

VxSdkNet::Event::Event(VxSdk::IVxEvent* vxEvent) {
    _event = vxEvent;
}

VxSdkNet::Event::!Event() {
    _event->Delete();
    _event = nullptr;
}

VxSdkNet::Device^ VxSdkNet::Event::_GetGeneratorDevice() {
    // Get the generator device for this event
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _event->GetGeneratorDevice(device);

    // Return the device if GetGeneratorDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew Device(device);

    // Return nullptr if GetGeneratorDevice is unsuccessful
    return nullptr;
}

System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ VxSdkNet::Event::_GetProperties() {
    // Create a list of key value pair objects
    System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>^ mList =
        gcnew System::Collections::Generic::List<System::Collections::Generic::KeyValuePair<System::String^, System::String^>>();

    // Populate the list with the event properties
    for (int i = 0; i < _event->propertySize; i++) {
        System::Collections::Generic::KeyValuePair<System::String^, System::String^> kvPair(gcnew System::String(_event->properties[i]->key),
            gcnew System::String(_event->properties[i]->value));

        mList->Add(kvPair);
    }

    return mList;
}

VxSdkNet::Situation^ VxSdkNet::Event::_GetSituation() {
    // Get the situation associated with this event
    VxSdk::IVxSituation* situation = nullptr;
    VxSdk::VxResult::Value result = _event->GetSituation(situation);

    // Return the situation if GetSituation was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Situation(situation);

    // Return nullptr if GetSituation is unsuccessful
    return nullptr;
}

VxSdkNet::Device^ VxSdkNet::Event::_GetSourceDevice() {
    // Get the source device for this event
    VxSdk::IVxDevice* device = nullptr;
    VxSdk::VxResult::Value result = _event->GetSourceDevice(device);

    // Return the device if GetSourceDevice was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew Device(device);

    // Return nullptr if GetSourceDevice is unsuccessful
    return nullptr;
}

VxSdkNet::User^ VxSdkNet::Event::_GetSourceUser() {
    // Get the source user associated with this event
    VxSdk::IVxUser* user = nullptr;
    VxSdk::VxResult::Value result = _event->GetUser(user);

    // Return the user if GetUser was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::User(user);

    // Return nullptr if GetUser is unsuccessful
    return nullptr;
}