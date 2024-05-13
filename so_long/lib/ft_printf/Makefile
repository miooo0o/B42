# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 19:22:56 by minakim           #+#    #+#              #
#    Updated: 2023/04/20 00:07:07 by mi■■■■■          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#standard
NAME		=	libftprintf.a
INCLUDE		=	-I../../include
SRCS_DIR	=	src/
OBJS_DIR	=	obj/
LIBFT		=	../libft/libft.a

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
SRC_FILES	=	ft_printf ft_printf_arg ft_utoa ft_get_nbr ft_put_n_char \
 				ft_put_char	ft_put_str ft_put_int ft_put_uint \
 				ft_put_hex_up ft_put_hex_low ft_put_ptr

SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

###


all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C ../libft
			cp $(LIBFT) $(NAME)
			@$(AR) $(NAME) $(OBJS)
			@echo "	$(GREEN)$(BOLD)[ft_print]$(RESET) $(BOLD)compiled!$(RESET)"
	
$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
			@mkdir -p $(@D)
			@echo -n "["
			@echo -n $$(expr $$(echo "$$(ls -1 $(OBJS_DIR) | wc -l) * 100 / $$(echo "$(SRC_FILES)" | wc -w)" | bc) / 1)
			@echo "%] $(GREEN)Building ft_print $@$(RESET)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean:
			$(RM) -rf $(OBJS_DIR)
			@make clean -C ../libft
			@echo "	$(BLUE)$(BOLD)[ft_printf]$(RESET) objects files cleaned!"

fclean:		clean
			$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)
			@echo "	$(BLUE)$(BOLD)[ft_printf]$(RESET) executable files cleaned!"

re:			fclean all
			@echo "	$(GREEN)$(BOLD)[ft_printf]$(RESET) $(BOLD)cleaned and rebuilt everything$(RESET)"

.PHONY:		all clean fclean re
