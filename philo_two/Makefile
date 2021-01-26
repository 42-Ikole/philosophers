# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ikole <ikole@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/15 16:36:12 by ikole         #+#    #+#                  #
#    Updated: 2021/01/26 14:46:30 by ingmar        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo_two

SRC		= philo_two.c init.c helpers.c phil_stuff.c time.c error.c

FLAGS	= -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

re: fclean all

clean:

fclean:
	@ rm -rf $(NAME)
