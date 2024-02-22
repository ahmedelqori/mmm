NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
RM = rm -rf

SRC = ./src/minishell.c\
	  ./src/buildin/env/ft_env.c\
	  ./src/prompt/prompt.c\
	  ./src/signals/signals.c\
	  ./src/struct/env/env_list.c\
	  ./src/parsing/ft_add_space_to_pipe.c\
	  ./src/parsing/ft_add_space_to_input.c\
	  ./src/parsing/ft_add_space_to_output.c\
	  ./src/parsing/ft_parsing.c\
	  ./src/struct/list/list_pipe.c\
	  ./src/struct/tree/tree.c\
	  ./src/execute/ft_execute.c\

	#   ./src/parsing/ft_handle_redirection.c\
	#   ./src/buildin/pwd/ft_pwd.c\
	#   ./src/buildin/cd/ft_cd.c\
	#   ./src/buildin/export/ft_export.c\
	#   ./src/struct/tree/tree.c\
	#   ./src/struct/list/list.c\
	#   ./src/struct/node/node.c\


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) ./libft/libft.a -o $(NAME) -lreadline

clean:
	$(RM) $(OBJ)
fclean:clean
	$(RM) $(NAME)
re: fclean all
