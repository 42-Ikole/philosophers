/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_two.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:35:14 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/28 15:41:56 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

static void		ft_destruction(t_phil *phil, t_data *data, pthread_t *threads)
{
	free(data->colors);
	if (threads)
		free(threads);
	if (phil)
		free(phil);
}

static void		monitor(t_phil *phil)
{
	unsigned int	i;
	unsigned long	time;

	i = 0;
	while (i < phil->data->phil_amount)
	{
		sem_wait(phil[i].eat);
		time = get_time();
		if (time - phil[i].last_eaten >= phil->data->ttdie &&
			phil[i].done == false)
		{
			sem_wait(phil->data->die_lock);
			phil->data->dead = true;
			sem_post(phil->data->die_lock);
			phil_msg(&(phil[i]), MSG_DIED, true);
			sem_post(phil[i].eat);
			break ;
		}
		sem_post(phil[i].eat);
		if (phil->data->done_eating == phil->data->phil_amount)
			break ;
		i++;
		if (i == phil->data->phil_amount)
			i = 0;
	}
}

static void		join_threads(pthread_t *threads, int i)
{
	while (i > 0)
	{
		i--;
		pthread_join(threads[i], NULL);
	}
}

static void		create_threads(t_data *data, pthread_t *threads, t_phil *phil)
{
	unsigned int	i;

	i = 0;
	while (i < data->phil_amount)
	{
		if (phil_init(&(phil[i]), i, data))
			return (join_threads(threads, i));
		if (pthread_create(&(threads[i]), NULL, (void*)phil_stuff, &(phil[i])))
			return (join_threads(threads, i));
		i++;
	}
	monitor(phil);
	join_threads(threads, data->phil_amount);
}

int				main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;
	t_phil		*phil;

	if (!(argc == 5 || argc == 6))
		return (1);
	if (data_init(argv, &data))
		return (1);
	threads = malloc(sizeof(pthread_t) * data.phil_amount);
	phil = malloc(sizeof(t_phil) * data.phil_amount);
	if (threads && phil)
		create_threads(&data, threads, phil);
	ft_destruction(phil, &data, threads);
	return (0);
}
