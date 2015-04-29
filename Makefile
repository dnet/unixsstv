BINARIES=gen_samples gen_values
CFLAGS+=-O2 -march=native
LDFLAGS+=-lm

all: $(BINARIES)

gen_samples: gen_samples.c

gen_values: gen_values.c

clean:
	rm -r $(BINARIES)

.PHONY: clean
