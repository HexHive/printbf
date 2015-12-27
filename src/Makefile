GENSRC=bf_fib.c bf_life.c bf_hello.c
BIN=$(GENSRC:.c=)

all: $(BIN)

bf_fib: bf_pre.c ../bfprogs/fib.bf
	python toker.py -t bf_pre.c -bf ../bfprogs/fib.bf > bf_fib.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 bf_fib.c -o bf_fib

bf_life: bf_pre.c ../bfprogs/life.bf
	python toker.py -t bf_pre.c -i "efeefe\\n\\n\\n" -bf ../bfprogs/life.bf > bf_life.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 bf_life.c -o bf_life

bf_hello: bf_pre.c ../bfprogs/hello.bf
	python toker.py -t bf_pre.c -bf ../bfprogs/hello.bf > bf_hello.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 bf_hello.c -o bf_hello

.PHONY=clean
clean:
	rm -f $(BIN) $(GENSRC)
