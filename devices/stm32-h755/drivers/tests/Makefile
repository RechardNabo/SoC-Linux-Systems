# Makefile — native gcc mirror of the Ceedling suite. No Ruby needed.
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -std=c99 -g -DUNIT_TEST_HOST
UNITY   := vendor/unity/unity.c
SUPPORT := unit/support/mock_sfr.c
INC     := -Ivendor/unity -Iunit/support -I..

MODULES := gpio uart spi i2c tim adc hsem dev_dig_in dev_dig_out dev_analog_in dev_pwm_out dev_quad_enc dev_kit app_climate app_alarm
BINS    := $(MODULES:%=build/test_%)

all: $(BINS) run

build:
	mkdir -p build

DEVPAL := ../devices/pal/devpal.c
GPIODRV := ../peripherals/gpio/stm_gpio.c

build/test_gpio: unit/test_stm_gpio.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../peripherals/gpio/stm_gpio.c $(UNITY) $(SUPPORT)
build/test_uart: unit/test_stm_uart.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../peripherals/uart/stm_uart.c $(UNITY) $(SUPPORT)
build/test_spi: unit/test_stm_spi.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../peripherals/spi/stm_spi.c $(UNITY) $(SUPPORT)
build/test_i2c: unit/test_stm_i2c.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../peripherals/i2c/stm_i2c.c $(UNITY) $(SUPPORT)
build/test_tim: unit/test_stm_tim.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../peripherals/tim/stm_tim.c $(UNITY) $(SUPPORT)
build/test_adc: unit/test_stm_adc.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../peripherals/adc/stm_adc.c $(UNITY) $(SUPPORT)
build/test_hsem: unit/test_stm_hsem.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../peripherals/hsem/stm_hsem.c $(UNITY) $(SUPPORT)
build/test_dev_dig_in: unit/test_dev_dig_in.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../devices/dig_in/dig_in.c $(DEVPAL) $(GPIODRV) $(UNITY) $(SUPPORT)
build/test_dev_dig_out: unit/test_dev_dig_out.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../devices/dig_out/dig_out.c $(DEVPAL) $(GPIODRV) $(UNITY) $(SUPPORT)
build/test_dev_analog_in: unit/test_dev_analog_in.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../devices/analog_in/analog_in.c ../devices/kit/kit.c ../peripherals/adc/stm_adc.c $(UNITY) $(SUPPORT)
build/test_dev_pwm_out: unit/test_dev_pwm_out.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../devices/pwm_out/pwm_out.c ../peripherals/tim/stm_tim.c $(UNITY) $(SUPPORT)
build/test_dev_quad_enc: unit/test_dev_quad_enc.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../devices/quad_enc/quad_enc.c $(DEVPAL) $(GPIODRV) $(UNITY) $(SUPPORT)
build/test_dev_kit: unit/test_dev_kit.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../devices/kit/kit.c $(DEVPAL) $(GPIODRV) $(UNITY) $(SUPPORT)
build/test_app_climate: unit/test_app_climate.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../apps/climate_station/climate_station.c ../devices/analog_in/analog_in.c ../devices/pwm_out/pwm_out.c ../devices/kit/kit.c ../peripherals/adc/stm_adc.c ../peripherals/tim/stm_tim.c $(UNITY) $(SUPPORT)
build/test_app_alarm: unit/test_app_alarm.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../apps/security_alarm/security_alarm.c $(UNITY) $(SUPPORT)

run: $(BINS)
	@total=0; fail=0; \
	for b in $(BINS); do \
		out=$$(./$$b); echo "$$out" | tail -1; \
		n=$$(echo "$$out" | grep -oE '^[0-9]+ Tests' | grep -oE '^[0-9]+'); \
		f=$$(echo "$$out" | grep -oE '[0-9]+ Failures' | grep -oE '^[0-9]+'); \
		total=$$((total+n)); fail=$$((fail+f)); \
	done; \
	echo "== mirror total: $$total tests, $$fail failures =="; \
	test $$fail -eq 0

clean:
	rm -rf build

.PHONY: all run clean
