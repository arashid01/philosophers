/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:45:41 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/17 03:01:13 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	join_partial_threads(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			ft_putendl_fd("Error: Failed to join thread", 2);
		i++;
	}
}

int	create_philos_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.num_of_philos)
	{
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].thread,
				NULL, &philo_routine, &data->philos[i]) != 0)
		{
			join_partial_threads(data, i);
			destroy_philo_mutexes(data, i);
			free(data->philos);
			return (0);
		}
		i++;
	}
	return (1);
}

void	join_philos_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			ft_putendl_fd("Error: Failed to join thread", 2);
		i++;
	}
}
