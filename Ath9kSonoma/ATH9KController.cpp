#include "ATH9KController.h"
#include "ATH9KNetworkInterface.h"
#include "ath9k_interrupt.h"

OSDefineMetaClassAndStructors(ATH9KController, IOEthernetController)

static uint32_t ath9kRead(void *context, uint32_t reg) {
    return static_cast<ATH9KController *>(context)->readRegister(reg);
}

static void ath9kWrite(void *context, uint32_t reg, uint32_t value) {
    static_cast<ATH9KController *>(context)->writeRegister(reg, value);
}

bool ATH9KController::start(IOService *provider) {
    if (!super::start(provider)) return false;
    fPCI = OSDynamicCast(IOPCIDevice, provider);
    if (fPCI == nullptr || !fPCI->open(this)) return false;
    fPCI->setMemoryEnable(true);
    fMemoryMap = fPCI->mapDeviceMemoryWithRegister(kIOPCIConfigBaseAddress0);
    if (fMemoryMap == nullptr) return false;
    fHardware = {this, ath9kRead, ath9kWrite};
    fDMA = {};
    if (ath9k_hw_init(&fHardware) != 0 || ath9k_dma_setup(&fHardware, &fDMA) != 0) return false;
    if (ath9k_interrupt_enable(&fHardware) != 0) return false;
    fInterface = new ATH9KNetworkInterface;
    if (fInterface == nullptr || !fInterface->init() || !fInterface->attach(this) ||
        !fInterface->registerWithRegistry()) return false;
    return true;
}

void ATH9KController::stop(IOService *provider) {
    if (fInterface != nullptr) {
        fInterface->terminate();
        fInterface->release();
        fInterface = nullptr;
    }
    ath9k_dma_teardown(&fDMA);
    if (fMemoryMap != nullptr) {
        fMemoryMap->release();
        fMemoryMap = nullptr;
    }
    if (fPCI != nullptr) {
        fPCI->close(this);
        fPCI = nullptr;
    }
    super::stop(provider);
}

UInt32 ATH9KController::readRegister(UInt32 reg) {
    return fMemoryMap == nullptr ? 0 : fMemoryMap->read32(reg);
}

void ATH9KController::writeRegister(UInt32 reg, UInt32 value) {
    if (fMemoryMap != nullptr) fMemoryMap->write32(reg, value);
}
