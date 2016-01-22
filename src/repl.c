/*
IDEA: command count in prompt + unsaved keystroke to clear count
*/

#include <stdio.h>
#include <stdlib.h>

/* Replace libedit with linenoise once things are working, and I'm a
   a little more familiar with C. */
#include <editline/readline.h>

int main(int argc, char** argv) {
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
