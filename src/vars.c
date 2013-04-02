#include "vars.h"

#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define IS_VAR 1
#define IS_NOT_VAR 2

#define DELIM ':'

bool is_delim(char c) {
	return (c == DELIM);
}

bool is_space(char c) {
	return (c == ' ');
}

bool is_end(char c) {
	return (c == '\0');
}


var getVar(char *c) {
		errno = IS_VAR;
		var v;
		char *buf = NULL;
		int i=0;
		int char_number=1;
		do{
			if(is_end(c[i])) {
					errno = IS_NOT_VAR;
					return v;
			};
			if(!is_space(c[i])) {
				buf = (char*)realloc(buf, char_number*sizeof(char));
				buf[char_number - 1] = c[i];
				char_number++;
			}
			i++;
		} while(!is_delim(c[i]));
		v.name = buf;
		buf = NULL;
		char_number = 1;
		i++;
		while(!is_end(c[i])) {
			if(!is_space(c[i])) {
				buf = (char*)realloc(buf, char_number*sizeof(char));
				buf[char_number - 1] = c[i];
				char_number++;
			}
			i++;
		}
		v.value = buf;
		return v;
}
