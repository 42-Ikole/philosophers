/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:37:53 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/15 17:46:18 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>

typedef struct  s_data
{
    unsigned int	phil_amount;
	unsigned int	ttdie;
	unsigned int	tteat;
	unsigned int	ttsleep;
	unsigned int	must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}               t_data;

typedef struct	s_phil
{
	unsigned int	id;
	unsigned int	times_eaten;
	unsigned int	last_eaten;
	pthread_mutex_t	eat;
	t_data			*data;
}				t_phil;

int				data_init(char **, t_data *);
int				ft_atoi(char *);
void			phil_stuff(t_phil *);
int				phil_init(t_phil *, int, t_data *);
unsigned long	get_time();

#endif
