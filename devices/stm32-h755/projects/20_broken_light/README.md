# 20 — Light-Break (STM32H755 / NUCLEO-H755ZI-Q)

Standalone firmware for kit module #20. Wiring: Nucleo Zio connectors — M7 core owns app peripherals,
pin table in `drivers/devices/kit/kit.h`. Host-verified device logic:
`drivers/tests/` (60 tests). Target build: inside a CubeMX-generated HAL
project (clocks + startup) — compose this main.c there. Status:
implemented.
