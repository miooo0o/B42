#standard
NAME		=	get_next_line.a
INCLUDE		=	-I../../include
SRCS_DIR	=	src/
OBJS_DIR	=	obj/
FT_PRINTF	=	../ft_printf/libftprintf.a

#executables
AR			=	ar rcs
RM			=	rm -f
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

###

GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m
BOLD = \033[1m
WHITE=\033[37m

###

#sources
SRC_FILES	=	get_next_line get_next_line_utils	

SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))
###

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C ../ft_printf
			cp $(FT_PRINTF) $(NAME)
			@$(AR) $(NAME) $(OBJS)
			@echo -n "	$(GREEN)$(BOLD)[get_next_line]$(RESET) $(BOLD)compiled!$(RESET)"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
			@mkdir -p $(@D)
			@echo -n "["
			@echo -n $$(expr $$(echo "$$(ls -1 $(OBJS_DIR) | wc -l) * 100 / $$(echo "$(SRC_FILES)" | wc -w)" | bc) / 1)
			@echo "%] $(GREEN)Building get next line $@$(RESET)"
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
			
clean:
			$(RM) -rf $(OBJS_DIR)
			@make clean -C ../ft_printf
			@echo "	$(BLUE)$(BOLD)[get_next_line]$(RESET) executable files cleaned!"

fclean:		clean
			$(RM) -f $(NAME)
			@$(RM) -f $(FT_PRINTF)
			@echo "	$(BLUE)$(BOLD)[get_next_line]$(RESET) executable files cleaned!"

re:			fclean all
			@echo "	$(GREEN)$(BOLD)[get_next_line]$(RESET) $(BOLD)cleaned and rebuilt everything$(RESET)"
.PHONY:		all clean fclean re
