# printbf -- Brainfuck interpreter in printf

## Authors

* [Mathias Payer](http://nebelwelt.net)
* [Nicholas Carlini](http://nicholas.carlini.com)


## Background

Generic POSIX printf itself can be Turing complete as shown in [Control-Flow
Bending](http://nebelwelt.net/publications/#15SEC). Here we take
printf-oriented programming one step further and preset a brainfuck
interpreter inside a single printf statement.

An attacker can control a printf statement through a format string
vulnerability (where an attacker-controlled string is used as first parameter
to a printf-like statement) or if the attacker can control the first argument
to a printf statement through, e.g., a generic memory corruption. See the
disclaimer below for practical ``in the wild'' considerations.

Brainfuck is a Turing-complete language that has the following commands (and
their mapping to format strings):

* > == dataptr++  (%1$.\*1$d %2$hn)
* < == dataptr--  (%1$65535d%1$.\*1$d%2$hn)
* + == \*dataptr++  (%3$.\*3$d %4$hhn)
* - == \*dataptr--  (%3$255d%3$.\*3$d%4$hhn -- plus check for ovfl)
* . == putchar(\*dataptr)  (%3$.\*3$d%5$hn)
* , == getchar(dataptr)  (%13$.\*13$d%4$hn)
* [ == if (\*dataptr == 0) goto ']'  (%1$.\*1$d%10$.\*10$d%2$hn)
* ] == if (\*dataptr != 0) goto '['  (%1$.\*1$d%10$.\*10$d%2$hn)


## Demo and sources

Have a look at the bf_pre.c sources to see what is needed to setup the
interpreter and also look at the tokenizer in toker.py.

Run make in ./src to generate a couple of sample programs (in ./src).


## Disclaimer

Keep in mind that this printbf interpreter is supposed to be a fun example of
Turing completeness that is available in current programs and not a new
generic attack vector. This demo is NOT intended to be a generic
FORTIFY_SOURCE bypass.

Current systems often either (i) disable %n (which is used to write to memory
and allowed according to the standard but rarely used in practicy) or (ii)
through a set of of patches that test for attack-like conditions, e.g., if
the format string is in writable memory.

To use printbf in the wild an attacker will either have to disable
FORTIFY_SOURCE checking or get around the checks by placing lining up the
format strings and placing them in readonly memory. The FORTIFY_SOURCE
mitigations are glibc specific. The attacker model for printbf assumes that
the attacker can use memory corruption vulnerabilities to set-up the attack or
that the sources are compiled without enabled FORTIFY_SOURCE defenses. 
