/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 03:14:18 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/17 03:49:24 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (check_stop_flag(philo))
			return ;
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		if (check_stop_flag(philo))
			return ;
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	print_status(t_philo *philo, const char *str)
{
	long	time;

	if (check_stop_flag(philo))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	time = current_time(philo->data->start_time);
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_sleep(t_philo *philo, int time)
{
	long	start_time;

	if (check_stop_flag(philo))
		return ;
	start_time = current_time(philo->data->start_time);
	while (current_time(philo->data->start_time) - start_time < time)
	{
		if (check_stop_flag(philo))
			return ;
		usleep(100);
	}
}

void	wait_for_all_threads(t_data *data)
{
	pthread_mutex_lock(&data->ready_mutex);
	while(!data->ready_flag)
	{
		pthread_mutex_unlock(&data->ready_mutex);
		usleep(100);
		pthread_mutex_lock(&data->ready_mutex);
	}
	pthread_mutex_unlock(&data->ready_mutex);
}
