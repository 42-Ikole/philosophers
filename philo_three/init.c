/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:48:42 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/22 17:05:45 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include "colors.h"
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

static int init_semaphore(t_data *data)
{
	data->forks = sem_open("phil_forks", O_CREAT | O_EXCL, 0644, data->phil_amount);
	if (data->forks == SEM_FAILED)
		return (1);
	sem_unlink("phil_forks");
	data->write = sem_open("phil_write", O_CREAT | O_EXCL, 0644, 1);
	if (data->write == SEM_FAILED)
		return (1);
	sem_unlink("phil_write");
	data->die_lock = sem_open("phil_die_lock", O_CREAT | O_EXCL, 0644, 1);
	if (data->die_lock == SEM_FAILED)
		return (1);
	sem_unlink("phil_die_lock");
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
	data->done_eating = 0;
	data->dead = false;
	if (arg[5])
		data->must_eat = atoi(arg[5]);
	else
		data->must_eat = 0;
	if (init_semaphore(data) == 1)
		return (1);
	return (0);
}

int	phil_init(t_phil *phil, int id, t_data *data)
{
	phil->id = id;
	phil->times_eaten = 0;
	phil->last_eaten = get_time();
	phil->eat = sem_open("phil_eat", O_CREAT, 0644, 1);
	if (phil->eat == SEM_FAILED)
		return (1);
	sem_unlink("phil_eat");
	phil->done = false;
	phil->data = data;
	return (0);
}
