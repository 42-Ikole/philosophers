/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:52:58 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/20 17:25:19 by ingmar        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include "colors.h"
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

void			zzz(unsigned long to_sleep)
{
	unsigned long start;

	start = get_time();
	while (get_time() - start < to_sleep)
		usleep(100);
}

unsigned long	get_time()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

static void	ft_putnbr(unsigned long n)
{
	char print[1];

	if (n >= 10)
		ft_putnbr(n / 10);
	*print = n % 10 + 48;
	write(1, print, 1);
}

static int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void			phil_msg(t_phil *phil, char *msg, bool force_write)
{
	unsigned long	time;

	pthread_mutex_lock(&(phil->data->write));
	if (phil->data->dead == false || force_write == true)
	{
		time = get_time();
		ft_putnbr(time - phil->data->start_time);
		write (1, phil->data->colors[phil->id % 8], ft_strlen(phil->data->colors[phil->id % 8]));
		write(1, " [", 2);
		ft_putnbr(phil->id);
		write(1, msg, ft_strlen(msg));
	}
	pthread_mutex_unlock(&(phil->data->write));
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
