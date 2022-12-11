#include <stdio.h>

#include "cardgame.h"

typedef struct {
  uint8_t card[6];
  uint8_t r;
} card_test_t;

const card_test_t card_tests[] = {
  { "2c",     SUIT_CLUB     | 2   },
  { "3C",     SUIT_CLUB     | 3   },
  { "4♣",     SUIT_CLUB     | 4   },
  { "5d",     SUIT_DIAMOND  | 5   },
  { "6D",     SUIT_DIAMOND  | 6   },
  { "7♦",     SUIT_DIAMOND  | 7   },
  { "8c",     SUIT_CLUB     | 8   },
  { "9C",     SUIT_CLUB     | 9   },
  { "10♣",    SUIT_CLUB     | 10  },
  { "Js",     SUIT_SPADE    | 11  },
  { "QS",     SUIT_SPADE    | 12  },
  { "K♠",     SUIT_SPADE    | 13  },
  { "A♠",     SUIT_SPADE    | 14  },
  { "joker",  JOKER_MASK          },
  { "JOKER",  JOKER_MASK          },
  { "JoKeR",  JOKER_MASK          },
  { "11h",    INVALID_CARD        },
  { "1c",     INVALID_CARD        },
  { "Q",      INVALID_CARD        },
  { "R♠",     INVALID_CARD        },
  { "" },
};

static int
run_card_tests()
{
  int failed = 0;

  for (const card_test_t *test = card_tests; test->card[0]; test++) {
    printf("card parser test: %s: ", test->card);

    uint8_t r = parse_card(test->card);
    if (r == test->r)
      printf("SUCCESS\n");
    else {
      printf("FAILED (expected %02x, got %02x)\n", test->r, r);
      failed |= 1;
    }
  }

  return failed;
}


typedef struct {
  uint8_t suit[4];
  uint8_t r;
} suit_test_t;

const suit_test_t suit_tests[] = {
  { "c",  SUIT_CLUB    },
  { "d",  SUIT_DIAMOND },
  { "h",  SUIT_HEART   },
  { "s",  SUIT_SPADE   },
  { "C",  SUIT_CLUB    },
  { "D",  SUIT_DIAMOND },
  { "H",  SUIT_HEART   },
  { "S",  SUIT_SPADE   },
  { "♣",  SUIT_CLUB    },
  { "♦",  SUIT_DIAMOND },
  { "♥",  SUIT_HEART   },
  { "♠",  SUIT_SPADE   },
  { "a",  INVALID_CARD },
  { "X",  INVALID_CARD },
  { "5",  INVALID_CARD },
  { "♧",  INVALID_CARD },
  { "cc", INVALID_CARD },
  { "" },
};

static int
run_suit_tests()
{
  int failed = 0;

  for (const suit_test_t *test = suit_tests; test->suit[0]; test++) {
    printf("suit parser test: %s: ", test->suit);

    uint8_t r = parse_suit(test->suit);
    if (r == test->r)
      printf("SUCCESS\n");
    else {
      printf("FAILED (expected %02x, got %02x)\n", test->r, r);
      failed |= 1;
    }
  }

  return failed;
}

int run_parse_tests()
{
  int failed = 0;
  failed |= run_suit_tests();
  failed |= run_card_tests();
  return failed;
}
