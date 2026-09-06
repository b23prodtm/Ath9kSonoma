#ifndef ATH9K_HW_H
#define ATH9K_HW_H

#include <stdint.h>

#define AR_SREV        0x0000
#define AR_CR          0x0008
#define AR_CFG         0x0014
#define AR_DIAG        0x001C
#define AR_ISR         0x0020
#define AR_IMR         0x0024
#define AR_TXDP(_q)    (0x0800 + ((_q) * 4))
#define AR_TXDP0       AR_TXDP(0)
#define AR_TXDP1       AR_TXDP(1)
#define AR_TXDP2       AR_TXDP(2)
#define AR_TXDP3       AR_TXDP(3)
#define AR_TXDP4       AR_TXDP(4)
#define AR_TXDP5       AR_TXDP(5)
#define AR_TXDP6       AR_TXDP(6)
#define AR_TXDP7       AR_TXDP(7)
#define AR_RXDP        0x0C00
#define AR_RTC_RESET   0x7000
#define AR_RTC_STATUS  0x7004

#define AR_CR_RXE      0x00000004
#define AR_CR_RXD      0x00000020
#define AR_RTC_RESET_EN 0x00000001
#define AR_RTC_STATUS_ON 0x00000001
#define AR_DIAG_SW_DIS_WEP 0x00000000

typedef uint32_t (*ath9k_read_register_t)(void *context, uint32_t reg);
typedef void (*ath9k_write_register_t)(void *context, uint32_t reg, uint32_t value);

typedef struct {
    void *context;
    ath9k_read_register_t read;
    ath9k_write_register_t write;
} ath9k_hw_t;

/** Initialize the device and apply the common RTC configuration. */
int ath9k_hw_init(ath9k_hw_t *hw);
/** Perform a complete RTC reset cycle and wait for the device to become ready. */
int ath9k_hw_reset(ath9k_hw_t *hw);

#endif
