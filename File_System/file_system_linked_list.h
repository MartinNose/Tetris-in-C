/*
 * This file contains functions that maintains a linked-list which saves the scores
 */

#ifndef _FILE_SYSTEM_LINKED_LIST_H_
#define _FILE_SYSTEM_LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANK_FILE "rank.csv" // File Name

/*Node Data Structure*/
typedef struct user_node {
    char name[100];         /*Username*/
    int score;              /*score*/
    struct user_node *next; /*Node to the next*/
} userNode;

/*
 * Function: Load_Rank
 * Usage: Just call it and it will return the head
 * pointer of the linked-list
 * -----------------------------------------------
 * This function reads the file, and creates a linked-list
 */
userNode *Load_Rank ();

userNode *Add_Node (userNode *head, int score, char *name);

void write_Rank (userNode *head);

#endif //_FILE_SYSTEM_LINKED_LIST_H_
