CC			= gcc

NAME		= minishell

SRCS_DIR	= srcs/

EXEC_DIR	= $(SRCS_DIR)execute/

PARSER_DIR	= $(SRCS_DIR)parser/

BUILTINS_DIR	= $(SRCS_DIR)builtins/

CMDLST_DIR	= $(SRCS_DIR)commands_list/

HNDRS_DIR	= $(PARSER_DIR)handlers/

REDIR_DIR	= $(SRCS_DIR)redirects/

ERROR_DIR	= $(SRCS_DIR)errors_handler/

OBJ_DIR		= objs/

INCLUDES	= includes/

SRCS		= $(SRCS_DIR)main.c						$(PARSER_DIR)ft_parser.c \
			  $(PARSER_DIR)select_command.c			$(BUILTINS_DIR)ft_echo.c \
			  $(BUILTINS_DIR)ft_env.c				$(BUILTINS_DIR)ft_cd.c \
			  $(BUILTINS_DIR)ft_export.c			$(BUILTINS_DIR)ft_pwd.c \
			  $(REDIR_DIR)redir_handler.c			$(BUILTINS_DIR)ft_unset.c\
			  $(EXEC_DIR)ft_exec.c					$(BUILTINS_DIR)ft_exit.c\
			  $(PARSER_DIR)utils.c					$(PARSER_DIR)search_tokens.c \
			  $(PARSER_DIR)check_tokens.c			$(HNDRS_DIR)vars_handler.c \
			  $(HNDRS_DIR)vars_handler_utils.c		$(HNDRS_DIR)args_handler.c \
			  $(HNDRS_DIR)commands_handler.c		$(CMDLST_DIR)add_to_command_list.c \
			  $(CMDLST_DIR)destroy_command_list.c	$(REDIR_DIR)stdstreams_handler.c \
			  $(REDIR_DIR)redir2_input.c			$(SRCS_DIR)file_exists.c \
			  $(ERROR_DIR)errors_handler.c			$(EXEC_DIR)save_path_to_bin.c

CFLAGS		= #-Wall -Wextra -Werror

LIBS		= -lreadline -Llibft -lft # ubuntu
#LIBS		= -L/Users/brice/.brew/opt/readline/lib -lreadline -Llibft -lft
# LIBS		= -L/Users/dkenchur/.brew/opt/readline/lib -lreadline -Llibft -lft

#OBJS		= $(SRCS:.c=.o)
OBJS		= $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS)) 

$(OBJ_DIR)%.o:	$(SRCS_DIR)%.c
	#$(CC) $(CFLAGS) -I $(INCLUDES) -I/Users/brice/.brew/opt/readline/include -c $< -o $@
	$(CC) -g $(CFLAGS) -I $(INCLUDES) -c $< -o $@
	# $(CC) -g $(CFLAGS) -I $(INCLUDES) -I/Users/dkenchur/.brew/opt/readline/include -c $< -o $@

$(NAME):	$(OBJ_DIR) $(OBJS)
	make -C libft/
	$(CC) -g -o $(NAME) $(CFLAGS) $(OBJS) $(LIBS)

all:		$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)parser
	@mkdir -p $(OBJ_DIR)builtins
	@mkdir -p $(OBJ_DIR)commands_list
	@mkdir -p $(OBJ_DIR)parser/handlers
	@mkdir -p $(OBJ_DIR)redirects
	@mkdir -p $(OBJ_DIR)errors_handler
	@mkdir -p $(OBJ_DIR)execute/

clean:
	rm -rf $(OBJS)
	make -C libft/ clean

fclean:	clean
	make -C libft/ fclean
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)

re:	fclean all