//
// Created by Tao Chiang on 5/27/2019.
//

#include "file_system.h"
#include <stdio.h>

void Load_Rank()
{
    int num, score;
    char name[100];
    FILE* rank_table = fopen("rank.txt", "r");
    if (rank_table == NULL)
    {
        printf ("No such file or directory! Will create new one!\n");
        FILE* rank_table = fopen("rank.txt", "w");
    }
    else
    {
        while (!feof(rank_table))
        {
            fscanf(rank_table, "%d %d %s", &num, &score, name);
            printf ("%d %d %s\n", num, score, name);
        }
    }
    fclose(rank_table);

}

int main()
{
    Load_Rank ();
    return 0;
}