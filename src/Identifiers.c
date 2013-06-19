#include "Identifiers.h"
#include <string.h>


bool I_compare(void* a, void* b) {
	return ((((Identifier*)a)->id) > (((Identifier*)b)->id));
}


void I_free(void* i) {
	Identifier* I = (Identifier*)i;

	if(I->standard) {
		free(i);
	} else {
		free((void*)I->name);
		free((void*)I->params);
		free((void*)I->sub);
		free((void*)I->args);
		free(i);
	}
}


int I_getID(const char* string) {
	int res = 0;
	int i = 0;
	while(string[i] != '\0') {
		res += (int)string[i];
		i++;
	}
	return res;
}

int compare2(void* a, void* b) {
	int id = ((Identifier*)b)->id;
	int val = *((int*)a);
	if(val > id) {
		return 1;
	} else {
		if(val == id) {
			return 0;
		} else {
			return -1;
		}
	}
}

Identifier I_find(const char* name) {
	Identifier Id;
	Identifier* p_Id;
	int id = I_getID(name);
	p_Id = (Identifier*)BBT_find(identifiers, (void*)&id, compare2);
	if(p_Id == NULL) {
		Id.name = "NotFound";
	} else {
		Id = *p_Id;
	}	
	return Id;
}

Identifier* I_create(const char* name, const char* args, Var (*function)(LinkedList)) {
	Identifier* I = (Identifier*)malloc(sizeof(Identifier));
	I->id = I_getID(name);
	I->name = name;
	I->args = args;
	I->standard = true;
	I->function = function;
	I->sub = NULL;
	I->params = NULL;
	return I;
}
