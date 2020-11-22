/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:35:14 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/22 19:58:06 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <signal.h>

static void	ft_destruction(t_phil *phil, t_data *data, pid_t *pid)
{
	unsigned int i;

	sem_close(data->write);
	sem_close(data->die_lock);
	i = 0;
	while (i < data->phil_amount)
	{
		sem_close(phil[i].eat);
		sem_close(data->forks);
		i++;
	}
	free(pid);
	free(data->colors);
}

static void guillotine(pid_t *pid, int i)
{
	while (i > 0)
	{
		i--;
		kill(pid[i], SIGKILL);
	}
}

static void	create_threads(t_data *data)
{
	pid_t			*pid;
	t_phil			*phil;
	unsigned int	i;
	int				status;
	
	pid = malloc(sizeof(pid_t) * data->phil_amount);
	phil = malloc(sizeof(t_phil) * data->phil_amount);
	if (!pid || !phil)
		return ;
	i = 0;
	while (i < data->phil_amount)
	{
		if (phil_init(&(phil[i]), i, data))
			return (guillotine(pid, i));
		printf("[%i] - before = [%lu]\n", i, get_time() - data->start_time);
		pid[i] = fork();
		printf("[%i] - eftoer = [%lu]\n", i, get_time() - data->start_time);
		// if (pid[i] < 0)÷
		if (pid[i] == 0)
			phil_stuff(&phil[i]);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->phil_amount)
	{
		waitpid(-1, &status, WUNTRACED);
		if (status == 1)
		{
			guillotine(pid, data->phil_amount);
			break ;
		}
		i++;
	}
	ft_destruction(phil, data, pid);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (!(argc == 5 || argc == 6))
		return (1);
	if (data_init(argv, &data))
		return (1);
	create_threads(&data);
    return (0);
}
