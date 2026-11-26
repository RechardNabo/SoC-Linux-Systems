# SoC-Linux-Systems

Firmware/SoC skills lab - device-separated workspace for the home-lab plan
(`firmware-skills-home-lab-plan.md`, git-ignored working doc).

## Layout

| Path | Contents |
|---|---|
| `devices/<board>/` | One directory per board - all projects for that target live inside |
| `hil/` | Lab A: pytest hardware-in-the-loop framework + CI glue |
| `projects/mini-nic/` | Flagship: host driver + device firmware + spec (spans Pi 5 + PIC32MX795) |
| `tools/` | Host-side Python CLIs, flash/provision scripts, log analysis |
| `ci/` | Self-hosted runner config, provisioning, systemd units |
| `docs/` | reference/ (datasheets, pinouts), notes/ (code-reading, post-mortems), bug-journal/ (Lab H) |
| `legacy/` | Pre-restructure content: AI-IoT demos, Embedded_C, Node-APPS, Node-Red (kept as-is) |

## Devices

| Dir | Board | Lab focus |
|---|---|---|
| `devices/rpi5/` | Raspberry Pi 5 | Linux drivers C1-C4, PCIe, mini-NIC host, CI runner |
| `devices/rpi3b/` | Raspberry Pi 3B | Bare-metal AArch64 (B1) |
| `devices/rpi-zero/` | Raspberry Pi Zero | USB gadget (C3 alt) |
| `devices/bpi-m5/` | Banana Pi BPI-M5 | Boot chain/U-Boot (C5), SoftRoCE peer (D3) |
| `devices/esp32/` | ESP32 | Secure boot v2 + flash encryption (F2) |
| `devices/pic32mx795/` | PIC32MX795 Eth Starter Kit | Own MAC/PHY driver (B2), signed bootloader (F1), mini-NIC device |
| `devices/dspic30f6014/` | dsPIC30F6014 | Q15 DSP + bit-exact verify (G), I2C reg device (C2) |
| `devices/stm32-h563/` | STM32H563 | Cortex-M33 bare-metal, MPU/cache/ETH DMA (B3) |
| `devices/stm32-h755/` | STM32H755 | Dual-core M7+M4 mailbox (B3) |
| `devices/cyclone3-fpga/` | Cyclone III EP3C16F484C6N (DE0) | RTL + cocotb (E1), soft-core RISC-V (E2) |

## Lab tracks (from the plan)

- **A** HIL + CI - `hil/`  |  **B** bare-metal - `devices/{rpi3b,pic32mx795,stm32-*}`
- **C** Linux drivers - `devices/{rpi5,bpi-m5}` + QEMU on PC  |  **D** networking - `devices/bpi-m5` + scripts
- **E** RTL/RISC-V - `devices/cyclone3-fpga` + QEMU  |  **F** security - `devices/{pic32mx795,esp32,stm32-*}`
- **G** DSP - `devices/dspic30f6014`  |  **H** debug - `docs/bug-journal`
