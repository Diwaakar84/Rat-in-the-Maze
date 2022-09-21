/*#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

using namespace sf;
using namespace std;

int maze[7][7] =
{{1, 1, 1, 1, 1, 1, 1},
{1, 0, 1, 1, 0, 0, 1},
{1, 0, 1, 0, 0, 0, 1},
{1, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 1, 1, 1},
{1, 0, 1, 0, 1, 0, 1},
{1, 1, 1, 1, 1, 1, 1}};

struct stack1
{
	int x, y, dir;
};
struct queue1
{
	int x, y;
};

void find_path(Vector2i start, Vector2i finish);
void shortest_path(Vector2i start, Vector2i finish);

void find_path(Vector2i start, Vector2i finish)
{
	if ((start.x == finish.x) && (start.y == finish.y))
	{
		return;
	}
	int mark[15][15] , i, j, k, dir, top, g, h;
	int move[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

	//Creating a copy of maze.
	for (i = 0; i < 7; i++)
		for (j = 0; j < 7; j++)
			mark[i][j] = maze[i][j];

	stack1 stack[150];
	top = 0;
	stack[top].x = start.x;
	stack[top].y = start.y;
	stack[top].dir = 0;
	cout << "\nStack:";
	while (top >= 0)
	{
		i = stack[top].x;
		j = stack[top].y;
		dir = stack[top].dir;
		top--;
		while (dir <= 8)
		{
			//cout << "\n" << i << " " << j << " " << dir << " " << top;
			g = i + move[dir][0];
			h = j + move[dir][1];
			if ((g == finish.x) && (h == finish.y))
			{
				cout << "\nPath";
				for (k = 0; k <= top; k++)
				{
					cout << endl;
					cout << stack[k].x << " " << stack[k].y << " ";
				}
				cout << "\n" <<  i << " " << j << "\n" << finish.x << " " << finish.y;
				return;
			}
			if ((maze[g][h] == 0) && (mark[g][h] == 0))
			{
				mark[g][h] = 1;
				top++;
				stack[top].x = i;
				stack[top].y = j;
				stack[top].dir = dir;
				i = g;
				j = h;
				dir = -1;
			}
			dir++;
		}
	}

	cout << "\nThere is no path";
}

void shortest_path(Vector2i start, Vector2i finish)
{
	int i, j, len, rear = 0;
	queue1 queue[150];
	Vector2i offset[4], here, neighbour, path[100];
	if ((start.x == finish.x) && (start.y == finish.y))
		return;

	offset[0].x = 0;
	offset[0].y = 1;
	offset[1].x = 1;
	offset[1].y = 0;
	offset[2].x = 0;
	offset[2].y = -1;
	offset[3].x = -1;
	offset[3].y = 0;

	here = start;
	maze[start.x][start.y] = 2;
	while(rear >= 0)
	{
		for (i = 0; i < 4; i++)
		{
			neighbour.x = here.x + offset[i].x;
			neighbour.y = here.y + offset[i].y;
			if (maze[neighbour.x][neighbour.y] == 0)
			{
				maze[neighbour.x][neighbour.y] = maze[here.x][here.y] + 1;
				if (neighbour == finish)
					break;
				queue[rear].x = neighbour.x;
				queue[rear].y = neighbour.y;
				rear++;
				cout << endl << neighbour.x << " " << neighbour.y << " " << rear << "\n";
			}
			//here = neighbour;
		}
		here.x = queue[0].x;
		here.y = queue[0].y;
		for (int i = 0; i < (rear - 1); i++)
					queue[i] = queue[i + 1];
			rear--;
	}
	for (i = 0; i < 7; i++)
	{
		cout << endl;
		for (j = 0; j < 7; j++)
			cout << maze[i][j] << " ";
	}
	len = maze[finish.x][finish.y] - 2;
	here = finish;

	for (j = len; j >= 0; j--)
	{
		path[j] = here;
		for (i = 0; i < 4; i++)
		{
			neighbour.x = here.x + offset[i].x;
			neighbour.y = here.y + offset[i].y;
			if (maze[neighbour.x][neighbour.y] == maze[here.x][here.y] - 1)
				break;
		}
		here = neighbour;
	}
	cout << endl;
	if (maze[finish.x][finish.y] == 0)
		cout << "There is no path";
	for (i = 0; i <= len; i++)
		cout << path[i].x << " " << path[i].y << "\n";
}

int main ()
{
	Vector2i start, finish;
	int i;
	start.x = 1;
	start.y = 1;
	finish.x = 5;
	finish.y = 5;
	for (i = 0; i <= 6; i++)
	{
		maze[0][i] = 1;
		maze[i][0] = 1;
		maze[i][6] = 1;
		maze[6][i] = 1;
	}

	shortest_path(start, finish);
}*/