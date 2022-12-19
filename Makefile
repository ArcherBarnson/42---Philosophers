# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 13:24:08 by bgrulois          #+#    #+#              #
#    Updated: 2022/09/28 09:59:09 by bgrulois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo	

SRCS	=	srcs/ft_strlen.c \
		srcs/ft_atoi.c \
		srcs/ft_itoa.c \
		srcs/struct_init.c \
		srcs/memory_tools.c \
		srcs/parsing.c \
		srcs/display.c \
		srcs/time.c \
		srcs/actions.c \
		srcs/routine_utils.c \
		srcs/routine.c \
		main.c

CC	=	gcc	

CFLAGS	=	-Wall -Wextra -Werror -pthread

OBJS	=	${SRCS:%.c=%.o}

all: 		${NAME}

%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@

${NAME}: 	$(OBJS)
		${CC} ${CFLAGS} $(OBJS) -o $(NAME)

clean:		
		rm -rf ${OBJS}

fclean:		clean
		rm -rf ${NAME}

re:		fclean 
		make

.PHONY:		all clean fclean re
