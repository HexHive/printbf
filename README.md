# printbf -- Brainfuck interpreter in printf

printf itself can be Turing complete as shown in [Control-Flow
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
