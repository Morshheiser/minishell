# Name of the executable
NAME = minishell

# Compiler
CC = cc

# Compilation flags
CFLAGS = -Wall -Wextra -Werror -g

# Source and object files
SOURCES = main.c/

OBJECTS = $(SOURCES:.c=.o)

# Removal command
RM = rm -rf

# Compilation rules
all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

# Rule to convert .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJECTS)

# Full clean, including the executable
fclean: clean
	$(RM) $(NAME)

# Rebuild everything from scratch
re: fclean all
