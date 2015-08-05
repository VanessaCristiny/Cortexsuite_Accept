TARGET := lda

CFLAGS  := -O2

LDFLAGS := -lm

SOURCES := $(wildcard *.c) includes/photonTiming.c

RUNGS := output.txt est .1 3 settings.txt small/small_data.dat

ACCEPT_DIR := ../../accept
include $(ACCEPT_DIR)/accept.mk

