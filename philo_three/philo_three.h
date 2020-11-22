/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:37:53 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/22 20:12:45 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include "colors.h"
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h> //

# define MSG_EATING "] " COLOR_EATING "is eating" COLOR_RESET "\n"
# define MSG_SLEEP "] " COLOR_SLEEPING "is sleeping" COLOR_RESET "\n"
# define MSG_PICK_FORK "] " COLOR_PICK_FORK "picked up a fork" COLOR_RESET "\n"
# define MSG_DROP_FORK "] " COLOR_DROP_FORK "dropped a fork" COLOR_RESET "\n"
# define MSG_THINKING "] " COLOR_THINKING "is thinking" COLOR_RESET "\n"
# define MSG_DONE "] " COLOR_GREEN "is done eating" COLOR_RESET "\n"
# define MSG_APPEAR "] " COLOR_APPEAR "appeard for an epic feast" COLOR_RESET "\n"
# define MSG_DIED "] " COLOR_RED "died" COLOR_RESET "\n"

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
	sem_t			*die_lock;
	sem_t			*forks;
	sem_t			*write;
}               t_data;

typedef struct	s_phil
{
	unsigned int	id;
	unsigned int	times_eaten;
	unsigned long	last_eaten;
	bool			done;
	sem_t			*eat;
	t_data			*data;
}				t_phil;

void			monitor(t_phil *);

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
bool			check_death(t_data *);

#endif
