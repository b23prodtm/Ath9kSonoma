#ifndef ATH9K_NETWORK_INTERFACE_H
#define ATH9K_NETWORK_INTERFACE_H

#include <IOKit/network/IOEthernetInterface.h>

class ATH9KNetworkInterface : public IOEthernetInterface {
    OSDeclareDefaultStructors(ATH9KNetworkInterface)
public:
    bool init(OSDictionary *properties = nullptr) override;
    UInt32 outputPacket(mbuf_t packet, void *param) override;
    void inputPacket(mbuf_t packet, UInt32 length, IOOptionBits options = 0);
};

#endif
