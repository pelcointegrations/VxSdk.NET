/// <summary>
/// Implements the configuration class.
/// </summary>
#include "Configuration.h"

using namespace System::Collections::Generic;

VxSdkNet::Configuration::Time::Time(VxSdk::IVxConfiguration::Time* vxConfigTime) {
    _configTime = vxConfigTime;
}

VxSdkNet::Configuration::Time::!Time() {
    _configTime->Delete();
    _configTime = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Time::Refresh() {
    return (VxSdkNet::Results::Value)_configTime->Refresh();
}

VxSdkNet::Configuration::Node::Node(VxSdk::IVxConfiguration::Node* vxConfigNode) {
    _configNode = vxConfigNode;
}

VxSdkNet::Configuration::Node::!Node() {
    _configNode->Delete();
    _configNode = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Node::Refresh() {
    return (VxSdkNet::Results::Value)_configNode->Refresh();
}

VxSdkNet::Configuration::Cluster::Cluster(VxSdk::IVxConfiguration::Cluster* vxConfigCluster) {
    _configCluster = vxConfigCluster;
}

VxSdkNet::Configuration::Cluster::!Cluster() {
    _configCluster->Delete();
    _configCluster = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Cluster::Refresh() {
    return (VxSdkNet::Results::Value)_configCluster->Refresh();
}

System::Collections::Generic::List<VxSdkNet::Configuration::Node^>^ VxSdkNet::Configuration::Cluster::_GetNodeConfigurations() {
    // Create a list of managed node objects
    List<Node^>^ mlist = gcnew List<Node^>();
    // Create a collection of unmanaged node objects
    VxSdk::VxCollection<VxSdk::IVxConfiguration::Node**> nodes;

    // Make the GetNodeConfigurations call, which will return with the total count of nodes, this allows the client to allocate memory.
    VxSdk::VxResult::Value result = _configCluster->GetNodeConfigurations(nodes);
    // Unless there are no nodes on the system, this should return VxSdk::VxResult::kInsufficientSize
    if (result == VxSdk::VxResult::kInsufficientSize) {
        // An array of pointers is allocated using the size returned by the previous GetNodeConfigurations call
        nodes.collection = new VxSdk::IVxConfiguration::Node*[nodes.collectionSize];
        result = _configCluster->GetNodeConfigurations(nodes);
        // The result should now be kOK since we have allocated enough space
        if (result == VxSdk::VxResult::kOK) {
            for (int i = 0; i < nodes.collectionSize; i++)
                mlist->Add(gcnew VxSdkNet::Configuration::Node(nodes.collection[i]));
        }
        // Remove the memory we previously allocated to the collection
        delete[] nodes.collection;
    }
    return mlist;
}

VxSdkNet::Configuration::Time^ VxSdkNet::Configuration::Cluster::_GetTimeConfig() {
    // Get the time config for the cluster
    VxSdk::IVxConfiguration::Time* time = nullptr;
    VxSdk::VxResult::Value result = _configCluster->GetTimeConfig(time);

    // Return the time config if GetTimeConfig was successful
    if (result == VxSdk::VxResult::kOK)
        return gcnew VxSdkNet::Configuration::Time(time);

    return nullptr;
}

VxSdkNet::Configuration::Storage::Storage(VxSdk::IVxConfiguration::Storage* vxConfigStorage) {
    _configStorage = vxConfigStorage;
}

VxSdkNet::Configuration::Storage::!Storage() {
    _configStorage->Delete();
    _configStorage = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Storage::Refresh() {
    return (VxSdkNet::Results::Value)_configStorage->Refresh();
}

VxSdkNet::Configuration::Motion::Motion(VxSdk::IVxConfiguration::Motion* vxConfigMotion) {
    _configMotion = vxConfigMotion;
}

VxSdkNet::Configuration::Motion::!Motion() {
    _configMotion->Delete();
    _configMotion = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Configuration::Motion::Refresh() {
    return (VxSdkNet::Results::Value)_configMotion->Refresh();
}