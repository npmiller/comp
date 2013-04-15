#ifndef ERR_H
#define ERR_H

#include "LinkedList.h"

typedef struct {
	bool error;
	char* msg;
	LinkedList backtrace;
}

#endif
