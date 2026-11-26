# 27 — Flash LED (STM32H563 / NUCLEO-H563ZI)

Standalone firmware for kit module #27. Wiring: Nucleo Zio connectors,
pin table in `drivers/devices/kit/kit.h`. Host-verified device logic:
`drivers/tests/` (52 tests). Target build: inside a CubeMX-generated HAL
project (clocks + startup) — compose this main.c there. Status:
implemented.
