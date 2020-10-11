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
