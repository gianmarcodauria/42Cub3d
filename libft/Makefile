NAME = libft.a

CC = gcc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -gdwarf-2

SRCS = ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c \
		ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_atoi.c ft_itoa.c ft_putendl_fd.c \
		ft_strlcpy.c ft_tolower.c ft_bzero.c ft_putnbr_fd.c ft_strlen.c \
		ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c \
		ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c ft_strtok.c\
		ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_striteri.c \
		ft_printf.c prntf_num_utils.c prntf_ptr_utils.c prntf_utils.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_strcpy.c\
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
		ft_alloc.c gnl/get_next_line.c gnl/get_next_line_utils.c ft_utils.c ft_get_extention.c\

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all:	${NAME}

$(NAME): ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
		${RM} ${OBJDIR}
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all
