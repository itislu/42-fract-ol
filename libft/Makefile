# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/11/14 18:49:45 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

# Header files directory:
I			=	inc/

# Build artifacts directories:
B			=	build/
D			=	$Bdep/
O			=	$Bobj/

# Source files directory:
S			=	src/

# Makefiles in build/ dir - list all source files and store them in SRC variable
SOURCELIST	=	libft.mk

# Flags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(foreach X,$I,-I$X)
DEBUGFLAGS	=	-g
ARFLAGS		=	rcs

#******************************************************************************#

include			src/libft/libft.mk #$(wildcard $(S)/*.mk) # - or not?
# either prepend $S here or later...
#SRC			:=	$(foreach X,$(SRC),$S$X)

DEP			=	$(SRC:$S%.c=$D%.d)
OBJ			=	$(SRC:$S%.c=$O%.o)

.PHONY:			all cleandep cleanobj clean fclean re debug norm

all:			$(NAME)

$(NAME):		$(OBJ)
				ar $(ARFLAGS) $(NAME) $(OBJ)

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
#				rm -rf $B

fclean:			clean
				rm -f $(NAME)

re:				fclean all

# is it possible to do it in one line with , or ; ?
debug:			CFLAGS += $(DEBUGFLAGS)
debug:			re

norm:			# Prolly need to change the message now
				@read -p "Press Enter to check $$(basename "$$(pwd)")..." \
				userInput;
				-norminette -R CheckForbiddenSourceHeader -R CheckDefine \
				$(SRC) $(foreach X,$I,$X*.h)

ifeq ($(filter $(MAKECMDGOALS),cleandep cleanobj clean fclean norm),)
-include 		$(DEP)
endif
