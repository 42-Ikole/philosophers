
#include "one.h"

void	philosophers(t_stats *stats, int philosopher)
{
	while (1)
	{
		
	}
}

t_stats	init(t_stats stats, char **str)
{
	int i;

	stats.phil_amount = ft_atoi(str[1]);
	stats.time_to_die = ft_atoi(str[2]);
	stats.time_to_eat = ft_atoi(str[3]);
	stats.time_to_sleep = ft_atoi(str[4]);
	stats.must_eat = ft_atoi(str[5]);
	stats.queue = malloc(sizeof(int *) * stats.phil_amount);
	if (!stats.queue)
		return (1);
	i = 0;
	while (i < stats.phil_amount)
	{
		stats.queue[i] = malloc(sizeof(int) * 2);
		if (stats.queue[i])
			return (1);
		stats.queue[i][0] = i; //pk philosopher	
		stats.queue[i][1] = 0; //time since eaten
		i++;
	}

	return (stats);
}

int main(int argc, char **argv)
{
    t_stats		stats;
	int			i;

    if (argc != 6)
        return (1);
	stats = init(stats, argv);
	stats.philosophers = malloc(sizeof(pthread_t) * stats.phil_amount);
	if (!stats.philosophers)
		return (1);
	i = 0;
	while (i < stats.phil_amount)
	{
		//create threads here
		pthread_create(&stats.philosophers[i], NULL, philosophers, &stats);
		philosophers(&stats, i);
		i++;
	}
	i = 0;
	while (i < stats.phil_amount)
	{
		pthread_join(stats.philosophers[i], NULL);
		i++;
	}
	return (0);
}