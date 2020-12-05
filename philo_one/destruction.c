/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destruction.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 13:06:28 by ikole         #+#    #+#                 */
/*   Updated: 2020/12/05 13:44:39 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>

void		destroy_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
		pthread_mutex_unlock(mutex);
	pthread_mutex_destroy(mutex);
}

void		destroy_mutex_babies(pthread_mutex_t *forks, int i)
{
	while (i > 0)
	{
		i--;
		destroy_mutex(&forks[i]);
	}
	free(forks);
}
