/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:37:19 by oronda            #+#    #+#             */
/*   Updated: 2021/12/30 12:41:13 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_data *data, int id, char *string)
{
	pthread_mutex_lock(&data->write);
	if (!(data->is_dead))
	{
		printf("%ld ", get_time() - data->starttime);
		printf("%d ", id);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(data->write));
	return ;
}

int	print_error(char *str)
{
	printf("%s\n", str);
	return (0);
}
