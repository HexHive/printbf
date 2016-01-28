GENSRC=pbf_fib.c pbf_life.c pbf_hello.c pbf_mandel.c pbf_sierp.c pbf_demo.c pbf_99b.c
BIN=$(GENSRC:.c=)

# Without cheating but demo may run a little slower
#FLAGS=-W -Wall -Wextra -Wpedantic -O3 -D_FORTIFY_SOURCE=1 -DNOCHEATING

# Slight cheating during instruction execute but runs faster
FLAGS=-W -Wall -Wextra -Wpedantic -O3 -D_FORTIFY_SOURCE=1

all: $(BIN)

pbf_fib: pbf_pre.c ../bfprogs/fib.bf
	python toker.py -t pbf_pre.c -bf ../bfprogs/fib.bf > pbf_fib.c
	gcc $(FLAGS) pbf_fib.c -o pbf_fib

pbf_life: pbf_pre.c ../bfprogs/life.bf
	python toker.py -t pbf_pre.c -i "efeefe\\n\\n\\n" -bf ../bfprogs/life.bf > pbf_life.c
	gcc $(FLAGS) pbf_life.c -o pbf_life

pbf_hello: pbf_pre.c ../bfprogs/hello.bf
	python toker.py -t pbf_pre.c -bf ../bfprogs/hello.bf > pbf_hello.c
	gcc $(FLAGS) pbf_hello.c -o pbf_hello

pbf_mandel: pbf_pre.c ../bfprogs/mandelbrot.bf
	python toker.py -t pbf_pre.c -bf ../bfprogs/mandelbrot.bf > pbf_mandel.c
	gcc $(FLAGS) pbf_mandel.c -o pbf_mandel

pbf_sierp: pbf_pre.c ../bfprogs/sierpinski.bf
	python toker.py -t pbf_pre.c -bf ../bfprogs/sierpinski.bf > pbf_sierp.c
	gcc $(FLAGS) pbf_sierp.c -o pbf_sierp

pbf_demo: pbf_pre.c ../bfprogs/demo.bf
	python toker.py -t pbf_pre.c -i A -bf ../bfprogs/demo.bf > pbf_demo.c
	gcc $(FLAGS) pbf_demo.c -o pbf_demo

pbf_99b: pbf_pre.c ../bfprogs/99bottles.bf
	python toker.py -t pbf_pre.c -i A -bf ../bfprogs/99bottles.bf > pbf_99b.c
	gcc $(FLAGS) pbf_99b.c -o pbf_99b

.PHONY=clean
clean:
	rm -f $(BIN) $(GENSRC)
