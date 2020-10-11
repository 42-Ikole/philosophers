
#include "one.h"
#include "unistd.h"
#include <sys/time.h>

static int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_putnbr(int n)
{
	char print[1];

	if (n == -2147483648)
	{
		ft_putnbr(-214748364);
		write(1, "8", 1);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	if (n > 10)
		ft_putnbr(n / 10);
	*print = n % 10 + 48;
	write(1, print, 1);
}

void	phil_msg(t_phil *phil, char *msg)
{
	struct timeval current_time;

	pthread_mutex_lock(&(phil->stats->write));
	gettimeofday(&current_time, NULL);
	ft_putnbr(current_time.tv_sec * 1000);
	write(1, " [", 2);
	ft_putnbr(phil->id);
	write(1, "] ", 2);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	pthread_mutex_unlock(&(phil->stats->write));
}

int	ft_atoi(char *str)
{
	long long res;
	long long sgn;

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
