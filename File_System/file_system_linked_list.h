#ifndef _FILE_SYSTEM_LINKED_LIST_H_
#define _FILE_SYSTEM_LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANK_FILE "rank.csv"
typedef struct user_node
{
    char name[100];          /*名称*/
    int score;              /*成绩*/
    struct user_node *next; /*指向下个结点的指针*/
} userNode;

userNode *Load_Rank();

userNode* Add_Node(userNode *head, int score, char* name);

void write_Rank(userNode *head);


/* TODO
 *      5. 鲁棒性待修复，因为一旦文件在程序运行前被损坏，出了问题估计就凉了……
 *
 */

#endif //_FILE_SYSTEM_LINKED_LIST_H_
