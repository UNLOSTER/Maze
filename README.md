# Maze V1.0
---
项目：Maze

版本：V1.0

作者：Lost(QQ：2931404870)

时间：2020-7-22

环境：开始使用 VS2010，后来用 VS2017 修改

简介：一个普通的迷宫小游戏

感谢：感谢 QQ 群 C语言革命7 全体成员为该项目的开发做了巨大的贡献，没有你们，该作品也不能有现在的情况！

版权：作者原创，无抄袭，不涉及版权问题，仅用作学习、娱乐，欢迎各位fork!
### 玩法：
~~~cpp
游戏开始选择系列关卡

有三种系列：

森林（简单，基于 Prim 算法）

地牢（中等，基于图论 DFS 算法）

地狱（困难，基于暴力 DFS 算法）

选择系列后，进入游戏

WSAD 上下左右，游戏中有计时器
~~~
### 文件：
~~~cpp
Maze.h :          初始化头文件
Maze.cpp :        程序开端文件
Game.h :          游戏类头文件
Adventrue.cpp :   冒险模式类文件
Forest.cpp :      冒险模式-森林系列类实现文件
Dungeon.cpp :     冒险模式-地牢系列类实现文件
Infernal.cpp :    冒险模式-地狱系列类实现文件
Help.cpp :        帮助信息类实现文件
Other.cpp :       刷新界面、放置按钮、输出对话框类实现文件
~~~
### 运行效果：
![start](https://f.myid.email/87/b9/bc/dddf9c-08f8-9660-72f26953eac1/Files/maze-start.png)
![play](https://f.myid.email/87/b9/bc/dddf9c-08f8-9660-72f26953eac1/Files/maze-game.png)
