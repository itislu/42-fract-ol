# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fractol.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 13:33:38 by ldulling          #+#    #+#              #
#    Updated: 2023/12/14 18:39:34 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ****************************** PREPARATION ********************************* #

# Gets this file's name (without suffix) for automatic variable creation later.
FILENAME	:=	$(basename $(notdir $(lastword $(MAKEFILE_LIST))))

# Resets TMP to get rid of any old values from other .mk files.
TMP			:=


# ***************************** CONFIGURATION ******************************** #

# Dependencies - has to be the basename of the corresponding .mk file:
DEPS	:=

# Directory of source files in src/ directory:
DIR		:=	./

# Source files:
#  Main:
SUBDIR	:=	./
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			fractol.c \
)

#  Color:
SUBDIR	:=	color/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			color.c \
)

#  Events:
SUBDIR	:=	events/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			key_handling.c \
			mouse_handling.c \
)

#  Fractals:
SUBDIR	:=	fractals/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			barnsley_fern.c \
			calculation_utils.c \
			julia.c \
			mandelbrot.c \
			multibrot.c \
			multijulia.c \
)

#  Parsing:
SUBDIR	:=	parsing/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			parsing.c \
			parsing_utils.c \
)

#  Utils:
SUBDIR	:=	utils/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			exit.c \
			img_pixel_put.c \
			init.c \
			print_manual.c \
)


# *************************** VARIABLE CREATION ****************************** #

# Creates a final SRC variable and assigns all the source files specified above.
$(eval SRC_$(FILENAME)		:=	$(TMP))

# Creates an OBJ variable for the dependency rule below.
$(eval OBJ_$(FILENAME)		:=	$(SRC_$(FILENAME):%.c=$O%.o))

# Makes this file's object files dependent on any DEPS specified above.
$(OBJ_$(FILENAME)):	$O%.o	:	$(foreach dep,$(DEPS),$(OBJ_$(dep)))


# *************************** MAKEFILE DEBUGGING ***************************** #

# Prints the values of the variable given after the minus.
print-%	:
	@		echo $* = $($*)
