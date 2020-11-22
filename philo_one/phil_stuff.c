/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phil_stuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 17:20:42 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/22 12:02:48 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdbool.h>
#include <unistd.h>

static void state_sleep(t_phil *phil)
{
	phil_msg(phil, MSG_SLEEP, false);
	zzz(phil->data->ttsleep);
}

static bool	take_forks(t_phil *phil, int l_fork, int r_fork)
{
	pthread_mutex_lock(&(phil->data->forks[r_fork]));
	if (check_death(phil->data) == true)
	{
		pthread_mutex_unlock(&(phil->data->forks[r_fork]));
		return (false);
	}
	phil_msg(phil, MSG_PICK_FORK, false);
	pthread_mutex_lock(&(phil->data->forks[l_fork]));
	if (check_death(phil->data) == true)
	{
		pthread_mutex_unlock(&(phil->data->forks[r_fork]));
		pthread_mutex_unlock(&(phil->data->forks[l_fork]));
		return (false);
	}
	phil_msg(phil, MSG_PICK_FORK, false);
	return (true);
}

static void	state_eat(t_phil *phil)
{
	if (take_forks(phil, phil->l_fork, phil->r_fork) == false)
		return ;
	pthread_mutex_lock(&(phil->eat));
	phil_msg(phil, MSG_EATING, false);
	phil->times_eaten++;
	phil->last_eaten = get_time();
	pthread_mutex_unlock(&(phil->eat));
	zzz(phil->data->tteat);
	pthread_mutex_unlock(&(phil->data->forks[phil->r_fork]));
	phil_msg(phil, MSG_DROP_FORK, false);
	pthread_mutex_unlock(&(phil->data->forks[phil->l_fork]));
	phil_msg(phil, MSG_DROP_FORK, false);
}

void		phil_stuff(void	*v_phil)
{
	t_phil *phil;

	phil = (t_phil*)v_phil;
	phil_msg(phil, MSG_APPEAR, false);
	usleep(phil->id % 2 * 100);
	while (1)
	{
		phil_msg(phil, MSG_THINKING, false);
		if (check_death(phil->data) == true)
			break ;
		state_eat(phil);
		if (check_death(phil->data) == true)
			break ;
		if (phil->times_eaten > 0 && phil->times_eaten == phil->data->must_eat)
		{
			phil_msg(phil, MSG_DONE, false);
			phil->data->done_eating++;
			phil->done = true;
			break ;
		}
		state_sleep(phil);
	}
}
