/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:33:39 by oronda            #+#    #+#             */
/*   Updated: 2022/01/05 10:59:45 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "limits.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i != argc)
	{
		if (!is_num(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	range(long nb)
{
	if (nb > INT_MAX)
		return (0);
	if (nb <= 0)
		return (0);
	return (1);
}

int	init_args(int argc, char **argv, t_data *data)
{	
	if ((!range(ft_atoi(argv[1])) || !range(ft_atoi(argv[2]))
			|| !range(ft_atoi(argv[3])) || !range(ft_atoi(argv[4]))))
		return (0);
	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (!range(ft_atoi(argv[5])))
			return (0);
		data->must_eat_nb = ft_atoi(argv[5]);
	}		
	else
		data->must_eat_nb = -1;
	return (1);
}
