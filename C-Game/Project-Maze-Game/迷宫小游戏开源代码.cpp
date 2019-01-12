#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <iostream>
#include <stack>
//#include "mystack.h"
#include<stdlib.h>
#define MAXSIZE 1000

typedef struct point{
    int x;                  //栈记录小球x坐标 
    int y;                  //栈记录小球y坐标 
    int right;              //栈记录小球能否往右走（1为可以通行，0为不能通行） 
    int left;               //栈记录小球能否往左走（1为可以通行，0为不能通行） 
    int up;                 //栈记录小球能否往上走（1为可以通行，0为不能通行） 
    int down;               //栈记录小球能否往下走（1为可以通行，0为不能通行） 
}mark;

typedef mark DataType;

typedef struct {
    DataType data[MAXSIZE];
    int top;
}SeqStack, * PSeqStack;

PSeqStack Init_SeqStack (void)
{
    PSeqStack S;
    S = (PSeqStack)malloc(sizeof(SeqStack));
    if (S)
        S->top = -1;
    else
        exit(-1);
    return S;
}

int Empty_SeqStack(PSeqStack S)
{
    //return (S->top==-1);
    if (S->top == -1)
        return 1;
    else
        return 0;
}

int Push_SeqStack(PSeqStack S,DataType x)
{
    if (S->top == MAXSIZE - 1)
    {
        printf("栈满不能入栈\n");
        return 0;
    }
    else
    {
        S->top++;
        S->data[S->top] = x;
        return 1;
    }
}

int Pop_SeqStack(PSeqStack S,DataType *x)
{
    if(Empty_SeqStack(S))
        return 0;
    else
    {
        *x = S->data[S->top];
        S->top--;
        return 1;
    }
}                                        //   栈只需要弹栈、入栈、和判断是否为空 
                                         //   因为我们的迷宫生成算法必有通路，所以判断栈空没必要，但是是一种设计模式和思想 
using namespace std;                     //   因为是cpp程序，所以我加了命名空间和iostream，虽然后面都没用！ 

/***********************迷宫的尺寸***********************/
#define Height 25                 //迷宫的高度，必须为奇数
#define Width 25                   //迷宫的宽度，必须为奇数
/********************界面中显示的元素********************/
#define Wall 1
#define Road 0
#define Ball 6
#define Start 2
#define End 3
/********************Esc判断返回界面*********************/
#define Esc 5
/********************显示小球经过路径********************/
#define Up 10
#define Down 11
#define Left 12
#define Right 13
/********************Esc判断返回界面*********************/
#define Flag_menu 20
#define Flag_start_manu 21
#define Flag_start_auto 22
#define Flag_helpdoc 12
/*******************自动模式下小球速度*******************/
int speed=50;                             //此接口不对外，程序员默认speed为0小球速度最高，speed 越高速度越慢 
                                          //要改自动模式下小球速度，只在这儿改就可以了，改为0速度最高 
/**********************设定画布大小**********************/
int map[Height+2][Width+2];               //加2是因为上下两行两列是周围墙壁 
int pos_x=2,pos_y=1;  //小球位置          //界面中显示元素其实只有小球在动，所以我们要记录下小球位置坐标 
/***********************函数声明************************/
void setWinLong();                        //设定窗口样式（未被我用到） 
void setWinTransparent();                 //设定窗口透明度 
void fixWinSize();                        //固定窗口大小
void gotoxy(int x,int y);                 //光标移动函数
void hidden();                            //光标隐藏行数
void create(int x, int y);                //随机生成迷宫
void startup();                           //数据更新
void show();                              //显示界面
void visit();                             //小球移动后入栈，位置更新
void start_risk();                        //闯关模式 
void autogame();                          //自动游戏功能实现
void manugame();                          //手动游戏功能实现
void menu_head_show();         //菜单显示相关 
void menu_show_pos1();
void menu_show_pos2();
void menu_show_pos3();
void menu_show_pos4();
void menu_show_pos5();
void menu_show_pos6();
void menu();                              //主菜单
void start_auto();                        //自动游戏框架
void start_manu();                        //手动游戏框架
void helpdoc();                           //帮助文档
void over(int flag);                      //结束游戏
void pass();                              //通关提示
void restart(int flag);                   //重新开始
void set();                               //设置 
/***********************函数实现************************/
void setWinLong()                         //设定窗口样式（未被我用到） 
{ 
    HWND hwnd = GetConsoleWindow();
    LONG Style;	//窗口风格
    Style = GetWindowLong(hwnd, GWL_STYLE);	 // 得到窗口风格
    Style = Style & ~WS_CAPTION;			 //去掉标题栏
    SetWindowLong(hwnd, GWL_STYLE, Style);	 //为窗口设置新的风格
}
void setWinTransparent()                  //设定窗口透明度 
{
	HWND hwnd = GetConsoleWindow();
    int ExdStyle = (int)GetWindowLong(hwnd, GWL_EXSTYLE);
    //通过SetWindowLong设置窗口的属性，多增加了一个WS_EX_LAYERED支持透明
    SetWindowLong(hwnd, GWL_EXSTYLE, ExdStyle | WS_EX_LAYERED);
    SetLayeredWindowAttributes(GetConsoleWindow(),RGB(255, 255, 255), 255,LWA_ALPHA); //200为透明度值，从0-255 
}
void fixWinSize()                         //固定窗口大小
{
    HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
    RECT rc;
    GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形

    //改变cmd窗口风格
    SetWindowLongPtr(hWnd,GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
}
void gotoxy(int x,int y)                  //光标移动函数
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
void hidden()                             //光标隐藏行数
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=0;//赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut,&cci);
}
void create(int x,int y)                  //随机生成迷宫
{
    int c[4][2]={0,1,1,0,0,-1,-1,0}; //四个方向
    int i,j,t;
        //将方向打乱
    for(i=0;i<4;i++)
    {
        j=rand()%4;
        t=c[i][0];c[i][0]=c[j][0];c[j][0]=t;
        t=c[i][1];c[i][1]=c[j][1];c[j][1]=t;
    }
    map[x][y]=Road;
    for(i=0;i<4;i++)
    if(map[x+2*c[i][0]][y+2*c[i][1]]==Wall)
    {
        map[x+c[i][0]][y+c[i][1]]=Road;
        create(x+2*c[i][0],y+2*c[i][1]);
    }
}

void startup()                            // 数据初始化以及数据更新 
{
    system("mode con cols=50 lines=25");
    system("title 迷宫小游戏         --version3.0实训答辩版");
    fixWinSize();
	setWinTransparent();                  //设定窗口透明度 
    int i,j;
    srand((unsigned)time(NULL)); //初始化随即种子
    hidden(); //隐藏光标
    for(i=0;i<=Height+1;i++)
        for(j=0;j<=Width+1;j++)
            if(i==0||i==Height+1||j==0||j==Width+1) //初始化迷宫
                map[i][j]=Road;
            else
                map[i][j]=Wall;

    create(2*(rand()%(Height/2)+1),2*(rand()%(Width/2)+1)); //从随机一个点开始生成迷宫，该点行列都为偶数
    for(i=0;i<=Height+1;i++) //边界处理
    {
        map[i][0]=Wall;
        map[i][Width+1]=Wall;
    }

    for(j=0;j<=Width+1;j++) //边界处理
    {
        map[0][j]=Wall;
        map[Height+1][j]=Wall;
    }
    map[2][1]=Start;
    pos_x=2;
    pos_y=1;
}

void show()                               // 显示画面
{
    gotoxy(0,0);  // 光标移动到原点位置，以下重画清屏
    int i,j;
    for (i=1;i<=Height;i++)
    {
        for (j=1;j<=Width;j++)
        {
            gotoxy(2*j-2,i-1);
            if (map[i][j]==Start){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//设置颜色，15为亮白色 
                printf("入");   //   画入口
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色，07为默认黑底白字 
            }
            else if (map[i][j]==End){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//设置颜色，15为亮白色
                printf("出");   //   画出口
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色，07为默认黑底白字
            }
            else if (map[i][j]==Wall){ 
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//设置颜色，15为亮白色
                printf("▇");   //   画墙壁
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色，07为默认黑底白字
        	} 
            else if (map[i][j]==Road)
                printf(" ");   //    画路
            else if (map[i][j]==Ball){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("●");   //   画点
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色，07为默认黑底白字
            }
            else if(map[i][j]==Up){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//设置颜色，11为亮蓝色 
                printf("↑");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色，07为默认黑底白字
            } 
            else if(map[i][j]==Down){ 
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);	//设置颜色，10为绿色 
                printf("↓");
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色，07为默认黑底白字
            } 
			else if(map[i][j]==Left){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	//设置颜色，9为淡蓝色 
                printf("←");
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色，07为默认黑底白字
            } 
			else if(map[i][j]==Right){
			 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色，6为淡黄色 
                printf("→");
        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色，07为默认黑底白字
        	} 
		}
    }

    map[2][1]=Start;                          //给定入口
    map[Height-1][Width]=End;                 //给定出口
    map[pos_x][pos_y]=Ball;                   //小球位置最后固定，因为小球要显示在出入口上 
}

void visit(mark p,int sign, PSeqStack S)      //小球移动后入栈，位置更新
{
    Push_SeqStack(S,p);
    p.left=1;p.right=1;p.up=1;p.down=1;       //压栈后数据更新，默认1四个方向可以走 
    switch (sign)
    {
    case Right:
        p.y++;pos_y++;
        Push_SeqStack(S, p);
        break;//向右
    case Down:
        p.x++;pos_x++;
        Push_SeqStack(S, p);
        break;//向下
    case Left:
        p.y--;pos_y--;
        Push_SeqStack(S, p);
        break;//向左
    case Up:
        p.x--;pos_x--;
        Push_SeqStack(S, p);
        break;//向上
    }
}

void autogame()                               // 自动游戏功能实现
{
    struct point p;
    p.x=2;
    p.y=1;
    int road_exit=1;
    PSeqStack S = Init_SeqStack();
    Push_SeqStack(S,p);
    while (!Empty_SeqStack(S))
    {
        char input;
        if(kbhit()){
            input=getch();
            if(input==27)
                over(Flag_start_auto);     //Esc
            if(input==114||input==82)
                restart(Flag_start_auto);                 //R键重新开始,R对应ASCII码值
            input = getch(); 
	        if(input==72){   //上
	            if(speed-25>=0){
	                speed-=25;
	            }
	            else{
	            	speed=0;
				}
	        }
	        else if(input==80){  //下
	            speed+=25;
	        }    
        }
        map[pos_x][pos_y]=Ball;
        Sleep(speed);                                    //速度
        show();
        if(road_exit==1)
            Pop_SeqStack(S, &p);
        road_exit=1;
        if(pos_x==Height-1&&pos_y==Width-1)
        {
            pass();
        }
        if(map[p.x][p.y+1] == Road)//向右
        {
            map[pos_x][pos_y]=Right;
            visit(p,Right,S);
            continue;
        }
        if(map[p.x+1][p.y] == Road)//向下
        {
            map[pos_x][pos_y]=Down;
            visit(p,Down,S);
            continue;
        }
        if(map[p.x][p.y-1] == Road)//向左
        {
            map[pos_x][pos_y]=Left;
            visit(p,Left,S);
            continue;
        }
        if(map[p.x-1][p.y] == Road)//向上
        {
            map[pos_x][pos_y]=Up;
            visit(p,Up,S);
            continue;
        }//以上是对迷宫的四个方向进行操作

                                                          //如果四个方向没有路，只能回退，下面是回退代码 
        if(map[pos_x][pos_y-1]==Right&&p.left==1)         //往左
        {
            Pop_SeqStack(S, &p);
            p.right=0;
            map[pos_x][pos_y]=Left;
            pos_y--;
        }
        else if(map[pos_x][pos_y+1]==Left&&p.right==1)    //往右
        {
            Pop_SeqStack(S, &p);
            p.left=0;
            map[pos_x][pos_y]=Right;
            pos_y++;
        }
        else if(map[pos_x+1][pos_y]==Up&&p.down==1)       //往下
        {
            Pop_SeqStack(S, &p);
            p.up=0;
            map[pos_x][pos_y]=Down;
            pos_x++;
        }
        else if(map[pos_x-1][pos_y]==Down&&p.up==1)        //往上
        {
            Pop_SeqStack(S, &p);
            p.down=0;
            map[pos_x][pos_y]=Up;
            pos_x--;
        }
        road_exit=0;
    }

}

void manugame()                               // 手动游戏功能实现
{
    char input;
    if(kbhit())
    {
        start:input = getch();
        if(input==27)
            over(Flag_start_manu); //Esc
        if(input==114||input==82)
            restart(Flag_start_manu);             //R键重新开始,R对应ASCII码值
        if(pos_x==Height-1&&pos_y==Width-1)
        {
            pass();
        }
        //map[pos_x][pos_y]=Road;
        if(input!=-32)  goto start;
        input = getch(); 
        if(input==72){ //上
            if(map[pos_x-1][pos_y]!=Wall){
                map[pos_x][pos_y]=Up;
                pos_x--;
            }
        }
        else if(input==80){  //下
            if(map[pos_x+1][pos_y]!=Wall){
                map[pos_x][pos_y]=Down;
                pos_x++;
            }
        }
        else if(input==75){ //左
            if(map[pos_x][pos_y-1]!=Wall){
                map[pos_x][pos_y]=Left;
                pos_y--;
            }
        }
        else if(input==77){//右
            if(map[pos_x][pos_y+1]!=Wall){
                map[pos_x][pos_y]=Right;
                pos_y++;
            }
        }

    }
}

void menu_head_show()
{
	gotoxy(15,6);   //15是宽，6是高
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
    for(int i=0;i<14;i++)
        printf(" ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色
    printf("☆ ☆ 迷宫小游戏 ☆ ☆\n\n");
}

void menu_show_pos1()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf(">  ");
    printf("手动模式\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("自动模式\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("闯关模式(新)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("设置\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("帮助\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("退出");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
}

void menu_show_pos2()
{
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("手动模式\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf(">  ");
    printf("自动模式\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("闯关模式(新)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("设置\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("帮助\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("退出");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
}

void menu_show_pos3()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("手动模式\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("自动模式\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf(">  ");
    printf("闯关模式(新)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("设置\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("帮助\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("退出");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
}

void menu_show_pos4()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("手动模式\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("自动模式\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("闯关模式(新)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf(">    ");
    printf("设置\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("帮助\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("退出");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
}

void menu_show_pos5()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("手动模式\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("自动模式\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("闯关模式(新)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("设置\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf(">    ");
    printf("帮助\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("退出");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
}

void menu_show_pos6()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("手动模式\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("自动模式\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("闯关模式(新)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("设置\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("帮助\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf(">    ");
    printf("退出");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
}

void menu()                                   //主菜单
{
    system("mode con cols=50 lines=25");
    startup();      // 数据初始化
    menu_head_show();

    int pos=1;
    menu_show_pos1();

    char input;
    while(1)
    {
        input=getch();
        if(input==27) over(Flag_menu); //Esc
        if(input==13){
            system("cls");
            if(pos==1){
                start_manu();
            }
            if(pos==2){
                start_auto();
            }
            if(pos==3){
                //start_risk();
                MessageBoxA(0,"           不想写了，哈哈","尴尬",MB_OK|MB_SYSTEMMODAL);
			    ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_SHOW);
			    menu();
            }
            if(pos==4){
                set();
            }
            if(pos==5){
                helpdoc();
            }
            if(pos==6){
                over(Flag_menu);
            }
        }
        if(input!=-32) continue;
        input=getch();
        if(input==72){  //上
            if(pos==2){
                menu_head_show();
				menu_show_pos1();
				pos=1;
            }
            else if(pos==3){
                menu_head_show();
				menu_show_pos2();
                pos=2;
            }
            else if(pos==4){
                menu_head_show();
				menu_show_pos3();
                pos=3;
            }
            else if(pos==5){
                menu_head_show();
				menu_show_pos4();
                pos=4;
            }
            else if(pos==6){
                menu_head_show();
				menu_show_pos5();
                pos=5;
            }
        }
        if(input==80){  //下
            if(pos==1){
                menu_head_show();
				menu_show_pos2();
				pos=2;
            }
            else if(pos==2){
                menu_head_show();
				menu_show_pos3();
                pos=3;
            }
            else if(pos==3){
                menu_head_show();
				menu_show_pos4();
                pos=4;         
            }
            else if(pos==4){
                menu_head_show();
				menu_show_pos5();
                pos=5;
            }
            else if(pos==5){
                menu_head_show();
				menu_show_pos6();
                pos=6;
            }
        }

    }

}

void start_auto()                             //自动游戏框架
{
    system("mode con cols=50 lines=25");
    while (1) //  游戏循环执行
    {
        show();  // 显示画面
        autogame();  // 自动游戏
        //manugame();  // 手动游戏
    }
}

void start_manu()                             //手动游戏框架
{
    system("mode con cols=50 lines=25");
    while (1) //  游戏循环执行
    {
        show();  // 显示画面
        manugame();  // 手动游戏
    }
}
void helpdoc()                                //帮助文档
{
    system("mode con cols=50 lines=25");
    gotoxy(15,1);   //15是宽，1是高
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
    for(int i=0;i<13;i++)
        printf(" ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//设置颜色
    printf("★ ☆ ★ 说明书 ★ ☆ ★\n\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("◇控制方法◇\n");
    for(int i=0;i<12;i++)
        printf(" ");
    printf("上:↑  下:↓  左:←  右:→\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("◇重新开始◇\n");
    for(int i=0;i<23;i++)
        printf(" ");
    printf("R键\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("◇暂停游戏◇\n");
    for(int i=0;i<17;i++)
        printf(" ");
    printf("鼠标左键窗口暂停\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("右键窗口恢复\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("◇退出游戏◇\n");
    for(int i=0;i<22;i++)
        printf(" ");
    printf("Esc键\n\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("◇游戏介绍◇\n");
    for(int i=0;i<14;i++)
        printf(" ");
    printf("手动模式的迷宫和大家平\n");
    for(int i=0;i<17;i++)
        printf(" ");
    printf("时玩的没什么两样.\n");
    for(int i=0;i<14;i++)
        printf(" ");
    printf("自动模式的迷宫是利用栈\n");
    for(int i=0;i<17;i++)
        printf(" ");
    printf("的知识来实现的.\n");
    for(int i=0;i<21;i++)
        printf(" ");
    printf("◇作者◇\n");
    for(int i=0;i<22;i++)
        printf(" ");
    printf("范茂伟\n\n");
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色
    for(int i=0;i<20;i++)
        printf(" ");
    printf(">  ");
    printf("返回");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色

    char input;
    while(1)
    {
        input=getch();
        if(input==27) over(Flag_helpdoc); //Esc
        if(input==13){                  //回车 
    		system("cls");
        	menu();
        }
        if(input!=-32) continue;    
    }
}
void over(int flag)                           //结束游戏
{
    system("mode con cols=20 lines=7");  //设置窗口大小
    gotoxy(0,0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
    printf("\n      是否退出？\n");
    printf("--------------------");
    int pos=1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//设置颜色
    printf("      > 确定\n");
    printf("        返回\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
    printf("--------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色

    char input;
    while(1)
    {
        input=getch();
        if(input==13){
            system("cls");
            if(pos==1){            //确认退出
                exit(Esc);
            }
            if(pos==2){            //返回
                if(flag==Flag_start_manu){
                    start_manu();  //返回手动开始模式
                }
                else if(flag==Flag_start_auto){
                    start_auto();  //返回自动开始模式
                }
                else if(flag==Flag_menu){
                    menu();        //返回菜单
                }
                else if(flag==Flag_helpdoc){
                    helpdoc();     //返回帮助界面
                }
            }
        }
        if(input!=-32) continue;
        input=getch();
        if(input==72){  //上
            if(pos==2){
                gotoxy(0,0);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("\n      是否退出？\n");
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//设置颜色
                printf("      > 确定\n");
                printf("        返回\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
                pos=1;
            }
        }
        if(input==80){  //下
            if(pos==1){
                gotoxy(0,0);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("\n      是否退出？\n");
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//设置颜色
                printf("        确定\n");
                printf("      > 返回\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
                pos=2;
            }
        }
    }
}
void pass()                                   //通关提示
{
    //ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_HIDE);				//设置指定窗口的显示状态
    MessageBoxA(0,"           恭喜通关！","提示",MB_OK|MB_SYSTEMMODAL);
    ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_SHOW);
    menu();
}
void restart(int flag)                        //重新开始
{
    system("mode con cols=20 lines=7");  //设置窗口大小
    gotoxy(0,0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色
    printf("\n      重新开始？\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
    printf("--------------------");
    int pos=1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色
    printf("      > 确定\n");
    printf("        返回\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
    printf("--------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色

    char input;
    while(1)
    {
        input=getch();
        if(input==13){
            system("cls");
            if(pos==1){            //确认返回
                menu();
            }
            if(pos==2){            //继续游戏
                if(flag==Flag_start_manu){
                    start_manu();  //继续手动开始模式
                }
                else if(flag==Flag_start_auto){
                    start_auto();  //继续自动开始模式
                }
            }
        }
        if(input!=-32) continue;
        input=getch();
        if(input==72){  //上
            if(pos==2){
                gotoxy(0,0);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色
                printf("\n      重新开始？\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色
                printf("      > 确定\n");
                printf("        返回\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
                pos=1;
            }
        }
        if(input==80){  //下
            if(pos==1){
                gotoxy(0,0);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色
                printf("\n      重新开始？\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//设置颜色
                printf("        确定\n");
                printf("      > 返回\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//设置颜色
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//设置颜色
                pos=2;
            }
        }
    }
}
void set()                                    //设置 
{
	//ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_HIDE);				//设置指定窗口的显示状态
	MessageBoxA(0,"           功能未开放！","提示",MB_OK|MB_SYSTEMMODAL);
    ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_SHOW);
    menu();
}

int main()
{
    menu();

    return 0;
}


