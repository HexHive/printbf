# printbf -- Brainfuck interpreter in printf

## Authors
* [Mathias Payer](http://nebelwelt.net)
* [Nicholas Carlini](http://nicholas.carlini.com)

## Background
printf itself "can" [1] be Turing complete as shown in [Control-Flow
Bending](http://nebelwelt.net/publications/#15SEC). Here we take
printf-oriented programming one step further and preset a brainfuck
interpreter inside a single printf statement.

Now, an attacker can control a printf statement through a format string
vulnerability (where an attacker-controlled string is used as first
parameter to a printf-like statement) or if the attacker can control the
first argument to a printf statement through, e.g., a generic memory
corruption.

Brainfuck is a Turing-complete language that has the following commands (and
their mapping to format strings):

* > == dataptr++  (%1$65535d%1$.*1$d%2$hn)
* < == dataptr--  (%1$.*1$d %2$hn)
* + == *dataptr++  (%3$.*3$d %4$hhn)
* - == *datapr--  (%3$255d%3$.*3$d%4$hhn -- plus check for ovfl)
* . == putchar(*dataptr)  (%3$.*3$d%5$hn)
* , == getchar(dataptr)  (%13$.*13$d%4$hn)
* [ == if (*dataptr == 0) goto ']'  (%1$.*1$d%10$.*10$d%2$hn)
* ] == if (*dataptr != 0) goto '['  (%1$.*1$d%10$.*10$d%2$hn)

[1] Can, provided that we cheat and claim this has any real-life relevance to push our own agenda, despite the fact that this cheating in previous papers has been pointed out repeatedly by others.  We have thus not mentioned anywhere in the slides or in the source code the reason for the inserted -D_FORTIFY_SOURCE=0 to disable security that's been around for a decade now, as we would then have to explain how our write primitives aren't possible and simply result in the below failure on running any of the generated programs:

    *** invalid %N$ use detected ***
    Aborted (core dumped)


## Demo and sources
Have a look at the bf_pre.c sources to see what is needed to setup the
interpreter and also look at the tokenizer in toker.py.

Run make in ./src to generate a couple of sample programs (in ./src).
