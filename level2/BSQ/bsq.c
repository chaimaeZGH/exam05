// #include "bsq.h"

// void	destructor(char** map, int size) {
// 	while (size && (free(*(map + --size)), 1));
// 	free(map);
// }

// int	parsing(FILE* stream, meta* info) {
// 	if (fscanf(stream, "%d%c%c%c%c\n", &info->height, &info->empty, &info->obstacle, &info->full, (char*)&info->width) != 5
// 		|| info->width != 10 || info->height == 0 || info->empty == 0 || info->obstacle == 0 || info->full == 0
// 		|| info->empty == info->obstacle || info->empty == info->full || info->obstacle == info->full)
// 		printf("Error: invssalid map\n");
// 	else errno = EXIT_SUCCESS;
// 	return (errno);
// }

// int	storing(FILE* stream, bsq* data) {
// 	data->map = malloc(8 * data->info.height);
// 	if (data->map) {
// 		for (int i = 0; i < data->info.height + 1; i++) {
// 			char*	line = NULL;
// 			size_t	len = 0;
// 			ssize_t	read = getline(&line, &len, stream);
// 			if (errno) {
// 				printf("Error: failure memory allocation\n");
// 				destructor(data->map, i);
// 				break ;
// 			}
// 			if (read == -1) {
// 				if (i == data->info.height) break ;
// 				printf("Error: invalid map\n");
// 				destructor(data->map, i);
// 				errno = EXIT_FAILURE;
// 				break ;
// 			}
// 			if (line[read - 1] == '\n') line[read - 1] = 0;
// 			len = 0;
// 			while (*(line + len) && ++len);
// 			if ((i && (int)len != data->info.width) || !len) errno = EXIT_FAILURE;
// 			else data->info.width = len;
// 			data->map[i] = line;
// 			while (!errno && *line) {
// 				if (*line != data->info.empty && *line != data->info.obstacle) errno = EXIT_FAILURE;
// 				++line;
// 			}
// 			if (errno) {
// 				destructor(data->map, i + 1);
// 				printf("Error: invalid mp");
// 				break ;
// 			}
// 		}
// 	}
// 	else printf("Error: failure memory allocation\n");
// 	return (errno);
// }

// int	minimoon(int a, int b, int c) {
// 	if (!a || !b || !c) a = 0;
// 	else {
// 		if (a > b) a = b;
// 		if (a > c) a = c;
// 	}
// 	return (a + 1);
// }

// void	selectSquire(bsq data) {
// 	for (int i = 0; i < data.info.height; i++) {
// 		for (int j = 0; j < data.info.width; j++) {
// 			if (data.solve.db[i][j] == 1)
// 			{
// 				if (i != 0 && j != 0)
// 					data.solve.db[i][j] = minimoon(data.solve.db[i - 1][j], data.solve.db[i - 1][j - 1], data.solve.db[i][j - 1]);
// 				if (data.solve.size < data.solve.db[i][j]) {
// 					data.solve.size = data.solve.db[i][j];
// 					data.solve.i = i - data.solve.size + 1;
// 					data.solve.j = j - data.solve.size + 1;
// 				}
// 			}
// 		}
// 	}

// 	for (int i = data.solve.i; i < data.solve.i + data.solve.size; i++) {
// 		for (int j = data.solve.j; j < data.solve.j + data.solve.size; j++)
// 			data.map[i][j] = data.info.full;
// 	}

// 	for (int i = 0; i < data.info.height; i++) printf("%s\n", data.map[i]);
// }

// int	duplicate(bsq* data) {
// 	data->solve.db = malloc(8 * data->info.height);
// 	if (data->solve.db) {
// 		for (int i = 0; i < data->info.height; i++) {
// 			data->solve.db[i] = malloc(4 * data->info.width);
// 			if (!data->solve.db[i]) {
// 				destructor((char**)data->solve.db, i);
// 				printf("Error: failure memory allocation\n");
// 				errno = EXIT_FAILURE;
// 				break ;
// 			}

// 			for (int j = 0; j < data->info.width; j++) {
// 				if (data->map[i][j] == data->info.obstacle) data->solve.db[i][j] = 0;
// 				else data->solve.db[i][j] = 1;
// 			}
// 		}
// 	}
// 	else printf("Error: failure memory allocation\n");

// 	return (errno);
// }

// void	 biggest_square(FILE* stream) {
// 	bsq	data = {0};

// 	if (parsing(stream, &data.info) || storing(stream, &data)) return ;
// 	if (!duplicate(&data)) {
// 		selectSquire(data);
// 		destructor((char**)data.solve.db, data.info.height);
// 	}
// 	destructor(data.map, data.info.height);
// }

// int main(int argc, char** argv) {
// 	errno = EXIT_FAILURE;

// 	if (argc == 1) biggest_square(stdin);
// 	else if (argc == 2) {
// 		FILE*	stream = fopen(*(++argv), "r");
// 		if (stream) {
// 			biggest_square(stream);
// 			fclose(stream);
// 		}
// 		else printf("Error: cannot open file %s\n", *argv);
// 	}
// 	else printf("Error: too many arguments\n");

// 	return (errno);
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

typedef struct {
	int height;
	int width;
	char empty;
	char obstacle;
	char full;
} meta;

typedef struct {
	meta info;
	char **map;
	struct {
		int **db;
		int size;
		int i;
		int j;
	} solve;
} bsq;

void destructor(char** map, int size)
{
	if (!map) return;
	for (int i = 0; i < size; i++) free(map[i]);
	free(map);
}

int parsing(FILE* stream, meta* info) {
	// On lit : Nombre, Vide, Obstacle, Plein.
	// %d s'arrête dès qu'il voit un caractère non-numérique.
	if (fscanf(stream, "%d%c%c%c", &info->height, &info->empty, &info->obstacle, &info->full) != 4)
		return (1);

	// On consomme le \n après la définition
	fgetc(stream);

	if (info->height <= 0 || info->empty == info->obstacle ||
		info->empty == info->full || info->obstacle == info->full)
		return (1);
	return (0);
}

int storing(FILE* stream, bsq* data) {
	data->map = malloc(sizeof(char*) * data->info.height);
	if (!data->map) return (1);

	for (int i = 0; i < data->info.height; i++) {
		char* line = NULL;
		size_t len = 0;
		ssize_t read = getline(&line, &len, stream);

		if (read <= 0) {
			destructor(data->map, i);
			return (1);
		}

		if (line[read - 1] == '\n') line[--read] = '\0';

		// Définir la largeur à partir de la première ligne
		if (i == 0) data->info.width = (int)read;
		else if ((int)read != data->info.width) {
			free(line);
			destructor(data->map, i);
			return (1);
		}

		// Vérification des caractères autorisés
		for (int j = 0; j < (int)read; j++) {
			if (line[j] != data->info.empty && line[j] != data->info.obstacle) {
				free(line);
				destructor(data->map, i);
				return (1);
			}
		}
		data->map[i] = line;
	}
	return (0);
}

int minimoon(int a, int b, int c) {
	int min = a;
	if (b < min) min = b;
	if (c < min) min = c;
	return (min + 1);
}



void solve_bsq(bsq *data) {
	// Allocation de la table de score (DP table)
	data->solve.db = malloc(sizeof(int*) * data->info.height);
	data->solve.size = 0;
	data->solve.i = 0;
	data->solve.j = 0;

	for (int i = 0; i < data->info.height; i++) {
		data->solve.db[i] = malloc(sizeof(int) * data->info.width);
		for (int j = 0; j < data->info.width; j++) {
			if (data->map[i][j] == data->info.obstacle) {
				data->solve.db[i][j] = 0;
			} else {
				if (i == 0 || j == 0) data->solve.db[i][j] = 1;
				else data->solve.db[i][j] = minimoon(data->solve.db[i-1][j],
													 data->solve.db[i][j-1],
						0							 data->solve.db[i-1][j-1]);

				// On met à jour le max seulement si strictement supérieur
				// pour garder le plus "en haut à gauche"
				if (data->solve.db[i][j] > data->solve.size) {
					data->solve.size = data->solve.db[i][j];
					data->solve.i = i;
					data->solve.j = j;
				}
			}
		}
	}

	// Dessiner le carré plein
	for (int y = data->solve.i - data->solve.size + 1; y <= data->solve.i; y++) {
		for (int x = data->solve.j - data->solve.size + 1; x <= data->solve.j; x++) {
			data->map[y][x] = data->info.full;
		}
	}

	// Affichage
	for (int i = 0; i < data->info.height; i++) {
		printf("%s\n", data->map[i]);
		free(data->solve.db[i]);
	}
	free(data->solve.db);
}

void biggest_square(FILE* stream) {
	bsq data = {0};

	if (parsing(stream, &data.info) || storing(stream, &data)) {
		fprintf(stderr, "map error\n");
		return;
	}
	solve_bsq(&data);
	destructor(data.map, data.info.height);
}

int main(int argc, char** argv) {
	if (argc == 1) {
		biggest_square(stdin);
	} else {
		for (int i = 1; i < argc; i++) {
			FILE* stream = fopen(argv[i], "r");
			if (stream) {
				biggest_square(stream);
				fclose(stream);
			} else {
				fprintf(stderr, "map error\n");
			}
		}
	}
	return (0);
}