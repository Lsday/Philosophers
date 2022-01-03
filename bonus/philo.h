/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oronda <oronda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:57:54 by oronda            #+#    #+#             */
/*   Updated: 2022/01/03 10:57:56 by oronda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef enum s_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_nb;
	struct s_philo	*philos;
	long			starttime;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*eat_check;
	t_bool			is_dead;
	pthread_t		death_checker;

}	t_data;	

typedef struct s_philo
{
	int				philo_id;
	struct s_philo	*next;
	t_data			*data;
	int				current_eat_nb;
	int				pid;
	long			last_eat;
	pthread_t		check_death;
}	t_philo;

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
void	philo_main(t_philo *philo);
void	create_processes(t_philo *current, t_data *data);
void	wait_processes(t_data *data);
void	philo_eat(t_philo *philo);
void	*check_death(void *arg);
void	init_sems(t_data *data);

#endif