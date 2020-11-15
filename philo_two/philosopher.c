
#include "two.h"
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>

void	*do_things(void	*v_philosopher)
{
	t_phil *phil;

	phil = (t_phil*)v_philosopher;
	phil_msg(phil, "appeared!");
	while (phil->stats->dead == false)
	{
		if (phil->stats->must_eat > 0 && phil->times_eaten == phil->stats->must_eat)
		{
			phil_msg(phil, "is done eating");
			phil->stats->done++;
			sem_close(phil->eatsies);
			return (NULL);
		}
		phil_msg(phil, "is thinking");
		if (phil->stats->dead == false)
			take_chopstick(phil);
		if (phil->stats->dead == false)
			state_sleep(phil);
	}
	sem_close(phil->eatsies);
	return (NULL);
}

void	monitor(t_phil *phil)
{
	unsigned int	i;
	unsigned int	done_eating;

	i = 0;
	done_eating = 0;
	while (i < phil->stats->phil_amount)
	{
		if (phil->stats->dead == true)
			break ;
		else if (phil->stats->must_eat >= 0 && phil->stats->done == phil->stats->phil_amount)
			break ;
		sem_wait(phil->eatsies);
		check_death(&(phil[i]));
		sem_post(phil->eatsies);
		i++;
		if (i == phil->stats->phil_amount)
			i = 0;
	}
}

void	create_threads(t_phil *phil, t_stats stats)
{
	pthread_t		*threads;
	unsigned int	i;

	threads = malloc(sizeof(pthread_t) * stats.phil_amount);
	if (!threads)
		return ;
	i = 0;
	sem_unlink("eatsies");
	while (i < stats.phil_amount)
	{
		phil_init(&(phil[i]), &stats, i);
		phil->eatsies = sem_open("eatsies", O_CREAT, 0666, stats.phil_amount);
		if (phil->eatsies == SEM_FAILED)
		{
			printf("nani?!?!?!\n");
			return ;
		}
		if (pthread_create(&(threads[i]), NULL, do_things, &(phil[i])))
		{
			while (i > 0)
			{
				i--;
				pthread_join(threads[i], NULL);
			}
			return ;
		}
		i++;
	}
	monitor(phil);
	i = 0;
	while (i < stats.phil_amount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}


int 	main(int argc, char **argv)
{
	t_stats		stats;
    t_phil		*phil;

    if (!(argc == 5 || argc == 6))
        return (1);
	if(stat_init(&stats, argv, argc) == -1)
		return (1);
	phil = malloc(sizeof(t_phil) * stats.phil_amount);
	if (!phil)
		return (1);
	create_threads(phil, stats);
	sem_close(stats.write);
	sem_close(stats.chopsticks);
	return (0);
}
