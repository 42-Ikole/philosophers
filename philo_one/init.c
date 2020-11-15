/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:48:42 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/15 17:46:25 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <pthread.h>
#include <stdlib.h>

int	data_init(char **arg, t_data *data)
{
	int	i;

	data->phil_amount = atoi(arg[1]);
	data->ttdie = atoi(arg[2]) * 1000;
	data->tteat = atoi(arg[3]) * 1000;
	data->ttsleep = atoi(arg[4]) * 1000;
	if (arg[5])
		data->must_eat = atoi(arg[5]);
	else
		data->must_eat = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->phil_amount);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->phil_amount)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(data->write), NULL))
		return (1);
	return (0);
}

int	phil_init(t_phil *phil, int id, t_data *data)
{
	phil->id = id;
	phil->times_eaten = 0;
	phil->last_eaten = get_time();
	if (pthread_mutex_init(&(phil->eat))
		return (1);
	phil->data = data;
	return (0);
}
