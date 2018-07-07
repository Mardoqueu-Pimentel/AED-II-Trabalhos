#include <benchmark.h>
#include <float.h>
#include <pcg_basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

static void seed () {
	pcg32_srandom(rand(), rand());
}

static void seed_rng (pcg32_random_t *rng) {
	pcg32_srandom_r(rng, rand(), rand());
}

static void printUsage () {	
	struct rusage r_usage;
	getrusage(RUSAGE_SELF, &r_usage);
	// Print the maximum resident set size used (in kilobytes).
	fprintf(stderr, "Memory usage: %ld kilobytes\n", r_usage.ru_maxrss);
}

benchmark_rng_t benchmark_new_rng () {
	benchmark_rng_t rng = (benchmark_rng_t) malloc(sizeof(pcg32_random_t));
	pcg32_srandom_r(rng, rand(), rand());
	return rng;
}

bool benchmark_chance (char perc) {
	static pcg32_random_t rng;
	static bool seeded = false;

	if (seeded == false) {
		seed_rng (&rng);
		seeded = true;
	}

	return pcg32_boundedrand_r(&rng, 101) <= perc;
}

uint32_t benchmark_brand (uint32_t lb, uint32_t ub) {
	static pcg32_random_t rng;
	static bool seeded = false;

	if (seeded == false) {
		seed_rng(&rng);
		seeded = true;
	}

	return lb + pcg32_boundedrand_r(&rng, ub - lb);
}

uint32_t benchmark_rand () {
	static bool seeded = false;
	
	if (seeded == false) {
		seed ();
		seeded = true;
	}

	return pcg32_random();
}

double benchmark_brand_double (double lb, double up) {
	static pcg32_random_t rng_frac;
	static bool seeded = false;

	if (seeded == false) {
		seed_rng(&rng_frac);
		seeded = true;
	}

	double frac = benchmark_rng_brand(&rng_frac, 1, 0x7FFFFFFF) / (double) 0x7FFFFFFF;
	
	return lb + ((up - lb) * frac);
}

uint32_t benchmark_rng_brand (benchmark_rng_t rng, uint32_t lb, uint32_t ub) {
	return lb + pcg32_boundedrand_r(rng, ub - lb);
}

uint32_t benchmark_rng_rand (benchmark_rng_t rng) {
	return pcg32_random_r(rng);
}

void benchmark_seed (uint32_t seed) {
	srand(seed);
}

void benchmark_seed_rand () {
	srand(time(NULL));
}

void benchmark_pause (const char *message) {
	fprintf(stderr, message);
	printUsage();
	getchar();
}

benchmark_times_t benchmark_times_new () {
	return (benchmark_times_t) { 0.0, DBL_MAX, 0.0, 0.0, 0.0, 0 };
}

void benchmark_times_update (benchmark_times_t *times, double new_time) {
	times->sum += new_time;	
	times->last = new_time;	
	times->count += 1;

	times->lower = (new_time < times->lower) ? new_time : times->lower;
	times->bigger = (new_time > times->bigger) ? new_time : times->bigger;
	times->mean = times->sum / times->count;
}

double benchmark_clock () {
	static clock_t begin, end;
	static char mode = 1;

	if (mode) {
		mode = 0;
		begin = clock();
	} else {
		end = clock();
		mode = 1;		
		
		return ( ((double)(end - begin)) / CLOCKS_PER_SEC ) * 1000;
	}

	return 0;
}

double benchmark_gettime () {	
	static struct timespec begin, end;
	static char mode = 1;

	if (mode) {	
		mode = 0;
		clock_gettime(CLOCK_MONOTONIC, &begin);				
	} else {
		clock_gettime(CLOCK_MONOTONIC, &end);
		mode = 1;
		return 1e3*(end.tv_sec - begin.tv_sec) + 1e-6*(end.tv_nsec - begin.tv_nsec);
	}

	return 0;
}

uint64_t benchmark_memory (benchmark_memory_OPT WHERE) {
	static struct rusage usage_before;
	static struct rusage usage_curr;

	if (WHERE == BEFORE) {
		getrusage(RUSAGE_SELF, &usage_before);
		return usage_before.ru_maxrss;
	} else {
		getrusage(RUSAGE_SELF, &usage_curr);
		return usage_before.ru_maxrss - usage_curr.ru_maxrss;
	}
}