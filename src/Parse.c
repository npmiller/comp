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
			buf = P_matchingBracket(line, '"', '"', &pos);
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
	if((line[pos] == END)) { 
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

void P_process_sign(const char* word, Var* p) {
	int i = 1;
	char* nameBuffer = NULL;
	int numNameBuffer = 1;
	char* valueBuffer = NULL;
	int numValueBuffer = 1;
	char** currentBuffer = &nameBuffer;
	int* currentNum = &numNameBuffer;

	while(word[i]!=END) {
		discardBlankChars(word, &i);
		while(word[i]!=':' && word[i]!=' ') {
			*currentBuffer = (char*)realloc(*currentBuffer, (*currentNum)*sizeof(char));
			(*currentBuffer)[*currentNum - 1] = word[i];
			i++;
			(*currentNum)++;
		}
		discardBlankChars(word, &i);
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
		if(word[i] != END) {
			i++;
		}
	}
	nameBuffer = (char*)realloc(nameBuffer, (numNameBuffer)*sizeof(char));
	nameBuffer[numNameBuffer - 1] = '\0';
	valueBuffer = (char*)realloc(valueBuffer, (numValueBuffer)*sizeof(char));
	valueBuffer[numValueBuffer - 1] = '\0';

	V_setName(p, nameBuffer);
	V_setValue(p, (void*)valueBuffer);
}

Var* P_process(const char* word) {
	errno = GOOD;
	char* wordcp;
	Var *p = (Var*)malloc(sizeof(Var));
	V_init(p);
	if(word[0] == '"') {
		V_setValue(p, P_process_string(word));
		V_setType(p, STRING);
		return p;
	} else if(word[0] == '(') {
		V_setValue(p, P_process_call(word));
		V_setType(p, SUBEXPRESSION);
		return p;
	} else if(isdigit(word[0])) {
		V_setValue(p, P_process_digit(word));
		V_setType(p, NUMBER);
		return p;
	} else if(word[0] == '{') {
		V_setType(p, SIGNATURE);
		P_process_sign(word, p);
		return p;
	} else if (strcmp(word, "true")==0) {
		bool* res = (bool*)malloc(sizeof(bool));
		*res = true;
		V_setType(p, BOOLEAN);
		V_setValue(p, (void*)res);
		return p;
	} else if (strcmp(word, "false")==0) {
		bool* res = (bool*)malloc(sizeof(bool));
		*res = false;
		V_setType(p, BOOLEAN);
		V_setValue(p, (void*)res);
		return p;
	} else {
		/*p->value = P_process_var(word);*/
		wordcp = (char*)malloc(sizeof(char)*(strlen(word)+1));
		strcpy(wordcp, word);
		V_setType(p, VARIABLE);
		V_setName(p, wordcp);
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
	free((void*)word);
	lend = res;
	while(end!=-1) {
		word = P_getNextWord(line, end, &end);
		/*printf("word : %s\n", word);*/
		LL_add(&ltemp, P_process(word));
		free((void*)word);
		LL_setNext(&lend, ltemp);
		lend = ltemp;
		ltemp = NULL;
	}
	return res;
}
