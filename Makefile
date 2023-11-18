# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 12:48:32 by ldulling          #+#    #+#              #
#    Updated: 2023/11/14 18:26:16 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export 			MAKECMDGOALS

NAME		=	fractol
I			=	./ libft/inc/
L			=	libft/
l			=	ft mlx Xext X11 m
B			=	build/
D			=	$B_dep/
O			=	$B_obj/

SRC			=	fractol.c \

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror $(foreach X,$I,-I$X)
DEBUGFLAGS	=	-g

DEP			=	$(SRC:%.c=$D%.d)
OBJ			=	$(SRC:%.c=$O%.o)

LAST_TARGET	=	$(shell cat $B.last_target 2>/dev/null)

.PHONY:			all bonus lib cleandep cleanobj clean fclean re debug debuglib \
norm print-% dir

ifeq ($(LAST_TARGET),debug)
all:			fclean lib $(NAME)
    ifeq (,$(filter debug,$(MAKECMDGOALS)))
	@			echo "Last target was debug, so recompiled."
    endif
else
all:			lib $(NAME)
endif

bonus:			all

lib:
ifeq (,$(filter debug,$(MAKECMDGOALS)))
	@			make -C $L --no-print-directory
endif

$(NAME):		$L $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) $(addprefix -L,$L) $(addprefix -l,$l) \
				-o $(NAME)

$(OBJ): $O%.o:	%.c | $O
				$(CC) $(CFLAGS) -c $< -o $@

$(DEP): $D%.d:	%.c | $D
	@			$(CC) $(CFLAGS) -M -MP -MF $@ -MT "$O$*.o $@" $<

$O $D:
	@			mkdir -p $@

cleandep:
ifneq ($(LAST_TARGET),debug)
    ifeq (,$(filter clean fclean re debug,$(MAKECMDGOALS)))
				make -C $L cleandep
    endif
				@rm -f $(DEP)
				-find $(D) -type d -empty -delete
endif

cleanobj:
ifneq ($(LAST_TARGET),debug)
    ifeq (,$(filter clean fclean re debug,$(MAKECMDGOALS)))
				make -C $L cleanobj
    endif
				@rm -f $(OBJ)
				-find $(O) -type d -empty -delete
endif

clean:			cleandep cleanobj
ifneq ($(LAST_TARGET),debug)
    ifeq (,$(filter fclean re debug,$(MAKECMDGOALS)))
				make -C $L clean
    endif
endif

fclean:			clean
ifeq (,$(filter debug,$(MAKECMDGOALS)))
				make -C $L fclean
endif
	@			rm -f $B.last_target
				rm -f $(NAME)

re:				fclean all

debug:			CFLAGS += $(DEBUGFLAGS)
debug:			debuglib re
				@echo "$@" > $B.last_target

debuglib:
				make -C $L debug

norm:
	@			-norminette -R CheckForbiddenSourceHeader -R CheckDefine \
				$(foreach src,$(SRC),$S$(src)) $(foreach dir,$I,$(dir)*.h)
	@			make -C $L norm --no-print-directory

ifeq (,$(filter cleandep cleanobj clean fclean re debug norm,$(MAKECMDGOALS)))
    -include 	$(DEP)
endif

# Makefile debugging
print-%		:
				@echo $* = $($*)
