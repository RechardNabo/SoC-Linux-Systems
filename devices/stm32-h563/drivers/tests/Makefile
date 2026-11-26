# Makefile — native gcc mirror of the Ceedling suite. No Ruby needed.
CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -std=c99 -g -DUNIT_TEST_HOST
UNITY   := vendor/unity/unity.c
SUPPORT := unit/support/mock_sfr.c
INC     := -Ivendor/unity -Iunit/support -I..

MODULES := gpio uart spi i2c tim
BINS    := $(MODULES:%=build/test_stm_%)

all: $(BINS) run

build:
	mkdir -p build

build/test_stm_%: unit/test_stm_%.c $(UNITY) $(SUPPORT) | build
	$(CC) $(CFLAGS) $(INC) -o $@ $< ../peripherals/$*/stm_$*.c $(UNITY) $(SUPPORT)

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
