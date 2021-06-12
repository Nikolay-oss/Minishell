CC			= gcc

NAME		= minishell

SRCS_DIR	= srcs/

PARSER_DIR	= $(SRCS_DIR)parser/

OBJ_DIR		= objs/

INCLUDES	= includes/

SRCS		= $(SRCS_DIR)main.c					$(PARSER_DIR)ft_parser.c \
			  $(PARSER_DIR)select_command.c

CFLAGS		= #-Wall -Wextra -Werror

LIBS		= -lreadline -Llibft -lft # ubuntu

#OBJS		= $(SRCS:.c=.o)
OBJS		= $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS)) 

$(OBJ_DIR)%.o:	$(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJ_DIR) $(OBJS)
	make -C libft/
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBS)

all:		$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser

clean:
	rm -rf $(OBJS)
	make -C libft/ clean

fclean:	clean
	make -C libft/ fclean
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)

re:	fclean all