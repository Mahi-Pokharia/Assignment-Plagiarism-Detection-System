#include "processing.h"

void processText(char *text){
    int i, j= 0;
    char temp[strlen(text)+1];
    for (i= 0; text[i] !='\0'; i++) {
        if (isalnum(text[i]) || isspace(text[i])){
            temp[j++]= tolower(text[i]);
        }
    }
    temp[j]='\0';
    strcpy(text, temp);
}

char **tokenizeText(char *text, int *wordCount){
    char **words= malloc(1000 * sizeof(char *));
    char *token= strtok(text, " ");
    int i=0;
    while (token) {
        words[i]= malloc(strlen(token) + 1);
        strcpy(words[i], token);
        i++;
        token=strtok(NULL, " ");
    }
    *wordCount=i;
    return words;
}

char **createNgrams(char **words, int wordCount, int n, int *ngramCount){
    int total=wordCount-n+1;
    char **ngrams=malloc(total *sizeof(char *));
    char buffer[256];

    for (int i=0; i< total; i++){
        buffer[0]='\0';
        for (int j=i; j<i+n; j++){
            strcat(buffer, words[j]);
            if (j < i+n-1) strcat(buffer," ");
        }
        ngrams[i]= malloc(strlen(buffer)+1);
        strcpy(ngrams[i], buffer);
    }
    *ngramCount=total;
    return ngrams;
}
