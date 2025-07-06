/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:12:32 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/06 04:14:33 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int check_stop_flag(t_philo *philo)
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

void    pick_forks(t_philo *philo)
{
    if (philo->id % 2 == 0 )
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
    }
}

void    drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void	check_meal_count(t_philo *philo)
{
    int done;

	if (philo->data->args.num_of_meals == -1)
		return;
	pthread_mutex_lock(&philo->meals_num_mutex);
	philo->meals_num++;
	done = (philo->meals_num == philo->data->args.num_of_meals);
	pthread_mutex_unlock(&philo->meals_num_mutex);

	if (done)
	{
		pthread_mutex_lock(&philo->data->meals_mutex);
		philo->data->meals_eaten++;
		if (philo->data->meals_eaten == philo->data->args.num_of_philos)
			philo->data->stop_flag = 1;
		pthread_mutex_unlock(&philo->data->meals_mutex);
	}
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(1000);
    while (1)
    {
        // die
        if (check_stop_flag(philo))
            break ;
        // eat
        pick_forks(philo);
        print_status(philo, "is eating");
        pthread_mutex_lock(&philo->last_meal_mutex);
        philo->last_meal = current_time(philo->data->start_time);
        pthread_mutex_unlock(&philo->last_meal_mutex);
        ft_sleep(philo, philo->data->args.time_to_eat);
        drop_forks(philo);
        check_meal_count(philo);
        // sleep
        print_status(philo, "is sleeping");
        ft_sleep(philo, philo->data->args.time_to_sleep);
        // overthink
        print_status(philo, "is thinking");
    }
    return (NULL);
}
