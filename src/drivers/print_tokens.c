#include <stdio.h>          /* FILE*, getc() */
#include <errno.h>			/* errno, strerror() */
#include "token/token.h"	/* token, token_Free(), get_type() */
#include "lex/lex.h"		/* lexer_make(), lexer_init(), lex_token() */

static void print_token(token t, FILE* out)
{
	char* name;
	switch(get_type(t)) {
	case TOKEN_START:
		name = "start";
		break;
	case TOKEN_EOF:
		name = "eof";
		break;
	case TOKEN_NUMBER:
		name = "number";
		break;
	case TOKEN_OPERATOR:
		name = "operator";
		break;
	case TOKEN_LPAREN:
		name = "Open parenthesis";
		break;
	case TOKEN_RPAREN:
		name = "Close parenthesis";
		break;
	};
	fprintf(out, "Found %s : %s\n", name, get_value(t));
}

int main(void)
{
	token t = NULL;
	int c;
	size_t bufuse = 0;
	size_t bufsize = 1000024;
	char* buf = malloc(sizeof *buf * bufsize);
	struct lexer* lex = lexer_make();
	assert(buf); /* TODO: Error handling. */
	assert(lex); /* TODO: Error handling. */
	while ((c = getchar_unlocked()) != EOF) {
		buf[bufuse++] = (char) c;
		if (bufuse == bufsize) {
			bufsize *= 2;
			buf = realloc(buf, bufsize);
			assert(buf); /* TODO: Error handling. */
		}
	}
	buf[bufuse + 1] = '\0'; /* Guarenteed to work by mathematical relationship. */
	assert(strlen(buf) == bufuse);

	lexer_init(lex, buf, "stdin");
	for (t =lex_token(lex, t); get_type(t) != TOKEN_EOF; t =lex_token(lex, t)) {
		print_token(t, stdout);
	}
	token_free(t);
	if (fclose(stdin)) {
		fprintf(stderr, "error in: %s\n", strerror(errno));
		fclose(stdout);
		return errno;
	}
	if (fclose(stdout)) {
		fprintf(stderr, "error out: %s\n", strerror(errno));
		return errno;
	}
	lexer_free(lex);
	return 0;
}
