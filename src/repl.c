/*
IDEA: command count in prompt + unsaved keystroke to clear count

TODO: Replace libedit with linenoise once things are working, and
      I'm a a little more familiar with C.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../extern/mpc/mpc.h"

/* there has to be a better way to do cross-platform work...
   this seems vile */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline on windows. */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}

/* Fake add_history on windows. */
void add_history(char* unused) {}

/* not windows means real libedit */
#else
#include <editline/readline.h>
#endif

int main(int argc, char** argv) {
  /* build our parsers */
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expression = mpc_new("expr");
  mpc_parser_t* Lisp_P = mpc_new("lisp_p");

  /* define our language */
  mpca_lang(MPCA_LANG_DEFAULT,
            " \
             number: /-?[0-9]+/; \
             operator: '+' | '-' | '*' | '/' | '%' | '^'; \
             expr: <number> | '(' <operator> <expr>+ ')'; \
             lisp_p: /^/ <operator> <expr>+ /$/; \
            ",
            Number, Operator, Expression, Lisp_P);

  puts("LispP Version 0.0");
  puts("Ctrl-C to Exit.\n");

  /* REPL main loop. Strictly speaking, not yet a REP loop yet so much
     as an Echo loop for now. */
  while (1) {
    /* Get user input. Note that libedit handles the allocation of memory
       for the input, and gives us back a pointer to that string. We're
       responsible for freeing the pointer once we're done. */
    char* input = readline("LispP: ");

    /* libedit keeps a command history, but we need to add the input to it
       ourselves. */
    add_history(input);

    /* Like I said, no actual E in the REPL yet. */
    printf("No you're a towel. Now where's my %s?\n\n", input);

    /* We're done with input, so it's time to free it. */
    free(input);
  }

  return 0;
}
