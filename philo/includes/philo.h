/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:22:01 by amal              #+#    #+#             */
/*   Updated: 2025/07/17 03:50:17 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

typedef struct s_args
{
	int	num_of_philos;
	int	num_of_forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_meals;
}	t_args;

typedef struct s_data
{
	int				stop_flag;
	int				ready_flag;
	int				meals_eaten;
	long			start_time;
	t_args			args;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t ready_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_num;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lm_mutex;
	pthread_mutex_t	nmeals;
	t_data			*data;
}	t_philo;

int		ft_atoi(char *nbr);
int		ft_strlen(char *str);
int		correct_args(int argc, char **argv);
int		parse_args(int argc, char **argv, t_args *args);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
t_data	*init_data(t_args *args);
long	init_timer(void);
int		init_forks(t_data *data, int num_forks);
void	destroy_data(t_data *data);
void	destroy_philo_mutexes(t_data *data, int num_philos);
void	destroy_forks_mutexes(t_data *data, int num_forks);
long	current_time(long start_time);
int		create_philos_threads(t_data *data);
void	join_philos_threads(t_data *data);
void	*philo_routine(void *arg);
void	print_status(t_philo *philo, const char *str);
void	ft_sleep(t_philo *philo, int time);
int		check_stop_flag(t_philo *philo);
void	*monitor_routine(void *data);
void	pick_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
t_data	*allocate_data_struct(t_args *args);
int		allocate_forks(t_data *data, t_args *args);
void	cleanup_on_mutexes_fail(t_data *data, t_args *args);
void	cleanup_on_philos_fail(t_data *data, t_args *args);
void	cleanup_on_forks_fail(t_data *data);
void	wait_for_all_threads(t_data *data);

#endif
