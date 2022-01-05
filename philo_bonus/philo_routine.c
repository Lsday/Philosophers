/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:45:39 by oronda            #+#    #+#             */
/*   Updated: 2022/01/01 13:07:07 by oronda           ###   ########.fr       */
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

void	init_sems(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("eatcheck");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU,
			data->nb_of_philo);
	data->write = sem_open("write", O_CREAT | O_EXCL, S_IRWXU, 1);
	data->eat_check = sem_open("eatcheck", O_CREAT | O_EXCL, S_IRWXU, 1);
}

void	philo_eat(t_philo *philo)
{	
	sem_wait(philo->data->forks);
	print_msg(philo->data, philo->philo_id, "has taken a fork");
	sem_wait(philo->data->forks);
	print_msg(philo->data, philo->philo_id, "has taken a fork");
	sem_wait(philo->data->eat_check);
	print_msg(philo->data, philo->philo_id, "is eating");
	philo->last_eat = get_time();
	sem_post(philo->data->eat_check);
	ft_wait(philo->data->time_to_eat, philo->data);
	philo->current_eat_nb++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_main(t_philo *philo)
{
	philo->last_eat = get_time();
	pthread_create(&philo->check_death, NULL, &check_death, (void *)philo);
	while (!philo->data->is_dead)
	{
		philo_eat(philo);
		if (philo->data->must_eat_nb != -1
			&& philo->current_eat_nb >= philo->data->must_eat_nb)
			break ;
		print_msg(philo->data, philo->philo_id, "is sleeping");
		ft_wait(philo->data->time_to_sleep, philo->data);
		print_msg(philo->data, philo->philo_id, "is thinking");
	}
	pthread_join(philo->check_death, NULL);
	if (philo->data->is_dead)
		exit(1);
	exit(0);
}
