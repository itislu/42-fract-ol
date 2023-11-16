# Gets this file's name (without suffix) which will be the final variable's name
VARNAME	:=	$(basename $(notdir $(lastword $(MAKEFILE_LIST))))

# Resets TMP to get rid of any old values
TMP		:=

#******************************************************************************#

# Directory of source files in src/ directory
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

# Creates the final variable and assigns all the listed source files to it
$(eval $(VARNAME)	:=	$(TMP))
