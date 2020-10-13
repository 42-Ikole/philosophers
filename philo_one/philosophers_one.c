
#include "one.h"
#include <pthread.h>
#include <stdlib.h>

void	*fphilosophers(void	*v_philosopher)
{
	t_phil *phil;

	phil = (t_phil*)v_philosopher;
	phil_msg(phil, "appeared!");
	// if (phil->id % 2)
	// 	state_eat(phil);
	// else
	// 	state_sleep(phil);
	while (phil->stats->dead == false)
	{
		if (phil->stats->must_eat && phil->times_eaten == phil->stats->must_eat)
		{
			phil_msg(phil, "is done eating");
			return (NULL);
		}
		if (phil->stats->dead == false)
			state_eat(phil);
		if (phil->stats->dead == false)
			state_sleep(phil);
	}
	return (NULL);
}

void	monitor(t_phil *phil)
{
	int i;

	i = 0;
	while (i < phil->stats->phil_amount)
	{
		if (phil->stats->dead == true)
			break ;
		pthread_mutex_lock(&(phil->stats->eatsies[i]));
		check_death(&(phil[i]));
		pthread_mutex_unlock(&(phil->stats->eatsies[i]));
		i++;
		if (i == phil->stats->phil_amount)
			i = 0;
	}
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
	stats.eatsies = malloc(sizeof(pthread_mutex_t) * stats.phil_amount);
	philosophers = malloc(sizeof(t_phil) * stats.phil_amount);
	if (!philosophers)
		return (1); //
	i = 0;
	while (i < stats.phil_amount)
	{
		//create threads here
		phil_init(&(philosophers[i]), &stats, i);
		pthread_mutex_init(&(stats.eatsies[i]), NULL);
		if (pthread_create(&(threads[i]), NULL, fphilosophers, &(philosophers[i]))) // oude threads weghalen
			return (1); //
		i++;
	}
	monitor(philosophers);
	i = 0;
	while (i < stats.phil_amount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
