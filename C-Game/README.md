## 🚀 《C语言》游戏开发基础讲解
+ **游戏框架搭建**
  ```c
  // 函数外全局变量定义

  int main()
  {
      startup();  // 数据初始化
      while (1) //  游戏循环执行
      {
          show();  // 显示画面
          updateWithoutInput();  // 与用户输入无关的更新
          updateWithInput();  // 与用户输入有关的更新
      }
      return 0;
  }
  ```
+ **清屏函数**
  ```c
  #include <stdlib.h>
  system("cls");
  ```
+ **延时函数**
  ```c
  #include <windows.h>
  Sleep(20);    //其中20的单位为毫秒
  ```
+ **停止等待函数**
  ```c
  #include <windows.h>
  system("pause");
  ```
+ **系统自带发出铃声**
  ```c
  printf("\a");
  ```
+ **读取键盘上输入的值(需要回车)**
  ```c
  char input;
  scanf("%c",&input);
  if(input=='w')
      printf("w");
  ```
+ **读取键盘上输入的值(不需要回车)**
  ```c
  #include<conio.h>
  
  char input;
  //scanf("%c",&input);
  input = getch();
  if(input=='w')
      printf("w");
  ```
+ **判断是否有键盘输入的函数**
  ```c
  #include <conio.h>
  kbhit();   //若有则返回一个非0值，否则返回0
  ```
  > 示例：
  ```c
  #include <stdio.h>
  #include <conio.h>

  int main()
  {
      char input;
      if(kbhit()){
          scanf("%c",&input);    //需要按下回车键来读取
          //input=getch();
          printf("按下了键\n");
      }
  }
  ```
  ```c
  #include <stdio.h>
  #include <conio.h>

  int main()
  {
      char input;
      if(kbhit()){
          //scanf("%c",&input);    
          input=getch();           //不需要按下回车键来读取
          printf("按下了键\n");
      }
  }
  ```
+ **产生随机数的函数**
  ```c
  #include<stdlib.h>
  rand();
  ```
+ **光标移动到原点位置进行重画(实现类似于清屏函数的效果)**
  ```c
  #include <windows.h>
  
  void gotoxy(int x,int y)//类似于清屏函数，光标移动到原点位置进行重画
  {
      HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD pos;
      pos.X = x;
      pos.Y = y;
      SetConsoleCursorPosition(handle,pos);
  }
  
  int main()
  {
      gotoxy(0,0);
  }
  ```
+ **隐藏光标显示函数**
  ```c
  #include <windows.h>
  
  void HideCursor()
  {
      CONSOLE_CURSOR_INFO cursor_info={1,0};   //第二个值为0表示隐藏光标
      SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
  }
  
  int main()
  {
      HideCursor();
  }
  ```
+ **修改窗口大小**
  ```c
  #include <windows.h>
  system("mode con cols=30 lines=20");  //其中30为宽的值，20为高的值
  ```
+ **固定窗口大小**
  ```c
  #include <windows.h>
  void fixWinSize()  
  {
      HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
      RECT rc;
      GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形

      //改变cmd窗口风格
      SetWindowLongPtr(hWnd,GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
  }
  
  fixWinSize();
  ```
+ **修改窗口标题**

  > ***方法一：***
  ```c
  #include <windows.h>
  SetConsoleTitleA("name");
  ```
  > ***方法二：***
  ```c
  #include <windows.h>
  system("title name");
  ```
+ **修改字体颜色、背景颜色**

  > ***方法一：***
  ```c
  #include <windows.h>
  system("color 07");     //(07)为默认的黑底白字。其中0为背景色，7为前景色
  
  /*
  颜色属性由两个十六进制数字指定 
  -- 第一个为背景色，第二个则为前景色。
  每个数字可以为以下任何值之一:
  0 = 黑色 8 = 灰色
  1 = 蓝色 9 = 淡蓝色
  2 = 绿色 A = 淡绿色
  3 = 湖蓝色 B = 淡浅绿色
  4 = 红色 C = 淡红色
  5 = 紫色 D = 淡紫色
  6 = 黄色 E = 淡黄色
  7 = 白色 F = 亮白色
  */
  ```
  > ***方法二：***
  ```c
  #include <windows.h>
  
  void SetColor(unsigned short BackGroundColor,unsigned short ForeColor)
  {
      HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hCon,(ForeColor%16)|(BackGroundColor%16*16));
  }
  
  SetColor(0,7);   //(0,7)为默认的黑底白字。其中0为背景色，7为前景色
  ```
  > ***示例：***
  ```c
  #include <windows.h>
  #include <stdio.h>

  void SetColor(unsigned short BackGroundColor,unsigned short ForeColor)
  {
      HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hCon,(ForeColor%16)|(BackGroundColor%16*16));
  }

  int main()
  {
      system("color 70");
      printf("方法一\n");

      int i,j;
      while(scanf("%d %d",&i,&j))
      {
          SetColor(i,j);
          printf("方法二\n");
      }
  }
  ```
  ![color.png](https://i.loli.net/2018/11/18/5bf0d8d1cd1eb.png)
+ **修改字体大小**
  ```c
  //暂未
  ```
+ **修改字体大小**
  ```c
  //暂未
  ```
