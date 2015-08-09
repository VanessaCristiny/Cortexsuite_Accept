TARGET := sphinx

LDFLAGS := -lm

CFLAGS := 

HEADERS := $(wildcard helper/*.h)

SOURCES := main.c $(wildcard includes/*.c) $(wildcard pocketsphinx/*.c) $(wildcard sphinxbase/fe/*.c) $(wildcard sphinxbase/feat/*.c) $(wildcard sphinxbase/lm/*.c)  $(wildcard sphinxbase/util/*.c) 

RUNARGS := small/audio.raw language_model/turtle/ out.txt

ACCEPT_DIR := ../../accept
include $(ACCEPT_DIR)/accept.mk