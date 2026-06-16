#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int height;
	int width;
	char empty;
	char obstacle;
	char full;
} meta;

typedef struct
{
	meta info;
	char **map;

	struct
	{
		int size;
		int i;
		int j;
		int **db;
	} solve;

} bsq;

int parsing(FILE * stream, meta *info)
{
	if (fscanf(stream,"%d%c%c%c%c",&info->height,&info->empty,&info->obstacle,&info->full,(char *)&info->width) != 5 ||
		info->empty == 0 || info->full == 0 || info->height ==0 || info->obstacle == 0 || info->width != 10
		|| info->empty == info->full || info->empty == info->obstacle || info->obstacle == info->full)
			return 1;
	return 0;
}

void free_map(char **map, int size)
{
	if (!map)
		return;
	for (int i = 0; i < size ; i++)
		free(map[i]);
	free(map);
}

int storing(FILE *stream, bsq *data)
{
	data->map = malloc(sizeof(char *) * data->info.height);
	if (!data->map)
		return 1;

	for (int i = 0; i < data->info.height ; i++)
	{
		char *line = NULL;
		size_t read = 0;
		size_t len = 0;
		read = getline(&line,&len,stream);
		if (read <= 0)
			return 1;

		if (line[read - 1] == '\n')
		{
			line[read -1] = '\0';
			read--;
		}

		if (i == 0)
			data->info.width = (int)read;
		else if ((int)read != data->info.width)
		{
			free_map(data->map, i);
			free(line);
			return (1);
		}

		for (int j = 0; j < data->info.width ; j++)
		{
			if (line[j] != data->info.empty && line[j] != data->info.obstacle)
			{
				free_map(data->map,i);
				free(line);
				return 1;
			}
		}
		data->map[i] = line;
	}
	return (0);
}

int mini(int a, int b, int c)
{
	int min = a;
	if (min > b)
		min = b;
	if (min > c)
		min = c;
	return (min + 1);
}

void ft_solve(bsq *data)
{
	data->solve.db = malloc(sizeof(int *) * data->info.height);
	if (!data->solve.db)
		return ;
	data->solve.size = 0;
	data->solve.i = 0;
	data->solve.j = 0;
	for (int i = 0; i < data->info.height ; i++)
	{
		data->solve.db[i] = malloc(sizeof(int) * data->info.width);
		if (!data->solve.db[i])
			return;
		for (int j = 0 ; j < data->info.width ; j++)
		{
			if (data->map[i][j] == data->info.obstacle)
				data->solve.db[i][j] = 0;
			else if (i == 0 || j == 0)
				data->solve.db[i][j] = 1;
			else
				data->solve.db[i][j] = mini(data->solve.db[i][j-1],data->solve.db[i-1][j-1],data->solve.db[i - 1][j]);

			if (data->solve.db[i][j] > data->solve.size)
			{
				data->solve.size = data->solve.db[i][j];
				data->solve.i = i;
				data->solve.j = j;
			}

		}
	}
	if (data->solve.size > 0)
	{
		for (int i = data->solve.i - data->solve.size + 1; i <= data->solve.i ; i++)
		{
			for (int j = data->solve.j - data->solve.size + 1 ; j <= data->solve.j ; j++)
			{
				data->map[i][j] = data->info.full;
			}
		}
	}
	for (int i = 0 ; i < data->info.height ; i++)
	{
		printf("%s\n",data->map[i]);
		free(data->solve.db[i]);
	}
	free(data->solve.db);
}

void	ft_bsq(FILE *stream)
{
	bsq data = {0};
	if (parsing(stream, &data.info) || storing(stream, &data))
	{
		printf("map error\n");
		return ;
	}
	ft_solve(&data);
	free_map(data.map,data.info.height);
}

int main(int ac, char *av[])
{
	if (ac == 1)
		ft_bsq(stdin);
	else
	{
		for (int i = 1; i < ac ; i++)
		{
			FILE *stream = fopen(av[i], "r");
			if (stream)
			{
				ft_bsq(stream);
				fclose(stream);
			}
			else
				printf("error map");
		}
	}
	return (0);
}