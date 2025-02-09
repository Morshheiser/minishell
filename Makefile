NAME	=	minishell

CC		= 	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -f

LIBRARY	=	./libft/

SRCS	=	./src/builtins/cmd_builtin/cd.c\
			./src/builtins/cmd_builtin/echo.c\
			./src/builtins/cmd_builtin/env.c\
			./src/builtins/cmd_builtin/exit.c\
			./src/builtins/cmd_builtin/export.c\
			./src/builtins/ft_builtin.c\
			./src/builtins/cmd_builtin/pwd.c\
			./src/builtins/cmd_builtin/unset.c\
			./src/env/utils_env_1.c\
			./src/env/utils_env_2.c\
			./src/env/utils_env_3.c\
			./src/executer/ft_executer.c\
			./src/executer/utils_exec.c\
			./src/expansion/ft_expansion.c\
			./src/expansion/utils_expansion/utils_expan_1.c\
			./src/expansion/utils_expansion/utils_expan_2.c\
			./src/expansion/utils_expansion/utils_expan_3.c\
			./src/lexer/ft_check_lexer.c\
			./src/lexer/lexer.c\
			./src/main/main.c\
			./src/main/utils_main_1.c\
			./src/main/utils_main_2.c\
			./src/main/utils_main_3.c\
			./src/main/utils_main_4.c\
			./src/parser/ft_parser.c\
			./src/parser/utils_parser_1.c\
			./src/parser/utils_parser_2.c\
			./src/utils/utils_1.c\
			./src/utils/utils_2.c\
			./src/utils/utils_3.c\
			./src/utils/utils_split_pipe_1.c\
			./src/utils/utils_split_pipe_2.c\

all: $(NAME)

libft:
	cd $(LIBRARY) && $(MAKE) && cp -v libft.a ../

minishell: libft
	cc -g $(SRCS) libft.a -lreadline -o $(NAME)

run: re
	./$(NAME)

val: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supressions.supp --track-fds=yes ./$(NAME)

norm:
	@-norminette -R CheckForbiddenSourceHeader

clean:
	cd $(LIBRARY) && $(MAKE) clean

fclean:	clean
	$(RM) $(NAME)
	$(RM) libft.a
	cd $(LIBRARY) && $(MAKE) fclean

re:	fclean all

.PHONY:	all clean fclean re libft