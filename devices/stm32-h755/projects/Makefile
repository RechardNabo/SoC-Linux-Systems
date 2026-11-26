# Makefile — native gcc mirror for the 35 module projects (STM32H563).
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -std=c99 -g -DUNIT_TEST_HOST
TDIR    := ../drivers/tests
UNITY   := $(TDIR)/vendor/unity/unity.c
SUPPORT := $(TDIR)/unit/support/mock_sfr.c
INC     := -I$(TDIR)/vendor/unity -I$(TDIR)/unit/support -I../drivers -Ilib

DEVSRC := ../drivers/devices/dig_in/dig_in.c ../drivers/devices/analog_in/analog_in.c \
          ../drivers/devices/dig_out/dig_out.c ../drivers/devices/pwm_out/pwm_out.c \
          ../drivers/devices/quad_enc/quad_enc.c ../drivers/devices/kit/kit.c \
          ../drivers/devices/pal/devpal.c \
          ../drivers/peripherals/gpio/stm_gpio.c ../drivers/peripherals/adc/stm_adc.c \
          ../drivers/peripherals/tim/stm_tim.c
LIBSRC := lib/blink.c lib/edge_count.c lib/hysteresis.c lib/colorwheel.c lib/sequencer.c lib/peak_detect.c

BINS := build/test_01_joystick build/test_02_ir_receiver build/test_03_laser build/test_04_dht11 build/test_05_ir_proximity build/test_06_relay build/test_07_obstacle build/test_08_heartbeat build/test_09_sound_analog build/test_10_touch build/test_11_flame build/test_12_rgb_led build/test_13_line build/test_14_hall_linear build/test_15_rotary_encoder build/test_16_buzzer_active build/test_17_magic_cup build/test_18_buzzer_passive build/test_19_ds18b20 build/test_20_broken_light build/test_21_lm35 build/test_22_dual_led build/test_23_mercury build/test_24_hall_switch build/test_25_reed_rgb build/test_26_tilt build/test_27_flash_led build/test_28_button build/test_29_ldr build/test_30_vibration build/test_31_knock build/test_32_lm35_b build/test_33_hall_linear_b build/test_34_mic_sound build/test_35_reed_big

all: $(BINS) run

build:
	mkdir -p build

build/test_01_joystick: 01_joystick/test_joystick_app.c 01_joystick/joystick_app.c | build
	$(CC) $(CFLAGS) $(INC) -I01_joystick -o $@ $< 01_joystick/joystick_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_02_ir_receiver: 02_ir_receiver/test_ir_receiver_app.c 02_ir_receiver/ir_receiver_app.c | build
	$(CC) $(CFLAGS) $(INC) -I02_ir_receiver -o $@ $< 02_ir_receiver/ir_receiver_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_03_laser: 03_laser/test_laser_app.c 03_laser/laser_app.c | build
	$(CC) $(CFLAGS) $(INC) -I03_laser -o $@ $< 03_laser/laser_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_04_dht11: 04_dht11/test_dht11_app.c 04_dht11/dht11_app.c | build
	$(CC) $(CFLAGS) $(INC) -I04_dht11 -o $@ $< 04_dht11/dht11_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_05_ir_proximity: 05_ir_proximity/test_ir_proximity_app.c 05_ir_proximity/ir_proximity_app.c | build
	$(CC) $(CFLAGS) $(INC) -I05_ir_proximity -o $@ $< 05_ir_proximity/ir_proximity_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_06_relay: 06_relay/test_relay_app.c 06_relay/relay_app.c | build
	$(CC) $(CFLAGS) $(INC) -I06_relay -o $@ $< 06_relay/relay_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_07_obstacle: 07_obstacle/test_obstacle_app.c 07_obstacle/obstacle_app.c | build
	$(CC) $(CFLAGS) $(INC) -I07_obstacle -o $@ $< 07_obstacle/obstacle_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_08_heartbeat: 08_heartbeat/test_heartbeat_app.c 08_heartbeat/heartbeat_app.c | build
	$(CC) $(CFLAGS) $(INC) -I08_heartbeat -o $@ $< 08_heartbeat/heartbeat_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_09_sound_analog: 09_sound_analog/test_sound_analog_app.c 09_sound_analog/sound_analog_app.c | build
	$(CC) $(CFLAGS) $(INC) -I09_sound_analog -o $@ $< 09_sound_analog/sound_analog_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_10_touch: 10_touch/test_touch_app.c 10_touch/touch_app.c | build
	$(CC) $(CFLAGS) $(INC) -I10_touch -o $@ $< 10_touch/touch_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_11_flame: 11_flame/test_flame_app.c 11_flame/flame_app.c | build
	$(CC) $(CFLAGS) $(INC) -I11_flame -o $@ $< 11_flame/flame_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_12_rgb_led: 12_rgb_led/test_rgb_led_app.c 12_rgb_led/rgb_led_app.c | build
	$(CC) $(CFLAGS) $(INC) -I12_rgb_led -o $@ $< 12_rgb_led/rgb_led_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_13_line: 13_line/test_line_app.c 13_line/line_app.c | build
	$(CC) $(CFLAGS) $(INC) -I13_line -o $@ $< 13_line/line_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_14_hall_linear: 14_hall_linear/test_hall_linear_app.c 14_hall_linear/hall_linear_app.c | build
	$(CC) $(CFLAGS) $(INC) -I14_hall_linear -o $@ $< 14_hall_linear/hall_linear_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_15_rotary_encoder: 15_rotary_encoder/test_rotary_encoder_app.c 15_rotary_encoder/rotary_encoder_app.c | build
	$(CC) $(CFLAGS) $(INC) -I15_rotary_encoder -o $@ $< 15_rotary_encoder/rotary_encoder_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_16_buzzer_active: 16_buzzer_active/test_buzzer_active_app.c 16_buzzer_active/buzzer_active_app.c | build
	$(CC) $(CFLAGS) $(INC) -I16_buzzer_active -o $@ $< 16_buzzer_active/buzzer_active_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_17_magic_cup: 17_magic_cup/test_magic_cup_app.c 17_magic_cup/magic_cup_app.c | build
	$(CC) $(CFLAGS) $(INC) -I17_magic_cup -o $@ $< 17_magic_cup/magic_cup_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_18_buzzer_passive: 18_buzzer_passive/test_buzzer_passive_app.c 18_buzzer_passive/buzzer_passive_app.c | build
	$(CC) $(CFLAGS) $(INC) -I18_buzzer_passive -o $@ $< 18_buzzer_passive/buzzer_passive_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_19_ds18b20: 19_ds18b20/test_ds18b20_app.c 19_ds18b20/ds18b20_app.c | build
	$(CC) $(CFLAGS) $(INC) -I19_ds18b20 -o $@ $< 19_ds18b20/ds18b20_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_20_broken_light: 20_broken_light/test_broken_light_app.c 20_broken_light/broken_light_app.c | build
	$(CC) $(CFLAGS) $(INC) -I20_broken_light -o $@ $< 20_broken_light/broken_light_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_21_lm35: 21_lm35/test_lm35_app.c 21_lm35/lm35_app.c | build
	$(CC) $(CFLAGS) $(INC) -I21_lm35 -o $@ $< 21_lm35/lm35_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_22_dual_led: 22_dual_led/test_dual_led_app.c 22_dual_led/dual_led_app.c | build
	$(CC) $(CFLAGS) $(INC) -I22_dual_led -o $@ $< 22_dual_led/dual_led_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_23_mercury: 23_mercury/test_mercury_app.c 23_mercury/mercury_app.c | build
	$(CC) $(CFLAGS) $(INC) -I23_mercury -o $@ $< 23_mercury/mercury_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_24_hall_switch: 24_hall_switch/test_hall_switch_app.c 24_hall_switch/hall_switch_app.c | build
	$(CC) $(CFLAGS) $(INC) -I24_hall_switch -o $@ $< 24_hall_switch/hall_switch_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_25_reed_rgb: 25_reed_rgb/test_reed_rgb_app.c 25_reed_rgb/reed_rgb_app.c | build
	$(CC) $(CFLAGS) $(INC) -I25_reed_rgb -o $@ $< 25_reed_rgb/reed_rgb_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_26_tilt: 26_tilt/test_tilt_app.c 26_tilt/tilt_app.c | build
	$(CC) $(CFLAGS) $(INC) -I26_tilt -o $@ $< 26_tilt/tilt_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_27_flash_led: 27_flash_led/test_flash_led_app.c 27_flash_led/flash_led_app.c | build
	$(CC) $(CFLAGS) $(INC) -I27_flash_led -o $@ $< 27_flash_led/flash_led_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_28_button: 28_button/test_button_app.c 28_button/button_app.c | build
	$(CC) $(CFLAGS) $(INC) -I28_button -o $@ $< 28_button/button_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_29_ldr: 29_ldr/test_ldr_app.c 29_ldr/ldr_app.c | build
	$(CC) $(CFLAGS) $(INC) -I29_ldr -o $@ $< 29_ldr/ldr_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_30_vibration: 30_vibration/test_vibration_app.c 30_vibration/vibration_app.c | build
	$(CC) $(CFLAGS) $(INC) -I30_vibration -o $@ $< 30_vibration/vibration_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_31_knock: 31_knock/test_knock_app.c 31_knock/knock_app.c | build
	$(CC) $(CFLAGS) $(INC) -I31_knock -o $@ $< 31_knock/knock_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_32_lm35_b: 32_lm35_b/test_lm35_b_app.c 32_lm35_b/lm35_b_app.c | build
	$(CC) $(CFLAGS) $(INC) -I32_lm35_b -o $@ $< 32_lm35_b/lm35_b_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_33_hall_linear_b: 33_hall_linear_b/test_hall_linear_b_app.c 33_hall_linear_b/hall_linear_b_app.c | build
	$(CC) $(CFLAGS) $(INC) -I33_hall_linear_b -o $@ $< 33_hall_linear_b/hall_linear_b_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_34_mic_sound: 34_mic_sound/test_mic_sound_app.c 34_mic_sound/mic_sound_app.c | build
	$(CC) $(CFLAGS) $(INC) -I34_mic_sound -o $@ $< 34_mic_sound/mic_sound_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)
build/test_35_reed_big: 35_reed_big/test_reed_big_app.c 35_reed_big/reed_big_app.c | build
	$(CC) $(CFLAGS) $(INC) -I35_reed_big -o $@ $< 35_reed_big/reed_big_app.c $(DEVSRC) $(LIBSRC) $(UNITY) $(SUPPORT)

run: $(BINS)
	@total=0; fail=0; \
	for b in $(BINS); do \
		out=$$(./$$b); echo "$$out" | tail -1; \
		n=$$(echo "$$out" | grep -oE '^[0-9]+ Tests' | grep -oE '^[0-9]+'); \
		f=$$(echo "$$out" | grep -oE '[0-9]+ Failures' | grep -oE '^[0-9]+'); \
		total=$$((total+n)); fail=$$((fail+f)); \
	done; \
	echo "== projects total: $$total tests, $$fail failures =="; \
	test $$fail -eq 0

clean:
	rm -rf build

.PHONY: all run clean
