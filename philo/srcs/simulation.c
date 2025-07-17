/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:12:32 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/17 03:30:06 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_stop_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->stop_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

void	check_meal_count(t_philo *philo)
{
	int	done;

	if (philo->data->args.num_of_meals == -1)
		return ;
	pthread_mutex_lock(&philo->nmeals);
	philo->meals_num++;
	done = (philo->meals_num == philo->data->args.num_of_meals);
	pthread_mutex_unlock(&philo->nmeals);
	if (done)
	{
		pthread_mutex_lock(&philo->data->meals_mutex);
		philo->data->meals_eaten++;
		if (philo->data->meals_eaten == philo->data->args.num_of_philos)
			philo->data->stop_flag = 1;
		pthread_mutex_unlock(&philo->data->meals_mutex);
	}
}

void	handle_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->stop_flag = 1;
	pthread_mutex_unlock(&philo->data->death_mutex);
	usleep(philo->data->args.time_to_die * 1000);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d died\n", current_time(philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	eat_routine(t_philo *philo)
{
	pick_forks(philo);
	print_status(philo, "is eating");
	ft_sleep(philo, philo->data->args.time_to_eat);
	pthread_mutex_lock(&philo->lm_mutex);
	philo->last_meal = current_time(philo->data->start_time);
	pthread_mutex_unlock(&philo->lm_mutex);
	drop_forks(philo);
	check_meal_count(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->args.num_of_philos == 1)
	{
		handle_one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 != 0)
		usleep(100);
	while (1)
	{
		usleep(153);
		if (check_stop_flag(philo))
			break ;
		eat_routine(philo);
		print_status(philo, "is thinking");
		print_status(philo, "is sleeping");
		ft_sleep(philo, philo->data->args.time_to_sleep);
	}
	return (NULL);
}
