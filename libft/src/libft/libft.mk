#		Reset TMP
TMP	=

#		Chars
TMP	+=	ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_tolower.c \
		ft_toupper.c

#		Lists
TMP	+=	ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c

#		Memory
TMP	+=	ft_bzero.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c

#		Numbers
TMP	+=	ft_atof.c \
		ft_atoi.c

#		Put
TMP	+=	ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c

#		Strings
TMP	+=	ft_itoa.c \
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
		ft_substr.c

#		Prepend current directory to all SRC files
DIR	:=	$(shell basename "$$(pwd)")
SRC	+=	$(foreach X,$(TMP),$(DIR)/$X)
