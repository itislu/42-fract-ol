#If I'm already here I can also name the folder too
DIR		:=	libft/

#			Reset TMP
TMP		:=

#			Chars
SUBDIR	:=	chars/
TMP		+=	$(addprefix $(SUBDIR), \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_tolower.c \
			ft_toupper.c \
)

#			Lists
SUBDIR	:=	lists/
TMP		+=	$(addprefix $(SUBDIR), \
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

#			Memory
SUBDIR	:=	memory/
TMP		+=	$(addprefix $(SUBDIR), \
			ft_bzero.c \
			ft_calloc.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
)

#			Numbers
SUBDIR	:=	numbers/
TMP		+=	$(addprefix $(SUBDIR), \
			ft_atof.c \
			ft_atoi.c \
)

#			Put
SUBDIR	:=	put/
TMP		+=	$(addprefix $(SUBDIR), \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
)

#			Strings
SUBDIR	:=	strings/
TMP		+=	$(addprefix $(SUBDIR), \
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

#			Various
SUBDIR	:=	various/
TMP		+=	$(addprefix $(SUBDIR), \
)

#			Prepend current directory to all SRC files
#DIR		:=	$(shell basename "$$(pwd)")
#SRC		+=	$(foreach X,$(TMP),$(DIR)/$X)
#SRC_LIBFT	+=	$(foreach X,$(TMP),$(DIR)$X)
#SRC_LIBFT	+=	$(patsubst $(CURDIR)/%,%,$(TMP))
SRC_LIBFT	+=	$(addprefix $(DIR),$(TMP))

print-%  : ; @echo $* = $($*)