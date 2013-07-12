BINARIES=gen_samples

gen_samples: gen_samples.c

clean:
	rm -r $(BINARIES)

.PHONY: clean
