# Alias
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm
AR			= ar -rc

MAKEFLAGS	+= --silent
# -r : replace or add the specified files to the archive.
# -c : create archive without message. `ar: creating archive libft.a`
# -v : provide verbose output. `a` if the file is added and \
		`r` if the file replace a file already in the archive.

# standard
NAME		=	philo
INCLUDE		=	-I ./include/
SRCS_DIR	=	./src/
OBJS_DIR	=	./obj/
#LIBS_DIR	=	./lib/

# sources
SRCS		=	$(shell find $(SRCS_DIR) -name "*.c")
OBJS		=	$(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))
#LIBS		= 	$(shell find $(LIBS_DIR) -name "*.a")


# Main Command
all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
#			@$(foreach dir,$(LIB_DIR),make -C $(dir);)
			@#$(CC) $(CFLAGS) $(OBJS) $(LIB_PATH) -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
			@mkdir -p $(@D)
			@$(CC) $(INCLUDE) -c $< -o $@

clean:
			@$(RM) -rf $(OBJS_DIR)
#			@$(foreach dir,$(LIB_DIR),make clean -C $(dir);)

fclean:		clean
			@$(RM) -f $(NAME)
			@#$(RM) -f $(LIBS)

re:			fclean all

.PHONY:		all clean fclean re

dev:
			@$(CC) -g -o $(NAME) $(SRCS) $^ $(INCLUDE)