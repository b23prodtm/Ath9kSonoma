#ifndef ATH9K_CONTROLLER_H
#define ATH9K_CONTROLLER_H

#include <IOKit/network/IOEthernetController.h>
#include <IOKit/pci/IOPCIDevice.h>
#include "ath9k_hw.h"
#include "ath9k_dma.h"

class ATH9KNetworkInterface;

class ATH9KController : public IOEthernetController {
    OSDeclareDefaultStructors(ATH9KController)
public:
    bool start(IOService *provider) override;
    void stop(IOService *provider) override;
    UInt32 readRegister(UInt32 reg);
    void writeRegister(UInt32 reg, UInt32 value);

private:
    IOPCIDevice *fPCI = nullptr;
    IOMemoryMap *fMemoryMap = nullptr;
    ATH9KNetworkInterface *fInterface = nullptr;
    ath9k_hw_t fHardware;
    ath9k_dma_t fDMA;
};

#endif
