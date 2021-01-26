# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/16 13:27:45 by odhazzar          #+#    #+#              #
#    Updated: 2020/11/19 13:24:17 by odhazzar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_three

SRC			= main.c init.c utils.c states.c parsing.c

OBJ			= $(SRC:.c=.o)

HEADER		= philo_three.h

CC			= gcc

FLAGS		= -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) ${FLAGS} ${OBJ} -o ${NAME}

%.o : 		%.c $(HEADER)
			$(CC) $(FLAGS) -c $< -o $@

clean:
			rm -rf $(OBJ)

fclean:
			rm -rf $(OBJ) $(NAME)

re:			fclean all