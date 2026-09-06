#ifndef ATH9K_PHY_H
#define ATH9K_PHY_H
typedef struct { unsigned int channel; } ath9k_phy_t;
int ath9k_phy_calibrate(ath9k_phy_t *phy);
#endif
