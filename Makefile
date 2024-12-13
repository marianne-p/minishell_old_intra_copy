# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpihur <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 15:17:25 by mpihur            #+#    #+#              #
#    Updated: 2024/07/18 18:01:22 by mpihur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
SRC	:= raw_mode.c ft_split.c ft_split_verify.c ft_split_envv.c signal.c \
	   ft_utils.c ft_utils_2.c main.c exit.c exit_free.c parser.c parsed_set.c \
	   cmd_create.c cmd_crt_builtin.c pipe_create.c redir_create.c syntax_tree.c \
	   syntax_tree_extra.c execute.c execute_extra.c exec_builtin.c cmd_redir_handler.c \
	   echo_pwd.c export_no_arg.c export_unset.c env.c ft_env.c protection.c \
	   check_redir_cmd.c 
OBJ	:= $(SRC:.c=.o)
M_SRC	:= export_no_arg.c
M_OBJ	:= $(M_SRC:.c=.o)
LIBFT	:= ./Libft/libft.a
LIB	:= -lreadline -I./Libft -L./Libft -lft

%.o: %.c
	cc -Wall -Wextra -Werror -g -c $< -o $@ 

$(NAME): $(OBJ) $(LIBFT)
	cc -Wall -Wextra -Werror -g $^ -o $@ $(LIB) 

$(LIBFT):
	make -C ./Libft

mari:	$(M_OBJ) $(LIBFT)
	cc -Wall -Wextra -Werror $(M_OBJ) -o mari $(LIB) 

clean:
	rm -rf $(OBJ)
	rm -rf $(M_OBJ)
	make -C ./Libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./Libft fclean

all:	$(LIBFT) $(OBJ) $(NAME)

re:	fclean all

.PHONY:  clean fclean re all
