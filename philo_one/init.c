
#include "one.h"
#include <sys/time.h>
#include <stdlib.h>

int		stat_init(t_stats *stats, char **str, int argc)
{
	unsigned int i;

	stats->phil_amount = ft_atoi(str[1]);
	stats->time_to_die = ft_atoi(str[2]);
	stats->time_to_eat = ft_atoi(str[3]) * 1000;
	stats->time_to_sleep = ft_atoi(str[4]) * 1000;
	if (argc == 6)
		stats->must_eat = ft_atoi(str[5]);
	else
		stats->must_eat = 0;
	stats->done = 0;
	stats->chopsticks = malloc(sizeof(pthread_mutex_t) * stats->phil_amount);
	if (!stats->chopsticks)
		return (-1);
	i = 0;
	while (i < stats->phil_amount)
	{
		pthread_mutex_init(&(stats->chopsticks[i]), NULL); //check of hij faalt
		i++;
	}
	pthread_mutex_init(&(stats->write), NULL);
	stats->start = get_time();
	return (0);
}

void	phil_init(t_phil *phil, t_stats *stats, int id)
{
	phil->stats = stats;
	phil->id = id;
	phil->time_since_eaten = get_time();
	phil->times_eaten = 0;
	phil->l_chop = phil->id + 1;
	phil->r_chop = phil->id - 1;
	if (phil->l_chop >= (int)phil->stats->phil_amount)
		phil->l_chop = 0;
	if (phil->r_chop < 0)
		phil->r_chop = phil->stats->phil_amount - 1;
	printf("l = [%d] - r = [%d]\n", phil->l_chop, phil->r_chop);
}
