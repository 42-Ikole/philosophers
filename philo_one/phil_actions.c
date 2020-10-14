
#include "one.h"
#include <pthread.h>
#include "unistd.h"
#include <sys/time.h>

void	state_sleep(t_phil *phil)
{
	if (phil->stats->dead == true)
		return ;
	phil_msg(phil, "is sleeping");
	usleep(phil->stats->time_to_sleep);
	phil_msg(phil, "is thinking");
}

void	state_eat(t_phil *phil)
{
	struct timeval current_time;

	pthread_mutex_lock(&(phil->stats->eatsies[phil->id]));
	phil_msg(phil, "is eating");
	usleep(phil->stats->time_to_eat);
	pthread_mutex_unlock(&(phil->stats->eatsies[phil->id]));
	pthread_mutex_unlock(&(phil->stats->chopsticks[phil->l_chop]));
	phil_msg(phil, "has dropped a fork");
	pthread_mutex_unlock(&(phil->stats->chopsticks[phil->r_chop]));
	phil_msg(phil, "has dropped a fork");
	phil->times_eaten++;
	gettimeofday(&current_time, NULL);
	phil->time_since_eaten = get_time();
}


void	take_chopstick(t_phil *phil)
{
	if (phil->stats->dead == true)
		return ;
	pthread_mutex_lock(&(phil->stats->chopsticks[phil->l_chop]));
	phil_msg(phil, "has taken a fork");
	if (phil->stats->dead == true)
	{
		pthread_mutex_unlock(&(phil->stats->chopsticks[phil->l_chop]));
		return ;
	}
	pthread_mutex_lock(&(phil->stats->chopsticks[phil->r_chop]));
	phil_msg(phil, "has taken a fork");
	if (phil->stats->dead == true)
	{
		pthread_mutex_unlock(&(phil->stats->chopsticks[phil->l_chop]));
		pthread_mutex_unlock(&(phil->stats->chopsticks[phil->r_chop]));
		return ;
	}
	state_eat(phil);
}