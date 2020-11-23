/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ikole <ikole@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 12:56:20 by ikole         #+#    #+#                 */
/*   Updated: 2020/11/23 12:58:37 by ikole         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

unsigned long	get_time(void)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void			zzz(unsigned long to_sleep)
{
	unsigned long start;

	start = get_time();
	while (get_time() - start < to_sleep)
		usleep(100);
}
