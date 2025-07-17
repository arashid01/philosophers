/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:48:01 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/17 03:48:33 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	*allocate_data_struct(t_args *args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->start_time = init_timer();
	data->stop_flag = 0;
	data->ready_flag = 0;
	data->meals_eaten = 0;
	data->args = *args;
	return (data);
}

int	allocate_forks(t_data *data, t_args *args)
{
	data->forks = malloc(args->num_of_forks * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	return (1);
}

void	cleanup_on_forks_fail(t_data *data)
{
	free(data->forks);
	free(data);
}

void	cleanup_on_philos_fail(t_data *data, t_args *args)
{
	destroy_forks_mutexes(data, args->num_of_forks);
	free(data->forks);
	free(data);
}

void	cleanup_on_mutexes_fail(t_data *data, t_args *args)
{
	destroy_forks_mutexes(data, args->num_of_forks);
	destroy_philo_mutexes(data, args->num_of_philos);
	free(data->forks);
	free(data->philos);
	free(data);
}
