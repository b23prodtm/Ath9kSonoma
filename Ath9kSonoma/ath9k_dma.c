#include "ath9k_dma.h"
#include <libkern/OSMalloc.h>

int ath9k_dma_setup(ath9k_hw_t *hw, ath9k_dma_t *dma) {
    if (hw == 0 || dma == 0 || hw->write == 0) {
        return -1;
    }
    dma->tx_ring = (ath9k_tx_desc_t *)IOMallocAligned(sizeof(ath9k_tx_desc_t) * ATH9K_RING_SIZE, 4096);
    dma->rx_ring = (ath9k_rx_desc_t *)IOMallocAligned(sizeof(ath9k_rx_desc_t) * ATH9K_RING_SIZE, 4096);
    if (dma->tx_ring == 0 || dma->rx_ring == 0) {
        ath9k_dma_teardown(dma);
        return -1;
    }
    bzero(dma->tx_ring, sizeof(ath9k_tx_desc_t) * ATH9K_RING_SIZE);
    bzero(dma->rx_ring, sizeof(ath9k_rx_desc_t) * ATH9K_RING_SIZE);
    /* TODO: replace virtual-address placeholders with IODMACommand mappings. */
    dma->tx_dma = (uintptr_t)dma->tx_ring;
    dma->rx_dma = (uintptr_t)dma->rx_ring;
    hw->write(hw->context, AR_TXDP0, (uint32_t)dma->tx_dma);
    hw->write(hw->context, AR_RXDP, (uint32_t)dma->rx_dma);
    return 0;
}

void ath9k_dma_teardown(ath9k_dma_t *dma) {
    if (dma == 0) {
        return;
    }
    if (dma->tx_ring != 0) IOFreeAligned(dma->tx_ring, sizeof(ath9k_tx_desc_t) * ATH9K_RING_SIZE);
    if (dma->rx_ring != 0) IOFreeAligned(dma->rx_ring, sizeof(ath9k_rx_desc_t) * ATH9K_RING_SIZE);
    dma->tx_ring = 0;
    dma->rx_ring = 0;
}
