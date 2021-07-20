# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkenchur <dkenchur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 00:19:11 by dkenchur          #+#    #+#              #
#    Updated: 2021/07/20 22:19:59 by dkenchur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

ANALYZ_DIR	= $(PARSER_DIR)analyzer/

SHELL_DIR	= $(SRCS_DIR)shell/

SIG_DIR		= $(SRCS_DIR)signals/

OBJ_DIR		= objs/

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
			  $(REDIR_DIR)redir2_input.c			$(SHELL_DIR)file_exists.c \
			  $(ERROR_DIR)error_msgs.c				$(EXEC_DIR)save_path_to_bin.c \
			  $(ANALYZ_DIR)syn_analyzer.c			$(BUILTINS_DIR)ft_export_utils.c \
			  $(PARSER_DIR)var_parser.c				$(ERROR_DIR)errors_handlers.c \
			  $(SHELL_DIR)shell_handler.c			$(SHELL_DIR)ft_pipes.c \
			  $(REDIR_DIR)heredocs_handler.c		$(SHELL_DIR)init_shell.c \
			  $(SHELL_DIR)destroy_shell.c			$(REDIR_DIR)launch_dual_redir.c \
			  $(SIG_DIR)ft_signals.c				$(BUILTINS_DIR)unset_tools.c \

CFLAGS		= #-Wall -Wextra -Werror

#  INCLUDES	= -I includes/ # ubuntu
INCLUDES	= -I includes/ -I /Users/$(USER)/.brew/opt/readline/include # macOS

#  LIBS		= -lreadline -Llibft -lft # ubuntu
LIBS		= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -Llibft -lft # macOS

OBJS		= $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS)) 

$(OBJ_DIR)%.o:	$(SRCS_DIR)%.c $(INCLUDES)
	$(CC) -g $(CFLAGS) $(INCLUDES) -c $< -o $@

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
	@mkdir -p $(OBJ_DIR)parser/analyzer/
	@mkdir -p $(OBJ_DIR)shell/
	@mkdir -p $(OBJ_DIR)signals/

clean:
	rm -rf $(OBJS)
	make -C libft/ clean

fclean:	clean
	make -C libft/ fclean
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)

re:	fclean all