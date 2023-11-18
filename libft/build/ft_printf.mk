# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_printf.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 13:33:22 by ldulling          #+#    #+#              #
#    Updated: 2023/11/17 15:05:13 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Gets this file's name (without suffix) for automatic variable creation later.
FILENAME	:=	$(basename $(notdir $(lastword $(MAKEFILE_LIST))))

# Resets TMP to get rid of any old values from other .mk files.
TMP		:=

# ******************************** CONFIG ************************************ #

# Dependencies - has to be the basename of the corresponding .mk file:
DEPS	:=	libft

# Directory of source files in src/ directory:
DIR		:=	ft_printf/

# ft_printf
TMP		+=	$(addprefix $(DIR), \
			ft_printf.c \
			ft_putnbr_base_fd.c \
			ft_putnchar_fd.c \
			ft_putnstr_fd.c \
			print_char.c \
			print_nbr.c \
			print_parsed.c \
			print_ptr.c \
			print_str.c \
			set_format.c \
)

# **************************************************************************** #

# Creates a final SRC variable and assigns all the source files specified above.
$(eval SRC_$(FILENAME)		:=	$(TMP))

# Creates an OBJ variable for the dependency rule below.
$(eval OBJ_$(FILENAME)		:=	$(SRC_$(FILENAME):%.c=$O%.o))

# Makes this file's object files dependent on any DEPS specified above.
$(OBJ_$(FILENAME)):	$O%.o	:	$(foreach dep,$(DEPS),$(OBJ_$(dep)))
