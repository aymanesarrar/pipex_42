MAIN=pipex
NAME=libft.a
CC=gcc
CCFLAGS=-Wall -Wextra -Werror
MAINSRC=srcs/mandatory/main.c
SRCS = ft_atoi.c \
       ft_bzero.c \
	ft_calloc.c \
       ft_itoa.c \
       ft_isalnum.c \
       ft_isalpha.c \
       ft_isascii.c \
       ft_isdigit.c \
       ft_isprint.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_memset.c \
       ft_putchar_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_putstr_fd.c \
       ft_split.c \
       ft_strchr.c \
       ft_strdup.c \
       ft_strjoin.c \
       ft_strlcat.c \
       ft_strlcpy.c \
       ft_strlen.c \
       ft_strmapi.c \
       ft_strncmp.c \
       ft_strnstr.c \
       ft_strrchr.c \
       ft_strtrim.c \
       ft_substr.c \
       ft_tolower.c \
       ft_toupper.c \
       ft_striteri.c \
       pipex_utils.c

BONUS_SRCS = ft_lstadd_back.c \
	   ft_lstadd_front.c \
	   ft_lstclear.c \
	   ft_lstdelone.c \
	   ft_lstiter.c \
	   ft_lstlast.c \
	   ft_lstmap.c \
	   ft_lstnew.c \
	   ft_lstsize.c \

OBJS = my_libft/ft_atoi.o \
       my_libft/ft_bzero.o \
	my_libft/ft_calloc.o \
       my_libft/ft_itoa.o \
       my_libft/ft_isalnum.o \
       my_libft/ft_isalpha.o \
       my_libft/ft_isascii.o \
       my_libft/ft_isdigit.o \
       my_libft/ft_isprint.o \
       my_libft/ft_memchr.o \
       my_libft/ft_memcmp.o \
       my_libft/ft_memcpy.o \
       my_libft/ft_memmove.o \
       my_libft/ft_memset.o \
       my_libft/ft_putchar_fd.o \
       my_libft/ft_putendl_fd.o \
       my_libft/ft_putnbr_fd.o \
       my_libft/ft_putstr_fd.o \
       my_libft/ft_split.o \
       my_libft/ft_strchr.o \
       my_libft/ft_strdup.o \
       my_libft/ft_strjoin.o \
       my_libft/ft_strlcat.o \
       my_libft/ft_strlcpy.o \
       my_libft/ft_strlen.o \
       my_libft/ft_strmapi.o \
       my_libft/ft_strncmp.o \
       my_libft/ft_strnstr.o \
       my_libft/ft_strrchr.o \
       my_libft/ft_strtrim.o \
       my_libft/ft_substr.o \
       my_libft/ft_tolower.o \
       my_libft/ft_toupper.o \
       my_libft/ft_striteri.o \
       my_libft/pipex_utils.o \

BONUS_OBJS = ft_lstadd_back.o \
	   ft_lstadd_front.o \
	   ft_lstclear.o \
	   ft_lstdelone.o \
	   ft_lstiter.o \
	   ft_lstlast.o \
	   ft_lstmap.o \
	   ft_lstnew.o \
	   ft_lstsize.o \

RM = rm -rf

.c.o:	
			${CC} ${CCFLAGS} -c $<

all:		${MAIN}
              
$(MAIN):	${NAME}
			${CC} ${CCFLAGS} $(MAINSRC) $(NAME) -o $(MAIN)

$(NAME):	${OBJS}
			ar rcs ${NAME} ${SRCS:.c=.o}

bonus: 		${OBJS} ${BONUS_OBJS}
			ar rcs ${NAME} ${OBJS} ${BONUS_OBJS}

clean:
			${RM} ${SRCS:.c=.o} ${BONUS_OBJS}

fclean:		clean
			${RM} ${NAME} $(MAIN)

re:			fclean all
