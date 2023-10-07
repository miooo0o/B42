
# Alias
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm
AR			= ar -rc
# -r : replace or add the specified files to the archive.
# -c : create archive without message. `ar: creating archive libft.a`
# -v : provide verbose output. `a` if the file is added and \
		`r` if the file replace a file already in the archive.

# standard
NAME		=	libft.a
INCLUDE		=	-I ./include
SRCS_DIR	=	./src/
OBJS_DIR	=	./obj/

# sources
SRCS		=	$(shell find $(SRCS_DIR) -name "*.c")
OBJS		=	$(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

###

all:		$(NAME)

$(NAME):	$(OBJS)
			@mkdir -p $(@D)
			@$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@$(RM) -rf $(OBJS_DIR)

fclean:		clean
			@$(RM) -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re