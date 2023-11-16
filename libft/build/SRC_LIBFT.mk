# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    SRC_LIBFT.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldulling <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 13:33:38 by ldulling          #+#    #+#              #
#    Updated: 2023/11/16 13:33:44 by ldulling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Gets this file's name (without suffix) which will be the final variable's name
VARNAME	:=	$(basename $(notdir $(lastword $(MAKEFILE_LIST))))

# Resets TMP to get rid of any old values
TMP		:=

#******************************************************************************#

# Directory of source files in src/ directory
DIR		:=	libft/

# Chars
SUBDIR	:=	chars/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_tolower.c \
			ft_toupper.c \
)

# Lists
SUBDIR	:=	lists/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
)

# Memory
SUBDIR	:=	memory/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_bzero.c \
			ft_calloc.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
)

# Numbers
SUBDIR	:=	numbers/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_atof.c \
			ft_atoi.c \
)

# Put
SUBDIR	:=	put/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
)

# Strings
SUBDIR	:=	strings/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
			ft_itoa.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strmatches_any.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
)

# Various
SUBDIR	:=	various/
TMP		+=	$(addprefix $(DIR)$(SUBDIR), \
)

# Creates the final variable and assigns all the listed source files to it
$(eval $(VARNAME)	:=	$(TMP))
