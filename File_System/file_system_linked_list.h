/*
 * This file contains functions that maintains a linked-list which saves the scores
 */

#ifndef _FILE_SYSTEM_LINKED_LIST_H_
#define _FILE_SYSTEM_LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*File Name*/
#define RANK_FILE "rank.csv"

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

/*
 * Function: Add_Node
 * Usage: Give the head, score, and username to it,
 * it will add this node into the list
 * ------------------------------------------------
 * This function helps maintain the linked-list
 * It will ensure the score in every node is descending
 */
userNode *Add_Node (userNode *head, int score, char *name);

/*
 * Function: Write_Rank
 * Usage: Just give the head pointer of the list,
 * it will write the data into the file
 * ----------------------------------------------
 * This function traverses the linked-list and writes
 * the data in CSV format
 */
void Write_Rank (userNode *head);

#endif //_FILE_SYSTEM_LINKED_LIST_H_
