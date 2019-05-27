//
// Created by Tao Chiang on 5/27/2019.
//

#include "file_system.h"
#include <stdio.h>
#include <stdlib.h>

struct user_node
{
    int num;                /*编号*/
    char name[100];          /*名称*/
    int score;              /*成绩*/
    struct user_node *next; /*指向下个结点的指针*/
};

struct user_node* rank_list;

struct user_node *Load_Rank()
{
    int num, score;
    char name[100];
    struct user_node *head = NULL, *p, *tail = NULL;

    FILE* rank_table = fopen("rank.txt", "r");
    if (rank_table == NULL)
    {
        printf ("No such file or directory! Will create new one!\n");
        FILE* rank_table = fopen("rank.txt", "w");
        return NULL;
    }
    else
    {
        while (!feof(rank_table))
        {
            fscanf(rank_table, "%d %d", &num, &score);
            printf ("%d %d\n", num, score);
            p = (struct user_node *)malloc(sizeof(struct user_node));
            p->num = num;
            p->score = score;
            fscanf (rank_table, "%s", p->name);
            p->next = NULL;
            if (tail)
                tail->next = p;
            else
                head = p;
            tail = p;
        }
    }
    fclose(rank_table);
    return head;
}

int main()
{
    rank_list = Load_Rank ();

    return 0;
}
