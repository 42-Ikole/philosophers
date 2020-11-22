# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ikole <ikole@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/15 16:36:12 by ikole         #+#    #+#                  #
#    Updated: 2020/11/22 16:13:15 by ikole         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo_three

SRC		= philo_three.c init.c helpers.c phil_stuff.c

FLAGS	= -Wall -Wextra -Werror -pthread

all: $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

re: fclean all

clean:

fclean:
	@ rm -rf $(NAME)