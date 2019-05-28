//
// Created by Tao Chiang on 5/28/2019.
//
#include "file_system.h"

int main()
{
    userNode* rank_list;
    rank_list = Load_Rank ();
    rank_list = Add_Node (rank_list, 996, "007");
    write_Rank (rank_list);
    return 0;
}