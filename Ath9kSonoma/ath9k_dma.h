#ifndef ATH9K_DMA_H
#define ATH9K_DMA_H

#include <stdint.h>
#include "ath9k_hw.h"

#define ATH9K_RING_SIZE 256

typedef struct __attribute__((packed)) {
    uint32_t link;
    uint32_t data;
    uint32_t ctl0;
    uint32_t ctl1;
} ath9k_tx_desc_t;

typedef struct __attribute__((packed)) {
    uint32_t link;
    uint32_t data;
    uint32_t status0;
    uint32_t status1;
} ath9k_rx_desc_t;

typedef struct {
    ath9k_tx_desc_t *tx_ring;
    ath9k_rx_desc_t *rx_ring;
    uintptr_t tx_dma;
    uintptr_t rx_dma;
} ath9k_dma_t;

/** Allocate coherent descriptor rings and publish their addresses to hardware. */
int ath9k_dma_setup(ath9k_hw_t *hw, ath9k_dma_t *dma);
void ath9k_dma_teardown(ath9k_dma_t *dma);

#endif
