#include <stdlib.h>         /* exit() */
#include <stdio.h>          /* FILE*, fprintf() */
#include <unistd.h>         /* read() */
#include <string.h>         /* strerror() */
#include <errno.h>          /* errno */
#include "mem/mem.h"		/* mem_alloc(), mem_free() */
#include "token/token.h"	/* Tokens from lexer. (token) */
#include "value/value.h"	/* Value types */
#include "ASTNode.h"		/* ASTNode definitions */

int parse(int in, FILE *out);
