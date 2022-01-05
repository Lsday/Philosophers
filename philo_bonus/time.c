/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:38:34 by oronda            #+#    #+#             */
/*   Updated: 2021/12/30 19:52:13 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_time_diff(long past, long current)
{
	return (current - past);
}

void	ft_wait(long time, t_data *data)
{
	long	start;

	start = get_time();
	while (!data->is_dead)
	{
		if (get_time_diff(start, get_time()) >= time)
			break ;
		usleep(10);
	}
}
