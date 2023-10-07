
# Alias
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm
AR			= ar -rc
# -r : replace or add the specified files to the archive.
# -c : create archive without message. `ar: creating archive libft.a`
# -v : provide verbose output. `a` if the file is added and \
		`r` if the file replace a file already in the archive.

NAME		= libft.a
INCLUDE		= ./include

SRC 		= $(shell find ./src -iname "*.c")
OBJ 		= $(SRC_NAME:.c=.o)


# Main Command
all: $(NAME)

%.o: %.c
		@$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

$(NAME): $(OBJ)
		@$(AR) $@ $^

clean:
		@$(RM) -f $(OBJ)

fclean: clean
		@$(RM) -f $(NAME)

re: fclean all
