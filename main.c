#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd = open("test.txt", O_RDONLY);
	char *str;
	int i = 0;
	while ((str = get_next_line(fd)) != NULL)
	{
		if (i == 2)
			fd = 100;
		printf("|%s|\n", str);
		free(str);
		i++;
	}
	printf("|%s|\n", str);

}