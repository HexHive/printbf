SRC=gol.c bf.c bf2.c bf_obfuscated.c bf_fib bf_life
BIN=$(SRC:.c=)

all: $(BIN)

gol: gol.c
	gcc -std=c99 -Wall -O3 gol.c -o gol

bf: bf.c
	gcc -std=c99 -Wall -O3 bf.c -o bf

bf2: bf2.c
	gcc -std=c99 -Wall -O3 -D_FORTIFY_SOURCE=0 bf2.c -o bf2

bf_obfuscated: bf_obfuscated.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 bf_obfuscated.c -o bf_obfuscated

bf_fib: bf_pre.c ../bfprogs/fib.bf
	python toker.py -t bf_pre.c -i "efeefe\\n\\n\\n" -bf ../bfprogs/fib.bf > bf_fib.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 bf_fib.c -o bf_fib

bf_life: bf_pre.c ../bfprogs/life.bf
	python toker.py -t bf_pre.c -i "efeefe\\n\\n\\n" -bf ../bfprogs/life.bf > bf_life.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 bf_life.c -o bf_life

.PHONY=clean
clean:
	rm -f $(BIN)
