/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:46:01 by oronda            #+#    #+#             */
/*   Updated: 2022/01/03 10:56:30 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chech_eat(t_philo *philo)
{
	if (philo->data->must_eat_nb != -1
		&& philo->current_eat_nb >= philo->data->must_eat_nb)
		return (0);
	return (1);
}

void	*check_death(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)arg;
	philo = data->philos;
	while (!data->is_dead)
	{
		while (philo)
		{
			if (!chech_eat(philo))
				return (NULL);
			pthread_mutex_lock(&data->eat_mutex);
			if (get_time_diff(philo->last_eat, get_time()) > data->time_to_die)
			{
				print_msg(philo->data, philo->philo_id, "is dead");
				pthread_mutex_unlock(&philo->fork.mutex);
				data->is_dead = TRUE;
			}
			pthread_mutex_unlock(&data->eat_mutex);
			if (data->is_dead)
				return (NULL);
			philo = philo->next;
		}
	}
	return (NULL);
}

void	start_philos(t_data *data)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = data->philos;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	data->starttime = get_time();
	create_threads(current, data);
	check_death(data);
	current = data->philos;
	join_threads(current, data);
	while (current->next && i < data->nb_of_philo)
	{	
		pthread_mutex_destroy(&current->fork.mutex);
		current = current->next;
		i++;
	}
	pthread_mutex_destroy(&data->write);
}

void	free_philos(t_data *data)
{
	t_philo	*current;
	t_philo	*next;
	int		i;

	i = -1;
	current = data->philos;
	while (++i < data->nb_of_philo)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!check_args(argc, argv))
		return (print_error("args not valid"));
	init_args(argc, argv, &data);
	init_philos(&data);
	start_philos(&data);
	free_philos(&data);
	return (0);
}
