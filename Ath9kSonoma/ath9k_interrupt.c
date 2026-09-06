#include "ath9k_interrupt.h"

int ath9k_interrupt_enable(ath9k_hw_t *hw) {
    if (hw == 0 || hw->write == 0) return -1;
    hw->write(hw->context, AR_IMR, ATH9K_INT_TX | ATH9K_INT_RX);
    return 0;
}

uint32_t ath9k_interrupt_handler(ath9k_hw_t *hw, ath9k_interrupt_callback_t callback, void *context) {
    if (hw == 0 || hw->read == 0) return 0;
    uint32_t status = hw->read(hw->context, AR_ISR);
    if (callback != 0 && (status & (ATH9K_INT_TX | ATH9K_INT_RX)) != 0) callback(context, status);
    return status;
}
