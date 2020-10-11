
#include "one.h"
#include <pthread.h>
#include "unistd.h"
#include "stdio.h" //

int		eat(t_phil *phil)
{
	int lc;
	int rc;
	int	status;

	if (phil->stats->dead == true)
		return (-1);
	lc = phil->id + 1;
	rc = phil->id - 1;
	if (lc > phil->stats->phil_amount)
		lc = 0;
	if (rc < 0)
		rc = phil->stats->phil_amount - 1;
	status = pthread_mutex_trylock(&(phil->stats->chopsticks[lc]));
	if (status)
		return (-1);
	printf("%i has taken fork\n", phil->id);
	status = pthread_mutex_trylock(&(phil->stats->chopsticks[rc]));
	if (status)
	{
		pthread_mutex_unlock(&(phil->stats->chopsticks[lc]));
		printf("%i has dropped fork\n", phil->id);
	}
	printf("%i has taken fork\n", phil->id);
	usleep(phil->stats->time_to_eat);
	pthread_mutex_unlock(&(phil->stats->chopsticks[lc]));
	printf("%i has dropped fork\n", phil->id);
	pthread_mutex_unlock(&(phil->stats->chopsticks[rc]));
	printf("%i has dropped fork\n", phil->id);
	return (0);
}