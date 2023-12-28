#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int generateRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int main()
{
	char	**map;
	int		i;
	int		j;
	int		x;
	int		y;
	int		rand;
	int		rand1;
	int		rand2;

    srand((unsigned int)time(NULL));
    int min = 3;
    int max = 30;

	int	fd = open("rand_map.ber", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (1);

    x = generateRandomNumber(min, max);
    y = generateRandomNumber(min, max);
    map = (char **)calloc(sizeof(char *), y + 1);
	i = 0;
	while (i < y)
	{
		map[i] = (char *)calloc(sizeof(char), x + 1);
		i++;
	}
	i = 0;
	while (i < y - 1)
	{
		j = 0;
		while (j < x - 1)
			map[i][j++] = '0';
		i++;
	}
	i = 0;
	while (i < y - 1)
	{
		map[i][0] = '1';
		map[i][x - 1] = '1';
		i++;
	}
	i = 0;
	while (i < x)
	{
		map[0][i] = '1';
		map[y - 1][i] = '1';
		i++;
	}
	rand1 = generateRandomNumber(1, y - 2);
	rand2 = generateRandomNumber(1, x - 2);
	map[rand1][rand2] = 'P';
	rand1 = generateRandomNumber(1, y - 2);
	rand2 = generateRandomNumber(1, x - 2);
	map[rand1][rand2] = 'E';

	rand = generateRandomNumber(x / 2, x);
	i = 0;
	while (i < rand)
	{
		rand1 = generateRandomNumber(1, y - 2);
		rand2 = generateRandomNumber(1, x - 2);
		if (map[rand1][rand2] != 'E' || map[rand1][rand2] != 'P')
			map[rand1][rand2] = 'C';
		i++;
	}
	rand = generateRandomNumber(x * 2, x * 4);
	i = 0;
	while (i < rand)
	{
		rand1 = generateRandomNumber(1, y - 2);
		rand2 = generateRandomNumber(1, x - 2);
		if (map[rand1][rand2] != 'E' || map[rand1][rand2] != 'P' || map[rand1][rand2] != 'C')
			map[rand1][rand2] = '1';
		i++;
	}
	i = 0;
	while (i < y)
	{
		write(fd, map[i], strlen(map[i]));
		write(fd, "\n", 1);
		i++;
	}
	i = 0;
	while (i < y)
		free(map[i++]);
	free(map);
	close(fd);
    return 0;
}