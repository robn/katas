#include <string.h>

#include "cardgame.h"

uint8_t
parse_suit(const uint8_t *suitp)
{
  uint8_t suit = 0;

  switch (*suitp++) {
    case 'c': case 'C':
      suit = SUIT_CLUB;
      break;
    case 'd': case 'D':
      suit = SUIT_DIAMOND;
      break;
    case 'h': case 'H':
      suit = SUIT_HEART;
      break;
    case 's': case 'S':
      suit = SUIT_SPADE;
      break;
    case 0xe2:
      // ♠ - U+02660 - E2 99 A0 - BLACK SPADE SUIT
      // ♣ - U+02663 - E2 99 A3 - BLACK CLUB SUIT
      // ♥ - U+02665 - E2 99 A5 - BLACK HEART SUIT
      // ♦ - U+02666 - E2 99 A6 - BLACK DIAMOND SUIT
      if (*suitp++ != 0x99)
        return INVALID_CARD;
      switch (*suitp++) {
        case 0xa0:
          suit = SUIT_SPADE;
          break;
        case 0xa3:
          suit = SUIT_CLUB;
          break;
        case 0xa5:
          suit = SUIT_HEART;
          break;
        case 0xa6:
          suit = SUIT_DIAMOND;
          break;
        default:
          return INVALID_CARD;
      }
      break;
    default:
      return INVALID_CARD;
  }

  if (*suitp)
    return INVALID_CARD;

  return suit;
}

uint8_t
parse_card(const uint8_t *cardp)
{
  if (strcasecmp((const char *)cardp, "joker") == 0)
    return JOKER_MASK;

  uint8_t card = 0;
  const uint8_t *suitp = &cardp[1];

  switch (cardp[0]) {
    case 'j': case 'J':
      card = 11;
      break;
    case 'q': case 'Q':
      card = 12;
      break;
    case 'k': case 'K':
      card = 13;
      break;
    case 'a': case 'A':
      card = 14;
      break;
    case '1':
      if (cardp[1] != '0')
        return INVALID_CARD;
      card = 10;
      suitp++;
      break;
    default:
      if (cardp[0] < '2' || cardp[0] > '9')
        return INVALID_CARD;
      card = cardp[0] & 0xf;
      break;
  }

  uint8_t suit = parse_suit(suitp);
  if (suit == INVALID_CARD)
    return INVALID_CARD;
  card |= suit;

  return card;
}
