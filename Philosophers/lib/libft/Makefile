# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 19:22:56 by minakim           #+#    #+#              #
#    Updated: 2023/04/30 18:06:37 by mi■■■■■          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#standard
NAME		=	libft.a
INCLUDE		=	-I../include
SRCS_DIR	=	src/
OBJS_DIR	=	obj/

#executables
AR			=	ar rcs
RM			=	rm -f
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

###

###

#sources
SRC_FILES	=	$(MAIN) $(EXTRA)

MAIN		=	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
				ft_toupper ft_tolower ft_atoi ft_itoa ft_split \
				ft_strlen ft_strnstr ft_strdup ft_strlcpy ft_strlcat \
				ft_strnstr ft_strchr ft_strrchr ft_strncmp ft_substr \
				ft_strjoin ft_strtrim ft_strmapi ft_striteri \
				ft_memset ft_bzero ft_memcpy ft_memmove ft_memchr ft_memcmp ft_calloc \
				ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
				ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
				ft_lstdelone ft_lstclear ft_lstiter ft_lstmap
EXTRA		=	ft_strcpy ft_ilen ft_putnbr_base


SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

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