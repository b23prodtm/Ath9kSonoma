# Ath9kSonoma implementation tasks

1. Port the AR9285/AR9287/AR9380 register and reset sequences from `ath9k`.
2. Replace the physical-address placeholder in `ath9k_dma.c` with `IODMACommand` mappings.
3. Implement TX descriptor submission and completion handling.
4. Implement RX buffer replenishment and `inputPacket()` delivery.
5. Add interrupt filtering, deferred processing, and error recovery.
6. Implement per-chip PHY calibration and channel configuration.
7. Migrate the networking layer from the temporary `IOEthernetController` API to `IO80211Controller`.
8. Add hardware-independent unit tests for descriptor and register logic.

The kext is an intentionally incomplete, unsigned development skeleton. It must not be
loaded on a production system until hardware access, locking, power management, and
code-signing have been completed and reviewed.
