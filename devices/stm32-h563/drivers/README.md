# STM32H563 Peripheral Driver Library

Register-level drivers for STM32H563 (Cortex-M33, 250 MHz) — the register-
level counterpart to the MPT-Firmware-1U-BTS-POPO project's HAL drivers,
host-verified bit-exact. Fifth architecture family in the driver-library
program (after PIC32MX795, dsPIC30F6014, ESP32, RP2040).

## Modules (21 host tests green — gcc mirror)

| Peripheral | Channels | Tests | What the tests pin down |
|---|---|---|---|
| GPIO | ports A-H | 5 | MODER 2-bit fields preserving other pins, BSRR atomic set/reset, toggle roundtrip |
| USART | 1-3 | 4 | direct BRR divisor (no fractional table — simplest hardware, highest clock), config-while-disabled ordering |
| SPI master | 1-2 | 4 | power-of-two baud quantization honestly exposed, DSIZE-1 encoding, CPOL/CPHA orthogonality |
| I2C master | 1-2 | 4 | TIMINGR five-field packing, prescaler escalation when counts overflow, PE-before-TIMINGR rule |
| TIM PWM | 2-5 | 4 | PSC/ARR solver maximizing resolution within 16-bit-safe range, value+1 double encoding, shadow-load UG |

## The STM32H5-specific traps this library absorbs

1. **TIMINGR is five packed fields** — SCLL/SCLH/SDADEL/SCLDEL/PRESC in one
   register with non-obvious valid combinations. The driver computes with
   prescaler escalation and exposes the decomposition for verification.
2. **PSC and ARR are BOTH value+1 encoded** — the double minus-one in
   `f = clk/((psc+1)(arr+1))` is the classic off-by-two timer bug.
3. **Config-while-disabled is silicon-enforced** — USART CR1, I2C TIMINGR,
   SPI CFGx all ignore writes while enabled. The init sequences disable,
   configure, enable-last uniformly.
4. **SPI baud is power-of-two only** — asking for 10 MHz at 250 MHz sysclk
   yields 7.8125 MHz, not 10. The driver exposes `actual_clock()` rather
   than pretending — the caller decides whether the quantization is
   acceptable, same honesty contract as the dsPIC CAN driver.
5. **BSRR write-only atomicity** — single-instruction set/reset, no RMW;
   the mock models it consuming pending writes on ODR access.

## Honest scope

- Host-verified only; CubeIDE/ARM GCC target compilation not yet proven
- SPI register bit layout per RM0481 documented as owed target verification
- ADC/DMA/GPDMA/HASH/ETH out of scope this pass — the MPT reference shows
  these in HAL form; porting them to register level is the natural next batch
- TIM coverage limited to channels 1-2 PWM on TIM2-5; encoders, input
  capture, advanced TIM1/8 dead-time are follow-on work
