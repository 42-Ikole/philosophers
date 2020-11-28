/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:35:14 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/28 13:45:49 by ikole         ########   odam.nl         */
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
	free(data->colors);
	if (pid)
		free(pid);
	if (phil)
		free(phil);
}

static void	guillotine(pid_t *pid, int i)
{
	while (i > 0)
	{
		i--;
		kill(pid[i], BEHEAD);
	}
}

static void	wait_phil(t_data *data, pid_t *pid)
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
}

static void	create_processes(t_data *data, pid_t *pid, t_phil *phil)
{
	unsigned int	i;

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
	wait_phil(data, pid);
}

int			main(int argc, char **argv)
{
	t_data	data;
	pid_t	*pid;
	t_phil	*phil;

	if (!(argc == 5 || argc == 6))
		return (1);
	if (data_init(argv, &data))
		return (1);
	pid = malloc(sizeof(pid_t) * data.phil_amount);
	phil = malloc(sizeof(t_phil) * data.phil_amount);
	if (pid && phil)
		create_processes(&data, pid, phil);
	ft_destruction(phil, &data, pid);
	return (0);
}
