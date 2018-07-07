#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct benchmark_times{
	double last, lower, bigger, sum, mean;
	long count;
}benchmark_times_t;

typedef struct pcg_state_setseq_64 * benchmark_rng_t;

benchmark_rng_t benchmark_new_rng ();

bool benchmark_chance (char perc);

uint32_t benchmark_brand (uint32_t lb, uint32_t ub);
uint32_t benchmark_rand ();
uint32_t benchmark_rng_brand (benchmark_rng_t rng, uint32_t lb, uint32_t ub);
uint32_t benchmark_rng_rand (benchmark_rng_t rng);

void benchmark_seed (uint32_t seed);
void benchmark_seed_rand ();

void benchmark_pause (const char *message);

benchmark_times_t benchmark_times_new ();

void benchmark_times_update (benchmark_times_t *times, double time);

double benchmark_clock ();

double benchmark_gettime ();

double benchmark_brand_double (double lb, double up);

typedef enum benchmark_memory_OPT {
	BEFORE, CURR
} benchmark_memory_OPT;
uint64_t benchmark_memory (benchmark_memory_OPT WHERE);

#endif