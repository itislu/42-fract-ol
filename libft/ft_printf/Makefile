# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/10/22 21:55:27 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftprintf.a
I			=	./
D			=	build/dep/
O			=	build/obj/
L			=	libft/

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
ARFLAGS		=	rcs

DEP			=	$(SRC:%.c=$D%.d)
OBJ			=	$(SRC:%.c=$O%.o)

.PHONY:			all bonus cleandep cleanobj clean fclean re norminette

all:			$(NAME)

$(NAME):		$(OBJ)
				make -C $L
				cp $Llibft.a ./$@
				ar $(ARFLAGS) $(NAME) $^

bonus:			all

$(OBJ): $O%.o:	%.c | $O
				$(CC) $(CFLAGS) -c $< -o $@

$(DEP): $D%.d:	%.c | $D
				@$(CC) $(CFLAGS) -MM -MP -MF $@ -MT "$O$*.o $@" $<

$O $D:
				@mkdir -p $@

cleandep:
ifeq ($(filter $(MAKECMDGOALS),clean fclean re),)
				make -C $L cleandep
endif
				rm -rf $D

cleanobj:
ifeq ($(filter $(MAKECMDGOALS),clean fclean re),)
				make -C $L cleanobj
endif
				rm -rf $O

clean:			cleandep cleanobj
				rm -rf build/
ifeq ($(filter $(MAKECMDGOALS),fclean re),)
				make -C $L clean
endif

fclean:			clean
				make -C $L fclean
				rm -f $(NAME)

re:				fclean all

norminette:
				norminette -R CheckForbiddenSourceHeader
				norminette -R CheckDefine $I*.h

ifeq ($(filter $(MAKECMDGOALS),cleandep cleanobj clean fclean),)
-include 		$(DEP)
endif