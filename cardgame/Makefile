CFLAGS := -Wall -Werror -O3

BIN := cardgame

OBJS := \
	cardgame.o \
	parse.o \
	play_round_ref.o \
	play_round_bits.o \
	test.o \
	test_compare.o \
	test_game.o \
	test_parse.o \
	test_perf.o \

HEADERS := \
	cardgame.h

all: $(BIN)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

$(BIN): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(BIN) $(OBJS)
