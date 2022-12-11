#include "cardgame.h"

/* reference version */
uint8_t
play_round_ref(uint8_t card1, uint8_t card2, uint8_t trump)
{
  // same card
  if (card1 == card2)
    return R_SAME;

  // joker wins
  if (card1 & JOKER_MASK)
    return R_CARD1;
  if (card2 & JOKER_MASK)
    return R_CARD2;

  // different suits
  if ((card1 & SUIT_MASK) != (card2 & SUIT_MASK)) {

    // trump wins
    if ((card1 & SUIT_MASK) == trump)
      return R_CARD1;
    if ((card2 & SUIT_MASK) == trump)
      return R_CARD2;

    // different suits, no trump -> no result
    return R_NONE;
  }

  // same suit -> biggest wins
  return (card1 & VALUE_MASK) > (card2 & VALUE_MASK) ? R_CARD1 : R_CARD2;
}
