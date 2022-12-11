#include <stdio.h>

#include "cardgame.h"

typedef struct {
  uint8_t   card1[6];
  uint8_t   card2[6];
  uint8_t   trump[4];
  uint8_t   r;
} game_test_t;

const game_test_t game_tests[] = {
  { "3♣",     "Q♣",     "♦",  R_CARD2,  },
  { "5♥",     "A♣",     "♦",  R_NONE,   },
  { "8♠",     "8♠",     "♣",  R_SAME,   },
  { "2♦",     "A♠",     "♦",  R_CARD1,  },
  { "joker",  "joker",  "♦",  R_SAME,   },
  { "joker",  "A♠",     "♠",  R_CARD1,  },
  { "7♦",     "10♦",    "♦",  R_CARD2,  },
  { "6♦",     "joker",  "♠",  R_CARD2,  },
  { "Q♣",     "3♣",     "♥",  R_CARD1,  },
  { "" },
};

static int
run_game_test(const char *name, uint8_t (*play_round)(uint8_t, uint8_t, uint8_t))
{
  int failed = 0;

  for (const game_test_t *test = game_tests; test->card1[0]; test++) {
    printf("game test [%s]: %s %s %s: ", name, test->card1, test->card2, test->trump);

    uint8_t card1 = parse_card(test->card1);
    uint8_t card2 = parse_card(test->card2);
    uint8_t trump = parse_suit(test->trump);

    if ((card1 | card2 | trump) == INVALID_CARD) {
      printf("FAILED (parse failed, got %02x %02x %02x)\n", card1, card2, trump);
      failed |= 1;
      continue;
    }

    uint8_t r = play_round(card1, card2, trump);

    if (RESULT_OK(r, test->r))
      printf("SUCCESS\n");
    else {
      printf("FAILED: card1=%02x card2=%02x trump=%02x; expected=%02x got=%02x\n", card1, card2, trump, test->r, r);
      failed |= 1;
    }
  }

  return failed;
}

int
run_game_tests()
{
  int failed = 0;
  failed |= run_game_test("ref", play_round_ref);
  failed |= run_game_test("bits", play_round_bits);
  return failed;
}
