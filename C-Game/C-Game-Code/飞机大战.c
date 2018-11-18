#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 15  // 游戏画面尺寸
#define Width 25
#define EnemyNum 5 // 敌机个数

// 全局变量
int position_x,position_y; // 飞机位置
int enemy_x[EnemyNum],enemy_y[EnemyNum];  // 敌机位置
int canvas[High][Width] = {0}; // 二维数组存储游戏画布中对应的元素
                        // 0为空格，1为飞机*，2为子弹|，3为敌机@
int score; // 得分
int BulletWidth; // 子弹宽度
int EnemyMoveSpeed; // 敌机移动速度

void fixWinSize()   //固定窗口大小
{
    HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
    RECT rc;
    GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形

    //改变cmd窗口风格
    SetWindowLongPtr(hWnd,GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
}

void gotoxy(int x,int y)  //光标移动到(x,y)位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info={1,0};   //第二个值为0表示隐藏光标
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

void startup() // 数据初始化
{
    HideCursor();  //隐藏光标
    system("mode con cols=25 lines=17");  //设置窗口大小
    system("color F0");   //调色
    fixWinSize();   //固定窗口大小
    SetConsoleTitleA("飞机大战");  //设置窗口标题

    position_x = High-1;
    position_y = Width/2;
    canvas[position_x][position_y] = 1;
    int k;
    for (k=0;k<EnemyNum;k++)
    {
        enemy_x[k] = rand()%2;
        enemy_y[k] = rand()%Width;
        canvas[enemy_x[k]][enemy_y[k]] = 3;
    }
    score = 0;
    BulletWidth = 0;
    EnemyMoveSpeed = 20;
}

void begin()  //开始界面
{

    printf("\n\n\n    飞机大战の游戏说明\n\n\n");
    printf("\n     方向键： W   ");
    printf("\n             ASD\n");
    printf("\n     攻击键：空格\n");
    printf("\n\n     ");
    system("pause");

}

void show()  // 显示画面
{
    gotoxy(0,0);  // 光标移动到原点位置，以下重画清屏
    int i,j;
    for (i=0;i<High;i++)
    {
        for (j=0;j<Width;j++)
        {
            if (canvas[i][j]==0)
                printf(" ");   //   输出空格
            else if (canvas[i][j]==1)
                printf("*");   //   输出飞机*
            else if (canvas[i][j]==2)
                printf("|");   //   输出子弹|
            else if (canvas[i][j]==3)
                printf("@");   //  输出飞机@
        }
        printf("\n");
    }
    printf("得分：%d\n",score);
    Sleep(20);
}

void updateWithoutInput()  // 与用户输入无关的更新
{
    int i,j,k;
    for (i=0;i<High;i++)
    {
        for (j=0;j<Width;j++)
        {
            if (canvas[i][j]==2)
            {
                for (k=0;k<EnemyNum;k++)
                {
                    if ((i==enemy_x[k]) && (j==enemy_y[k]))  // 子弹击中敌机
                    {
                        score++;                // 分数加1
                        if (score%5==0 && EnemyMoveSpeed>3)   // 达到一定积分后，敌机变快
                            EnemyMoveSpeed--;
                        if (score%5==0)   // 达到一定积分后，子弹变厉害
                            BulletWidth++;
                        canvas[enemy_x[k]][enemy_y[k]] = 0;
                        enemy_x[k] = rand()%2;           // 产生新的飞机
                        enemy_y[k] = rand()%Width;
                        canvas[enemy_x[k]][enemy_y[k]] = 3;
                        canvas[i][j] = 0;      // 子弹消失
                    }
                }
                // 子弹向上移动
                canvas[i][j] = 0;
                if (i>0)
                    canvas[i-1][j] = 2;
            }
        }
    }

    static int speed = 0;
    if (speed<EnemyMoveSpeed)
        speed++;

    for (k=0;k<EnemyNum;k++)
    {
        if ((position_x==enemy_x[k]) && (position_y==enemy_y[k]))  // 敌机撞到我机
        {
            printf("失败！\n");
            Sleep(3000);
            system("pause");
            exit(0);
        }

        if (enemy_x[k]>High)   // 敌机跑出显示屏幕
        {
            canvas[enemy_x[k]][enemy_y[k]] = 0;
            enemy_x[k] = rand()%2;           // 产生新的飞机
            enemy_y[k] = rand()%Width;
            canvas[enemy_x[k]][enemy_y[k]] = 3;
            score--;  // 减分
        }

        if (speed == EnemyMoveSpeed)
        {
            // 敌机下落
            for (k=0;k<EnemyNum;k++)
            {
                canvas[enemy_x[k]][enemy_y[k]] = 0;
                enemy_x[k]++;
                speed = 0;
                canvas[enemy_x[k]][enemy_y[k]] = 3;
            }
        }
    }
}

void updateWithInput()  // 与用户输入有关的更新
{
    char input;
    if(kbhit())  // 判断是否有输入
    {
        input = getch();  // 根据用户的不同输入来移动，不必输入回车
        if (input == 'a' && position_y>0)
        {
            canvas[position_x][position_y] = 0;
            position_y--;  // 位置左移
            canvas[position_x][position_y] = 1;
        }
        else if (input == 'd' && position_y<Width-1)
        {
            canvas[position_x][position_y] = 0;
            position_y++;  // 位置右移
            canvas[position_x][position_y] = 1;
        }
        else if (input == 'w')
        {
            if(position_x>0)                 //不能超过上边界
            {
                canvas[position_x][position_y] = 0;
                position_x--;  // 位置上移
                canvas[position_x][position_y] = 1;
            }
        }
        else if (input == 's')
        {
            if(position_x<High-2)            //不能超过下边界
            {
                canvas[position_x][position_y] = 0;
                position_x++;  // 位置下移
                canvas[position_x][position_y] = 1;
            }
        }
        else if (input == ' ')  // 发射子弹
        {
            int left = position_y-BulletWidth;
            int right = position_y+BulletWidth;
            if (left<0)
                left = 0;
            if (right>Width-1)
                right = Width-1;
            int k;
            for (k=left;k<=right;k++) // 发射闪弹
                canvas[position_x-1][k] = 2; // 发射子弹的初始位置在飞机的正上方
        }
    }
}

int main()
{
    startup();  // 数据初始化
    begin();    // 开始界面
    while (1) //  游戏循环执行
    {
        show();  // 显示画面
        updateWithoutInput();  // 与用户输入无关的更新
        updateWithInput();  // 与用户输入有关的更新
    }
    return 0;
}
