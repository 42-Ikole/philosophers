/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_two.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 16:37:53 by ikole         #+#    #+#                 */
/*   Updated: 2021/01/26 14:48:24 by ingmar        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <semaphore.h>
# include <stdbool.h>

/*
** COLOR DEFINES
*/
# define COLOR_RED 		"\033[38;5;196m"
# define COLOR_GREEN	"\033[38;5;46m"
# define COLOR_BLUE 	"\033[38;5;51m"
# define COLOR_BLU		"\033[38;5;190m"
# define COLOR_ORANGE	"\033[38;5;214m"
# define COLOR_PURPLE	"\033[38;5;98m"
# define COLOR_YELLOW	"\033[38;5;220m"
# define COLOR_PINK		"\033[38;5;205m"
# define COLOR_YOS		"\033[38;5;226"

/*
** COLORED PIHLO MESSAGES
*/
# define MSG_EATING		"] \033[38;5;113mis eating\033[37m\n"
# define MSG_SLEEP		"] \033[38;5;117mis sleeping\033[37m\n"
# define MSG_PICK_FORK	"] \033[38;5;218mpicked up a fork\033[37m\n"
# define MSG_DROP_FORK	"] \033[38;5;166mdropped a fork\033[37m\n"
# define MSG_THINKING	"] \033[38;5;101mis thinking\033[37m\n"
# define MSG_DONE		"] \033[38;5;46mis done eating\033[37m\n"
# define MSG_APPEAR		"] \033[38;5;198mappeard for an epic feast\033[37m\n"
# define MSG_DIED		"] \033[38;5;196mdied\033[37m\n"

/*
** ERROR MESSAGES
*/
# define ERR_MISSARG	"\e[38;5;196mYou are missing some arguments\n"
# define ERR_PHILAMT	"\e[38;5;196mYou need atleast two philosophers\n"
# define ERR_TOOMANY	"\e[38;5;196mOver 200 philosophers is prohibited\n"
# define ERR_TTDIE		"\e[38;5;196mTime to die needs te be atleast 60ms\n"
# define ERR_TTEAT		"\e[38;5;196mTime to sleep needs te be atleast 60ms\n"
# define ERR_TTSLEEP	"\e[38;5;196mTime to eat needs te be atleast 60ms\n"
# define ERR_NOEAT		"\e[38;5;196mEating zero times is weird\n"
# define ERR_NAN		"\e[38;5;196mNOT A DIGIT <3 ABEL\n"
# define ERR_IMPOSSIBLE	"\e[38;5;220m<WARNING> \e[38;5;196mDeath is comming!\n"

typedef struct	s_data
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
}				t_data;

typedef struct	s_phil
{
	unsigned int	id;
	unsigned int	times_eaten;
	unsigned long	last_eaten;
	bool			done;
	sem_t			*eat;
	t_data			*data;
}				t_phil;

void			phil_stuff(void *v_phil);

/*
**	Init
*/
int				data_init(char **arg, t_data *data);
int				phil_init(t_phil *phil, int id, t_data *data);

/*
**	Helpers
*/
int				ft_strlen(char *str);
void			phil_msg(t_phil *phil, char *msg, bool force_write);
int				ft_atoi(char *nb);
void			zzz(unsigned long sleep_time);
bool			check_death(t_data *data);

/*
** TIME
*/
unsigned long	get_time(void);

/*
** Errors
*/
bool			error(char *msg);
bool			validate_input(char **arg, t_data *dat);

#endif
