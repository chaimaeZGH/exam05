#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int ac, char *av[])
{
	int i , j;
	if (ac != 4)
		return -1;
	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int it = atoi(av[3]);

	int data[2][2 + height][2 + width];
	for (int k = 0; k < 2 ; k++)
	{
		for (i = 0; i < height + 2 ; i++)
			for (j = 0; j < width + 2 ; j++)
				data[k][i][j] = 0;
	}
	int pen = 0;
	int x = 0 , y = 0;
	char c;
	while (read(0,&c , 1) > 0)
	{
		if (c == 'x') pen = !pen;
		else if (c == 's' && y < height) y++;
		else if (c == 'd' && x < width) x++;
		else if (c == 'w' && y > 1) y--;
		else if (c == 'a' && x > 1) x--;
		if (pen) data[0][y][x] = 1;
	}
	for (int its = 0 ; its < it ; its++)
	{
		for (i = 1; i < height -1; i++)
		{
			for (j = 1 ; j < width - 1; j++)
			{
				int nb = 0;
				for (x = -1 ; x <= 1 ; x++)
				{
					for (y = -1 ; y <= 1 ; y++)
					{
						if (!(x == 0 && y ==0))
							nb += data[its % 2][i + x][j + y];
					}
				}
				if (((data[its % 2][i][j] && (nb == 2 || nb == 3)) || (!data[its % 2][i][j] && nb == 3)))
					data[(its + 1) % 2][i][j] = 1;
				else
					data[(its + 1) % 2][i][j] = 0;
			}
		}
	}
	for (int j = 0; j < height; j++)
	{
		for (int i = 1 ; i < width; i++)
		{
			if (data[it % 2][j][i] == 1)
				putchar('O');
			else if (data[it % 2][j][i] == 0)
				putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}