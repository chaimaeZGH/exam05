#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {int y,x, size;}square;

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return i;
}

int min3(int a, int b , int c)
{
	int min = a;
	if(min > b)
		min = b;
	else if(min > c)
		min = c;
	return min;
}


int ft_map(FILE *f)
{
	int h = 0;
	char empty = 0, obs =0 , full = 0;
	if (fscanf(f, "%d %c %c %c\n",&h, &empty, &obs, &full) != 4)
		return (fprintf(stdout, "map error \n"), 1);
	if (empty == obs || empty == full || obs == full)
		return (fprintf(stdout, "map error \n"), 1);
	char **map = calloc(h, sizeof(char *));
	if (!map)
		return (fprintf(stdout, "map error \n"), 1);
	int w = 0;

	for(int i = 0 ; i < h ; i++)
	{
		char *line = NULL;
		size_t len = 0;

		if(getline(&line, &len, f) < 0)
			return (fprintf(stdout, "map error \n"), 1);
		int l = ft_strlen(line);
		if (l > 0 && line[l - 1] == '\n')
		       line[--l] = '\0';
		if (!w) w = l;
		else if (w != l)
			return (fprintf(stdout, "map error \n"), 1);
		map[i] = line;
	}

	if (f != stdin)
		fclose(f);
	square sq = {0,0,0};

	int **db = calloc(h + 1, sizeof(int *));
	if(!db)
		return (fprintf(stdout, "map error \n"), 1);
	for(int i = 0 ; i < h +1 ; i++)
	{
		db[i] = calloc(w + 1, sizeof(int));
	}

	for(int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if(map[i][j] == empty)
			{
				db[i + 1][j + 1] = 1 + min3(db[i][j + 1], db[i + 1][j], db[i][j]);
				if (sq.size < db[i+ 1][j + 1])
					sq = (square){i,j,db[i+1][j+1]};
			}
			else if (map[i][j] != obs)
				return (fprintf(stdout, "map error \n"), 1);
		}
	}

	for(int i = sq.y - sq.size + 1; i <= sq.y; i++)
	{
		printf("here\n");
		for(int j = sq.x - sq.size  + 1 ; j <= sq.x ; j++)
		{
			map[i][j] = full;
		}
	}

	for(int i = 0; i < h; i++)
	{
		fprintf(stdout, "%s\n", map[i]);
	}
	return 0;
}


void ft_file(char * filename)
{
	FILE *f = fopen(filename , "r");
	if (!f)
		return;
	ft_map(f);
}


int main (int ac , char **av)
{
	if (ac == 1)
		ft_map(stdin);
	else{
		for(int i = 1 ; i < ac ; i++)
		{
			ft_file(av[i]);
			if(i < ac -1)
				fprintf(stdout, "\n");
		}
	}
	return 0;
}