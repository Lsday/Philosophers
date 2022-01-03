/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:48:12 by oronda            #+#    #+#             */
/*   Updated: 2021/12/30 12:55:22 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo *current, t_data *data)
{
	int	i;

	i = 0;
	while (current->next && i < data->nb_of_philo)
	{
		pthread_create(&current->thread, NULL, &philo_main, current);
		current->last_eat = get_time();
		current = current->next;
		i++;
	}
}

void	join_threads(t_philo *current, t_data *data)
{
	int	i;

	i = 0;
	while (current->next && i < data->nb_of_philo)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
		i++;
	}
}
