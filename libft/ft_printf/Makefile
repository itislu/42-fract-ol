# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/11/14 12:41:34 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft_printf.a
I			=	./ ../
L			=	../
D			=	_build/dep/
O			=	_build/obj/

SRC			=	ft_printf.c \
				ft_putnbr_base_fd.c \
				ft_putnchar_fd.c \
				ft_putnstr_fd.c \
				print_char.c \
				print_nbr.c \
				print_parsed.c \
				print_ptr.c \
				print_str.c \
				set_format.c

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(foreach X,$I,-I$X)
DEBUGFLAGS	=	-g
ARFLAGS		=	rcs

DEP			=	$(SRC:%.c=$D%.d)
OBJ			=	$(SRC:%.c=$O%.o)

.PHONY:			all cleandep cleanobj clean fclean re debug norm

all:			$(NAME)	#Possibly | ?

$(NAME):		$(OBJ)
				make -C $L
				mv $Llibft.a ./$(NAME)
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

norm:
				@read -p "Press Enter to check $$(basename "$$(pwd)")..." \
				userInput;
				-norminette -R CheckForbiddenSourceHeader -R CheckDefine \
				$(SRC) $(foreach X,$I,$X*.h)

ifeq ($(filter $(MAKECMDGOALS),cleandep cleanobj clean fclean norm),)
-include 		$(DEP)
endif