# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangtran <dangtran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/28 18:38:00 by dangtran          #+#    #+#              #
#    Updated: 2025/03/08 14:23:03 by dangtran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS= -Wall -Wextra -Werror -I${HEADER_DIR} -g

SRCS_DIR = 	$(addprefix sources/, parsing.c manage.c philo.c main.c)

SRCS_OBJ = ${SRCS_DIR:.c=.o}

HEADER_DIR=./includes/

all: $(NAME)

$(NAME): $(SRCS_OBJ)
	$(CC) $(CFLAGS) $(SRCS_OBJ) -o $(NAME)


clean :
	rm -f ${SRCS_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all