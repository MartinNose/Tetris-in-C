#include <stdlib.h>

#include "file_system_game_status.h"

#include <Windows.h>
#include <CommDlg.h>

static OPENFILENAME ofn;

void PopFileInitialize (HWND hwnd)
{
    static TCHAR szFilter[] = TEXT ("Tetris Game File (*.tetris_game)\0*.tetris_game\0\0");

    ofn.lStructSize = sizeof (OPENFILENAME);
    ofn.hwndOwner = hwnd;
    ofn.hInstance = NULL;
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxCustFilter = 0;
    ofn.nFilterIndex = 0;
    ofn.lpstrFile = NULL;          // Set in Open and Close functions
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFileTitle = NULL;          // Set in Open and Close functions
    ofn.nMaxFileTitle = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = NULL;
    ofn.Flags = 0;             // Set in Open and Close functions
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = TEXT ("jpg");
    ofn.lCustData = 0L;
    ofn.lpfnHook = NULL;
    ofn.lpTemplateName = NULL;
}

BOOL PopFileOpenDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = pstrFileName;
    ofn.lpstrFileTitle = pstrTitleName;
    ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

    return GetOpenFileName (&ofn);
}

BOOL PopFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = pstrFileName;
    ofn.lpstrFileTitle = pstrTitleName;
    ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;

    return GetSaveFileName (&ofn);
}

bool
File_Load_Saved_Game (Checkerboard *saved_board, tetrimino *saved_tetri, tetrimino *saved_que1, tetrimino *saved_que2, tetrimino *saved_held_tetri, int *score, bool *mouse_mode, bool *music_on)
{
    int i, j;
    bool ok_flag = TRUE;
    static TCHAR szFileName[MAX_PATH], szTitleName[MAX_PATH];
    HWND hwnd;
    hwnd = GetForegroundWindow (); //获取前台窗口句柄。本程序中的前台窗口就是控制台窗口。
    PopFileInitialize (hwnd);  //初始化ofn
    PopFileOpenDlg (hwnd, szFileName, szTitleName);//打开文件对话框
    printf ("%s\n", szFileName);  //在控制台中显示选中文件的路径
    FILE *saved_game = fopen (szFileName, "r");
    if (saved_game == NULL) {
        ok_flag = FALSE;
    } else {
        for (i = 0; i < 14; i++) {
            for (j = 0; j < 25; j++)
                if (fscanf (saved_game, "%d", &saved_board->block[i][j]) != 1) {
                    ok_flag = FALSE;
                    break;
                }
            if (!ok_flag)
                break;
        }

        /*Saved-Tetri*/
        if (!ok_flag ||
            fscanf (saved_game, "%d %d %d %d", &saved_tetri->x, &saved_tetri->y, &saved_tetri->type, &saved_tetri->direction)
            != 4) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%lf", &saved_tetri->yVelocity) != 1) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%d", &saved_tetri->isPaused) != 1) {
            ok_flag = FALSE;
        }

        /*Que1*/
        if (!ok_flag ||
            fscanf (saved_game, "%d %d %d %d", &saved_que1->x, &saved_que1->y, &saved_que1->type, &saved_que1->direction)
            != 4) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%lf", &saved_que1->yVelocity) != 1) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%d", &saved_que1->isPaused) != 1) {
            ok_flag = FALSE;
        }

        /*Que2*/
        if (!ok_flag ||
            fscanf (saved_game, "%d %d %d %d", &saved_que2->x, &saved_que2->y, &saved_que2->type, &saved_que2->direction)
            != 4) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%lf", &saved_que2->yVelocity) != 1) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%d", &saved_que2->isPaused) != 1) {
            ok_flag = FALSE;
        }


        /*Held-Tetri*/
        if (!ok_flag ||
            fscanf (saved_game, "%d %d %d %d", &saved_held_tetri->x, &saved_held_tetri->y, &saved_held_tetri->type, &saved_held_tetri->direction)
            != 4) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%lf", &saved_held_tetri->yVelocity) != 1) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%d", &saved_held_tetri->isPaused) != 1) {
            ok_flag = FALSE;
        }

        if (!ok_flag || fscanf (saved_game, "%d", score) != 1) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%d", mouse_mode) != 1) {
            ok_flag = FALSE;
        }
        if (!ok_flag || fscanf (saved_game, "%d", music_on) != 1) {
            ok_flag = FALSE;
        }
    }
    fclose (saved_game);
    return ok_flag;
}

void
File_Save_Game (Checkerboard *cur_board, tetrimino *cur_tetri, tetrimino *que1, tetrimino *que2, tetrimino *held_tetri, int score, bool mouse_mode, bool music_on)
{
    int i, j;
    static TCHAR szFileName[MAX_PATH], szTitleName[MAX_PATH];
    HWND hwnd;
    hwnd = GetForegroundWindow (); //获取前台窗口句柄。本程序中的前台窗口就是控制台窗口。
    PopFileInitialize (hwnd);  //初始化ofn
    PopFileSaveDlg (hwnd, szFileName, szTitleName);//打开文件对话框
    printf ("%s\n", szFileName);  //在控制台中显示选中文件的路径
    FILE *saved_game = fopen (szFileName, "w");
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