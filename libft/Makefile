# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfranco <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 11:53:58 by lfranco           #+#    #+#              #
#    Updated: 2024/08/27 16:10:52 by larissa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = 	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isalpha.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putnbr_fd.c\
	ft_putendl_fd.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_toupper.c\
	ft_tolower.c

SRCSBONUS = ft_lstnew_bonus.c\
	    ft_lstadd_front_bonus.c\
	    ft_lstsize_bonus.c \
	    ft_lstlast_bonus.c\
	    ft_lstadd_back_bonus.c\
	    ft_lstdelone_bonus.c\
	    ft_lstclear_bonus.c\
	    ft_lstiter_bonus.c\
	    ft_lstmap_bonus.c

OBJS = $(SRCS:.c=.o)

OBJSBONUS = $(SRCSBONUS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I . -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs libft.a $(OBJS)

bonus: $(NAME) $(OBJSBONUS)
	ar -rcs libft.a $(OBJSBONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJSBONUS)

fclean : clean
	rm -f $(NAME)
	rm -f $(OBJSBONUS)

re : fclean all

#so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
#	gcc -nostartfiles -shared -o libft.so $(OBJS)
.PHONY : all clean fclean re bonus
