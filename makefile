NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -fPIC
RM = rm -rf
INCLUDE = -L ./libft -lft
SRCS = pipex.c \
	utils.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

all : $(NAME)

clean :
	$(RM) $(OBJS)
	@cd libft/ && $(MAKE) clean

fclean : clean
	$(RM) $(NAME)
	@cd libft/ && $(MAKE) fclean

re : fclean all
