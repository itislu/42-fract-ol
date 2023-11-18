# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/11/18 13:27:46 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ***************************** CONFIGURATION ******************************** #

NAME		:=	fractol

# Header files directories:
I			:=	inc/ libft/inc/

#TODO: find names and see if I will create a lib/ directory
#
L			:=	libft/
l			:=	ft mlx Xext X11 m

# Build direcoties:
B			:=	build/
D			:=	$B_dep/
O			:=	$B_obj/

# Source files directory:
S			:=	src/

#TODO: think where to put it
SRC			:=	fractol.c \

# Flags:
CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror $(addprefix -I,$I)
DEBUGFLAGS	:=	-g

# ***************************** BUILD PROCESS ******************************** #

DEP				:=	$(SRC:%.c=$D%.d)
OBJ				:=	$(SRC:%.c=$O%.o)
SUBDIRS_D		:=	$(sort $(dir $(DEP)))
SUBDIRS_O		:=	$(sort $(dir $(OBJ)))

#TODO: test if := works too
LAST_TARGET		=	$(shell cat $B.last_target 2>/dev/null)

export 				MAKECMDGOALS

#TODO: test if dir still works with file called "dir" existing (bc of the tabs)
.PHONY			:	all bonus lib cleandep cleanobj clean fclean re debug debuglib \
					norm print-% dir

ifeq ($(LAST_TARGET),debug)
all				:	fclean lib $(NAME)
    ifeq (,$(filter debug,$(MAKECMDGOALS)))
	@				echo "Last target was debug, so recompiled."
    endif
else
all				:	lib $(NAME)
endif

bonus			:	all

lib				:
ifeq (,$(filter debug,$(MAKECMDGOALS)))
	@				make -C $L --no-print-directory
endif

$(NAME)			:	$L $(OBJ)
					$(CC) $(CFLAGS) $(OBJ) $(addprefix -L,$L) $(addprefix -l,$l) \
					-o $(NAME)

$(OBJ):	$O%.o	:	$S%.c | $(SUBDIRS_O)
					$(CC) $(CFLAGS) -c $< -o $@

$(DEP):	$D%.d	:	$S%.c | $(SUBDIRS_D)
	@				$(CC) $(CFLAGS) -M -MP -MF $@ -MT "$O$*.o $@" $<

$(SUBDIRS_O) $(SUBDIRS_D):
	@				mkdir -p $@

cleandep		:
ifneq ($(LAST_TARGET),debug)
    ifeq (,$(filter clean fclean re debug,$(MAKECMDGOALS)))
					make -C $L cleandep
    endif
	@				rm -f $(DEP)
					-find $(D) -type d -empty -delete
endif

cleanobj		:
ifneq ($(LAST_TARGET),debug)
    ifeq (,$(filter clean fclean re debug,$(MAKECMDGOALS)))
					make -C $L cleanobj
    endif
	@				rm -f $(OBJ)
					-find $(O) -type d -empty -delete
endif

clean			:	cleandep cleanobj
ifneq ($(LAST_TARGET),debug)
    ifeq (,$(filter fclean re debug,$(MAKECMDGOALS)))
					make -C $L clean
    endif
endif

fclean			:	clean
ifeq (,$(filter debug,$(MAKECMDGOALS)))
					make -C $L fclean
endif
	@				rm -f $B.last_target
					rm -f $(NAME)

re				:	fclean all

debug			:	CFLAGS += $(DEBUGFLAGS)
debug			:	debuglib re
	@				echo "$@" > $B.last_target

debuglib		:
					make -C $L debug

dir				:
					mkdir $B $I $L $S

#TODO: align with the other Makefiles
norm			:
	@				-norminette -R CheckForbiddenSourceHeader -R CheckDefine \
					$(addprefix $S,$(SRC)) $(foreach dir,$I,$(dir)*.h)
	@				make -C $L norm --no-print-directory

ifeq (,$(filter cleandep cleanobj clean fclean re debug norm,$(MAKECMDGOALS)))
    ifneq (,$(wildcard $O))
        -include	$(DEP)
    endif
endif

# *************************** MAKEFILE DEBUGGING ***************************** #

# Makefile debugging
print-%			:
	@				echo $* = $($*)
