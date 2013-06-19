#include "Vars.h"

void V_print(Var v) {
	Type t = V_getType(v);
	if(t!=NONE) {
		switch(t) {
			case NUMBER :
				printf("%d\n", *((int*)V_getValue(v)));
				break;
			case STRING :
				printf("%s\n", (char*)V_getValue(v));
				break;
			case BOOLEAN :
				printf("%s\n", *((bool*)V_getValue(v)) ? "true" : "false");
				break;
			default :
				printf("Erreur, retour non affichable : %s\n", T_toString(t));
		}
	}
}

/*void V_print(Var v) {*/
	/*printf("'%s' : '%s'\n", v.name, T_toString(v.type));*/
/*}*/

void V_init(Var* v) {
	v->name = NULL;
	v->type = NONE;
	v->vtype = NONE,
	v->value = NULL;
}


void V_free(void** v) {
	Var* var = *((Var**)v);
	free((void*)var->name);
	free((void*)var->value);
	free(var);
	*v = NULL;
}

void V_free_name(void** v) {
	free((void*)((*(Var**)v))->name);
	free(*v);
	*v = NULL;
}

bool V_isEmpty(Var v) {
	return ((v.name == NULL) && (v.type == NONE) && (v.value == NULL));
}

const char* V_getName(Var v) {
	return v.name;
}

Type V_getType(Var v) {
	return v.type;
}

Type V_getVType(Var v) {
	return v.vtype;
}

void* V_getValue(Var v) {
	return v.value;
}
void V_setName(Var* v, const char* name) {
	v->name = name;
}

void V_setValue(Var* v, void* value) {
	v->value = value;
}

void V_setType(Var* v, Type type) {
	v->type = type;
}

void V_setVType(Var* v, Type vtype) {
	v->vtype = vtype;
}

void* V_copyValue(void* value, Type type) {
	void* valuecp = NULL;
	switch(type) {
		case STRING :
			valuecp = malloc(sizeof((strlen((char*)value)+1)*sizeof(char)));
			memcpy(valuecp, value, (strlen((char*)value)+1)*sizeof(char));
			return valuecp;
		case NUMBER :
			valuecp = malloc(sizeof(value));
			memcpy(valuecp, value, sizeof(int));
			return valuecp;
		case BOOLEAN :
			valuecp = malloc(sizeof((strlen((char*)value)+1)*sizeof(char)));
			memcpy(valuecp, value, (strlen((char*)value)+1)*sizeof(char));
			return valuecp;
		case SUBEXPRESSION :
			valuecp = malloc(sizeof((strlen((char*)value)+1)*sizeof(char)));
			memcpy(valuecp, value, (strlen((char*)value)+1)*sizeof(char));
			return valuecp;
		case SIGNATURE :
			valuecp = malloc(sizeof((strlen((char*)value)+1)*sizeof(char)));
			memcpy(valuecp, value, (strlen((char*)value)+1)*sizeof(char));
			return valuecp;
		default:
			return valuecp;
	}
}

Var V_copy(Var v) {
	Var result;
	V_init(&result);
	V_setType(&result, V_getType(v));
	V_setVType(&result, V_getVType(v));
	if(V_getType(v) == VARIABLE) {
		V_setValue(&result, V_copyValue(V_getValue(v), V_getVType(v)));	
	} else {
		V_setValue(&result, V_copyValue(V_getValue(v), V_getType(v)));	
	}
	char* namecp = (char*)malloc(sizeof(char)*(strlen(V_getName(v))+1));
	strcpy(namecp, V_getName(v));
	V_setName(&result, namecp);
	return result;
}



/* ---------------------------------------------------------------------*/
Var VLH_getVar(LinkedList l) {
	return *((Var*)LL_getValue(l));
}

int VLH_getInt(LinkedList l) {
	return *((int*)((Var*)(LL_getValue(l)))->value);
}

bool VLH_getBool(LinkedList l) {
	return *((bool*)((Var*)(LL_getValue(l)))->value);
}

char* VLH_getString(LinkedList l) {
	return (char*)((Var*)(LL_getValue(l)))->value;
}

char* VLH_getName(LinkedList l) {
	return (char*)((Var*)(LL_getValue(l)))->name;
}

Type VLH_getType(LinkedList l) {
	return (Type)((Var*)(LL_getValue(l)))->type;
}

Type VLH_getVType(LinkedList l) {
	return (Type)((Var*)(LL_getValue(l)))->vtype;
}

void* VLH_getValue(LinkedList l) {
	return (void*)((Var*)(LL_getValue(l)))->value;
}

void VLH_setType(LinkedList l, Type type) {
	((Var*)LL_getValue(l))->type = type;
}

void VLH_setVType(LinkedList l, Type type) {
	((Var*)LL_getValue(l))->vtype = type;
}

void VLH_setName(LinkedList l, const char* name) {
	((Var*)LL_getValue(l))->name = name;
}

void VLH_setValue(LinkedList l, void* value) {
	((Var*)LL_getValue(l))->value = value;
}
