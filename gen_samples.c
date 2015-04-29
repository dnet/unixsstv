#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ALIAS_SIZE 1024

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <bits per sample>\n", argv[0]);
		exit(1);
	}
	int bits_per_sample = atoi(argv[1]);
	exit(gen_samples(bits_per_sample));
}

int gen_samples(const int bits_per_sample) {
	const double max_value = 1 << bits_per_sample;
	const double alias = 1.0 / max_value;
	const double amp = max_value / 2.0;
	double lowest = -amp;
	double highest = amp - 1.0;
	double alias_cache[ALIAS_SIZE];
	float input;
	double calc;
	int32_t output;
	uint16_t alias_index;
	uint8_t outbytes, outshift;

	outshift = 32 - bits_per_sample;
	outbytes = bits_per_sample / 8;

	for (alias_index = 0; alias_index < ALIAS_SIZE; alias_index++) {
		double rnd = ((double)random()) / (double)RAND_MAX;
		alias_cache[alias_index] = alias * (rnd - 0.5);
	}

	alias_index = 0;
	while (!feof(stdin)) {
		if (alias_index++ == ALIAS_SIZE) alias_index = 0;

		if (fread(&input, sizeof(input), 1, stdin) == 1) {
			calc = input * amp + alias_cache[alias_index];
			if (calc > highest) calc = highest;
			else if (calc < lowest) calc = lowest;
			output = calc;
			output >>= outshift;
			fwrite(&output, outbytes, 1, stdout);
		}
	}

	return 0;
}
