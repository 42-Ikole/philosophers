/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:35:14 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/23 17:03:43 by ikole         ########   odam.nl         */
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

static void	guillotine(pid_t *pid, int i)
{
	while (i > 0)
	{
		i--;
		kill(pid[i], SIGKILL);
	}
}

static void	wait_phil(t_data *data, t_phil *phil, pid_t *pid)
{
	unsigned int	i;
	int				status;

	i = 0;
	while (i < data->phil_amount)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WEXITSTATUS(status) == 1)
			return (guillotine(pid, data->phil_amount));
		i++;
	}
	ft_destruction(phil, data, pid);
}

static void	create_threads(t_data *data)
{
	pid_t			*pid;
	t_phil			*phil;
	unsigned int	i;

	pid = malloc(sizeof(pid_t) * data->phil_amount);
	phil = malloc(sizeof(t_phil) * data->phil_amount);
	if (!pid || !phil)
		return ;
	i = 0;
	while (i < data->phil_amount)
	{
		if (phil_init(&(phil[i]), i, data))
			return (guillotine(pid, i));
		pid[i] = fork();
		if (pid[i] < 0)
			return (guillotine(pid, i));
		if (pid[i] == 0)
			monitor(&phil[i]);
		usleep(100);
		i++;
	}
	wait_phil(data, phil, pid);
}

int			main(int argc, char **argv)
{
	t_data	data;

	if (!(argc == 5 || argc == 6))
		return (1);
	if (data_init(argv, &data))
		return (1);
	create_threads(&data);
	return (0);
}
