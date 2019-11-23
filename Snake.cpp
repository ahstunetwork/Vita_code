#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
//实际上不需要宏定义，但是定义了看起来有逼格
#define MAPX 60
#define MAPY 16
#define SNAKESIZE 50

using namespace std;

/////////////////////////////////////////////
//                 食物
struct
{
	int x;
	int y;
}food;

//////////////////////////////////////////////
//              本来准备用链表，可是太他妈难了  ，，五月十七第一版
//蛇
struct
{
	int x[SNAKESIZE];
	int y[SNAKESIZE];
	int len;
	int speed;
}snake;

///////////////////////////////////////////////
//                全局变量
int key = 52;            //初始化移动方向
int changeflag = 0;
int Count = 1;
int Number = 1;
int num = 1;
int step = 0;
int speed;
int rightkey;

///////////////////////////////////////////////
//                 全部工作函数
//绘图 
void DrawMap();
//产生食物 
void CreateFood();
//检索键盘操作 
void KeyDown();
//主题状态，判断游戏进程 
void SnakeStatue();
//辅助函数：光标移动 注入灵魂
void gotoxy(int x, int y);

void SnakeSpeed();

//////////////////////////////////////////////////////////////////// 
//     main函数            
int main()
{
	DrawMap();
	while (1)
	{
		SnakeSpeed();
		KeyDown();
		CreateFood();


		gotoxy(0, MAPY + 1);
		cout << "移动距离：" << num;
		num++;

		gotoxy(15, MAPY + 1);
		cout << "操作次数：" << step;

		gotoxy(30, MAPY + 1);
		cout << "速度等级：" << speed;

		gotoxy(45, MAPY + 1);
		cout << "游戏分数：" << snake.len - 4;

		SnakeStatue();
		if (Count == 0)
		{
			gotoxy(MAPX / 2, MAPY / 2);
			cout << "Gameover!" << endl;
			break;
		}

		//		gotoxy(0,MAPY+1);

		if (snake.len == SNAKESIZE)
		{
			gotoxy(MAPX / 2 - 4, MAPY / 2);
			cout << "你真牛批!";
			break;
			gotoxy(1, MAPY + 3);
		}
	}

	system("pause");
	return 0;
}
/////////////////////////////////////////// ///////////////////// 
//            画图 
void DrawMap()
{
	//"+”头，身体 
	srand((unsigned int)time(NULL));
	//左右边框
	for (int i = 0; i <= MAPY; i++)
	{
		gotoxy(0, i);
		cout << "*" << endl;
		gotoxy(MAPX, i);

		cout << "*" << endl;
	}
	//上下边框 
	for (int j = 0; j <= MAPX; j++)
	{
		gotoxy(j, 0);
		cout << "*" << endl;
		gotoxy(j, MAPY);
		cout << "*" << endl;
	}
	//身体参数 
	snake.len = 4;
	snake.speed = 350;
	//初始化头部位置
	snake.x[0] = MAPX / 2;
	snake.y[0] = MAPY / 2;
	//头
	gotoxy(snake.x[0], snake.y[0]);
	cout << "*" << endl;
	//for循环建立,让后一个始终跟着前一个，再用gotoxy追踪显示 
	for (int k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 1;      //sanke[1]=snake[0]+1 
		snake.y[k] = snake.y[k - 1];        //y不需要*1，因为这是初始化建立整体 
		gotoxy(snake.x[k], snake.y[k]);
		cout << "*" << endl;
	}
	//建立第一个，后续需单独用函数建立 
	food.x = rand() % (MAPX - 2) + 1;
	food.y = rand() % (MAPY - 2) + 1;
	gotoxy(food.x, food.y);
	cout << "!" << endl;
	//把光标移走
	gotoxy(0, MAPY + 1);

}

///////////////////////////////////////////////////////////////////////////////
//          定义gotoxy函数,使用win32 API
void gotoxy(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(handle, coord);
}
///////////////////////////////////////////////////////////////////////////////
//        监控键盘的操作
void KeyDown()
{
	fflush(stdin);

	if (changeflag == 0)    //如果get到了，则长度+1，即原来尾部的不动，头加一，没吃到，头加一，尾减一 
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		cout << " ";
	}

	for (int i = snake.len - 1; i > 0; i--)      //其余位置的坐标跟踪上一个 
	{
		snake.x[i] = snake.x[i - 1];
		snake.y[i] = snake.y[i - 1];
	}


	if (Number != 1)
	{
		key = rightkey;
	}


	//监控键盘，如果有输入，这执行输入的命令 
	if (_kbhit())
	{
		Number++;
		step++;
		switch (key)  //判断刚执行到这儿的时候，运动的方向 
		{

		case 56:  //如果默认是56/8 
			fflush(stdin);   //清空缓冲区 
			key = _getch();     //把8的ASCII值给key

			if (key == 52 || key == 54 || key == 56)
			{
				rightkey = key;
			}
			else
			{
				gotoxy(MAPX +1, MAPY + 1);
				cout << "输入非法！";
			}

			switch (rightkey)         //检验key的数值 
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
			break;



		case 50:
			fflush(stdin);
			key = _getch();
			if (key == 52 || key == 54 || key == 50)
			{
				rightkey = key;
			}
			else
			{
				gotoxy(MAPX +1, MAPY + 1);
				cout << "输入非法！";
			}

			switch (rightkey)
			{
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
			break;


		case 52:
			//调试	
//          gotoxy(MAPX+1,2);
//			cout<<key;

			fflush(stdin);
			key = _getch();
			if (key == 52 || key == 56 || key == 50)
			{
				rightkey = key;
			}
			else
			{
				gotoxy(MAPX+1, MAPY + 1);
				cout << "输入非法！";
			}
			//调试 
//			gotoxy(MAPX+1,8);
	//		cout<<key;
			switch (rightkey)
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				//			        gotoxy(MAPX+1,MAPY+1);
				//			        cout<<"FUCK! you";
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				//			        gotoxy(MAPX+1,MAPY+1);
				//			        cout<<"FUCK! you";
				break;
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			}
			break;

		case 54:
			fflush(stdin);
			key = _getch();
			if (key == 54 || key == 56 || key == 50)
			{
				rightkey = key;
			}
			else
			{
				gotoxy(MAPX +1, MAPY + 1);
				cout << "输入非法！";
			}
			switch (rightkey)
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				break;
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
			break;
		}
		//默认为8，则不能输入2，下同 

	}

	//		key=getch();
	//		cout<<"here";
	//		switch(key)
	//	    {
	//	    	
	//		    case '8':
	//			    snake.y[0]=snake.y[0]-1;
	//			    break;
	//		    case '2':
	//			    snake.y[0]=snake.y[0]+1;
	//			    break;
	//		    case '4':
	//			    snake.x[0]=snake.x[0]-1;
	//			    break;
	//		    case '6':
	//			    snake.x[0]=snake.x[0]+1;
	//			    break;
	//		}				

	////////////////////////////////////////////////////////////////////////
	//    Sleep(snake.speed);
	////////////////////////////////////////////////////////////////////////

	else
	{
		if (Number == 1)
		{
			switch (key)
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				break;
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
		}
		else
		{
			switch (rightkey)
			{
			case 56:
				snake.y[0] = snake.y[0] - 1;
				break;
			case 50:
				snake.y[0] = snake.y[0] + 1;
				break;
			case 52:
				snake.x[0] = snake.x[0] - 1;
				break;
			case 54:
				snake.x[0] = snake.x[0] + 1;
				break;
			}
		}

	}

	gotoxy(snake.x[0], snake.y[0]);
	cout << "*";
	//	Sleep(200);
}
/////////////////////////////////////////////////////////////////
//          食物
void CreateFood()
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)
	{

		//调试 
//		gotoxy(0,MAPY+5);
//		cout<<"here";

		int flag = 1;
		food.x = rand() % (MAPX - 2) + 1;
		food.y = rand() % (MAPY - 2) + 1;

		srand((unsigned int)time(NULL));
		while (1)
		{

			for (int k = 0; k < snake.len; k++)
			{
				if (snake.x[k] == food.x && snake.y[k] == food.y)
				{
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				gotoxy(food.x, food.y);
				cout << "!";
				break;
			}
		}
		snake.len = snake.len + 1;;
		changeflag = 1;
	}
	else
	{
		changeflag = 0;
	}
}
//////////////////////////////////////////////////////////////////////
//       主体的状态

void SnakeStatue()
{
	//到尽头或者撞到自己，就把count赋值0
	if (snake.x[0] == 0 || snake.x[0] == MAPX - 1 || snake.y[0] == 0 || snake.y[0] == MAPY - 1)
	{
		Count = 0;
	}

	for (int k = 1; k < snake.len; k++)
	{
		if (snake.x[0] == snake.x[k] && snake.y[0] == snake.y[k])
		{
			gotoxy(10, MAPY + 1);
			cout << "here!";
			Count = 0;
		}
	}

}
/////////////////////////////////////////////////////////////////////
//           移动速度
void SnakeSpeed()
{
	if (snake.len < 10)
	{
		Sleep(snake.speed - 50);
		speed = 1;
	}
	if (snake.len >= 10 && snake.len < 20)
	{
		Sleep(snake.speed - 100);
		speed = 2;
	}
	if (snake.len >= 20 && snake.len < 30)
	{
		Sleep(snake.speed - 150);
		speed = 3;
	}
	if (snake.len >= 30 && snake.len < 40)
	{
		Sleep(snake.speed - 200);
		speed = 4;
	}
	if (snake.len >= 40 && snake.len < 50)
	{
		Sleep(snake.speed - 250);
		speed = 5;
	}
	if (snake.len > 50)
	{
		Sleep(snake.speed - 300);
		speed = 6;
	}
}