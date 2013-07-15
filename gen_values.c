#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct freq_tuple {
	float freq;
	float msec;
} freq_tuple_t;

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <samples per second>\n", argv[0]);
		exit(1);
	}
	int samples_per_second = atoi(argv[1]);
	exit(gen_values(samples_per_second));
}

int gen_values(int samples_per_second) {
	double spms = ((double)samples_per_second) / 1000.0;
	double offset = 0.0;
	double factor = 2.0 * M_PI / ((double)samples_per_second);
	double freq_factor;
	double samples = 0.0;
	freq_tuple_t input;
	float output;
	int sample, tx;

	while (!feof(stdin)) {
		if (fread(&input, sizeof(freq_tuple_t), 1, stdin) == 1) {
			samples += spms * input.msec;
			tx = (int)samples;
			freq_factor = input.freq * factor;
			for (sample = 0; sample < tx; sample++) {
				output = sinf(sample * freq_factor + offset);
				fwrite(&output, sizeof(output), 1, stdout);
			}
			offset += sample * freq_factor;
			samples -= tx;
		}
	}

	return 0;
}
