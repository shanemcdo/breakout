#include<iostream>
#include<string>
#include<conio.h>
#include"Hide.h"
#include"Color.h"
#include"gotoxy.h"
using namespace std;

const int HEIGHT=15,WIDTH=35,rgb[6]={4,6,14,10,11,1};
int score = 0, tick=0,grid[HEIGHT][WIDTH] = {0};//zero in grid means gone 1 means there is still a box there
string dir= "";
char yesno;
bool win=true,running = true;
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
}//moveball

//////////////create tick timer////////////////////
void newtick()
{
	Sleep(10);
	tick++;
	if(tick >100000)
		tick=1;
}//newtick

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
}//PrintBox

//////////////print paddle//////////////////////
void PrintPad()
{
	for(int i = 0; i<21;i++)
	{
		cout << char(219);
	}
}//PrintPad

//////////////move paddle//////////////////////
void MovePad(char leftright)
{
	if(leftright == 'L')
	{
		paddle.x--;
		if(paddle.x < 1)
			paddle.x=1;
		else
		{
			gotoxy(paddle.x,paddle.y);
			cout <<char(219);
			gotoxy(paddle.x+21,paddle.y);
			cout << " ";
		}
	}
	else if(leftright == 'R')
	{
		paddle.x++;
		if(paddle.x > 85)
			paddle.x=85;
		else
		{
			gotoxy(paddle.x-1,paddle.y);
			cout <<" ";
			gotoxy(paddle.x+20,paddle.y);
			cout <<char(219);
		}
	}
}//MovePad
//////////////bounce//////////////////////
void bouncewall()
{
	
	if(dir=="left")
	{
		dir="right";
	}
	else if(dir=="right")
	{
		dir="left";
	}
	else if(dir=="up-left")
	{
		dir="up-right";
	}
	else if(dir=="up-right")
	{
		dir="up-left";
	}
	else if(dir=="down-left")
	{
		dir="down-right";
	}
	else if(dir=="down-right")
	{
		dir="down-left";
	}

}//bouncewall
void bounceceil()
{
	if(dir=="up")
	{
		dir="down";
	}
	else if(dir=="down")
	{
		dir="up";
	}
	else if(dir=="up-left")
	{
		dir="down-left";
	}
	else if(dir=="up-right")
	{
		dir="down-right";
	}
	else if(dir=="down-left")
	{
		dir="up-left";
	}
	else if(dir=="down-right")
	{
		dir="up-right";
	}

}//bounceceil
void bouncepad()
{
	if(ball.x>=paddle.x&&ball.x<=paddle.x+6)
		if(dir=="down")
		{
			dir="up-left";
		}
		if(dir=="down-right")
		{
			dir="up";
		}
	else if(ball.x>=paddle.x+7&&ball.x<=paddle.x+13)
		if(dir=="down")
		{
			dir="up";
		}
		if(dir=="down-left")
		{
			dir="up-left";
		}
		if(dir=="down-right")
		{
			dir="up-right";
		}
	else if(ball.x>=paddle.x+14&&ball.x<=paddle.x+20)
		if(dir=="down")
		{
			dir="up-right";
		}
		if(dir=="down-left")
		{
			dir="up";
		}

}//bouncepad
//////////////detect win   ////////////////////
bool Won()
{
	for(int i = 0; i < HEIGHT;i++)
	{
		for(int j = 0; j < WIDTH;j++)
		{
			if(grid[i][j]==1)
				return false;
		}
	}
	return true;
}//won
//////////////detect colision////////////////////
void detect()
{
	if(ball.x==0||ball.x==105)
		bouncewall();
	else if(ball.y<=0)
		bounceceil();
	else if(ball.y==paddle.y-1&&ball.x>=paddle.x-1&&ball.x<=paddle.x+20)
		bouncepad();
	else if(ball.y==paddle.y+1)
		win = false;
	else
	{
		for(int i = 0;i<HEIGHT;i++)
		{
			for(int j = 0; j < WIDTH;j++)
			{
				if(grid[i][j]==1)
				{
					if(dir=="up-right")
					{
						if((ball.x>=((j*3)-1))&&(ball.x<=((j*3)+1))&&(ball.y==(i+1)))
						{
							dir="down-right";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//if
						else if((ball.x>=((j*3)-1))&&(ball.y==(i)))
						{
							dir="up-left";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//else if
					}//up-right
					else if(dir=="up-left")
					{
						if((ball.x>=((j*3)+1))&&(ball.x<=((j*3)+3))&&(ball.y==(i+1)))
						{
							dir="down-left";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//if
						else if((ball.x>=((j*3)+1))&&(ball.y==(i)))
						{
							dir="up-right";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//else if
					}//up-left
					else if(dir=="up")
					{
						if((ball.x>=(j*3))&&(ball.x<=((j*3)+2))&&(ball.y==(i+1)))
						{
							dir="down";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//if
					}//up
					else if(dir=="down-right")
					{
						if((ball.x>=((j*3)-1))&&(ball.x<=((j*3)+1))&&(ball.y==(i-1)))
						{
							dir="up-right";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//if
						else if((ball.x>=((j*3)-1))&&(ball.y==(i)))
						{
							dir="down-left";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//else if
					}//down-right
					else if(dir=="down-left")
					{
						if((ball.x>=((j*3)+1))&&(ball.x<=((j*3)+3))&&(ball.y==(i-1)))
						{
							dir="up-left";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//if
						else if((ball.x>=(j*3)+4)&&(ball.y==(i)))
						{
							dir="down-right";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//else if
					}//down-left
					else if(dir=="down")
					{
						if((ball.x>=(j*3))&&(ball.x<=((j*3)+2))&&(ball.y==(i-1)))
						{
							dir="up";
							grid[i][j]=0;
							gotoxy((j*3),i);
							cout << "   ";
							score += 100;
						}//if
					}//down
				}//if
			}//for j
		}//for i
	}//else

}//detect

int main()
{
	do{
		char ch;
		paddle.x = 43;
		paddle.y = 26;
		ball.x = paddle.x+10;
		ball.y = paddle.y-1;
		dir="up-left";
		yesno = ' ';
		score = 0;
		win = true;
		ShowConsoleCursor(false);
		system("cls");
		PrintBox();
		gotoxy(paddle.x,paddle.y);
		PrintPad();
		gotoxy(1,paddle.y+2);
		cout << "score: 0";
	      	while(1)
	      	{
			if(kbhit())/////////DETECT IMPUT///////
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
			if(tick%4==0)//how often ball moves
			{
				detect();
				gotoxy(ball.x,ball.y);
				cout << " ";	
				MoveBall();
				gotoxy(ball.x,ball.y);
				cout << char(254);
				gotoxy(8,paddle.y+2);
				cout << score;
				if(!win||Won())
					break;

			}
			newtick();
		}//while
		ShowConsoleCursor(true);
		system("cls");
		if(!win)
		{
			cout << "you lose!" << endl;
		}
		else
		{
			cout << "you win!" <<endl;
		}
		cout << "your score was " << score << endl;
		while(yesno != 'n'&&yesno != 'N'&&yesno != 'y'&& yesno != 'Y')
		{
			cout << "Play again? y/n\n";
			cin >> yesno;
		}
		if(yesno != 'y'&&yesno !='Y')
			break;
	}while(running);
			

	return 0;
}
