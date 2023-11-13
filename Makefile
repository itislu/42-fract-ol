# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/11/12 14:10:43 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol
D			=	build/dep/
O			=	build/obj/
I			=	./ libft/
L			=	libft/
l			=	ft mlx Xext X11

SRC			=	fractol.c \


CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(foreach X,$I,-I$X)

DEP			=	$(SRC:%.c=$D%.d)
OBJ			=	$(SRC:%.c=$O%.o)

.PHONY:			all libraries bonus cleandep cleanobj clean fclean re norminette

all:			libraries $(NAME)

libraries:
				@make -C $L --no-print-directory

$(NAME):		$L $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) $(foreach X,$L,-L$X) $(foreach X,$l,-l$X) -o $(NAME)

bonus:			all

$(OBJ): $O%.o:	%.c | $O
				make -C $L
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