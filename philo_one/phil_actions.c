
#include "one.h"
#include <pthread.h>
#include "unistd.h"

int		state_sleep(t_phil *phil)
{
	phil_msg(phil, "is sleeping");
	usleep(phil->stats->time_to_sleep);
	phil_msg(phil, "is thinking");
	return (1);
}

int		state_eat(t_phil *phil)
{
	int	status;

	if (phil->stats->dead == true)
		return (-1);
	status = pthread_mutex_lock(&(phil->stats->chopsticks[phil->l_chop]));
	if (status)
		return (-1);
	phil_msg(phil, "has taken a fork");
	status = pthread_mutex_lock(&(phil->stats->chopsticks[phil->r_chop]));
	if (status)
	{
		pthread_mutex_unlock(&(phil->stats->chopsticks[phil->l_chop]));
		phil_msg(phil, "has dropped a fork");
	}
	phil_msg(phil, "has taken a fork");
	usleep(phil->stats->time_to_eat);
	pthread_mutex_unlock(&(phil->stats->chopsticks[phil->l_chop]));
	phil_msg(phil, "has dropped a fork");
	pthread_mutex_unlock(&(phil->stats->chopsticks[phil->r_chop]));
	phil_msg(phil, "has dropped a fork");
	phil->times_eaten++;
	state_sleep(phil);
	return (0);
}