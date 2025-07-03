/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:22:01 by amal              #+#    #+#             */
/*   Updated: 2025/07/03 22:41:07 by amal             ###   ########.fr       */
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

typedef struct s_args {
	int	num_of_philo;
	int	num_of_forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_meals;
}	t_args;

typedef struct s_data {
	long			start_time;
	int				death_flag;
	int				meals_eaten;
	t_args			args;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_mutex;
	struct s_philo	*philos;
} t_data;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_num;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meals_num_mutex;
	t_data			*data;
} t_philo;

int		ft_atoi(char *nbr);
int		ft_strlen(char *str);
int		correct_args(int argc, char **argv);
void	ft_putendl_fd(char *str, int fd);
t_data	*init_data(t_args *args);
int		init_forks(t_data *data, int num_forks);

#endif