#include "stdlib/string.h"

void use_string(Identifiers* I) {
	BBT_add(I, (void*)I_create("concat", "string string", concat), I_compare);
}

Var concat(LinkedList l) {
	Var vRes;
	V_init(&vRes);
	char* ch1 = VLH_getString(l);
	l = LL_getNext(l);
	char* ch2 = VLH_getString(l);
	V_setType(&vRes, STRING);
	int len1 = strlen(ch1);
	int len2 = strlen(ch2);
	char* res = (char*)malloc((len1+len2+1)*sizeof(char));
	int i;
	for(i=0; i<len1; i++) {
		res[i] = ch1[i];
	}
	for(i=len1; i<(len1+len2); i++) {
		res[i] = ch2[i-len1];
	}
	res[len1+len2+1] = '\0';
	V_setValue(&vRes, (void*)res);
	return vRes;
}
