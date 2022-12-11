https://www.codewars.com/kata/5a3141fe55519e04d90009d8

### Compile it:

```
$ make
```

### Run the tests:

```
$ ./cardgame
```

### Play a game:

```
$ ./cardgame 3♣ Q♣ ♦
The second card won.
```

### Isn't this all a bit overkill?

Absolutely.

So what I actually wanted to do was write the constant-time bit-swizzling
version of the game player - no branches, no loops, no compares, just bitstuff.
Partly to see if I could, partly to see if it could perform better.

But to do that, I had to make sure that it worked, so I built a "dumb" version
first and an entire testing edifice to go with it, so I could be sure mine
worked properly against the dumb one.

And I did that, see `play_round_bits.c`, so that's cool!

Then I wrote performance tests, and it turns out even with all the compiler
optimisations on, I'm still slower than the "dumb" version. I did achieve the
goal though, so I'm not too sad, but yeah, you can't beat the compiler unless
you know what you're doing.

(I suspect it would go faster with less insane input layout, and if it was
operating on 32-bit values. Also it would go faster if I did a SSE or AVX or
similar version, with the downside that you'd have to play like eight games
simultaneously to even use it).
