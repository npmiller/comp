#include "Parse.h"
#include "Vars.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* P_matchingBracket(const char* string, const char delimO, const char delimF, int* pos) {
	char* buf = NULL;
	int i = *pos;
	int bracketCounter = 0;
	int charNum = 1;
	buf = (char*)realloc(buf, charNum*sizeof(char));
	buf[charNum-1] = string[i];
	i++;
	while(!((string[i] == delimF) && (bracketCounter==0))) {
		if(string[i] == delimO) {
			bracketCounter++;
		}
		if((string[i] == delimF) && (bracketCounter != 0)) {
			bracketCounter--;
		}		
		charNum++;
		buf = (char*)realloc(buf, charNum*sizeof(char));
		buf[charNum-1] = string[i];
		i++;
	}
	*pos = i;
	/*printf("P_matchingBracket : %s\n", buf);*/
	return buf;
}

char* P_getNextWord(const char* line, int pos, int *end) {
	char *buf = NULL;
	int i = pos;
	int charNum = 1;
	char delim = DELIM;
	if(line[i] == END) { *end = -1;  return buf; }
	if(line[i] == '(') {
		delim = ')';
		buf = P_matchingBracket(line, '(', ')', &i);
	} else {
		if(line[i] == '"') { delim = '"'; }
		do{
			buf = (char*)realloc(buf, charNum*sizeof(char));
			buf[charNum - 1] = line[i];
			charNum++;
			i++;
		} while((line[i] != delim) && (line[i]!= END));
	}
	if(line[i] == END ) { 
		*end = -1; 
	} else { 
		if(line[i+1] == END) {
		   	*end=-1; 
		} else {
			if(delim != DELIM) {
				*end = i+2;
			} else {
				*end = i+1;
			}
		}
	}
	/*printf("P_getNextWord : %s\n", buf);*/
	return buf;
}



char* P_process_string(const char* word) {
	char *buf = NULL;
	int i;
	int len = strlen(word);
	buf = (char*)malloc((len-1)*sizeof(char));
	for(i=1; i<len; i++) {
		buf[i-1] = word[i];
	}
	return buf;
}
char* P_process_call(const char* word) {
	char* buf = NULL;
	int i,len;
	len = strlen(word);
    buf = (char*)malloc((len-1)*sizeof(char));
	for(i=1; i<len; i++) {
		buf[i-1] = word[i];
	}
	return buf;
}

int* P_process_digit(const char* word) {
	int* r =(int*)malloc(sizeof(int));

	/*while(word[i] != '\0') {*/
		/*if(!isdigit(word[i])) {*/
			/*errno = NOT_A_NUMBER;*/
			/**r = -1;*/
			/*return r;*/
		/*}*/
	/*}*/
	*r = atoi(word);
	return r;
}

void atest(int a, int b) {
	printf("%d\n", a+b);
}

/*void(*)(int, int) P_process_var(const char* word) {*/
	/*char* r = (char*)malloc((strlen(word)+1)*sizeof(char));*/
	/*strcpy(r, word);*/
	/*return &atest;*/
/*}*/

Var* P_process(const char* word) {
	errno = GOOD;
	Var *p = (Var*)malloc(sizeof(Var));
	if(word[0] == '"') {
		p->value = P_process_string(word);
		p->type = "string";
		return p;
	} else if(word[0] == '(') {
		p->value = P_process_call(word);
		/*printf("%s\n", word);*/
		p->type = "sub";
		return p;
	} else if(isdigit(word[0])) {
		p->value = P_process_digit(word);
		p->type = "int";
		return p;
	} else {
		/*p->value = P_process_var(word);*/
		p->type = "variable";
		p->name = word;
		return p;
	}
}
LinkedList P_parse(const char* line) {
	int end = 0;
	char *word;
	LinkedList ltemp = NULL;
	LinkedList lend = NULL;
	LinkedList res = NULL;
	word = P_getNextWord(line, end, &end);
	LL_add(&res, P_process(word));
	lend = res;
	while(end!=-1) {
		word = P_getNextWord(line, end, &end);
		LL_add(&ltemp, P_process(word));
		LL_setNext(lend, ltemp);
		lend = ltemp;
		ltemp = NULL;
	}
	return res;
}
