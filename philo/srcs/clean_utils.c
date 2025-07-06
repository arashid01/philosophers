/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:01:26 by amal              #+#    #+#             */
/*   Updated: 2025/07/06 02:07:02 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_forks_mutexes(t_data *data, int num_forks)
{
	int i;

	i = 0;
	while (i < num_forks)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	destroy_philo_mutexes(t_data *data, int num_philos)
{
	int i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].last_meal_mutex);
		pthread_mutex_destroy(&data->philos[i].meals_num_mutex);
		i++;
	}
}

void	destroy_shared_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meals_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}

void	destroy_data(t_data *data)
{
	destroy_forks_mutexes(data, data->args.num_of_forks);
    free(data->forks);
    destroy_philo_mutexes(data, data->args.num_of_philos);
    free(data->philos);
	destroy_shared_mutexes(data);
    free(data);
}
