
#include "one.h"
#include <pthread.h>
#include "unistd.h"
#include <sys/time.h>

void	state_sleep(t_phil *phil)
{
	check_death(phil);
	if (phil->stats->dead == true)
		return ;
	phil_msg(phil, "is sleeping");
	usleep(phil->stats->time_to_sleep);
	phil_msg(phil, "is thinking");
	return ;
}

void	state_eat(t_phil *phil)
{
	struct timeval current_time;

	check_death(phil);
	if (phil->stats->dead == true)
		return ;
	pthread_mutex_lock(&(phil->stats->chopsticks[phil->l_chop]));
	phil_msg(phil, "has taken a fork");
	check_death(phil);
	if (phil->stats->dead == true)
		return ;
	pthread_mutex_lock(&(phil->stats->chopsticks[phil->r_chop]));
	phil_msg(phil, "has taken a fork");
	phil_msg(phil, "is eating");
	usleep(phil->stats->time_to_eat);
	pthread_mutex_unlock(&(phil->stats->chopsticks[phil->l_chop]));
	phil_msg(phil, "has dropped a fork");
	pthread_mutex_unlock(&(phil->stats->chopsticks[phil->r_chop]));
	phil_msg(phil, "has dropped a fork");
	phil->times_eaten++;
	gettimeofday(&current_time, NULL);
	phil->time_since_eaten = current_time.tv_sec * 1000;
	return ;
}