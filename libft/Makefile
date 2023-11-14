# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/11/14 10:24:26 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
I			=	./ ft_printf/
D			=	_build/dep/
O			=	_build/obj/

SRC			=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_tolower.c \
				ft_toupper.c \
				\
				ft_itoa.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strmapi.c \
				ft_strtrim.c \
				ft_substr.c \
				\
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				\
				ft_atof.c \
				ft_isspace.c \
				ft_strcmp.c \
				ft_strmatches_any.c \
				\
				ft_printf/ft_printf.c \
				ft_printf/ft_putnbr_base_fd.c \
				ft_printf/ft_putnchar_fd.c \
				ft_printf/ft_putnstr_fd.c \
				ft_printf/print_char.c \
				ft_printf/print_nbr.c \
				ft_printf/print_parsed.c \
				ft_printf/print_ptr.c \
				ft_printf/print_str.c \
				ft_printf/set_format.c

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(foreach X,$I,-I$(X))
DEBUGFLAGS	=	-g
ARFLAGS		=	rcs

DEP			=	$(SRC:%.c=$D%.d)
OBJ			=	$(SRC:%.c=$O%.o)

.PHONY:			all cleandep cleanobj clean fclean re debug

all:			$(NAME)

$(NAME):		$(OBJ)
				ar $(ARFLAGS) $(NAME) $^

$(OBJ): $O%.o:	%.c | $O
				$(CC) $(CFLAGS) -c $< -o $@

$(DEP): $D%.d:	%.c | $D
				@$(CC) $(CFLAGS) -MM -MP -MF $@ -MT "$O$*.o $@" $<

$O $D:
				@mkdir -p $@

cleandep:
				rm -rf $D

cleanobj:
				rm -rf $O

clean:			cleandep cleanobj
				rm -rf _build/

fclean:			clean
				rm -f $(NAME)

re:				fclean all

debug:			CFLAGS += $(DEBUGFLAGS)
debug:			re

ifeq ($(filter $(MAKECMDGOALS),cleandep cleanobj clean fclean),)
-include 		$(DEP)
endif
