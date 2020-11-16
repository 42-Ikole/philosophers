/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:52:58 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/16 11:54:50 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <sys/time.h>
#include <pthread.h>

unsigned long	get_time()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

static int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void			phil_msg(t_phil *phil, char *msg)
{
	unsigned long	time;

	if (phil->data->dead == false)
	{
		pthread_mutex_lock(&(phil->data->write));
		time = get_time();
		ft_putnbr(time - phil->data->start_time);
		write(1, " [", 2);
		ft_putnbr(phil->id);
		write(1, "] ", 2);
		write(1, msg, ft_strlen(msg));
		write(1, "\n", 1);
		pthread_mutex_unlock(&(phil->data->write));
	}
}

int				ft_atoi(char *str)
{
	int	nb;
	int	sgn;
	int i;

	nb = 0;
	sgn = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		sgn = -1;
	while (str[i])
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * sgn);
}
