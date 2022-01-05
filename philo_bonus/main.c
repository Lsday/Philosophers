/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:46:01 by oronda            #+#    #+#             */
/*   Updated: 2022/01/05 10:58:34 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{	
		sem_wait(philo->data->eat_check);
		if (get_time_diff(philo->last_eat, get_time())
			> philo->data->time_to_die)
		{
			print_msg(philo->data, philo->philo_id, "is dead");
			philo->data->is_dead = TRUE;
			sem_wait(philo->data->write);
			exit(1);
		}
		sem_post(philo->data->eat_check);
		if (philo->data->is_dead)
			break ;
		if (philo->data->must_eat_nb != -1
			&& philo->current_eat_nb >= philo->data->must_eat_nb)
			break ;
		usleep(10);
	}
	return (NULL);
}

int	start_philos(t_data *data)
{
	int		i;
	t_philo	*current;

	i = -1;
	current = data->philos;
	data->starttime = get_time();
	while (++i < data->nb_of_philo)
	{
		current->pid = fork();
		if (current->pid < 0)
			return (0);
		if (current->pid == 0)
			philo_main(current);
		else if (current->pid > 0)
			current = current->next;
		usleep(100);
	}
	return (1);
}

void	clean_sems(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->write);
	sem_close(data->eat_check);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("eatcheck");
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
	if (!init_args(argc, argv, &data))
		return (print_error("args not valid"));
	init_sems(&data);
	init_philos(&data);
	if (!start_philos(&data))
		return (print_error("error when starting the child processes"));
	wait_processes(&data);
	free_philos(&data);
	return (0);
}
