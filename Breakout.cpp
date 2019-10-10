#include<iostream>
#include<string>
#include<conio.h>
#include"../Hide.h"
#include"../Color.h"
#include"../gotoxy.h"
using namespace std;

const int HEIGHT=15,WIDTH=35,rgb[6]={4,6,14,10,11,1};
int grid[HEIGHT][WIDTH] = {0};//zero in grid means gone 1 means there is still a box there
string dir= "";
struct{
	int x;
	int y;
}paddle,ball;

/////////////////create directions////////////////////
void MoveBall()
{
	if(dir=="up")
	{
		ball.y--;
	}
	else if(dir=="down")
	{
		ball.y++;
	}
	else if(dir=="left")
	{
		ball.x--;
	}
	else if(dir=="right")
	{
		ball.x++;
	}
	else if(dir=="up-left")
	{
		ball.y--;
		ball.x--;
	}
	else if(dir=="up-right")
	{
		ball.y--;
		ball.x++;
	}
	else if(dir=="down-left")
	{
		ball.y++;
		ball.x--;
	}
	else if(dir=="down-right")
	{
		ball.y++;
		ball.x++;
	}
}

//////////////create tick timer////////////////////
void newtick()
{
	Sleep(10);
}

//////////////create grid////////////////////
void PrintBox()
{
	for(int i = 0;i < HEIGHT;i++)
	{
		for(int j=0;j<WIDTH;j++)
		{
			color(rgb[(i+j)%6]);
			cout<< char(219)<<char(219)<<char(219);
			grid[i][j]=1;
		}
		cout << endl;
	}
	color(7);
}
//////////////print paddle//////////////////////
void PrintPad()
{
	for(int i = 0; i<21;i++)
	{
		cout << char(219);
	}
}

//////////////move paddle//////////////////////
void MovePad(char leftright)
{
	if(leftright == 'L')
	{
		paddle.x--;
		gotoxy(paddle.x,paddle.y);
		cout <<char(219);
		gotoxy(paddle.x+21,paddle.y);
		cout << " ";
	}
	else if(leftright == 'R')
	{
		paddle.x++;
		gotoxy(paddle.x-1,paddle.y);
		cout <<" ";
		gotoxy(paddle.x+20,paddle.y);
		cout <<char(219);
	}
}

//////////////TODO:detect colision////////////////////



int main()
{
	char ch;
	paddle.x = 43;
	paddle.y = 26;
	ShowConsoleCursor(false);
	system("cls");
	PrintBox();
	gotoxy(paddle.x,paddle.y);
	PrintPad();
	while(1)
	{
		while(kbhit)
		{

			ch = _getch();
			if(ch==-32)
			{
				ch = _getch();
				if(ch==75)//left
				{
					MovePad('L');
				}//if
				else if(ch==77)//right
				{
					MovePad('R');
				}//else if
			}//if ch-32
			else if(ch==113)
			{
				ShowConsoleCursor(true);
				exit(0);
			}
		}//if kbhit
	}//while


	return 0;
}