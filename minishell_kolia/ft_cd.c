//
// Created by galads on 12.06.2021.
//
//#include <sys/dir.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "builts.h"

void	ft_cd(char *path)
{
	int	res;

	res = chdir(path);
	if(res < 0)
		printf("Error: %s\n", strerror(errno));
	else
		printf("Error: %s\n", strerror(errno));
}
