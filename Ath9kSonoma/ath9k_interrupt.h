#ifndef ATH9K_INTERRUPT_H
#define ATH9K_INTERRUPT_H

#include "ath9k_hw.h"

#define ATH9K_INT_TX 0x00000001
#define ATH9K_INT_RX 0x00000002
typedef void (*ath9k_interrupt_callback_t)(void *context, uint32_t status);
/** Enable the TX and RX interrupt sources. */
int ath9k_interrupt_enable(ath9k_hw_t *hw);
uint32_t ath9k_interrupt_handler(ath9k_hw_t *hw, ath9k_interrupt_callback_t callback, void *context);
#endif
