#include "searching.h"
#include "processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total_phrases = 0;
int total_matches = 0;
float percent = 0.0;

void computeLPS(char *pattern, int M, int *lps){
    int len=0, i=1;
    lps[0] = 0;
    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i]=len;
            i++;
        } 
        else if(len!=0){
            len=lps[len-1];
        }
        else{
            lps[i++]=0;
        }
    }
}

int KMPSearch(char *pattern, char *text){
    int M=strlen(pattern), N=strlen(text);
    int *lps= malloc(M*sizeof(int));

    computeLPS(pattern, M, lps);

    int i=0, j=0;
    while (i<N){
        if (text[i] == pattern[j]){ 
            i++; 
            j++; 
        }
        if (j == M){ 
            free(lps); 
            return 1; 
        }
        else if(i<N && text[i]!= pattern[j]){
            j ? j = lps[j - 1] : i++;
        }
    }
    free(lps);
    return 0;
}

float detectPlagiarism(char *textA, char *textB){
    char *copyA=strdup(textA);
    char *copyB=strdup(textB);

    processText(copyA);
    processText(copyB);

    int countA, countB;
    char **wordsA=tokenizeText(copyA, &countA);
    char **wordsB=tokenizeText(copyB, &countB);
    int ngramCount;
    char **ngrams=createNgrams(wordsA, countA, 2, &ngramCount);
    total_phrases= ngramCount;
    total_matches=0;

    int bufSize=1;
    for(int i=0; i<countB; i++){
        bufSize += strlen(wordsB[i]) + 1;
    }

    char *textB_joined = malloc(bufSize);
    textB_joined[0] = '\0';
    for(int i = 0; i < countB; i++){
        strcat(textB_joined, wordsB[i]);
        strcat(textB_joined, " ");
    }

    for (int i = 0; i < ngramCount; i++){
        if (KMPSearch(ngrams[i], textB_joined)) total_matches++;
    }
    percent = total_phrases ? ((float)total_matches / total_phrases) * 100 : 0;

    for (int i = 0; i < countA; i++)
        free(wordsA[i]);
    for (int i = 0; i < countB; i++)
        free(wordsB[i]);
    for (int i = 0; i < ngramCount; i++)
        free(ngrams[i]);
    free(wordsA); 
    free(wordsB); 
    free(ngrams);
    free(textB_joined); 
    free(copyA); 
    free(copyB);
    return percent;
}
