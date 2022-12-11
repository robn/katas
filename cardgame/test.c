#include <stdlib.h>

#include "cardgame.h"

void
rand_game(uint8_t *card1, uint8_t *card2, uint8_t *trump)
{
  *card1 = rand() & (JOKER_MASK | SUIT_MASK | VALUE_MASK);
  if (*card1 & JOKER_MASK) *card1 = JOKER_MASK;
  *card2 = rand() & (JOKER_MASK | SUIT_MASK | VALUE_MASK);
  if (*card2 & JOKER_MASK) *card2 = JOKER_MASK;
  *trump = rand() & SUIT_MASK;
}

int
run_tests()
{
  int failed = 0;
  failed |= run_parse_tests();
  failed |= run_game_tests();
  if (failed)
    return failed;

  failed = run_comparison_tests();
  if (failed)
    return failed;

  run_perf_tests();

  return failed;
}
