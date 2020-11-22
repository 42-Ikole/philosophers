# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ikole <ikole@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/15 16:36:12 by ikole         #+#    #+#                  #
#    Updated: 2020/11/22 12:52:36 by ikole         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo_two

SRC		= philo_two.c init.c helpers.c phil_stuff.c

FLAGS	= -Wall -Wextra -Werror -pthread

all: $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

re: fclean all

clean:

fclean:
	@ rm -rf $(NAME)