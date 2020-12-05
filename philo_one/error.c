/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/05 15:24:01 by ikole         #+#    #+#                 */
/*   Updated: 2020/12/05 15:39:18 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "philo_one.h"

bool 		error(char *msg)
{
	write (2, msg, ft_strlen(msg));
	return (1);
}

static bool	is_nodigit(char *str)
{
	int i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

bool		validate_input(char **arg, t_data *dat)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if (is_nodigit(arg[i]) == 1)
			return (error(ERR_NAN));
		i++;
	}
	if (dat->phil_amount < 2)
		return (error(ERR_PHILAMT));
	if (dat->phil_amount > 200)
		return (error(ERR_TOOMANY));
	if (dat->ttdie < 60)
		return (error(ERR_TTDIE));
	if (dat->tteat < 60)
		return (error(ERR_TTEAT));
	if (dat->ttsleep < 60)
		return (error(ERR_TTSLEEP));
	if (arg[5] && dat->must_eat == 0)
		return (error(ERR_NOEAT));
	if (dat->ttdie <= (dat->tteat + dat->ttsleep) * (dat->phil_amount % 2 + 1))
		error(ERR_IMPOSSIBLE);
	return (0);
}
