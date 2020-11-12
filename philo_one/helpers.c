
#include "one.h"
#include "unistd.h"
#include <sys/time.h>


unsigned long get_time()
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void		check_death(t_phil *phil)
{
	unsigned long time;

	time = get_time();
	if (time - phil->time_since_eaten >= phil->stats->time_to_die &&
		(phil->times_eaten <= 0 || phil->times_eaten < phil->stats->must_eat))
	{
		phil_msg(phil, "has died from starvation");
		phil->stats->dead = true;
	}
}

static int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_putnbr(unsigned long n)
{
	char print[1];

	if (n > 10)
		ft_putnbr(n / 10);
	*print = n % 10 + 48;
	write(1, print, 1);
}

void	phil_msg(t_phil *phil, char *msg)
{
	unsigned long	kut;

	pthread_mutex_lock(&(phil->stats->write));
	kut = get_time();
	if (phil->stats->dead == false)
	{
		ft_putnbr(kut - phil->stats->start);
		write(1, " [", 2);
		ft_putnbr(phil->id);
		write(1, "] ", 2);
		write(1, msg, ft_strlen(msg));
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&(phil->stats->write));
}

int	ft_atoi(char *str)
{
	long res;
	long sgn;

	res = 0;
	sgn = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45)
		sgn = -1;
	if (*str == 43 || *str == 45)
		str++;
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return ((int)(res * sgn));
}
