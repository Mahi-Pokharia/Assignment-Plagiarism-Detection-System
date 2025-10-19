#ifndef PROCESSING_H
#define PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//lowercase and remove punctuation
void processText(char *text);

//tokenize
char **tokenizeText(char *text, int *wordCount);

//Creating n-grams
char **createNgrams(char **words, int wordCount, int n, int *ngramCount);

#endif
