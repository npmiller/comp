#ifndef VARS_H
#define VARS_H

typedef struct {
	char *name;
	char *type;
	void *value;
} var;

var getVar(char *c);

#endif
