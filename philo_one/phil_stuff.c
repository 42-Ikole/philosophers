/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_stuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:20:42 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/16 14:14:45 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdbool.h>
#include <unistd.h>

static void state_sleep(t_phil *phil)
{
	phil_msg(phil, "is sleeping");
	usleep(phil->data->ttsleep);
}

static bool	take_forks(t_phil *phil, int l_fork, int r_fork)
{
	pthread_mutex_lock(&(phil->data->forks[r_fork]));
	if (phil->data->dead == true)
	{
		pthread_mutex_unlock(&(phil->data->forks[r_fork]));
		return (false);
	}
	phil_msg(phil, "has grabbed the fork on his right");
	pthread_mutex_lock(&(phil->data->forks[l_fork]));
	if (phil->data->dead == true)
	{
		pthread_mutex_unlock(&(phil->data->forks[r_fork]));
		pthread_mutex_unlock(&(phil->data->forks[l_fork]));
		return (false);
	}
	phil_msg(phil, "has grabbed the fork on his left");
	return (true);
}

static void	state_eat(t_phil *phil)
{
	if (take_forks(phil, phil->l_fork, phil->r_fork) == false)
		return ;
	pthread_mutex_lock(&(phil->eat));
	phil_msg(phil, "is eating");
	usleep(phil->data->tteat);
	phil->times_eaten++;
	pthread_mutex_unlock(&(phil->eat));
	pthread_mutex_unlock(&(phil->data->forks[phil->r_fork]));
	phil_msg(phil, "has dropped the fork on his right");
	pthread_mutex_unlock(&(phil->data->forks[phil->l_fork]));
	phil_msg(phil, "has dropped the fork on his left");
}

void		phil_stuff(void	*v_phil)
{
	t_phil *phil;

	phil = (t_phil*)v_phil;
	phil_msg(phil, "appeard for an epic feast");
	while (phil->data->dead == false)
	{
		phil_msg(phil, "is thinking");
		if (phil->data->dead == true)
			break ;
		state_eat(phil);
		if (phil->data->dead == true)
			break ;
		if (phil->times_eaten > 0 && phil->times_eaten == phil->data->must_eat)
		{
			phil_msg(phil, "is done eating");
			phil->data->done_eating++;
			break ;
		}
		state_sleep(phil);
	}
	printf("wazap\n");
}
