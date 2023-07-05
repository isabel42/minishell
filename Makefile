<<<<<<< HEAD
SRCS	= main.c utils.c parsing.c type.c block.c free_clean.c 
=======
SRCS	= main.c utils.c parsing.c type.c signal.c builtin.c builtin_1.c unset.c export.c 
>>>>>>> kimi

OBJS 	= ${SRCS:.c=.o}

NAME 	= minishell

FT_NAME = ./libft/libft.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wextra -Wall -Werror

INCLUDE = -I./libft/ -I.

.c.o:	
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS} ${FT_NAME}
<<<<<<< HEAD
			${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} -lreadline -L./libft/ -lft -L/Users/ktomat/.brew/opt/readline/lib -I/Users/ktomat/.brew/opt/readline/include
=======
			${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} -L./libft/ -lft -lreadline
>>>>>>> isa

all:		${NAME}

${FT_NAME}:
	make -C ./libft/

clean:
			make clean -C ./libft
			${RM} ${OBJS}

fclean: 	clean
			make fclean -C ./libft
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re