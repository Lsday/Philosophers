/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:40:07 by oronda            #+#    #+#             */
/*   Updated: 2021/12/30 12:41:17 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_new_philo(t_data *data)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->data = data;
	philo->next = NULL;
	philo->fork.is_available = TRUE;
	pthread_mutex_init(&philo->fork.mutex, NULL);
	philo->current_eat_nb = 0;
	philo->data->is_dead = FALSE;
	return (philo);
}

t_philo	*getlast(t_philo *lst)
{
	t_philo	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_new_philo(t_data *data)
{
	t_philo	*philo;

	philo = NULL;
	if (!data->philos)
		data->philos = create_new_philo(data);
	else
	{
		philo = getlast(data->philos);
		philo->next = create_new_philo(data);
	}
}
