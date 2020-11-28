# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ikole <ikole@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/15 16:36:12 by ikole         #+#    #+#                  #
#    Updated: 2020/11/28 19:46:28 by ikole         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= philo_two

SRC		= philo_two.c init.c helpers.c phil_stuff.c time.c

FLAGS	= -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

re: fclean all

clean:

fclean:
	@ rm -rf $(NAME)
