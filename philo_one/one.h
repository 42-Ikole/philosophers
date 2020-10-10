#ifndef ONE_H
# define ONE_H

#include <pthread.h>

typedef struct	s_stats
{
	int			phil_amount;
	int			time_to_die;
    int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			**queue;
	int			can_write;
	pthread_t	*philosophers;
}				t_stats;

int	ft_atoi(char *str);

#endif
