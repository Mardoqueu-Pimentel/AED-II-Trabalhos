#include <macros.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void macros_debug (const char *s, ...) {

	va_list args;
	va_start(args, s);

	char names[strlen(s) + 1];
	strcpy(names, s);

	for (char *token = strtok(names, " ,"); token; token = strtok(NULL, " ,")) {
		token = strtok(NULL, " ,");

		fprintf(stderr, "%s: ", token);

		enum TYPE T = va_arg(args, enum TYPE);

		bool b;
		switch (T) {
			case CHAR:
			fprintf(stderr, "%c\n", va_arg(args, int));
			break;
			
			case UCHAR:
			fprintf(stderr, "%hhu\n", va_arg(args, unsigned));
			break;

			case INT:
			fprintf(stderr, "%d\n", va_arg(args, int));
			break;

			case UINT:
			fprintf(stderr, "%u\n", va_arg(args, unsigned));
			break;

			case FLOAT:
			fprintf(stderr, "%f\n", va_arg(args, double));
			break;

			case DOUBLE:
			fprintf(stderr, "%lf\n", va_arg(args, double));
			break;

			case LDOUBLE:
			fprintf(stderr, "%Lf\n", va_arg(args, long double));
			break;

			case BOOL:
			b = va_arg(args, int);
			fprintf(stderr, "%s\n", b ? "true" : "false");
		}
	}
	va_end(args);
}