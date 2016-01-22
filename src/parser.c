/*
  the parser
 */

#include "../extern/mpc/mpc.h"

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
