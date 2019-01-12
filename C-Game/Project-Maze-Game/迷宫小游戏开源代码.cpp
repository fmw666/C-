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
    int x;                  //ջ��¼С��x���� 
    int y;                  //ջ��¼С��y���� 
    int right;              //ջ��¼С���ܷ������ߣ�1Ϊ����ͨ�У�0Ϊ����ͨ�У� 
    int left;               //ջ��¼С���ܷ������ߣ�1Ϊ����ͨ�У�0Ϊ����ͨ�У� 
    int up;                 //ջ��¼С���ܷ������ߣ�1Ϊ����ͨ�У�0Ϊ����ͨ�У� 
    int down;               //ջ��¼С���ܷ������ߣ�1Ϊ����ͨ�У�0Ϊ����ͨ�У� 
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
        printf("ջ��������ջ\n");
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
}                                        //   ջֻ��Ҫ��ջ����ջ�����ж��Ƿ�Ϊ�� 
                                         //   ��Ϊ���ǵ��Թ������㷨����ͨ·�������ж�ջ��û��Ҫ��������һ�����ģʽ��˼�� 
using namespace std;                     //   ��Ϊ��cpp���������Ҽ��������ռ��iostream����Ȼ���涼û�ã� 

/***********************�Թ��ĳߴ�***********************/
#define Height 25                 //�Թ��ĸ߶ȣ�����Ϊ����
#define Width 25                   //�Թ��Ŀ�ȣ�����Ϊ����
/********************��������ʾ��Ԫ��********************/
#define Wall 1
#define Road 0
#define Ball 6
#define Start 2
#define End 3
/********************Esc�жϷ��ؽ���*********************/
#define Esc 5
/********************��ʾС�򾭹�·��********************/
#define Up 10
#define Down 11
#define Left 12
#define Right 13
/********************Esc�жϷ��ؽ���*********************/
#define Flag_menu 20
#define Flag_start_manu 21
#define Flag_start_auto 22
#define Flag_helpdoc 12
/*******************�Զ�ģʽ��С���ٶ�*******************/
int speed=50;                             //�˽ӿڲ����⣬����ԱĬ��speedΪ0С���ٶ���ߣ�speed Խ���ٶ�Խ�� 
                                          //Ҫ���Զ�ģʽ��С���ٶȣ�ֻ������ľͿ����ˣ���Ϊ0�ٶ���� 
/**********************�趨������С**********************/
int map[Height+2][Width+2];               //��2����Ϊ����������������Χǽ�� 
int pos_x=2,pos_y=1;  //С��λ��          //��������ʾԪ����ʵֻ��С���ڶ�����������Ҫ��¼��С��λ������ 
/***********************��������************************/
void setWinLong();                        //�趨������ʽ��δ�����õ��� 
void setWinTransparent();                 //�趨����͸���� 
void fixWinSize();                        //�̶����ڴ�С
void gotoxy(int x,int y);                 //����ƶ�����
void hidden();                            //�����������
void create(int x, int y);                //��������Թ�
void startup();                           //���ݸ���
void show();                              //��ʾ����
void visit();                             //С���ƶ�����ջ��λ�ø���
void start_risk();                        //����ģʽ 
void autogame();                          //�Զ���Ϸ����ʵ��
void manugame();                          //�ֶ���Ϸ����ʵ��
void menu_head_show();         //�˵���ʾ��� 
void menu_show_pos1();
void menu_show_pos2();
void menu_show_pos3();
void menu_show_pos4();
void menu_show_pos5();
void menu_show_pos6();
void menu();                              //���˵�
void start_auto();                        //�Զ���Ϸ���
void start_manu();                        //�ֶ���Ϸ���
void helpdoc();                           //�����ĵ�
void over(int flag);                      //������Ϸ
void pass();                              //ͨ����ʾ
void restart(int flag);                   //���¿�ʼ
void set();                               //���� 
/***********************����ʵ��************************/
void setWinLong()                         //�趨������ʽ��δ�����õ��� 
{ 
    HWND hwnd = GetConsoleWindow();
    LONG Style;	//���ڷ��
    Style = GetWindowLong(hwnd, GWL_STYLE);	 // �õ����ڷ��
    Style = Style & ~WS_CAPTION;			 //ȥ��������
    SetWindowLong(hwnd, GWL_STYLE, Style);	 //Ϊ���������µķ��
}
void setWinTransparent()                  //�趨����͸���� 
{
	HWND hwnd = GetConsoleWindow();
    int ExdStyle = (int)GetWindowLong(hwnd, GWL_EXSTYLE);
    //ͨ��SetWindowLong���ô��ڵ����ԣ���������һ��WS_EX_LAYERED֧��͸��
    SetWindowLong(hwnd, GWL_EXSTYLE, ExdStyle | WS_EX_LAYERED);
    SetLayeredWindowAttributes(GetConsoleWindow(),RGB(255, 255, 255), 255,LWA_ALPHA); //200Ϊ͸����ֵ����0-255 
}
void fixWinSize()                         //�̶����ڴ�С
{
    HWND hWnd = GetConsoleWindow(); //���cmd���ھ��
    RECT rc;
    GetWindowRect(hWnd, &rc); //���cmd���ڶ�Ӧ����

    //�ı�cmd���ڷ��
    SetWindowLongPtr(hWnd,GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
}
void gotoxy(int x,int y)                  //����ƶ�����
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
void hidden()                             //�����������
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=0;//��1Ϊ��ʾ����0Ϊ����
    SetConsoleCursorInfo(hOut,&cci);
}
void create(int x,int y)                  //��������Թ�
{
    int c[4][2]={0,1,1,0,0,-1,-1,0}; //�ĸ�����
    int i,j,t;
        //���������
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

void startup()                            // ���ݳ�ʼ���Լ����ݸ��� 
{
    system("mode con cols=50 lines=25");
    system("title �Թ�С��Ϸ         --version3.0ʵѵ����");
    fixWinSize();
	setWinTransparent();                  //�趨����͸���� 
    int i,j;
    srand((unsigned)time(NULL)); //��ʼ���漴����
    hidden(); //���ع��
    for(i=0;i<=Height+1;i++)
        for(j=0;j<=Width+1;j++)
            if(i==0||i==Height+1||j==0||j==Width+1) //��ʼ���Թ�
                map[i][j]=Road;
            else
                map[i][j]=Wall;

    create(2*(rand()%(Height/2)+1),2*(rand()%(Width/2)+1)); //�����һ���㿪ʼ�����Թ����õ����ж�Ϊż��
    for(i=0;i<=Height+1;i++) //�߽紦��
    {
        map[i][0]=Wall;
        map[i][Width+1]=Wall;
    }

    for(j=0;j<=Width+1;j++) //�߽紦��
    {
        map[0][j]=Wall;
        map[Height+1][j]=Wall;
    }
    map[2][1]=Start;
    pos_x=2;
    pos_y=1;
}

void show()                               // ��ʾ����
{
    gotoxy(0,0);  // ����ƶ���ԭ��λ�ã������ػ�����
    int i,j;
    for (i=1;i<=Height;i++)
    {
        for (j=1;j<=Width;j++)
        {
            gotoxy(2*j-2,i-1);
            if (map[i][j]==Start){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//������ɫ��15Ϊ����ɫ 
                printf("��");   //   �����
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ��07ΪĬ�Ϻڵװ��� 
            }
            else if (map[i][j]==End){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//������ɫ��15Ϊ����ɫ
                printf("��");   //   ������
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ��07ΪĬ�Ϻڵװ���
            }
            else if (map[i][j]==Wall){ 
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	//������ɫ��15Ϊ����ɫ
                printf("�~");   //   ��ǽ��
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ��07ΪĬ�Ϻڵװ���
        	} 
            else if (map[i][j]==Road)
                printf(" ");   //    ��·
            else if (map[i][j]==Ball){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("��");   //   ����
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ��07ΪĬ�Ϻڵװ���
            }
            else if(map[i][j]==Up){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//������ɫ��11Ϊ����ɫ 
                printf("��");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ��07ΪĬ�Ϻڵװ���
            } 
            else if(map[i][j]==Down){ 
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);	//������ɫ��10Ϊ��ɫ 
                printf("��");
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ��07ΪĬ�Ϻڵװ���
            } 
			else if(map[i][j]==Left){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	//������ɫ��9Ϊ����ɫ 
                printf("��");
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ��07ΪĬ�Ϻڵװ���
            } 
			else if(map[i][j]==Right){
			 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ��6Ϊ����ɫ 
                printf("��");
        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ��07ΪĬ�Ϻڵװ���
        	} 
		}
    }

    map[2][1]=Start;                          //�������
    map[Height-1][Width]=End;                 //��������
    map[pos_x][pos_y]=Ball;                   //С��λ�����̶�����ΪС��Ҫ��ʾ�ڳ������ 
}

void visit(mark p,int sign, PSeqStack S)      //С���ƶ�����ջ��λ�ø���
{
    Push_SeqStack(S,p);
    p.left=1;p.right=1;p.up=1;p.down=1;       //ѹջ�����ݸ��£�Ĭ��1�ĸ���������� 
    switch (sign)
    {
    case Right:
        p.y++;pos_y++;
        Push_SeqStack(S, p);
        break;//����
    case Down:
        p.x++;pos_x++;
        Push_SeqStack(S, p);
        break;//����
    case Left:
        p.y--;pos_y--;
        Push_SeqStack(S, p);
        break;//����
    case Up:
        p.x--;pos_x--;
        Push_SeqStack(S, p);
        break;//����
    }
}

void autogame()                               // �Զ���Ϸ����ʵ��
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
                restart(Flag_start_auto);                 //R�����¿�ʼ,R��ӦASCII��ֵ
            input = getch(); 
	        if(input==72){   //��
	            if(speed-25>=0){
	                speed-=25;
	            }
	            else{
	            	speed=0;
				}
	        }
	        else if(input==80){  //��
	            speed+=25;
	        }    
        }
        map[pos_x][pos_y]=Ball;
        Sleep(speed);                                    //�ٶ�
        show();
        if(road_exit==1)
            Pop_SeqStack(S, &p);
        road_exit=1;
        if(pos_x==Height-1&&pos_y==Width-1)
        {
            pass();
        }
        if(map[p.x][p.y+1] == Road)//����
        {
            map[pos_x][pos_y]=Right;
            visit(p,Right,S);
            continue;
        }
        if(map[p.x+1][p.y] == Road)//����
        {
            map[pos_x][pos_y]=Down;
            visit(p,Down,S);
            continue;
        }
        if(map[p.x][p.y-1] == Road)//����
        {
            map[pos_x][pos_y]=Left;
            visit(p,Left,S);
            continue;
        }
        if(map[p.x-1][p.y] == Road)//����
        {
            map[pos_x][pos_y]=Up;
            visit(p,Up,S);
            continue;
        }//�����Ƕ��Թ����ĸ�������в���

                                                          //����ĸ�����û��·��ֻ�ܻ��ˣ������ǻ��˴��� 
        if(map[pos_x][pos_y-1]==Right&&p.left==1)         //����
        {
            Pop_SeqStack(S, &p);
            p.right=0;
            map[pos_x][pos_y]=Left;
            pos_y--;
        }
        else if(map[pos_x][pos_y+1]==Left&&p.right==1)    //����
        {
            Pop_SeqStack(S, &p);
            p.left=0;
            map[pos_x][pos_y]=Right;
            pos_y++;
        }
        else if(map[pos_x+1][pos_y]==Up&&p.down==1)       //����
        {
            Pop_SeqStack(S, &p);
            p.up=0;
            map[pos_x][pos_y]=Down;
            pos_x++;
        }
        else if(map[pos_x-1][pos_y]==Down&&p.up==1)        //����
        {
            Pop_SeqStack(S, &p);
            p.down=0;
            map[pos_x][pos_y]=Up;
            pos_x--;
        }
        road_exit=0;
    }

}

void manugame()                               // �ֶ���Ϸ����ʵ��
{
    char input;
    if(kbhit())
    {
        start:input = getch();
        if(input==27)
            over(Flag_start_manu); //Esc
        if(input==114||input==82)
            restart(Flag_start_manu);             //R�����¿�ʼ,R��ӦASCII��ֵ
        if(pos_x==Height-1&&pos_y==Width-1)
        {
            pass();
        }
        //map[pos_x][pos_y]=Road;
        if(input!=-32)  goto start;
        input = getch(); 
        if(input==72){ //��
            if(map[pos_x-1][pos_y]!=Wall){
                map[pos_x][pos_y]=Up;
                pos_x--;
            }
        }
        else if(input==80){  //��
            if(map[pos_x+1][pos_y]!=Wall){
                map[pos_x][pos_y]=Down;
                pos_x++;
            }
        }
        else if(input==75){ //��
            if(map[pos_x][pos_y-1]!=Wall){
                map[pos_x][pos_y]=Left;
                pos_y--;
            }
        }
        else if(input==77){//��
            if(map[pos_x][pos_y+1]!=Wall){
                map[pos_x][pos_y]=Right;
                pos_y++;
            }
        }

    }
}

void menu_head_show()
{
	gotoxy(15,6);   //15�ǿ�6�Ǹ�
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
    for(int i=0;i<14;i++)
        printf(" ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ
    printf("�� �� �Թ�С��Ϸ �� ��\n\n");
}

void menu_show_pos1()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf(">  ");
    printf("�ֶ�ģʽ\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�Զ�ģʽ\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("����ģʽ(��)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("�˳�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
}

void menu_show_pos2()
{
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�ֶ�ģʽ\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf(">  ");
    printf("�Զ�ģʽ\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("����ģʽ(��)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("�˳�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
}

void menu_show_pos3()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�ֶ�ģʽ\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�Զ�ģʽ\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf(">  ");
    printf("����ģʽ(��)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("�˳�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
}

void menu_show_pos4()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�ֶ�ģʽ\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�Զ�ģʽ\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("����ģʽ(��)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf(">    ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("�˳�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
}

void menu_show_pos5()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�ֶ�ģʽ\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�Զ�ģʽ\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("����ģʽ(��)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf(">    ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("�˳�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
}

void menu_show_pos6()
{
	for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�ֶ�ģʽ\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("�Զ�ģʽ\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("   ");
    printf("����ģʽ(��)\n");
    
    for(int i=0;i<21;i++)
    	printf(" ");
    for(int i=0;i<8;i++)
        printf("-");
    printf("\n");
    
    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf("     ");
    printf("����\n");

    for(int i=0;i<18;i++)
        printf(" ");
    printf(">    ");
    printf("�˳�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
}

void menu()                                   //���˵�
{
    system("mode con cols=50 lines=25");
    startup();      // ���ݳ�ʼ��
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
                MessageBoxA(0,"           ����д�ˣ�����","����",MB_OK|MB_SYSTEMMODAL);
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
        if(input==72){  //��
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
        if(input==80){  //��
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

void start_auto()                             //�Զ���Ϸ���
{
    system("mode con cols=50 lines=25");
    while (1) //  ��Ϸѭ��ִ��
    {
        show();  // ��ʾ����
        autogame();  // �Զ���Ϸ
        //manugame();  // �ֶ���Ϸ
    }
}

void start_manu()                             //�ֶ���Ϸ���
{
    system("mode con cols=50 lines=25");
    while (1) //  ��Ϸѭ��ִ��
    {
        show();  // ��ʾ����
        manugame();  // �ֶ���Ϸ
    }
}
void helpdoc()                                //�����ĵ�
{
    system("mode con cols=50 lines=25");
    gotoxy(15,1);   //15�ǿ�1�Ǹ�
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 04);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
    for(int i=0;i<13;i++)
        printf(" ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//������ɫ
    printf("�� �� �� ˵���� �� �� ��\n\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("����Ʒ�����\n");
    for(int i=0;i<12;i++)
        printf(" ");
    printf("��:��  ��:��  ��:��  ��:��\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("�����¿�ʼ��\n");
    for(int i=0;i<23;i++)
        printf(" ");
    printf("R��\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("����ͣ��Ϸ��\n");
    for(int i=0;i<17;i++)
        printf(" ");
    printf("������������ͣ\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("�Ҽ����ڻָ�\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("���˳���Ϸ��\n");
    for(int i=0;i<22;i++)
        printf(" ");
    printf("Esc��\n\n");
    for(int i=0;i<19;i++)
        printf(" ");
    printf("����Ϸ���ܡ�\n");
    for(int i=0;i<14;i++)
        printf(" ");
    printf("�ֶ�ģʽ���Թ��ʹ��ƽ\n");
    for(int i=0;i<17;i++)
        printf(" ");
    printf("ʱ���ûʲô����.\n");
    for(int i=0;i<14;i++)
        printf(" ");
    printf("�Զ�ģʽ���Թ�������ջ\n");
    for(int i=0;i<17;i++)
        printf(" ");
    printf("��֪ʶ��ʵ�ֵ�.\n");
    for(int i=0;i<21;i++)
        printf(" ");
    printf("�����ߡ�\n");
    for(int i=0;i<22;i++)
        printf(" ");
    printf("��ïΰ\n\n");
    
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ
    for(int i=0;i<20;i++)
        printf(" ");
    printf(">  ");
    printf("����");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
    printf("\n");
    for(int i=0;i<Width*2;i++)
        printf("-");
    printf("\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ

    char input;
    while(1)
    {
        input=getch();
        if(input==27) over(Flag_helpdoc); //Esc
        if(input==13){                  //�س� 
    		system("cls");
        	menu();
        }
        if(input!=-32) continue;    
    }
}
void over(int flag)                           //������Ϸ
{
    system("mode con cols=20 lines=7");  //���ô��ڴ�С
    gotoxy(0,0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
    printf("\n      �Ƿ��˳���\n");
    printf("--------------------");
    int pos=1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//������ɫ
    printf("      > ȷ��\n");
    printf("        ����\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
    printf("--------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ

    char input;
    while(1)
    {
        input=getch();
        if(input==13){
            system("cls");
            if(pos==1){            //ȷ���˳�
                exit(Esc);
            }
            if(pos==2){            //����
                if(flag==Flag_start_manu){
                    start_manu();  //�����ֶ���ʼģʽ
                }
                else if(flag==Flag_start_auto){
                    start_auto();  //�����Զ���ʼģʽ
                }
                else if(flag==Flag_menu){
                    menu();        //���ز˵�
                }
                else if(flag==Flag_helpdoc){
                    helpdoc();     //���ذ�������
                }
            }
        }
        if(input!=-32) continue;
        input=getch();
        if(input==72){  //��
            if(pos==2){
                gotoxy(0,0);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("\n      �Ƿ��˳���\n");
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//������ɫ
                printf("      > ȷ��\n");
                printf("        ����\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
                pos=1;
            }
        }
        if(input==80){  //��
            if(pos==1){
                gotoxy(0,0);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("\n      �Ƿ��˳���\n");
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);	//������ɫ
                printf("        ȷ��\n");
                printf("      > ����\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
                pos=2;
            }
        }
    }
}
void pass()                                   //ͨ����ʾ
{
    //ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_HIDE);				//����ָ�����ڵ���ʾ״̬
    MessageBoxA(0,"           ��ϲͨ�أ�","��ʾ",MB_OK|MB_SYSTEMMODAL);
    ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_SHOW);
    menu();
}
void restart(int flag)                        //���¿�ʼ
{
    system("mode con cols=20 lines=7");  //���ô��ڴ�С
    gotoxy(0,0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ
    printf("\n      ���¿�ʼ��\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
    printf("--------------------");
    int pos=1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ
    printf("      > ȷ��\n");
    printf("        ����\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
    printf("--------------------");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ

    char input;
    while(1)
    {
        input=getch();
        if(input==13){
            system("cls");
            if(pos==1){            //ȷ�Ϸ���
                menu();
            }
            if(pos==2){            //������Ϸ
                if(flag==Flag_start_manu){
                    start_manu();  //�����ֶ���ʼģʽ
                }
                else if(flag==Flag_start_auto){
                    start_auto();  //�����Զ���ʼģʽ
                }
            }
        }
        if(input!=-32) continue;
        input=getch();
        if(input==72){  //��
            if(pos==2){
                gotoxy(0,0);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ
                printf("\n      ���¿�ʼ��\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ
                printf("      > ȷ��\n");
                printf("        ����\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
                pos=1;
            }
        }
        if(input==80){  //��
            if(pos==1){
                gotoxy(0,0);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ
                printf("\n      ���¿�ʼ��\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);	//������ɫ
                printf("        ȷ��\n");
                printf("      > ����\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//������ɫ
                printf("--------------------");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);	//������ɫ
                pos=2;
            }
        }
    }
}
void set()                                    //���� 
{
	//ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_HIDE);				//����ָ�����ڵ���ʾ״̬
	MessageBoxA(0,"           ����δ���ţ�","��ʾ",MB_OK|MB_SYSTEMMODAL);
    ShowWindow(FindWindowA("ConsoleWindowClass",NULL),SW_SHOW);
    menu();
}

int main()
{
    menu();

    return 0;
}


