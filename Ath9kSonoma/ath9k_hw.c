#include "ath9k_hw.h"

static void ath9k_hw_delay(void) {
    for (volatile unsigned int i = 0; i < 10000; ++i) {
    }
}

int ath9k_hw_reset(ath9k_hw_t *hw) {
    if (hw == 0 || hw->read == 0 || hw->write == 0) {
        return -1;
    }
    hw->write(hw->context, AR_RTC_RESET, AR_RTC_RESET_EN);
    ath9k_hw_delay();
    hw->write(hw->context, AR_RTC_RESET, 0);
    for (unsigned int i = 0; i < 100; ++i) {
        if (hw->read(hw->context, AR_RTC_STATUS) & AR_RTC_STATUS_ON) {
            return 0;
        }
        ath9k_hw_delay();
    }
    return -1;
}

int ath9k_hw_init(ath9k_hw_t *hw) {
    if (hw == 0 || hw->read == 0 || hw->write == 0) {
        return -1;
    }
    (void)hw->read(hw->context, AR_SREV);
    if (ath9k_hw_reset(hw) != 0) {
        return -1;
    }
    hw->write(hw->context, AR_DIAG, AR_DIAG_SW_DIS_WEP);
    hw->write(hw->context, AR_CFG, 0);
    return 0;
}
