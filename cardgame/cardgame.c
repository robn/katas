#include <stdio.h>

#include "cardgame.h"

int
main(int argc, char **argv)
{
  if (argc == 1) {
    int failed = run_tests();
    return failed;
  }

  if (argc != 4) {
    printf("usage: cardgame <card1> <card2> <trump suit>\n");
    return 1;
  }

  uint8_t card1 = parse_card((uint8_t *)argv[1]);
  if (card1 == INVALID_CARD) {
    printf("E: card1 is not a valid card\n");
    return 1;
  }

  uint8_t card2 = parse_card((uint8_t *)argv[2]);
  if (card1 == INVALID_CARD) {
    printf("E: card2 is not a valid card\n");
    return 1;
  }

  uint8_t trump = parse_suit((uint8_t *)argv[3]);
  if (card1 == INVALID_CARD) {
    printf("E: trump is not a valid suit\n");
    return 1;
  }

  uint8_t r = play_round_bits(card1, card2, trump);

  if (RESULT_OK(r, R_NONE))
      printf("Let us play again.\n");
  else if (RESULT_OK(r, R_SAME))
      printf("Someone cheats.\n");
  else if (RESULT_OK(r, R_CARD1))
      printf("The first card won.\n");
  else if (RESULT_OK(r, R_CARD2))
      printf("The second card won.\n");
  else {
      printf("Impossible result %02x, please tell robn what you did!\n", r);
      return 1;
  }

  return 0;
}
