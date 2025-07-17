/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:25:28 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/15 20:18:10 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	init_pmutexes(pthread_mutex_t *last_meal, pthread_mutex_t *meals_num)
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
		philo->last_meal = 0;
		philo->data = data;
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % num_philos];
		if (!init_pmutexes(&data->philos[i].lm_mutex, &data->philos[i].nmeals))
		{
			destroy_philo_mutexes(data, i);
			free(data->philos);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_shared_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->meals_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->death_mutex);
		return (0);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->meals_mutex);
		return (0);
	}
	return (1);
}

t_data	*init_data(t_args *args)
{
	t_data	*data;

	data = allocate_data_struct(args);
	if (!data || !allocate_forks(data, args))
	{
		if (data)
			free(data);
		return (NULL);
	}
	if (!init_forks(data, args->num_of_forks))
	{
		cleanup_on_forks_fail(data);
		return (NULL);
	}
	if (!init_philos(data, args->num_of_philos))
	{
		cleanup_on_philos_fail(data, args);
		return (NULL);
	}
	if (!init_shared_mutexes(data))
	{
		cleanup_on_mutexes_fail(data, args);
		return (NULL);
	}
	return (data);
}
