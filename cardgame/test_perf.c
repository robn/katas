#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "cardgame.h"

static void
run_perf_test(const size_t rounds, const uint8_t *testdata, const char *name, uint8_t (*play_round)(uint8_t, uint8_t, uint8_t))
{
  const uint8_t *p = testdata;
  struct timeval start, end;

  printf("perf test [%s]: ", name);

  gettimeofday(&start, 0);
  for (int i = 0; i < rounds; i++, p += 3)
    play_round(*p, *(p+1), *(p+2));
  gettimeofday(&end, 0);

  uint64_t delta =
    (end.tv_sec * 1000000llu + end.tv_usec) -
    (start.tv_sec * 1000000llu + start.tv_usec);

  double rps = ((double)delta / rounds) * 1000000.0;

  printf("%.02f r/s\n", rps);
}

void
run_perf_tests()
{
  static const size_t rounds = 100000000;
  uint8_t *testdata, *p;

  printf("generating %lu random games...\n", rounds);

  p = testdata = (uint8_t *) malloc(rounds*3);
  if (!testdata) {
    printf("E: out of memory!\n");
    return;
  }

  for (int i = 0; i < rounds; i++, p += 3)
    rand_game(p, p+1, p+2);

  run_perf_test(rounds, testdata, "ref", play_round_ref);
  run_perf_test(rounds, testdata, "bits", play_round_bits);

  free(testdata);
}
