
//Header files
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>

using namespace sf;
using namespace std;

int maze1[15][15] = {0};
int maze2[15][15] = {0};
//Creating a window
RenderWindow window(VideoMode(1024, 700), "Rat in the maze", Style::Default);

struct stack1
{
	int x, y, dir;
};
struct queue1
{
	int x, y;
};

void find_path(Vector2i start, Vector2i finish, int m, int n, RectangleShape wall, RectangleShape move, RectangleShape beg, RectangleShape dest, RectangleShape block);
void shortest_path(Vector2i start, Vector2i finish, int m, int n, RectangleShape wall, RectangleShape move, RectangleShape beg, RectangleShape dest, RectangleShape block);
void draw1 (Vector2i start, Vector2i finish, int m, int n, RectangleShape wall, RectangleShape move, RectangleShape beg, RectangleShape dest, RectangleShape block);
void draw2 (Vector2i start, Vector2i finish, int m, int n, RectangleShape wall, RectangleShape move, RectangleShape beg, RectangleShape dest, RectangleShape block);

void draw1 (Vector2i start, Vector2i finish, int m, int n, RectangleShape wall, RectangleShape move, RectangleShape beg, RectangleShape dest, RectangleShape block)
{
	window.clear();

	for (int i = 0; i <= (m + 1); i++)
		{
			for (int j = 0; j <= (n + 1); j++)
			{
				if ((i == start.x) && (j == start.y))
				{
					beg.setPosition(150 + (j * 50), 150 + (i * 50));
					window.draw(beg);
				}
				else if ((i == finish.x) && (j == finish.y))
				{
					dest.setPosition(150 + (j * 50), 150 + (i * 50));
					window.draw(dest);
				}
				else if (maze1[i][j] == 0)
				{
					move.setPosition(150 + (j * 50), 150 + (i * 50));
					window.draw(move);
				}
				else if (maze1[i][j] == 1)
				{
					wall.setPosition(150 + (j * 50), 150 + (i * 50));
					window.draw(wall);
				}
				else if (maze1[i][j] == 2)
				{
					block.setPosition(150 + (j * 50), 150 + (i * 50));
					block.setFillColor(Color::Yellow);
					block.setOutlineThickness(0);
					window.draw(block);
				}
				else if (maze1[i][j] == 3)
				{
					block.setPosition(150 + (j * 50), 150 + (i * 50));
					block.setFillColor(Color::Magenta);
					block.setOutlineThickness(1);
					block.setOutlineColor(Color::White);
					window.draw(block);
				}
			}
		}
}
void draw2 (Vector2i start, Vector2i finish, int m, int n, RectangleShape wall, RectangleShape move, RectangleShape beg, RectangleShape dest, RectangleShape block)
{
	window.clear();

	for (int i = 0; i <= (m + 1); i++)
		{
			for (int j = 0; j <= (n + 1); j++)
			{
				if ((i == start.x) && (j == start.y))
				{
					beg.setPosition(150 + (j * 50), 150 + (i * 50));
					window.draw(beg);
				}
				else if ((i == finish.x) && (j == finish.y))
				{
					dest.setPosition(150 + (j * 50), 150 + (i * 50));
					window.draw(dest);
				}
				else if ((maze2[i][j] == 0) || (maze2[i][j] > 1))
				{
					move.setPosition(150 + (j * 50), 150 + (i * 50));
					window.draw(move);
				}
				else if (maze2[i][j] == 1)
				{
					wall.setPosition(150 + (j * 50), 150 + (i * 50));
					window.draw(wall);
				}
				else if (maze2[i][j] == -1)
				{
					block.setPosition(150 + (j * 50), 150 + (i * 50));
					block.setFillColor(Color::Magenta);
					block.setOutlineThickness(1);
					block.setOutlineColor(Color::White);
					window.draw(block);
				}
			}
		}
}

void find_path(Vector2i start, Vector2i finish, int m, int n, RectangleShape wall, RectangleShape move, RectangleShape beg, RectangleShape dest, RectangleShape block)
{
	RectangleShape chk (Vector2f(50, 50)), way (Vector2f(50, 50));
	chk.setFillColor(Color::White);

	if ((start.x == finish.x) && (start.y == finish.y))
	{
		return;
	}
	int mark[15][15] , i, j, k, dir, top, g, h;
	int move_table[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

	//Creating a copy of maze.
	for (i = 0; i < m + 2; i++)
		for (j = 0; j < n + 2; j++)
			mark[i][j] = maze1[i][j];

	stack1 stack[1000];
	top = 0;
	stack[top].x = start.x;
	stack[top].y = start.y;
	stack[top].dir = 0;
	while (top >= 0)
	{
		i = stack[top].x;
		j = stack[top].y;
		dir = stack[top].dir + 1;
		top--;
		draw1 (start, finish, m, n, wall, move, beg, dest, block);
		while (dir <= 8)
		{
			block.setFillColor(Color::White);
			draw1 (start, finish, m, n, wall, move, beg, dest, block);
			g = i + move_table[dir][0];
			h = j + move_table[dir][1];
			chk.setPosition(150 + (h * 50), 150 + (g * 50));
			window.draw(chk);
			window.display();
			Sleep(100);
			window.clear();

			if ((g == finish.x) && (h == finish.y))
			{
				cout << "\nPath";
				for (k = 0; k <= top; k++)
				{
					cout << endl;
					cout << stack[k].x << " " << stack[k].y << " ";
					maze1[stack[k].x][stack[k].y] = 3;
				}
				cout << "\n" <<  i << " " << j << "\n" << finish.x << " " << finish.y;
				maze1[i][j] = 3;
				maze1[finish.x][finish.y] = 3;
				return;
			}
			if ((maze1[g][h] == 0) && (mark[g][h] == 0))
			{
				mark[g][h] = 1;
				top++;
				stack[top].x = i;
				stack[top].y = j;
				stack[top].dir = dir + 1;
				i = g;
				j = h;
				dir = -1;
			}
			dir++;
			if (dir >= 7)
			{
				maze1[i][j] = 2;
			}
		}
	}
	cout << "\nThere is no path";
}

void shortest_path(Vector2i start, Vector2i finish, int m, int n, RectangleShape wall, RectangleShape move, RectangleShape beg, RectangleShape dest, RectangleShape block)
{
	int i, j, len, rear = 0;
	queue1 queue[1000];
	Vector2i offset[4], here, neighbour, path[200];
	RectangleShape chk (Vector2f(50, 50));
	chk.setFillColor(Color::White);

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
	maze2[start.x][start.y] = 2;
	while(rear >= 0)
	{
		for (i = 0; i < 4; i++)
		{
			draw2 (start, finish, m, n, wall, move, beg, dest, block);
			neighbour.x = here.x + offset[i].x;
			neighbour.y = here.y + offset[i].y;
			if (maze2[neighbour.x][neighbour.y] == 0)
			{
				maze2[neighbour.x][neighbour.y] = maze2[here.x][here.y] + 1;
				chk.setPosition(150 + (neighbour.y * 50), 150 + (neighbour.x * 50));
				window.draw(chk);
				window.display();
				Sleep(100);
				window.clear();
				if (neighbour == finish)
					break;
				queue[rear].x = neighbour.x;
				queue[rear].y = neighbour.y;
				rear++;
			}
		}
		here.x = queue[0].x;
		here.y = queue[0].y;
		for (int i = 0; i < (rear - 1); i++)
					queue[i] = queue[i + 1];
			rear--;
	}

	if (maze2[finish.x][finish.y] == 0)
	{
		cout << "\nThere is no path";
		return;
	}
	len = maze2[finish.x][finish.y] - 2;
	here = finish;

	for (j = len; j >= 0; j--)
	{
		path[j] = here;
		for (i = 0; i < 4; i++)
		{
			neighbour.x = here.x + offset[i].x;
			neighbour.y = here.y + offset[i].y;
			if (maze2[neighbour.x][neighbour.y] == maze2[here.x][here.y] - 1)
				break;
		}
		here = neighbour;
	}

	cout << "\nShortest path: \n";
	for (i = 0; i <= len; i++)
	{
		cout << path[i].x << " " << path[i].y << "\n";
		maze2[path[i].x][path[i].y] = -1;
		draw2 (start, finish, m, n, wall, move, beg, dest, block);
		window.display();
	}
}

int main()
{
	//Declaring required variables
	int m, n, i, j;
	Vector2i click, start, finish;

	//Entering maze dimensions and start and end
	cout << "Enter the maze dimensions: ";
	cin >> m >> n;
	cout << "Enter the starting location: ";
	cin >> start.x >> start.y;
	cout << "Enter the ending location: ";
	cin >> finish.x >> finish.y;

	//Creating border walls
	for (i = 0; i <= (m + 1); i++)
	{
		maze1[0][i] = 1;
		maze1[m + 1][i] = 1;
		maze2[0][i] = 1;
		maze2[m + 1][i] = 1;
	}
	for (i = 0; i <= (n + 1); i++)
	{
		maze1[i][0] = 1;
		maze1[i][n + 1] = 1;
		maze2[i][0] = 1;
		maze2[i][n + 1] = 1;
	}

	RectangleShape wall (Vector2f(50, 50)), move (Vector2f(50, 50)), beg (Vector2f(50, 50)), dest (Vector2f(50, 50)), block (Vector2f(50, 50));

	//Setting path texture
	move.setFillColor(Color::Transparent);
	move.setOutlineThickness(1);
	move.setOutlineColor(Color::White);
	move.setPosition(150, 150);
	block.setFillColor(Color::Yellow);

	//Setting wall texture
	Texture texture1, texture2, texture3;
	texture1.loadFromFile("F:\\Class\\DSA\\sfml-vscode-boilerplate-master\\src\\Wall2.jpg");
	wall.setTexture(&texture1);
	wall.setFillColor(Color::Red);
	texture2.loadFromFile("F:\\Class\\DSA\\sfml-vscode-boilerplate-master\\src\\start.png");
	beg.setTexture(&texture2);
	texture3.loadFromFile("F:\\Class\\DSA\\sfml-vscode-boilerplate-master\\src\\Cheese.png");
	dest.setTexture(&texture3);

	while (window.isOpen())
	{
		Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		window.clear();
		draw1 (start, finish, m, n, wall, move, beg, dest, block);

		//Finding which tile was clicked
		if(Mouse::isButtonPressed(Mouse::Left))
		{
			click = Mouse::getPosition(window);
			click.x -= 150;
			click.y -= 150;
			j = click.x / 50;
			i = click.y / 50;
			if ((i >= 0) && (j >= 0) && (i <= n) && (j <= m))
			{
				maze1[i][j] = 1;
				maze2[i][j] = 1;
			}
		}
		window.display();

		if(Keyboard::isKeyPressed(Keyboard::A))
		{
			find_path (start, finish, m, n, wall, move, beg, dest, block);
		}

		if(Keyboard::isKeyPressed(Keyboard::S))
		{
			shortest_path (start, finish, m, n, wall, move, beg, dest, block);
			Sleep(2000);
		}
	}
    return 0;
}