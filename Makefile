NAME	=	minishell

CC		= 	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -f

LIBRARY	=	./libft/

SRCS	=	./src/builtins/ft_cd.c\
			./src/builtins/ft_echo.c\
			./src/builtins/ft_env.c\
			./src/builtins/ft_exit.c\
			./src/builtins/ft_export.c\
			./src/builtins/ft_builtins.c\
			./src/builtins/ft_pwd.c\
			./src/builtins/ft_unset.c\
			./src/cleanup/cleanup_cmd.c\
			./src/cleanup/cleanup_env.c\
			./src/cleanup/cleanup_fd.c\
			./src/cleanup/cleanup_shell.c\
			./src/data/ft_allocutils.c\
			./src/data/ft_cmdutils.c\
			./src/data/ft_fdutils.c\
			./src/data/ft_getenvp.c\
			./src/data/ft_pidutils.c\
			./src/data/ft_shellutils.c\
			./src/data/ft_strutils.c\
			./src/env/ft_arr_cpy.c\
			./src/env/ft_arr_free.c\
			./src/env/ft_arr_size.c\
			./src/env/ft_arr_srch.c\
			./src/env/ft_atolli.c\
			./src/env/ft_find_env.c\
			./src/env/ft_init_env.c\
			./src/executor/ft_executer.c\
			./src/executor/ft_executorutils.c\
			./src/executor/ft_getpathname.c\
			./src/expansion/ft_expansion.c\
			./src/expansion/ft_expnd_dquote.c\
			./src/expansion/ft_expnd_env.c\
			./src/expansion/ft_expnd_squote.c\
			./src/expansion/ft_expnd_txt.c\
			./src/expansion/ft_isolate.c\
			./src/expansion/ft_unify.c\
			./src/lexer/ft_lexer.c\
			./src/main/main.c\
			./src/main/ft_check_space.c\
			./src/main/ft_error_utils.c\
			./src/main/ft_set_prompt.c\
			./src/main/ft_start_shel.c\
			./src/parser/ft_parser.c\
			./src/parser/ft_heredoc.c\
			./src/parser/ft_mountarg.c\
			./src/parser/ft_prompt_split.c\
			./src/parser/ft_setredir.c\
			./src/parser/ft_skipquote.c\
			./src/signals/ft_signal_handler.c\
			./src/signals/ft_signal.c\
		
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