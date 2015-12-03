#include <stdlib.h>
#include <string.h>

char *string(char *arg, int size){
	char *str=malloc(size);
	str=arg;
	return str;
}

//find the position of c in string relative to string initial character
int charpos(const char *string, int c){
	char *p = strchr(string, c);
	if(p)
		return p-string;
	return -1; //not found;
}

char *getFilename(const char *string, int endpos){
	char *strdest = malloc(endpos);
	strncpy(strdest, string, endpos);
	strdest[endpos]='\0';
	return strdest;
}

//imgout/ + path 
char *appendString(char *string, char *string2){
	int nsize1=strlen(string);
	int nsize2=strlen(string2);
	//create string allocation and set all occupied mems to zero
	int nsize=nsize1+nsize2+1;
	char *strdest = malloc(nsize);
	memset(strdest,0,nsize);
	strcat(strdest, string);
	strcat(strdest, string2);
	return strdest;
}
