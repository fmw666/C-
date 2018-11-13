## 《飞跃忍者》流程
+ 打开Qt，`New Project`，选择项目中的`Application`->`Qt Widgets Application`

![C42FTMNB6}(ZY`}RT25)7VO.png](https://i.loli.net/2018/11/13/5beabacb99c85.png)

  
+ 设定窗口大小

  > 在[main.cpp]()中
  ```cpp
  w.setFixedSize(450,800);  //宽的大小,高的大小
  ```
+ 设定窗口名称

  > 在[main.cpp]()中
  ```cpp
  w.setWindowTitle("飞跃忍者");
  ```
+ 设定窗口图标

  右键项目`添加新文件...`，选择`C++ Source File`
  
  添加文件进去
  
  ![ZU9LT{0P$F82PO)EYDM}2)K.png](https://i.loli.net/2018/11/13/5beabe9a27234.png)
  
  选择`复制资源路径`
  > 在[main.cpp]()中
  ```cpp
  w.setWindowIcon(QIcon(":/new/prefix1/C:/Users/fmw19/Desktop/素材/武士忍者剪影图片/icon.png"));
  ```
  
  来看下效果
  
  ![J2E8RL_48FG@R\]HVA{3{PHO.png](https://i.loli.net/2018/11/13/5beabf81afe6d.png)
  
+ 进行ui设计，设计完成大体框架
