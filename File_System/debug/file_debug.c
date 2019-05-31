/*
 * This file is used to test the file module
 */

#include "file_system_linked_list.h"
#include "file_system_username_cache.h"

int main ()
{
    /*
    userNode *rank_list;
    rank_list = Load_Rank ();
    rank_list = Add_Node (rank_list, 996, "007");
    Write_Rank (rank_list);
    */
    Save_Username ("test");
    printf ("%s\n", Load_Last_Username ());
    return 0;
}