//
// Created by Tao Chiang on 5/28/2019.
//
#include <stdlib.h>

#include "file_system_game_status.h"

void Load_Saved_Game(Checkerboard** saved_board, tetrimino** saved_tetri, tetrimino** saved_next_tetri, tetrimino** saved_held_tetri)
{
    int i, j;
    FILE* saved_game = fopen ("saved_game.txt", "r");
    if (saved_game == NULL)
    {
        *saved_board = NULL;
        *saved_tetri = NULL;
        return;
    }
    else
    {
        *saved_board = (Checkerboard*)malloc (sizeof(Checkerboard));
        for (i = 0; i < 14; i++)
        {
            for (j = 0; j < 25; j++)
                if (fscanf (saved_game, "%d", &(*saved_board)->block[i][j]) != 1)
                {
                    *saved_board = NULL;
                    *saved_tetri = NULL;
                    return;
                }
        }

        *saved_tetri = (tetrimino*)malloc (sizeof (tetrimino));
        if (fscanf (saved_game, "%d %d %d %d", &(*saved_tetri)->x, &(*saved_tetri)->y, &(*saved_tetri)->type, &(*saved_tetri)->direction) != 4)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }
        if (fscanf (saved_game, "%lf", &(*saved_tetri)->yVelocity) != 1)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }
        if (fscanf (saved_game, "%d", &(*saved_tetri)->isPaused) != 1)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }

        *saved_next_tetri = (tetrimino*)malloc (sizeof (tetrimino));
        if (fscanf (saved_game, "%d %d %d %d", &(*saved_next_tetri)->x, &(*saved_next_tetri)->y, &(*saved_next_tetri)->type, &(*saved_next_tetri)->direction) != 4)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }
        if (fscanf (saved_game, "%lf", &(*saved_next_tetri)->yVelocity) != 1)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }
        if (fscanf (saved_game, "%d", &(*saved_next_tetri)->isPaused) != 1)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }

        *saved_held_tetri = (tetrimino*)malloc (sizeof (tetrimino));
        if (fscanf (saved_game, "%d %d %d %d", &(*saved_held_tetri)->x, &(*saved_held_tetri)->y, &(*saved_held_tetri)->type, &(*saved_held_tetri)->direction) != 4)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }
        if (fscanf (saved_game, "%lf", &(*saved_held_tetri)->yVelocity) != 1)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }
        if (fscanf (saved_game, "%d", &(*saved_held_tetri)->isPaused) != 1)
        {
            *saved_board = NULL;
            *saved_tetri = NULL;
            return;
        }
    }
}

void Save_Game(Checkerboard* cur_board, tetrimino* cur_tetri, tetrimino* next_tetri, tetrimino* held_tetri)
{
    int i, j;
    FILE* saved_game = fopen ("saved_game.txt", "w");
    if (saved_game == NULL)
    {
        printf ("Unable to create file!\n");
    }
    else
    {
        for (i = 0; i < 14; i++)
        {
            for (j = 0; j < 25; j++)
                fprintf (saved_game, "%d ", cur_board->block[i][j]);
            fprintf (saved_game, "\n");
        }
        fprintf (saved_game, "%d %d %d %d\n", cur_tetri->x, cur_tetri->y, cur_tetri->type, cur_tetri->direction);
        fprintf (saved_game, "%lf\n", cur_tetri->yVelocity);
        fprintf (saved_game, "%d\n", cur_tetri->isPaused);
        fprintf (saved_game, "%d %d %d %d\n", next_tetri->x, next_tetri->y, next_tetri->type, next_tetri->direction);
        fprintf (saved_game, "%lf\n", next_tetri->yVelocity);
        fprintf (saved_game, "%d\n", next_tetri->isPaused);
        fprintf (saved_game, "%d %d %d %d\n", held_tetri->x, held_tetri->y, held_tetri->type, held_tetri->direction);
        fprintf (saved_game, "%lf\n", held_tetri->yVelocity);
        fprintf (saved_game, "%d\n", held_tetri->isPaused);
    }
}