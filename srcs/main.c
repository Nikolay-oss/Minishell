#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h> // change to libft.h
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
// #include <termios.h>

#include "ft_parser.h"

void	ft_handler(int sig)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	char			*buf;
	// struct termios	term;

	buf = NULL;
	// free(buf);
	// tcgetattr(STDIN_FILENO, &term);
	// term.c_lflag &= ~(ISIG);
	// tcsetattr(STDIN_FILENO, TCSANOW, &term);
	
	// environment variables
	// int i = 0;
	// while (*(envp + i))
	// 	printf("%s\n", *(envp + i++));

	while (1)
	{
		signal(SIGINT, &ft_handler);
		buf = readline("prompt> ");
		if (!buf)
			break ;
		// printf("%s\n", buf);
		if (buf && !strcmp(buf, "exit"))
			break ;
		add_history(buf);
		ft_parser((const char *)buf);
		free(buf);
	}
	free(buf);
	clear_history();
	write(1, "exit\n", 5);
}


/*
"\4" - ^D
*/
/*
  export LDFLAGS="-L/Users/dkenchur/.brew/opt/readline/lib"
  export CPPFLAGS="-I/Users/dkenchur/.brew/opt/readline/include"
*/
