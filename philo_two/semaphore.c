
#include "two.h"
#include <semaphore.h>

void	create_semaphores(t_stats *stats)
{
	sem_unlink("chopsticks");
	stats->chopsticks = sem_open("chopsticks", O_CREAT | O_EXCL, 0666, stats->phil_amount);
	if (stats->chopsticks == SEM_FAILED)
		return ;
	sem_unlink("write");
	stats->write = sem_open("write", O_CREAT | O_EXCL, 0666, 1);
	if (stats->write == SEM_FAILED)
		return ;
}