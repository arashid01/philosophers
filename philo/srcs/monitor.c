/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:22:14 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/15 20:19:01 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	announce_death(t_philo *runner)
{
	if (runner->data->stop_flag == 0)
	{
		runner->data->stop_flag = 1;
		pthread_mutex_lock(&runner->data->print_mutex);
		printf("%ld %d died\n",
			current_time(runner->data->start_time), runner->id);
		pthread_mutex_unlock(&runner->data->print_mutex);
	}
}

static long	get_time_since_last_meal(t_philo *philo, t_data *data)
{
	long	last_time;

	pthread_mutex_lock(&philo->lm_mutex);
	last_time = current_time(data->start_time) - philo->last_meal;
	pthread_mutex_unlock(&philo->lm_mutex);
	return (last_time);
}

static int	check_philo_death(t_philo *philo, t_data *data)
{
	long	time_since_meal;

	time_since_meal = get_time_since_last_meal(philo, data);
	if (time_since_meal > data->args.time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		announce_death(philo);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

static int	monitor_all_philos(t_data *data)
{
	int		i;
	t_philo	*runner;

	i = 0;
	while (i < data->args.num_of_philos)
	{
		runner = &data->philos[i];
		if (check_philo_death(runner, data))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *data_struct)
{
	t_data	*data;

	data = (t_data *)data_struct;
	while (1)
	{
		if (monitor_all_philos(data))
			return (NULL);
		usleep(100);
	}
}
