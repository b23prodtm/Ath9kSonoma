# Ath9kSonoma

This repository contains an intentionally incomplete macOS Sonoma kernel-extension
skeleton for Atheros AR9285, AR9287, and AR9380 devices. It adapts the register and
hardware sequencing concepts from Linux `ath9k` to IOKit and temporarily exposes an
`IOEthernetController`; the network and PHY paths are marked with TODOs.

## Build

Open `Ath9kSonoma.xcodeproj` in Xcode 15 or newer and build the `Ath9kSonoma` target
with the macOS 14 SDK. CircleCI performs the same build on every push. The resulting
kext is unsigned and is not suitable for installation without completing the driver,
reviewing hardware access, and signing it manually.

See [TASKS.md](TASKS.md) for the implementation order.