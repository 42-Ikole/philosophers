
#include "two.h"
#include <semaphore.h>

void	create_semaphores(t_stats *stats)
{
	sem_unlink("chopsticks");
	stats->chopsticks = sem_open("chopsticks", O_CREAT | O_EXCL);
	if (stats->chopsticks == SEM_FAILED)
		return ;
	sem_unlink("write");
	stats->write = sem_open("write", O_CREAT | O_EXCL);
	if (stats->write == SEM_FAILED)
		return ;
	sem_unlink("eatsies");
	stats->eatsies = sem_open("eatsies", O_CREAT | O_EXCL);
	if (stats->eatsies == SEM_FAILED)
		return ;
}