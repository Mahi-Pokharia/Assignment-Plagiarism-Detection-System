#ifndef SEARCHING_H
#define SEARCHING_H

extern int total_phrases;
extern int total_matches;
extern float percent;

// KMP search for pattern in text
int KMPSearch(char *pattern, char *text);
// Detect plagiarism: input tokenized words arrays
float detectPlagiarism(char *textA, char *textB);

#endif
