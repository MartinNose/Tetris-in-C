#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#define SYSCOLOR "Red" 
#define TIMER_BLINK500  1     /*500ms定时器事件标志号*/
#define TIMER_BLINK1000 2     /*1000ms定时器时间标志号*/
void DefineRGBColor (string s, int r, int g, int b)
{
    DefineColor (s, r / 255.0, g / 255.0, b / 255.0);
}
void DefineColors ()
{
    DefineRGBColor ("Magenta", 138, 43, 226); //blueviolet
    DefineRGBColor ("Blue", 30, 144, 255); //dodgerblue
    DefineRGBColor ("Cyan", 127, 255, 212); //aquamarine
    DefineRGBColor ("Yellow", 255, 215, 0); //gold
    DefineRGBColor ("Green", 34, 139, 34);//forestgreen
    DefineRGBColor ("Light Gray", 105, 105, 105);//dimgray
    DefineRGBColor ("Red", 220, 20, 60);//crimson
    DefineRGBColor ("Dark Turquoise", 0, 206, 209);//dark turquoise
    DefineRGBColor ("Midnight Blue", 25, 25, 112);
    DefineRGBColor ("Corn Silk", 255, 248, 220);
    DefineRGBColor ("Light Cyan", 224, 255, 255);
    DefineRGBColor ("Gainsboro", 220, 220, 220);
    DefineRGBColor ("White Smoke",245, 245, 245);
};
const int mseconds500 = 500;   
const int mseconds1000 = 1000; 
typedef struct {/*矩形类型*/
	double x1, y1;/*左下角坐标*/
    double x2, y2;/*右上角坐标*/
    int PenSize; /*粗细*/
    string color; /*颜色*/
} *RectT;
	double x,y;
void fillRectangle(double x, double y, double w, double h)
{
    MovePen(x, y);
    StartFilledRegion(1); // 开始
        DrawLine(0, h);
        DrawLine(w, 0);
        DrawLine(0, -h);
        DrawLine(-w, 0);
    EndFilledRegion();   // 结束
}
void draw1(void){	

double x,y;
	 x = GetWindowWidth()/36;
     y = GetWindowHeight()/41;
    	SetPenColor("Red"); 
    	MovePen(16*x,25*y);
   fillRectangle(0,0,36*x,41*y);
   /*以下绘制Tetris!*/ 
   SetPenColor("White");
   fillRectangle(6*x,26*y,3*x,y);
   fillRectangle(7*x,19*y,x,7*y);
   fillRectangle(10*x,19*y,x,6*y);
   fillRectangle(10*x,19*y,3*x,y);
   fillRectangle(12*x,20*y,x,y);
   fillRectangle(10*x,22*y,3*x,y);
   fillRectangle(10*x,24*y,3*x,y);
   fillRectangle(12*x,22*y,x,2*y);
   fillRectangle(14*x,19*y,x,9*y);
   fillRectangle(14*x,19*y,2*x,y);
   fillRectangle(14*x,24*y,2*x,y);
   fillRectangle(17*x,19*y,x,6*y);
   fillRectangle(17*x,24*y,2*x,y);  
   fillRectangle(20*x,19*y,x,6*y);
   fillRectangle(20*x,26*y,x,y);
   fillRectangle(22*x,19*y,3*x,1*y);
   fillRectangle(22*x,21*y,1*x,4*y);
   fillRectangle(22*x,21*y,3*x,2*y);
   fillRectangle(24*x,20*y,1*x,1*y);
   fillRectangle(22*x,24*y,3*x,1*y);
   fillRectangle(26*x,19*y,1*x,1*y);
   fillRectangle(26*x,21*y,1*x,6*y);
   
   /*绘制分隔条*/ 
   fillRectangle(0,10*y,36*x,1*y); 
   /*绘制底部彩块*/ 
   SetPenColor("Yellow");
   fillRectangle(0*x,7*y,5*x,3*y);
   fillRectangle(2*x,4*y,6*x,3*y);
   SetPenColor("Blue");
   fillRectangle(0*x,0*y,8*x,4*y);
   fillRectangle(0*x,0*y,2*x,7*y);
   SetPenColor("Green");
   fillRectangle(5*x,7*y,6*x,3*y);
   fillRectangle(8*x,0*y,3*x,7*y);
   SetPenColor("Gray");
   fillRectangle(11*x,7*y,12*x,3*y);
   SetPenColor("Black");
   fillRectangle(11*x,0*y,3*x,7*y);
   fillRectangle(11*x,0*y,9*x,4*y);
   SetPenColor("Red");
   fillRectangle(14*x,4*y,12*x,3*y);
   SetPenColor("Green");
   fillRectangle(20*x,0*y,9*x,4*y);
   fillRectangle(26*x,0*y,3*x,7*y);
   SetPenColor("Yellow");
   fillRectangle(23*x,7*y,6*x,3*y);
   fillRectangle(29*x,4*y,3*x,6*y);
   SetPenColor("Green");
   fillRectangle(32*x,4*y,6*x,6*y);
      SetPenColor("Blue");
   fillRectangle(29*x,0*y,7*x,4*y);
	
}
void draw2(void){
		double x,y;
	 x = GetWindowWidth()/36;
     y = GetWindowHeight()/41;
    	SetPenColor("Red"); 
    	MovePen(16*x,25*y);
   fillRectangle(0,0,36*x,41*y);
   /*以下绘制Tetris!*/ 
   SetPenColor("Yellow");
   fillRectangle(6*x,26*y,3*x,y);
   fillRectangle(7*x,19*y,x,7*y);
   fillRectangle(10*x,19*y,x,6*y);
   fillRectangle(10*x,19*y,3*x,y);
   fillRectangle(12*x,20*y,x,y);
   fillRectangle(10*x,22*y,3*x,y);
   fillRectangle(10*x,24*y,3*x,y);
   fillRectangle(12*x,22*y,x,2*y);
   fillRectangle(14*x,19*y,x,9*y);
   fillRectangle(14*x,19*y,2*x,y);
   fillRectangle(14*x,24*y,2*x,y);
   fillRectangle(17*x,19*y,x,6*y);
   fillRectangle(17*x,24*y,2*x,y);  
   fillRectangle(20*x,19*y,x,6*y);
   fillRectangle(20*x,26*y,x,y);
   fillRectangle(22*x,19*y,3*x,1*y);
   fillRectangle(22*x,21*y,1*x,4*y);
   fillRectangle(22*x,21*y,3*x,2*y);
   fillRectangle(24*x,20*y,1*x,1*y);
   fillRectangle(22*x,24*y,3*x,1*y);
   fillRectangle(26*x,19*y,1*x,1*y);
   fillRectangle(26*x,21*y,1*x,6*y);
   
   /*绘制分隔条*/ 
   SetPenColor("White");
   fillRectangle(0,10*y,36*x,1*y); 
   /*绘制底部彩块*/ 
   SetPenColor("Red");
   fillRectangle(0*x,7*y,5*x,3*y);
   fillRectangle(2*x,4*y,6*x,3*y);
   SetPenColor("Green");
   fillRectangle(0*x,0*y,8*x,4*y);
   fillRectangle(0*x,0*y,2*x,7*y);
   SetPenColor("Yellow");
   fillRectangle(5*x,7*y,6*x,3*y);
   fillRectangle(8*x,0*y,3*x,7*y);
   SetPenColor("Blue");
   fillRectangle(11*x,7*y,12*x,3*y);
   SetPenColor("Brown");
   fillRectangle(11*x,0*y,3*x,7*y);
   fillRectangle(11*x,0*y,9*x,4*y);
   SetPenColor("Green");
   fillRectangle(14*x,4*y,12*x,3*y);
   SetPenColor("Red");
   fillRectangle(20*x,0*y,9*x,4*y);
   fillRectangle(26*x,0*y,3*x,7*y);
   SetPenColor("Yellow");
   fillRectangle(23*x,7*y,6*x,3*y);
   fillRectangle(29*x,4*y,3*x,6*y);
   SetPenColor("Gray");
   fillRectangle(32*x,4*y,6*x,6*y);
      SetPenColor("Green");
   fillRectangle(29*x,0*y,7*x,4*y);
}
void TimerEventProcess(int timerID);
void Main(){
	InitGraphics();
	registerTimerEvent(TimerEventProcess);
    startTimer(TIMER_BLINK500, mseconds500);
}
void TimerEventProcess(int timerID)
{
    	static int flag=1;
	  switch (timerID) {
	    case TIMER_BLINK500:{ /*500ms光标闪烁定时器*/
      		
			if(flag==1){
				draw1();
				flag=2;
			}
			else{
				draw2();
				flag=1;
			}
   			break;
		}

	    default:
		  break;
	  }
}
























