## 🚀 《C语言》游戏开发基础讲解
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
  
  修改窗口大小、字体大小、背景颜色
