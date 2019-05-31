#include "file_system_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

userNode *Load_Rank ()
{
    int score;
    char name[100];
    userNode *head = NULL, *p, *tail = NULL;

    FILE *rank_table = fopen (RANK_FILE, "r");
    if (rank_table == NULL) {
        printf ("No such file or directory! Will create new one!\n");
        FILE *rank_table = fopen (RANK_FILE, "w");
        return NULL;
    } else {
        while (!feof(rank_table)) {
            if (fscanf (rank_table, "%d,", &score) == EOF)
                break;
//            printf ("%d\n", score);
            p = (struct user_node *) malloc (sizeof (userNode));
            p->score = score;
            fscanf (rank_table, "\"%[^\"]\"", p->name);
            p->next = NULL;
            if (tail)
                tail->next = p;
            else
                head = p;
            tail = p;
        }
    }
    fclose (rank_table);
    return head;
}

userNode *Add_Node (userNode *head, int score, char *name)
{
    userNode *p, *q, *new;
    new = (userNode *) malloc (sizeof (userNode));
    new->score = score;
    strcpy (new->name, name);
    for (p = head, q = NULL; p; q = p, p = p->next) {
        if (score > p->score)
            break;
    } // move the last node
    if (q) // not head
    {
        q->next = new;
        new->next = p;
    } else // is head
    {
        new->next = head;
        head = new;
    }
    return head;
}

void Write_Rank (userNode *head)
{
    FILE *rank_table = fopen (RANK_FILE, "w");
    userNode *p = NULL;
    for (p = head; p; p = p->next) {
        fprintf (rank_table, "%d,\"%s\"\n", p->score, p->name);
    }
    fclose (rank_table);
}

