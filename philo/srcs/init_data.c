/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amal <amal@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:25:28 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/03 22:40:35 by amal             ###   ########.fr       */
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
			return (-1);
		}
		i++;
	}
	return (0);
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
	if (init_forks(data, args->num_of_forks) != 0)
	{
		free(data->forks);
		free(data);
		return (NULL);
	}
	return (data);
}
