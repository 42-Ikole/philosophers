
#include "one.h"
#include <pthread.h>
#include "stdlib.h"

void	*fphilosophers(void	*v_philosopher)
{
	t_phil *philosopher;

	philosopher = (t_phil*)v_philosopher;
	while (philosopher->stats->dead == false)
	{
		state_eat(philosopher);
	}
	return (NULL);
}

int		stat_init(t_stats *stats, char **str, int argc)
{
	int i;

	stats->phil_amount = ft_atoi(str[1]);
	stats->time_to_die = ft_atoi(str[2]) * 1000;
	stats->time_to_eat = ft_atoi(str[3]) * 1000;
	stats->time_to_sleep = ft_atoi(str[4]) * 1000;
	if (argc == 6)
		stats->must_eat = ft_atoi(str[5]);
	else
		stats->must_eat = 0;
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
	return (0);
}

void	phil_init(t_phil *phil, t_stats *stats, int id)
{
		phil->stats = stats;
		phil->id = id;
		phil->time_since_eaten = 0;
		phil->times_eaten = 0;
		phil->l_chop = phil->id + 1;
		phil->r_chop = phil->id - 1;
		if (phil->l_chop > phil->stats->phil_amount)
		phil->l_chop = 0;
		if (phil->r_chop < 0)
		phil->r_chop = phil->stats->phil_amount - 1;
}

int main(int argc, char **argv)
{
	t_stats		stats;
    t_phil		*philosophers;
	int			i;
	pthread_t	*threads;

    if (!(argc == 5 || argc == 6))
        return (1); //
	if(stat_init(&stats, argv, argc) == -1)
		return (1); //
	threads = malloc(sizeof(pthread_t) * stats.phil_amount);
	if (!threads)
		return (1); //
	philosophers = malloc(sizeof(t_phil) * stats.phil_amount);
	if (!philosophers)
		return (1); //
	i = 0;
	while (i < stats.phil_amount)
	{
		//create threads here
		phil_init(&(philosophers[i]), &stats, i);
		if (pthread_create(&(threads[i]), NULL, fphilosophers, &(philosophers[i]))) // oude threads weghalen
			return (1); //
		i++;
	}
	i = 0;
	while (i < stats.phil_amount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
