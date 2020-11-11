
NAME	= philo_one

SRC		= helpers.c init.c phil_actions.c philosophers_one.c

OFI		= $(SRC:.c=.o)

FLAGS	= -Wall -Wextra -Werror -pthread

all: $(SRC)
	gcc $(FLAGS) $(SRC) -o $(NAME)

re: fclean all

clean:
	@ rm $(OFI)

fclean:
	@ rm -rf $(NAME)