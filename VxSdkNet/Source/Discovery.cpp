/// <summary>
/// Implements the discovery class.
/// </summary>
///
#include "Discovery.h"
#include "DiscoveryRequest.h"

using namespace System::Collections::Generic;

VxSdkNet::Discovery::Discovery(VxSdk::IVxDiscovery* vxDiscovery) {
    _discovery = vxDiscovery;
}

VxSdkNet::Discovery::!Discovery() {
    _discovery->Delete();
    _discovery = nullptr;
}

VxSdkNet::Results::Value VxSdkNet::Discovery::Refresh() {
    return (VxSdkNet::Results::Value)_discovery->Refresh();
}

VxSdkNet::Results::Value VxSdkNet::Discovery::TriggerDiscovery(DiscoveryRequest^ discoveryRequest) {
    // Create the VxDiscoveryRequest using discoveryRequest
    VxSdk::VxDiscoveryRequest request = VxSdk::VxDiscoveryRequest();
    request.extend = discoveryRequest->ShouldExtend;
    request.protocols = nullptr;
    request.protocolsSize = discoveryRequest->Protocols->Count;
    if (request.protocolsSize > 0) {
        request.protocols = new VxSdk::VxDiscoveryProtocol::Value[request.protocolsSize];
        for (int i = 0; i < request.protocolsSize; i++) {
            request.protocols[i] = (VxSdk::VxDiscoveryProtocol::Value)discoveryRequest->Protocols[i];
        }
    }

    request.searchAt = nullptr;
    request.searchAtSize = discoveryRequest->SearchAt->Count;
    if (request.searchAtSize > 0) {
        request.searchAt = new VxSdk::VxDeviceSearch*[request.searchAtSize];
        for (int i = 0; i < request.searchAtSize; i++) {
            request.searchAt[i] = new VxSdk::VxDeviceSearch();
            request.searchAt[i]->port = discoveryRequest->SearchAt[i]->Port;
            VxSdk::Utilities::StrCopySafe(request.searchAt[i]->driverType, Utils::ConvertCSharpString(discoveryRequest->SearchAt[i]->DriverType).c_str());
            VxSdk::Utilities::StrCopySafe(request.searchAt[i]->host, Utils::ConvertCSharpString(discoveryRequest->SearchAt[i]->Host).c_str());
            VxSdk::Utilities::StrCopySafe(request.searchAt[i]->ipEndAddress, Utils::ConvertCSharpString(discoveryRequest->SearchAt[i]->IpEndAddress).c_str());
            VxSdk::Utilities::StrCopySafe(request.searchAt[i]->ipStartAddress, Utils::ConvertCSharpString(discoveryRequest->SearchAt[i]->IpStartAddress).c_str());
            VxSdk::Utilities::StrCopySafe(request.searchAt[i]->password, Utils::ConvertCSharpString(discoveryRequest->SearchAt[i]->Password).c_str());
            VxSdk::Utilities::StrCopySafe(request.searchAt[i]->username, Utils::ConvertCSharpString(discoveryRequest->SearchAt[i]->Username).c_str());
        }
    }

    VxSdk::VxResult::Value result = _discovery->TriggerDiscovery(request);

    return (VxSdkNet::Results::Value)result;
}


