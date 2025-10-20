#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_handling.h"
#include "processing.h"
#include "searching.h"
#include "report.h"

int main()
{
    char file1[100], file2[100];
    char *text1 = NULL, *text2 = NULL;
    float percent = 0.0;
    int ch;

    printf("\n-------------------------------------------");
    printf("\n       PLAGIARISM DETECTION SYSTEM");
    printf("\n-------------------------------------------");

    while (1)
    {
        printf("\n\n1. Input Files");
        printf("\n2. Check Plagiarism");
        printf("\n3. Show Report");
        printf("\n4. Exit");
        printf("\n-------------------------------------------");
        printf("\nEnter your choice : ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("\nEnter reference file name (original): ");
            scanf("%s", file1);
            printf("Enter file to check : ");
            scanf("%s", file2);

            text1 = readFile(file1);
            text2 = readFile(file2);

            if (text1 != NULL && text2 != NULL)
                printf("\nFiles read successfully.\n");
            else
                printf("\nError in reading files.\n");
            break;

        case 2:
            if (text1 != NULL && text2 != NULL)
            {
                processText(text1);
                processText(text2);
                percent = detectPlagiarism(text1, text2);
                printf("\nComparison Done.\n");
                printf("Copied content : %.2f %%\n", percent);
            }
            else
            {
                printf("\nPlease load both files first.\n");
            }
            break;

        case 3:
            if (percent > 0)
                generateReport(percent);
            else
                printf("\nNo report generated yet.\n");
            break;

        case 4:
            printf("\nExiting Program... Thank you!\n");
            free(text1);
            free(text2);
            exit(0);

        default:
            printf("\nInvalid choice. Try again.\n");
        }
    }

    return 0;
}