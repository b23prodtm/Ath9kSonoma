#include "ATH9KNetworkInterface.h"
#include <IOKit/network/IOEthernetController.h>
#include <sys/mbuf.h>

OSDefineMetaClassAndStructors(ATH9KNetworkInterface, IOEthernetInterface)

bool ATH9KNetworkInterface::init(OSDictionary *properties) {
    if (!super::init(properties)) return false;
    return true;
}

UInt32 ATH9KNetworkInterface::outputPacket(mbuf_t packet, void *param) {
    (void)param;
    if (packet != nullptr) mbuf_freem(packet);
    /* TODO: transmit the packet through the TX ring. */
    return kIOReturnSuccess;
}

void ATH9KNetworkInterface::inputPacket(mbuf_t packet, UInt32 length, IOOptionBits options) {
    (void)length;
    (void)options;
    /* TODO: read the RX ring and inject received packets into the network stack. */
    if (packet != nullptr) mbuf_freem(packet);
}
