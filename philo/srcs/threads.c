/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:45:41 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/15 19:16:28 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
