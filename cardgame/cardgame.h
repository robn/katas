#ifndef CARDGAME_H
#define CARDGAME_H

#include <stdint.h>

// 0 j ss vvvv
//   | |  +------ face value, 2-14
//   | +--------- suit, 0=clubs, 1=diamonds, 2=hearts, 3=spades
//   +----------- joker, other bits 0

#define VALUE_MASK (0x0f)
#define SUIT_MASK  (0x30)
#define JOKER_MASK (0x40)

#define SUIT_CLUB     (0x00)
#define SUIT_DIAMOND  (0x10)
#define SUIT_HEART    (0x20)
#define SUIT_SPADE    (0x30)

#define INVALID_CARD  (0xff)

#define R_SAME  (0x08)  // both cards same
#define R_NONE  (0x04)  // no result
#define R_CARD1 (0x02)  // card1 wins
#define R_CARD2 (0x01)  // card2 wins

// play function can return multiple bits. highest is the real one. this helper
// sorts it all out for you
#define RESULT_OK(r, m) ((r & m) && !(r & ~((m)+(m-1))))

// game-playing variants
uint8_t play_round_ref(uint8_t, uint8_t, uint8_t);
uint8_t play_round_bits(uint8_t, uint8_t, uint8_t);

// suit and card parsers
uint8_t parse_suit(const uint8_t *);
uint8_t parse_card(const uint8_t *);

// test things
int run_parse_tests();
int run_game_tests();
int run_comparison_tests();
void run_perf_tests();
int run_tests();

// silly helper to make a random game
void rand_game(uint8_t *, uint8_t *, uint8_t *);

#endif
