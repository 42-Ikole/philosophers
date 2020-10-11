#ifndef ONE_H
# define ONE_H

#include <pthread.h>

typedef enum	e_bool
{
	true = 1,
	false = 0
}	t_bool;

typedef struct	s_stats
{
	unsigned int	phil_amount;
	unsigned int	time_to_die;
    unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat;
	t_bool			dead;
	pthread_mutex_t	*chopsticks;
}				t_stats;

typedef struct	s_phil
{
	unsigned int	id;
	unsigned int	time_since_eaten;
	unsigned int	times_eaten;
	t_bool			l_chop;
	t_bool			r_chop;
	t_stats			*stats;
}				t_phil;


int	ft_atoi(char *str);
int	eat(t_phil *phil);

#endif
