.DEFAULT_GOAL := fdr

TARGET=fdr

CPPFLAGS+=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

CFLAGS+=-std=c11

LDLIBS+=-lm -lssl -lcrypto

.PHONY: clean debug profile

clean: 
	rm $(TARGET)
debug: 
	CFLAGS+=-g

profile: 
	FLAGS+=-pg

