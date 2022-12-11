#include <stdio.h>

#include "cardgame.h"

int
run_comparison_tests()
{
  int failed = 0;

  for (int i = 0; i < 1000000; i++) {
    uint8_t card1, card2, trump;
    rand_game(&card1, &card2, &trump);

    uint8_t r_ref = play_round_ref(card1, card2, trump);
    uint8_t r_bits = play_round_bits(card1, card2, trump);

    if (!(
      (RESULT_OK(r_ref, R_SAME)  && RESULT_OK(r_bits, R_SAME)) ||
      (RESULT_OK(r_ref, R_NONE)  && RESULT_OK(r_bits, R_NONE)) ||
      (RESULT_OK(r_ref, R_CARD1) && RESULT_OK(r_bits, R_CARD1)) ||
      (RESULT_OK(r_ref, R_CARD2) && RESULT_OK(r_bits, R_CARD2))
    )) {
      printf("comparison test: FAILED: card1=%02x card2=%02x trump=%02x; ref=%02x bits=%02x\n", card1, card2, trump, r_ref, r_bits);
      failed |= 1;
    }
  }

  if (!failed) {
    printf("comparison test: SUCCESS\n");
  }

  return failed;
}
