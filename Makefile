SRCS	= main.c \
			utils.c \
			utils_1.c \
			parsing.c \
			parsing_check_inputs.c \
			parsing_long.c \
			block_build_utils.c \
			block.c \
			free_clean.c \
			echo.c \
			builtin_1.c \
			export.c \
			unset.c \
			dolar.c \
			ft_heredoc.c \
			constants.c \
			free.c \
			param.c \
			param_flags.c \
			pipe_fork.c \
			pipe.c \
			builtin_exec.c \
			ft_exit.c \
			cd.c \
			signal.c \

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
			${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} -lreadline -L./libft/ -lft -L/Users/${USER}/.brew/opt/readline/lib -I/Users/${USER}/.brew/opt/readline/include

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