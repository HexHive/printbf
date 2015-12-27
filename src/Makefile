GENSRC=pbf_fib.c pbf_life.c pbf_hello.c pbf_mandel.c pbf_sierp.c
BIN=$(GENSRC:.c=)

all: $(BIN)

pbf_fib: pbf_pre.c ../bfprogs/fib.bf
	python toker.py -t pbf_pre.c -bf ../bfprogs/fib.bf > pbf_fib.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 pbf_fib.c -o pbf_fib

pbf_life: pbf_pre.c ../bfprogs/life.bf
	python toker.py -t pbf_pre.c -i "efeefe\\n\\n\\n" -bf ../bfprogs/life.bf > pbf_life.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 pbf_life.c -o pbf_life

pbf_hello: pbf_pre.c ../bfprogs/hello.bf
	python toker.py -t pbf_pre.c -bf ../bfprogs/hello.bf > pbf_hello.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 pbf_hello.c -o pbf_hello

pbf_mandel: pbf_pre.c ../bfprogs/mandelbrot.bf
	python toker.py -t pbf_pre.c -bf ../bfprogs/mandelbrot.bf > pbf_mandel.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 pbf_mandel.c -o pbf_mandel

pbf_sierp: pbf_pre.c ../bfprogs/sierpinski.bf
	python toker.py -t pbf_pre.c -bf ../bfprogs/sierpinski.bf > pbf_sierp.c
	gcc -std=c99 -Wall -O3 -D_BSD_SOURCE -D_FORTIFY_SOURCE=0 pbf_sierp.c -o pbf_sierp

.PHONY=clean
clean:
	rm -f $(BIN) $(GENSRC)
