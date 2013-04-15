#include "Parse.h"
#include "Vars.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Type.h"


char* P_matchingBracket(const char* string, const char delimO, const char delimF, int* pos) {
	char* buf = NULL;
	int bracketCounter = 0;
	int charNum = 1;
	buf = (char*)realloc(buf, charNum*sizeof(char));
	buf[charNum-1] = string[*pos];
	(*pos)++;
	while(!((string[*pos] == delimF) && (bracketCounter==0))) {
		if(string[*pos] == delimO) {
			bracketCounter++;
		}
		if((string[*pos] == delimF) && (bracketCounter != 0)) {
			bracketCounter--;
		}		
		charNum++;
		buf = (char*)realloc(buf, charNum*sizeof(char));
		buf[charNum-1] = string[*pos];
		(*pos)++;
	}
	charNum++;
	buf = (char*)realloc(buf, charNum*sizeof(char));
	buf[charNum-1] = '\0';
	(*pos)++; /* met la position au charactère suivant la parenthèse fermante */
	return buf;
}

char* P_getInBetween(const char* string, char delim, int* pos) {
	char* buf = NULL;
	int charNum = 1;
	do{
		buf = (char*)realloc(buf, charNum*sizeof(char));
		buf[charNum - 1] = string[*pos];
		charNum++;
		(*pos)++;
	} while(string[*pos] != delim);
	buf = (char*)realloc(buf, charNum*sizeof(char));
	buf[charNum - 1] = '\0';
	(*pos)++;
	return buf;
}

void discardBlankChars(const char* string, int* pos) {
	while(isblank(string[*pos])) {
		(*pos)++;
	}
}

char* P_getNextWord(const char* line, int pos, int *end) {
	char *buf = NULL;
	int charNum = 1;
	char delim = DELIM;
	discardBlankChars(line, &pos);
	switch(line[pos]) {
		case '(':
			buf = P_matchingBracket(line, '(', ')', &pos);
			break;
		
		case '{':
			buf = P_matchingBracket(line, '{', '}', &pos);
			break;

		case '"':
			buf = P_getInBetween(line, '"', &pos);
			break;

		default:
			while((line[pos] != delim) && (line[pos]!= END)) {
				buf = (char*)realloc(buf, charNum*sizeof(char));
				buf[charNum - 1] = line[pos];
				charNum++;
				pos++;
			}
			buf = (char*)realloc(buf, charNum*sizeof(char));
			buf[charNum - 1] = '\0';
	}
	discardBlankChars(line, &pos);
	if(line[pos] == END ) { 
		*end = -1; 
	} else {
		*end = pos;
	}
	return buf;
}



char* P_process_string(const char* word) {
	char *buf = NULL;
	int i;
	int len = strlen(word);
	buf = (char*)malloc((len)*sizeof(char));
	for(i=1; i<len; i++) {
		buf[i-1] = word[i];
	}
	buf[i-1]='\0';
	free((void*)word);
	return buf;
}

char* P_process_call(const char* word) {
	char* buf = NULL;
	int i,len;
	len = strlen(word);
    	buf = (char*)malloc((len)*sizeof(char));
	for(i=1; i<len; i++) {
		buf[i-1] = word[i];
	}
	buf[i-1]='\0';
	free((void*)word);
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
	free((void*)word);
	return r;
}

void P_process_sign(const char* word, const char** name, void** value) {
	int i = 1;
	char* nameBuffer = NULL;
	int numNameBuffer = 1;
	char* valueBuffer = NULL;
	int numValueBuffer = 1;
	char** currentBuffer = &nameBuffer;
	int* currentNum = &numNameBuffer;

	while(word[i]!='\0') {
		discardBlankChars(word, &i);
		while(word[i]!=':' && word[i]!=' ') {
			*currentBuffer = (char*)realloc(*currentBuffer, (*currentNum)*sizeof(char));
			(*currentBuffer)[*currentNum - 1] = word[i];
			i++;
			(*currentNum)++;
		}
		*currentBuffer = (char*)realloc(*currentBuffer, (*currentNum)*sizeof(char));
		(*currentBuffer)[*currentNum - 1] = ' ';
		(*currentNum)++;
		if(currentBuffer == &nameBuffer) {
			currentBuffer = &valueBuffer;
			currentNum = &numValueBuffer;
		} else {
			currentBuffer = &nameBuffer;
			currentNum = &numNameBuffer;
		}
		i++;
	}
	*name = nameBuffer;
	*value = (void*)valueBuffer;
	free((void*)word);
}

Var* P_process(const char* word) {
	errno = GOOD;
	Var *p = (Var*)malloc(sizeof(Var));
	V_init(p);
	if(word[0] == '"') {
		p->value = P_process_string(word);
		p->type = STRING;
		return p;
	} else if(word[0] == '(') {
		p->value = P_process_call(word);
		p->type = SUBEXPRESSION;
		return p;
	} else if(isdigit(word[0])) {
		p->value = P_process_digit(word);
		p->type = NUMBER;
		return p;
	} else if(word[0] == '{') {
		p->type = SIGNATURE;
		P_process_sign(word, &(p->name), &(p->value));
		return p;
	} else if ((strcmp(word, "true")==0) || (strcmp(word, "false")==0)) {
		p->type = BOOLEAN;
		p->value = word;
		return p;
	} else {
		/*p->value = P_process_var(word);*/
		p->type = VARIABLE;
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
