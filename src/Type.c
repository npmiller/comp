#include "Type.h"
#include "Vars.h"

bool T_equals(const char* typeString, Type type) {
	switch(type) {
		case STRING :
			return (strcmp(typeString, "string")==0);
		case NUMBER :
			return (strcmp(typeString, "number")==0);
		case BOOLEAN :
			return (strcmp(typeString, "boolean")==0);
		case SUBEXPRESSION :
			return (strcmp(typeString, "subexpression")==0);
		case SIGNATURE :
			return (strcmp(typeString, "signature")==0);
		case VARIABLE :
			return (strcmp(typeString, "variable")==0);
		case NONE :
			return (strcmp(typeString, "none")==0);
	}
}
char* T_toString(Type type) {
	switch(type) {
		case STRING :
			return "string";
		case NUMBER :
			return "number";
		case BOOLEAN :
			return "boolean";
		case SUBEXPRESSION :
			return "subexpression";
		case SIGNATURE :
			return "signature";
		case VARIABLE :
			return "variable";
		case NONE :
			return "none";
	}
}

void* TV_copyVarValue(void* src) {
	Var v = *((Var*)src);
	void* newValue = NULL;
	Type type = V_getVType(v);
	switch(type) {
		case STRING :
			newValue = malloc(sizeof(V_getValue(v)));
			memcpy(newValue, V_getValue(v), sizeof((strlen((char*)V_getValue(v))+1)*sizeof(char)));
			return newValue;
		case NUMBER :
			newValue = malloc(sizeof(V_getValue(v)));
			memcpy(newValue, V_getValue(v), sizeof(int));
			return newValue;
		case BOOLEAN :
			newValue = malloc(sizeof(V_getValue(v)));
			memcpy(newValue, V_getValue(v), sizeof((strlen((char*)V_getValue(v))+1)*sizeof(char)));
			return newValue;
		case SUBEXPRESSION :
			newValue = malloc(sizeof(V_getValue(v)));
			memcpy(newValue, V_getValue(v), sizeof((strlen((char*)V_getValue(v))+1)*sizeof(char)));
			return newValue;
		case SIGNATURE :
			newValue = malloc(sizeof(V_getValue(v)));
			memcpy(newValue, V_getValue(v), sizeof((strlen((char*)V_getValue(v))+1)*sizeof(char)));
			return newValue;
		case VARIABLE :
			return newValue;
		case NONE :
			return newValue;
	}

}
