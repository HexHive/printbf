#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

char buf[250000];

/* array will be used to not spill to stdout */
unsigned char* array_;
unsigned char* array;
int ptr;

int progn_[1000000];
int* progn;
int pc;

char* output_;
char* output;
int outptr;

char* input_;
char* input;
int inptr;


char* format_specifiers;

/* Arrays that hold our format strings */
char bf_LT_fmt[100];
char bf_GT_fmt[100];
char bf_PLUS_fmt[100];
char bf_MINUS_fmt[100];
char bf_DOT_fmt1[100];
char bf_DOT_fmt2[100];
char bf_GOTO_fmt[100];
char bf_COMMA_fmt1[100];
char bf_COMMA_fmt2[100];
char bf_CGOTO_fmt1[100];
char bf_CGOTO_fmt2[100];
char bf_CGOTO_fmt3[100];

char bf_ZERO_fmt[100];
char bf_FORWARD_N_fmt[100];
char bf_BACKWARD_N_fmt1[100];
char bf_BACKWARD_N_fmt2[100];
char bf_BACKWARD_N_fmt3[100];
char bf_ADD_N_fmt[100];

char bf_FETCH_fmt[100];

char* syms[] = {
  0,
  bf_LT_fmt, 
  bf_GT_fmt, 
  bf_PLUS_fmt, 
  bf_MINUS_fmt, 
  bf_DOT_fmt1, 
  bf_DOT_fmt2, 
  bf_COMMA_fmt1, 
  bf_COMMA_fmt2, 
  bf_CGOTO_fmt1, 
  bf_CGOTO_fmt2, 
  bf_CGOTO_fmt3, 
  bf_GOTO_fmt, 

  bf_ZERO_fmt, 
  bf_FORWARD_N_fmt, 
  bf_BACKWARD_N_fmt1, 
  bf_BACKWARD_N_fmt2, 
  bf_BACKWARD_N_fmt3, 
  bf_ADD_N_fmt,
  bf_FETCH_fmt
};

char** real_syms;

/**
 * setup - initialize basic variables and status for interpreter
 * Initialize interpreter, nothing that can't be done without a couple
 * of controlled memory writes and some limited alignment.
 * No cheating here, move along.
 */
void setup() {
  unsigned int i;
  inptr = 0;
  ptr = 0;
  pc = 2;

  real_syms = (char**)calloc(1,1<<17);
  real_syms = (char**)((char*)real_syms + 0x10000-(((long)real_syms)&0xFFFF));

  for (i = 0; i < sizeof(syms)/sizeof(*syms); i++) {
    real_syms[i] = syms[i];
  }

  array_ = malloc(2<<24);
  array = (void*)((char*)array_ + 0x1000000-(((long)array_)&0xFFFFFF));
  output_ = malloc(2<<24);
  output = (void*)((char*)output_ + 0x1000000-(((long)output_)&0xFFFFFF));
  input_ = malloc(2<<24);
  input = (void*)((char*)input_ + 0x1000000-(((long)input_)&0xFFFFFF));

  progn = (void*)((char*)progn_ + 0x10000-(((long)progn_)&0xFFFF));

  for (i = 0; i < sizeof(array_)/sizeof(*array); i++) {
    array_[i] = 0;
  }
  for (i = 0; i < sizeof(progn_)/sizeof(*progn); i++) {
    progn_[i] = 0;
  }
  for (i = 0; i < sizeof(input_)/sizeof(*input); i++) {
    input_[i] = -1;
  }

  strcpy(bf_LT_fmt, "%1$65535d%1$.*1$d%2$hn");
  strcpy(bf_GT_fmt, "%1$.*1$d %2$hn");
  strcpy(bf_PLUS_fmt, "%3$.*3$d %4$hhn");
  strcpy(bf_MINUS_fmt, "%3$255d%3$.*3$d%4$hhn");

  strcpy(bf_DOT_fmt1, "%3$.*3$d%5$hn");
  strcpy(bf_DOT_fmt2, "%6$.*6$d %7$hn");

  strcpy(bf_COMMA_fmt1, "%13$.*13$d%4$hn");
  strcpy(bf_COMMA_fmt2, "%14$.*14$d %15$hn");

  strcpy(bf_GOTO_fmt, "%10$.*10$d%11$hn");

  strcpy(bf_CGOTO_fmt1, "%8$n%4$s%8$hhn"); 
  strcpy(bf_CGOTO_fmt2, "%8$s%12$255d%9$hhn");
  strcpy(bf_CGOTO_fmt3, "    %10$.*10$d%11$hn"); 

  strcpy(bf_ZERO_fmt, "%4$hhn"); 

  strcpy(bf_FORWARD_N_fmt, "%1$.*1$d%10$.*10$d%2$hn"); 

  strcpy(bf_BACKWARD_N_fmt1, "%1$.*1$d%10$.*10$d%2$hn");

  strcpy(bf_ADD_N_fmt, "%3$.*3$d%10$.*10$d%4$hhn"); 

  strcpy(bf_FETCH_fmt, "%1$.*1$d%1$.*1$d%1$.*1$d%1$.*1$d%1$.*1$d%1$.*1$d%1$."
      "*1$d%1$.*1$d%2$hn");
}

int cond = 0;

/**
 * Loop --execute one bf instruction
 * Main interpreter loop, with only slight cheating to get around
 * overwriting printf internal data structures.
 * First decode the next bf instruction and set corresponding ptrs
 * then execute the instruction and update the output.
 */
void loop() {
  char* last = output;
  int* rpc = &progn[pc];

#ifdef NOCHEATING  
  long copyarray = 0;
  long copyoutput = 0;
  long copyinput = 0;
  int rpc1;
#endif

  while (*rpc != 0) {
    /* fetch -- decode next instruction */
    sprintf(buf, bf_FETCH_fmt, *rpc, (short*)(&real_syms));

#ifdef NOCHEATING
    sprintf((void*)(&copyarray), "%s", (char*)(&array));
    sprintf((void*)(&copyinput), "%s", (char*)(&input));
    sprintf((void*)(&copyoutput), "%s", (char*)(&output));
    sprintf((void*)(&rpc1), "%s", (char*)(&rpc[1]));
    sprintf((void*)(&rpc1)+1, "%s", (char*)(&rpc[1])+1);

    /* execute instruction */
    sprintf(buf, *real_syms,
	    copyarray, &array, /* 1, 2 */
	    *array, array, /* 3, 4 */
	    output, /* 5 */
	    copyoutput, &output, /* 6, 7 */
	    &cond, &bf_CGOTO_fmt3[0], /* 8, 9 */
	    rpc1, &rpc, /* 10, 11 */
	    0, /* 12 */
	    *input, /* 13 */
	    copyinput, &input /* 14, 15 */
	    );
#else
    /* execute instruction */
    sprintf(buf, *real_syms,
      /* slight cheating for bitwise and */
	    ((long)array)&0xFFFF, &array, /* 1, 2 */
	    *array, array, /* 3, 4 */
	    output, /* 5 */
      /* slight cheating for bitwise and */
      ((long)output)&0xFFFF, &output, /* 6, 7 */
	    &cond, &bf_CGOTO_fmt3[0], /* 8, 9 */
	    rpc[1], &rpc, /* 10, 11 */
	    0, /* 12 */
	    *input, /* 13 */
      /* slight cheating for bitwise and */
	    ((long)input)&0xFFFF, &input /* 14, 15 */
	    );
#endif
    /* retire -- update PC */
    sprintf(buf, "12345678%.*d%hn", 
      (int)(((long)rpc)&0xFFFF), 0, (short*)&rpc);

    /* for debug: do we need to print? */
    if (output != last) {
      putchar(output[-1]);
      last = output;
    }
  }
}

int main() {
  struct timeval tval_before, tval_after, tval_result;

  setup();

  /* program */
  ###TOKER###

  gettimeofday(&tval_before, NULL);

  strcpy(input, "###INPUT###");

  /* execute the bf program */
  loop();

  gettimeofday(&tval_after, NULL);

  timersub(&tval_after, &tval_before, &tval_result);

  printf("Time elapsed: %ld.%06ld\n", 
    (long int)tval_result.tv_sec,
    (long int)tval_result.tv_usec
    );

  return 0;
}
