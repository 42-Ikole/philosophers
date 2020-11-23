/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destruction.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 13:06:28 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/23 13:10:11 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>

void		destroy_mutex(pthread_mutex_t *fuck)
{
	if (pthread_mutex_destroy(fuck))
		pthread_mutex_unlock(fuck);
	pthread_mutex_destroy(fuck);
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
