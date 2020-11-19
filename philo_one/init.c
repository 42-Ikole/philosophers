/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:48:42 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/16 18:11:37 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include "colors.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static int init_mutex(t_data *data)
{
	unsigned int	i;

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

static int init_colors(t_data *data)
{
	data->colors = malloc(sizeof(char *) * 8);
	if (!data->colors)
		return (1);
	data->colors[0] = COLOR_RED;
	data->colors[1] = COLOR_GREEN;
	data->colors[2] = COLOR_BLUE;
	data->colors[3] = COLOR_BLU;
	data->colors[4] = COLOR_ORANGE;
	data->colors[5] = COLOR_PURPLE;
	data->colors[6] = COLOR_YELLOW;
	data->colors[7] = COLOR_PINK;
	return (0);
}

int	data_init(char **arg, t_data *data)
{
	data->phil_amount = atoi(arg[1]);
	if (data->phil_amount < 2)
	{
		write(2, "cmon man, we need atleast 2 philosophers?\n", 31);
		return (1);
	}
	if (init_colors(data))
		return (1);
	data->ttdie = atoi(arg[2]);
	data->tteat = atoi(arg[3]);
	data->ttsleep = atoi(arg[4]);
	data->start_time = get_time();
	data->dead = false;
	if (arg[5])
		data->must_eat = atoi(arg[5]);
	else
		data->must_eat = 0;
	if (init_mutex(data) == 1)
		return (1);
	return (0);
}

int	phil_init(t_phil *phil, int id, t_data *data)
{
	unsigned int	tmp;

	phil->id = id;
	phil->times_eaten = 0;
	phil->last_eaten = get_time();
	if (pthread_mutex_init(&(phil->eat), NULL))
		return (1);
	phil->done = false;
	phil->data = data;
	phil->l_fork = id + 1;
	phil->r_fork = id;
	if (phil->l_fork == data->phil_amount)
		phil->l_fork = 0;
	if (id % 2)
	{
		tmp = phil->l_fork;
		phil->l_fork = phil->r_fork;
		phil->r_fork = tmp;
	}
	return (0);
}
