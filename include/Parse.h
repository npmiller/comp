#ifndef PARSE_H
#define PARSE_H

#define IGNORED '\t'
#define DELIM ' '
#define END '\0'

#define GOOD 1
#define EXPECTED_TOKEN 2
#define NOT_A_NUMBER 3

#include "LinkedList.h"
#include <stdlib.h>
#include <errno.h>

LinkedList P_parse(const char*);

#endif
