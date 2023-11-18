# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/11/17 15:05:20 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ***************************** CONFIGURATION ******************************** #

NAME		:=		libft.a

# Header files directory:
I			:=		inc/

# Build directories:
B			:=		build/
D			:=		$Bdep/
O			:=		$Bobj/

# Source files directory:
S			:=		src/

# Makefiles in build/ directory with source file listings to be included
# (files that are dependent on others need to be below their dependency):
SOURCELISTS	:=		libft.mk \
					ft_printf.mk \

# Flags:
CC			:=		cc
CFLAGS		:=		-Wall -Wextra -Werror $(foreach X,$I,-I$X)
DEBUGFLAGS	:=		-g
ARFLAGS		:=		rcs

# ***************************** BUILD PROCESS ******************************** #

.DEFAULT_GOAL	:=	all

include				$(addprefix $B,$(SOURCELISTS))

SRC				:=	$(foreach name,$(basename $(SOURCELISTS)),$(SRC_$(name)))

DEP				:=	$(SRC:%.c=$D%.d)
OBJ				:=	$(SRC:%.c=$O%.o)
SUBDIRS_D		:=	$(sort $(dir $(DEP)))
SUBDIRS_O		:=	$(sort $(dir $(OBJ)))

.PHONY			:	all cleandep cleanobj clean fclean re debug norm print-%

all				:	$(NAME)

$(NAME)			:	$(OBJ)
					ar $(ARFLAGS) $(NAME) $(OBJ)

$(OBJ):	$O%.o	:	$S%.c | $(SUBDIRS_O)
					$(CC) $(CFLAGS) -c $< -o $@

$(DEP):	$D%.d	:	$S%.c | $(SUBDIRS_D)
	@				$(CC) $(CFLAGS) -M -MP -MF $@ -MT "$O$*.o $@" $<

$(SUBDIRS_D) $(SUBDIRS_O):
	@				mkdir -p $@

cleandep		:
					rm -rf $D

cleanobj		:
					rm -rf $O

clean			:	cleandep cleanobj

fclean			:	clean
					rm -f $(NAME)

re				:	fclean all

debug			:	CFLAGS += $(DEBUGFLAGS)
debug			:	re

norm			:	# Prolly need to change the message now
	@				read -p "Press Enter to check $$(basename "$$(pwd)")..." \
					userInput;
	@				-norminette -R CheckForbiddenSourceHeader -R CheckDefine \
					$(foreach src,$(SRC),$S$(src)) $(foreach dir,$I,$(dir)*.h)

ifeq (,$(filter cleandep cleanobj clean fclean re debug norm,$(MAKECMDGOALS)))
    -include 		$(DEP)
endif

# *************************** MAKEFILE DEBUGGING ***************************** #

# Prints the values of the variable given after the minus.
print-%			:
					@echo $* = $($*)
