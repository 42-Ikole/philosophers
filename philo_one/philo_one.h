/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:37:53 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/16 13:58:01 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h> //

typedef struct  s_data
{
    unsigned int	phil_amount;
	char			**colors;
	unsigned long	ttdie;
	unsigned int	tteat;
	unsigned int	ttsleep;
	unsigned int	must_eat;
	unsigned int	done_eating;
	unsigned long	start_time;
	bool			dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}               t_data;

typedef struct	s_phil
{
	unsigned int	id;
	unsigned int	times_eaten;
	unsigned long	last_eaten;
	unsigned int	l_fork;
	unsigned int	r_fork;
	bool			done;
	pthread_mutex_t	eat;
	t_data			*data;
}				t_phil;

void			phil_stuff(void *);

/*
**	Init
*/
int				data_init(char **, t_data *);
int				phil_init(t_phil *, int, t_data *);

/*
**	Helpers
*/
unsigned long	get_time();
void			phil_msg(t_phil *, char *, bool);
int				ft_atoi(char *);
void			zzz(unsigned long);

#endif
