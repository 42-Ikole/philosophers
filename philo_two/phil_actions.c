
#include "two.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

void	state_sleep(t_phil *phil)
{
	if (phil->stats->dead == true)
		return ;
	phil_msg(phil, "is sleeping");
	usleep(phil->stats->time_to_sleep);
}

void	state_eat(t_phil *phil)
{
	sem_wait(phil->eatsies);
	phil_msg(phil, "is eating");
	usleep(phil->stats->time_to_eat);
	phil->time_since_eaten = get_time();
	sem_post(phil->eatsies);
	sem_post(phil->stats->chopsticks);
	phil_msg(phil, "has dropped a fork");
	sem_post(phil->stats->chopsticks);
	phil_msg(phil, "has dropped a fork");
	phil->times_eaten++;
}


void	take_chopstick(t_phil *phil)
{
	if (phil->stats->dead == true)
		return ;
	sem_wait(phil->stats->chopsticks);
	phil_msg(phil, "has taken a fork");
	if (phil->stats->dead == true)
	{
		sem_post(phil->stats->chopsticks);
		phil_msg(phil, "has dropped a fork");
		return ;
	}
	sem_wait(phil->stats->chopsticks);
	phil_msg(phil, "has taken a fork");
	if (phil->stats->dead == true)
	{
		sem_post(phil->stats->chopsticks);
		phil_msg(phil, "has dropped a fork");
		sem_post(phil->stats->chopsticks);
		phil_msg(phil, "has dropped a fork");
		return ;
	}
	state_eat(phil);
}
