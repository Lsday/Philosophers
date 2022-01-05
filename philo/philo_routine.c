/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:45:39 by oronda            #+#    #+#             */
/*   Updated: 2022/01/03 10:58:44 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = NULL;
	while (i < data->nb_of_philo)
	{
		add_new_philo(data);
		getlast(data->philos)->philo_id = i + 1;
		i++;
	}
	getlast(data->philos)->next = data->philos;
}

int	philo_eat(t_philo *philo)
{	
	if (philo->data->is_dead)
		return (-1);
	while (!philo->fork.is_available && !philo->next->fork.is_available)
		usleep(1);
	pthread_mutex_lock(&philo->fork.mutex);
	pthread_mutex_lock(&philo->next->fork.mutex);
	philo->fork.is_available = FALSE;
	philo->next->fork.is_available = FALSE;
	print_msg(philo->data, philo->philo_id, "has taken a fork");
	print_msg(philo->data, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&philo->data->eat_mutex);
	print_msg(philo->data, philo->philo_id, "is eating");
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->eat_mutex);
	ft_wait(philo->data->time_to_eat, philo->data);
	philo->current_eat_nb++;
	pthread_mutex_unlock(&philo->fork.mutex);
	pthread_mutex_unlock(&philo->next->fork.mutex);
	philo->fork.is_available = TRUE;
	philo->next->fork.is_available = TRUE;
	return (0);
}

int	philo_sleep(t_philo *philo)
{	
	print_msg(philo->data, philo->philo_id, "is sleeping");
	ft_wait(philo->data->time_to_sleep, philo->data);
	return (0);
}

int	philo_think(t_philo *philo)
{	
	print_msg(philo->data, philo->philo_id, "is thinking");
	return (0);
}

void	*philo_main(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->is_dead)
	{
		if (philo_eat(philo) == -1)
			return (NULL);
		if (philo->data->must_eat_nb != -1
			&& philo->current_eat_nb >= philo->data->must_eat_nb)
			return (NULL);
		if (philo_sleep(philo) == -1)
			return (NULL);
		if (philo_think(philo) == -1)
			return (NULL);
	}
	return (NULL);
}
