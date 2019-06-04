#include "Serial.h"
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "graphics.h"

#include "handlers.h"

HANDLE hCom;

void ReadSerial ();

void InitSerial ()
{
    hCom = CreateFile (TEXT("com4"),//COM1口
                       GENERIC_READ, //允许读
                       0, //指定共享属性，由于串口不能共享，所以该参数必须为0
                       NULL,
                       OPEN_EXISTING, //打开而不是创建

                       FILE_ATTRIBUTE_NORMAL, //属性描述，该值为FILE_FLAG_OVERLAPPED，表示使用异步I/O，该参数为0，表示同步I/O操作
                       NULL);

    if (hCom == INVALID_HANDLE_VALUE) {
        printf ("Open COM Failed!\n");
        return;
    } else {
        printf ("Open COM Succeed!\n");
    }

    SetupComm (hCom, 1024, 1024); //输入缓冲区和输出缓冲区的大小都是1024

    /*********************************超时设置**************************************/
    COMMTIMEOUTS TimeOuts;
    //设定读超时
    TimeOuts.ReadIntervalTimeout = MAXDWORD;//读间隔超时
    TimeOuts.ReadTotalTimeoutMultiplier = 0;//读时间系数
    TimeOuts.ReadTotalTimeoutConstant = 0;//读时间常量
    //设定写超时
    TimeOuts.WriteTotalTimeoutMultiplier = 1;//写时间系数
    TimeOuts.WriteTotalTimeoutConstant = 1;//写时间常量
    SetCommTimeouts (hCom, &TimeOuts); //设置超时

    /*****************************************配置串口***************************/
    DCB dcb;
    GetCommState (hCom, &dcb);
    dcb.BaudRate = 9600; //波特率为9600
    dcb.ByteSize = 8; //每个字节有8位
    dcb.Parity = NOPARITY; //无奇偶校验位
    dcb.StopBits = ONESTOPBIT; //一个停止位
    SetCommState (hCom, &dcb);
}

DWORD WINAPI Serial_Func (LPVOID lpParam)
{
    ReadSerial ();
}

void Serial_Background ()
{
    CreateThread (
        NULL,   // default security attributes
        0, // use default stack size
        Serial_Func, // thread function
        NULL,// argument to thread function
        0, // use default creation flags
        NULL);// returns the thread identifier
}

void ReadSerial ()
{
    DWORD wCount;//实际读取的字节数
    bool bReadStat;
    static int cnt[4];

    char str[2] = {0};

    while (1) {
        // PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR); //清空缓冲区
        bReadStat = ReadFile (hCom, str, sizeof (str), &wCount, NULL);

        if (!bReadStat) {
            printf ("Read error!");
            return;
        } else {
            //str[1] = '\0';
            if (isalpha (str[0])) {
                printf ("%c\n", str[0]);
                switch (str[0]) {
                    case 'I'://up
                        keyboardEventHandler (VK_UP, KEY_DOWN);
                        break;
                    case 'J'://down
                        keyboardEventHandler (VK_SPACE, KEY_DOWN);
                        break;
                    case 'K'://left
                        keyboardEventHandler (VK_LEFT, KEY_DOWN);
                        break;
                    case 'L'://right
                        keyboardEventHandler (VK_RIGHT, KEY_DOWN);
                        break;
                    case 'A':
                        cnt[0] ++;
                        if (cnt[0] == 3)
                        {
                            cnt[0] = 0;
                            keyboardEventHandler (VK_UP, KEY_DOWN);
                        }
                        break;
                    case 'B':
                        cnt[1] ++;
                        if (cnt[1] == 3)
                        {
                            cnt[1] = 0;
                            keyboardEventHandler (VK_SPACE, KEY_DOWN);
                        }
                        break;
                    case 'C':
                        cnt[2] ++;
                        if (cnt[2] == 3)
                        {
                            cnt[2] = 0;
                            keyboardEventHandler (VK_LEFT, KEY_DOWN);
                        }
                        break;
                    case 'D':
                        cnt[3] ++;
                        if (cnt[3] == 3)
                        {
                            cnt[3] = 0;
                            keyboardEventHandler (VK_RIGHT, KEY_DOWN);
                        }
                        break;

                }
            }
        }
//        Sleep(1);
    }
}