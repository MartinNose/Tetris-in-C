#include "file_system_username_cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Save_Username (char *username)
{
    FILE *user_cache = fopen ("user_cache.txt", "w");
    if (user_cache == NULL) {
        printf ("File Generation Failed!");
    } else {
        fprintf (user_cache, "%s\n", username);
    }
    fclose (user_cache);
}

char *Load_Last_Username ()
{
    FILE *user_cache = fopen ("user_cache.txt", "r");
    char *res = (char *) malloc (19 * sizeof (char));
    if (user_cache == NULL) {
        strcpy (res, "DEFAULT");
    } else {
        fscanf (user_cache, "%[^\n]", res);
    }
    fclose (user_cache);
    return res;
}