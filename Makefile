CC			= gcc

NAME		= minishell

SRCS_DIR	= srcs/

PARSER_DIR	= $(SRCS_DIR)parser/

BUILTINS_DIR	= $(SRCS_DIR)builtins/

OBJ_DIR		= objs/

INCLUDES	= includes/

SRCS		= $(SRCS_DIR)main.c					$(PARSER_DIR)ft_parser.c \
			  $(PARSER_DIR)select_command.c		$(BUILTINS_DIR)ft_echo.c \
			  $(BUILTINS_DIR)ft_env.c			$(BUILTINS_DIR)ft_cd.c \
			  $(BUILTINS_DIR)ft_export.c		$(BUILTINS_DIR)ft_pwd.c \
			  $(SRCS_DIR)redir.c				$(BUILTINS_DIR)ft_unset.c\
			  $(SRCS_DIR)ft_exec.c

CFLAGS		= #-Wall -Wextra -Werror

LIBS		= -lreadline -Llibft -lft # ubuntu

#OBJS		= $(SRCS:.c=.o)
OBJS		= $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS)) 

$(OBJ_DIR)%.o:	$(SRCS_DIR)%.c
	$(CC) -g $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJ_DIR) $(OBJS)
	make -C libft/
	$(CC) -g -o $(NAME) $(CFLAGS) $(OBJS) $(LIBS)

all:		$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)parser
	@mkdir -p $(OBJ_DIR)builtins

clean:
	rm -rf $(OBJS)
	make -C libft/ clean

fclean:	clean
	make -C libft/ fclean
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)

re:	fclean all