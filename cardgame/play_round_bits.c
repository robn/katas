#include "cardgame.h"

static inline uint8_t
bitwise_true(uint8_t v) {
  v |= v >> 4;
  v |= v >> 2;
  v |= v >> 1;
  v = ~v & 0x1;
  return v;
}

/* constant time bit swizzling version */
uint8_t
play_round_bits(uint8_t card1, uint8_t card2, uint8_t trump)
{
  uint8_t card_xor = card1 ^ card2;

  uint8_t card1_trump_xor = card1 ^ trump;
  uint8_t card2_trump_xor = card2 ^ trump;

  // comparison by counting significant bits
  uint8_t cmp = (card1 & VALUE_MASK) ^ (card2 & VALUE_MASK);
  cmp |= (cmp >> 2);
  cmp |= (cmp >> 1);
  cmp = cmp - (cmp >> 1);
  cmp = ((card1 & VALUE_MASK) & cmp) ^ cmp;
  cmp |= (cmp >> 2);
  cmp |= (cmp >> 1);

  uint8_t mix =
    // [7] == 0: card1 not joker
    ((card1 << 1) & 0x80) |

    // [6] == 0: card2 not joker
    (card2 & 0x40) |

    // [5] == 0: same suits
    (((card_xor << 1) | card_xor) & 0x20) |

    // [4] == 0: card1 is trump
    ((card1_trump_xor | (card1_trump_xor >> 1)) & 0x10) |

    // [3] == 0: card2 is trump
    (((card2_trump_xor >> 1) | (card2_trump_xor >> 2)) & 0x08) |

    // [2] == 0: card1 is > card2
    ((cmp << 2) & 0x4);

  uint8_t ret =
    // [3]: R_SAME: same card
    (bitwise_true(card_xor) << 3) |

    // [2]: R_NONE: no result
    // no jokers [00], different suits [1], no trumps [11], value don't care [x]
    (bitwise_true((mix & 0xf8) ^ 0x38) << 2) |

    // [1]: R_CARD1: card1 wins
    // card1 wins if
    // - card1 is joker and card2 not joker
    // - different suits and card1 is trump and card2 is not trump
    // - card1 is higher
    ((
      bitwise_true((mix & 0xc0) ^ 0x80) |
      bitwise_true((mix & 0xf8) ^ 0x28) |
      bitwise_true((mix & 0xe4))
    ) << 1);

  // [0] R_CARD2: card2 wins
  ret |= ~ret & 0x1;

  return ret;
}
