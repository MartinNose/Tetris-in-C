#include "file_system_linked_list.h"

int main()
{
    userNode* rank_list;
    rank_list = Load_Rank ();
    rank_list = Add_Node (rank_list, 996, "007");
    write_Rank (rank_list);
    return 0;
}