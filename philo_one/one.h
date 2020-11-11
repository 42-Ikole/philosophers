#ifndef ONE_H
# define ONE_H

#include <pthread.h>

typedef enum	e_bool
{
	true = 1,
	false = 0
}	t_bool;

typedef struct	s_stats
{
	unsigned int	phil_amount;
	unsigned int	time_to_die;
    unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat;
	t_bool			dead;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t write;
	pthread_mutex_t	*eatsies;
	unsigned long start;
}				t_stats;

typedef struct	s_phil
{
	unsigned int	id;
	unsigned long	time_since_eaten;
	unsigned int	times_eaten;
	unsigned int	l_chop;
	unsigned int	r_chop;
	t_stats			*stats;
}				t_phil;


int				ft_atoi(char *str);
void			state_eat(t_phil *phil);
void			state_sleep(t_phil *phil);
void			phil_msg(t_phil *phil, char *msg);
void			check_death(t_phil *phil);
int				stat_init(t_stats *stats, char **str, int argc);
void			phil_init(t_phil *phil, t_stats *stats, int id);
unsigned long	get_time();
void			take_chopstick(t_phil *phil);

#endif
