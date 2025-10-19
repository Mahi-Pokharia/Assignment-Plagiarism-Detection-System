#include "file_handling.h"

char *readFile(const char *filename){
    FILE *fp=fopen(filename, "r");
    if (!fp) {
        printf("File '%s' not found. Creating a sample file...\n", filename);
        fp = fopen(filename, "w");
        if (!fp){
            printf("Cannot create file '%s'\n", filename);
            return NULL;
        }
        fprintf(fp,"This is a sample assignment for testing.\n");
        fclose(fp);
        fp = fopen(filename,"r");
        if (!fp){
            printf("Error reopening file '%s'\n", filename);
            return NULL;
        }
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *text = malloc(size + 1);
    if (!text){
        printf("Memory allocation failed.\n");
        fclose(fp);
        return NULL;
    }

    fread(text,1,size,fp);
    text[size]='\0';
    fclose(fp);

    printf("File '%s' read successfully (%ld bytes).\n", filename,size);
    return text;
}
