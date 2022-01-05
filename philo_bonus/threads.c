/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:48:12 by oronda            #+#    #+#             */
/*   Updated: 2022/01/01 13:11:26 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_processes(t_data *data)
{
	int		i;
	int		return_state;
	t_philo	*current;

	i = 0;
	while (i < data->nb_of_philo)
	{
		waitpid(-1, &return_state, 0);
		if (return_state != 0)
		{
			i = -1;
			current = data->philos;
			while (++i < data->nb_of_philo)
			{
				kill(current->pid, 15);
				current = current->next;
			}
			break ;
		}
		i++;
	}
}
