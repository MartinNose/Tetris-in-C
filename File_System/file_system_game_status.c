#include <stdlib.h>

#include "file_system_game_status.h"

bool
File_Load_Saved_Game (Checkerboard *saved_board, tetrimino *saved_tetri, tetrimino *saved_que1, tetrimino *saved_que2, tetrimino *saved_held_tetri, int *score, bool *mouse_mode, bool *music_on)
{
    int i, j;
    FILE *saved_game = fopen ("saved_game.txt", "r");
    if (saved_game == NULL) {
        return FALSE;
    } else {
        for (i = 0; i < 14; i++) {
            for (j = 0; j < 25; j++)
                if (fscanf (saved_game, "%d", &saved_board->block[i][j]) != 1) {
                    fclose (saved_game);
                    return FALSE;
                }
        }

        if (fscanf (saved_game, "%d %d %d %d", &saved_tetri->x, &saved_tetri->y, &saved_tetri->type, &saved_tetri->direction)
            != 4) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%lf", &saved_tetri->yVelocity) != 1) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%d", &saved_tetri->isPaused) != 1) {
            fclose (saved_game);
            return FALSE;
        }

        if (fscanf (saved_game, "%d %d %d %d", &saved_que1->x, &saved_que1->y, &saved_que1->type, &saved_que1->direction)
            != 4) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%lf", &saved_que1->yVelocity) != 1) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%d", &saved_que1->isPaused) != 1) {
            fclose (saved_game);
            return FALSE;
        }

        if (fscanf (saved_game, "%d %d %d %d", &saved_que2->x, &saved_que2->y, &saved_que2->type, &saved_que2->direction)
            != 4) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%lf", &saved_que2->yVelocity) != 1) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%d", &saved_que2->isPaused) != 1) {
            fclose (saved_game);
            return FALSE;
        }

        if (fscanf (saved_game, "%d %d %d %d", &saved_held_tetri->x, &saved_held_tetri->y, &saved_held_tetri->type, &saved_held_tetri->direction)
            != 4) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%lf", &saved_held_tetri->yVelocity) != 1) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%d", &saved_held_tetri->isPaused) != 1) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%d", score) != 1) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%d", mouse_mode) != 1) {
            fclose (saved_game);
            return FALSE;
        }
        if (fscanf (saved_game, "%d", music_on) != 1) {
            fclose (saved_game);
            return FALSE;
        }
    }
    fclose (saved_game);
    return TRUE;
} // TODO improve...

void
File_Save_Game (Checkerboard *cur_board, tetrimino *cur_tetri, tetrimino *que1, tetrimino *que2, tetrimino *held_tetri, int score, bool mouse_mode, bool music_on)
{
    int i, j;
    FILE *saved_game = fopen ("saved_game.txt", "w");
    if (saved_game == NULL) {
        printf ("Unable to create file!\n");
    } else {
        for (i = 0; i < 14; i++) {
            for (j = 0; j < 25; j++)
                fprintf (saved_game, "%d ", cur_board->block[i][j]);
            fprintf (saved_game, "\n");
        }
        fprintf (saved_game, "%d %d %d %d\n", cur_tetri->x, cur_tetri->y, cur_tetri->type, cur_tetri->direction);
        fprintf (saved_game, "%lf\n", cur_tetri->yVelocity);
        fprintf (saved_game, "%d\n", cur_tetri->isPaused);
        fprintf (saved_game, "%d %d %d %d\n", que1->x, que1->y, que1->type, que1->direction);
        fprintf (saved_game, "%lf\n", que1->yVelocity);
        fprintf (saved_game, "%d\n", que1->isPaused);
        fprintf (saved_game, "%d %d %d %d\n", que2->x, que2->y, que2->type, que2->direction);
        fprintf (saved_game, "%lf\n", que2->yVelocity);
        fprintf (saved_game, "%d\n", que2->isPaused);
        fprintf (saved_game, "%d %d %d %d\n", held_tetri->x, held_tetri->y, held_tetri->type, held_tetri->direction);
        fprintf (saved_game, "%lf\n", held_tetri->yVelocity);
        fprintf (saved_game, "%d\n", held_tetri->isPaused);
        fprintf (saved_game, "%d\n", score);
        fprintf (saved_game, "%d\n", mouse_mode);
        fprintf (saved_game, "%d\n", music_on);
    }
    fclose (saved_game);
}