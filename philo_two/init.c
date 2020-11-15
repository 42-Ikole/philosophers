
#include "two.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

int		stat_init(t_stats *stats, char **str, int argc)
{
	stats->phil_amount = ft_atoi(str[1]);
	stats->time_to_die = ft_atoi(str[2]);
	stats->time_to_eat = ft_atoi(str[3]) * 1000;
	stats->time_to_sleep = ft_atoi(str[4]) * 1000;
	if (argc == 6)
		stats->must_eat = ft_atoi(str[5]);
	else
		stats->must_eat = 0;
	stats->done = 0;
	stats->start = get_time();
	create_semaphores(stats);
	return (0);
}

void	phil_init(t_phil *phil, t_stats *stats, int id)
{
	phil->stats = stats;
	phil->id = id;
	phil->time_since_eaten = get_time();
	phil->times_eaten = 0;
	if (id % 2)
		usleep(400);
	else
		usleep(200);
}
