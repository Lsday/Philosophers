/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:57:24 by oronda            #+#    #+#             */
/*   Updated: 2022/01/03 10:57:27 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum s_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	t_bool			is_available;

}	t_fork;

typedef struct s_philo
{
	int				philo_id;
	struct s_philo	*next;
	struct s_data	*data;
	int				current_eat_nb;
	pthread_t		thread;
	t_fork			fork;
	long			last_eat;
}	t_philo;

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_nb;
	t_philo			*philos;
	long			starttime;
	pthread_mutex_t	*forks;
	t_bool			is_dead;
	pthread_mutex_t	write;
	pthread_mutex_t	eat_mutex;
	pthread_t		death_checker;

}	t_data;	

//UTILS
int		check_args(int argc, char **argv);
void	init_args(int argc, char **argv, t_data *data);
int		is_num(char *str);
int		ft_atoi(char *str);
int		print_error(char *str);
void	add_new_philo(t_data *data);
t_philo	*getlast(t_philo *lst);
t_philo	*create_new_philo(t_data *data);
void	init_philos(t_data *data);

void	print_msg(t_data *data, int id, char *string);
void	ft_wait(long time, t_data *data);
long	get_time_diff(long past, long current);
long	get_time(void);
void	*philo_main(void *arg);
void	create_threads(t_philo *current, t_data *data);
void	join_threads(t_philo *current, t_data *data);

#endif