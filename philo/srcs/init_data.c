/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:25:28 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/04 00:12:30 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	init_timer(void)
{
	struct timeval	start;
	long			sec;
	long			usec;
	long			time;
	
	gettimeofday(&start, NULL);
	sec = start.tv_sec;
	usec = start.tv_usec;
	time = (sec * 1000) + (usec / 1000);
	return (time);
}

int	init_forks(t_data *data, int num_forks)
{
	int	i;

	i = 0;
	while (i < num_forks)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philo_mutexes(pthread_mutex_t *last_meal, pthread_mutex_t *meals_num)
{
	if (pthread_mutex_init(last_meal, NULL) != 0)
		return (0);
	if (pthread_mutex_init(meals_num, NULL) != 0)
	{
		pthread_mutex_destroy(last_meal);
		return (0);
	}
	return (1);
}

int	init_philos(t_data *data, int num_philos)
{
	int		i;
	t_philo	*philo;

	data->philos = malloc(num_philos * sizeof(t_philo));
	if (!data->philos)
		return (0);
	i = 0;
	while (i < num_philos)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->meals_num = 0;
		philo->last_meal = data->start_time;
		philo->data = data;
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % num_philos];
		if (!init_philo_mutexes(&data->philos[i].last_meal_mutex, &data->philos[i].meals_num_mutex))
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
				pthread_mutex_destroy(&data->philos[i].meals_num_mutex);
			}
			free(data->philos);
			return (0);
		}
		i++;
	}
	return (1);
}

t_data	*init_data(t_args *args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = init_timer();
	data->death_flag = 0;
	data->args = *args;
	data->forks = malloc(args->num_of_forks * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		free(data);
		return (NULL);
	}
	if (!init_forks(data, args->num_of_forks))
	{
		free(data->forks);
		free(data);
		return (NULL);
	}
	if (!init_philos(data, args->num_of_philos))
	{
		destroy_forks_mutexes(data, args->num_of_forks);
		free(data->forks);
		free(data);
		return (NULL);
	}
	return (data);
}
