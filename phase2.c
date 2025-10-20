#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USERS_FILE "users.txt"
#define WM_START "WM_START:"
#define WM_END ":WM_END"
#define WM_PREFIX "@College2025"

typedef struct
{
    char uname[100];
    char pass[100];
} user;

void checkUserFile()
{
    FILE *fp = fopen(USERS_FILE, "r");
    if (fp)
    {
        fclose(fp);
        return;
    }
    fp = fopen(USERS_FILE, "w");
    if (!fp)
    {
        printf("Error creating users file!\n");
        return;
    }
    fprintf(fp, "admin:admin\n");
    fclose(fp);
}

int login(char *logged, int len)
{
    checkUserFile();
    char u[100], p[100];
    printf("Username: ");
    fgets(u, sizeof(u), stdin);
    printf("Password: ");
    fgets(p, sizeof(p), stdin);

    u[strcspn(u, "\n")] = 0;
    p[strcspn(p, "\n")] = 0;

    FILE *fp = fopen(USERS_FILE, "r");
    if (!fp)
    {
        printf("Error opening user file!\n");
        return 0;
    }

    char line[200];
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = 0;
        char *sep = strchr(line, ':');
        if (sep)
        {
            *sep = '\0';
            if (strcmp(line, u) == 0 && strcmp(sep + 1, p) == 0)
            {
                strncpy(logged, u, len - 1);
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

unsigned long getChecksum(const unsigned char *buf, size_t len)
{
    unsigned long h = 1469598103934665603UL;
    for (size_t i = 0; i < len; i++)
    {
        h ^= (unsigned long)buf[i];
        h *= 1099511628211UL;
    }
    return h;
}

char *makeWatermark(const char *user, unsigned long chk)
{
    time_t t = time(NULL);
    char *w = malloc(200);
    if (!w)
        return NULL;
    sprintf(w, "%s|%s|%ld|%lu", WM_PREFIX, user, (long)t, chk);
    return w;
}

int addWatermark(const char *fname, const char *user)
{
    FILE *fp = fopen(fname, "rb");
    if (!fp)
    {
        printf("File not found: %s\n", fname);
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    unsigned char *buf = malloc(size + 1);
    fread(buf, 1, size, fp);
    buf[size] = '\0';
    fclose(fp);

    if (strstr((char *)buf, WM_START))
    {
        printf("Watermark already added!\n");
        free(buf);
        return 0;
    }

    unsigned long chk = getChecksum(buf, size);
    char *wm = makeWatermark(user, chk);
    char final[400];
    sprintf(final, "\n%s%s%s\n", WM_START, wm, WM_END);

    fp = fopen(fname, "ab");
    if (!fp)
    {
        printf("Error writing file!\n");
        free(buf);
        free(wm);
        return 0;
    }

    fwrite(final, 1, strlen(final), fp);
    fclose(fp);

    printf("Watermark added successfully!\n");
    free(buf);
    free(wm);
    return 1;
}

void menu()
{
    printf("\n--- Watermark System ---\n");
    printf("1. Add Watermark\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    char logged[100];
    printf("Welcome to Watermarked File System (Phase 2)\n");

    if (!login(logged, sizeof(logged)))
    {
        printf("Login failed!\n");
        return 0;
    }

    printf("Login success. Hello %s!\n", logged);

    while (1)
    {
        menu();
        char ch[10];
        fgets(ch, sizeof(ch), stdin);
        int c = atoi(ch);

        if (c == 1)
        {
            char fname[100];
            printf("Enter file name: ");
            fgets(fname, sizeof(fname), stdin);
            fname[strcspn(fname, "\n")] = 0;
            addWatermark(fname, logged);
        }
        else if (c == 2)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Invalid option!\n");
        }
    }

    return 0;
}