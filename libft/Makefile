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

NAME		:=		libft.a

# Header files directory:
I			:=		inc/

# Build directories:
B			:=		build/
D			:=		$Bdep/
O			:=		$Bobj/

# Source files directory:
S			:=		src/

# Makefiles in build/ dir - list all source files and store them in SRC variable
SOURCELIST	:=		SRC_LIBFT.mk SRC_FT_PRINTF.mk

# Flags
CC			:=		cc
CFLAGS		:=		-Wall -Wextra -Werror $(foreach X,$I,-I$X)
DEBUGFLAGS	:=		-g
ARFLAGS		:=		rcs

#******************************************************************************#

include				$(addprefix $B,$(SOURCELIST))

SRC				:=	$(foreach VAR,$(basename $(SOURCELIST)),$($(VAR)))

DEP				:=	$(SRC:%.c=$D%.d)
OBJ				:=	$(SRC:%.c=$O%.o)
SUBDIRS_D		:=	$(sort $(dir $(DEP)))
SUBDIRS_O		:=	$(sort $(dir $(OBJ)))

.PHONY			:	all cleandep cleanobj clean fclean re debug norm

all				:	$(NAME)

#temporary - searching for fix, but not working yet
$(SRC_FT_PRINTF):	$(SRC_LIBFT)

$(NAME)			:	$(OBJ)
					ar $(ARFLAGS) $(NAME) $(OBJ)

$(OBJ):	$O%.o	:	$S%.c | $(SUBDIRS_O)
					$(CC) $(CFLAGS) -c $< -o $@

$(DEP):	$D%.d	:	$S%.c | $(SUBDIRS_D)
					@$(CC) $(CFLAGS) -MM -MP -MF $@ -MT "$O$*.o $@" $<

$(SUBDIRS_D) $(SUBDIRS_O):
					@mkdir -p $@

cleandep		:
					rm -rf $D

cleanobj		:
					rm -rf $O

clean			:	cleandep cleanobj

fclean			:	clean
					rm -f $(NAME)

re				:	fclean all

# is it possible to do it in one line with , or ; ?
debug			:	CFLAGS += $(DEBUGFLAGS)
debug			:	re

norm			:	# Prolly need to change the message now
					@read -p "Press Enter to check $$(basename "$$(pwd)")..." \
					userInput;
					-norminette -R CheckForbiddenSourceHeader -R CheckDefine \
					$(SRC) $(foreach X,$I,$X*.h)

ifeq ($(filter $(MAKECMDGOALS),cleandep cleanobj clean fclean norm),)
-include 			$(DEP)
endif

#Debugging
print-%  : ; @echo $* = $($*)