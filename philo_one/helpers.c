#include "one.h"

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

void	sort_philosophers(t_stats *stats)
{
	register int	i;
	register int	j;
	register int	*tmp;

	i = 0;
	while (i < stats->phil_amount)
	{
		j = i + 1;
		while (j < stats->phil_amount)
		{
			if (stats->queue[i][1] < stats->queue[j][1])
			{
				tmp = stats->queue[i];
				stats->queue[i] = stats->queue[j];
				stats->queue[j] = tmp;
			}
			j++;
		}
		i++;
	}
}