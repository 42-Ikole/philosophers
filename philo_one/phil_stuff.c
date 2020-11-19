/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_stuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:20:42 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/16 17:35:12 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdbool.h>
#include <unistd.h>

static void state_sleep(t_phil *phil)
{
	phil_msg(phil, "is sleeping", false);
	zzz(phil->data->ttsleep);
}

static bool	take_forks(t_phil *phil, int l_fork, int r_fork)
{
	pthread_mutex_lock(&(phil->data->forks[r_fork]));
	if (phil->data->dead == true)
	{
		pthread_mutex_unlock(&(phil->data->forks[r_fork]));
		return (false);
	}
	phil_msg(phil, "has grabbed a fork", false);
	pthread_mutex_lock(&(phil->data->forks[l_fork]));
	if (phil->data->dead == true)
	{
		pthread_mutex_unlock(&(phil->data->forks[r_fork]));
		pthread_mutex_unlock(&(phil->data->forks[l_fork]));
		return (false);
	}
	phil_msg(phil, "has grabbed a fork", false);
	return (true);
}

static void	state_eat(t_phil *phil)
{
	if (take_forks(phil, phil->l_fork, phil->r_fork) == false)
		return ;
	pthread_mutex_lock(&(phil->eat));
	phil_msg(phil, "is eating", false);
	phil->times_eaten++;
	phil->last_eaten = get_time();
	pthread_mutex_unlock(&(phil->eat));
	zzz(phil->data->tteat);
	pthread_mutex_unlock(&(phil->data->forks[phil->r_fork]));
	phil_msg(phil, "has dropped a fork", false);
	pthread_mutex_unlock(&(phil->data->forks[phil->l_fork]));
	phil_msg(phil, "has dropped a fork", false);
}

void		phil_stuff(void	*v_phil)
{
	t_phil *phil;

	phil = (t_phil*)v_phil;
	phil_msg(phil, "appeard for an epic feast", false);
	while (1)
	{
		phil_msg(phil, "is thinking", false);
		if (phil->data->dead == true)
			break ;
		state_eat(phil);
		if (phil->data->dead == true)
			break ;
		if (phil->times_eaten > 0 && phil->times_eaten == phil->data->must_eat)
		{
			phil_msg(phil, "is done eating", false);
			phil->data->done_eating++;
			break ;
		}
		state_sleep(phil);
	}
}
