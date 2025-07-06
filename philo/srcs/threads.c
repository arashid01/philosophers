/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:45:41 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/06 02:08:26 by amrashid         ###   ########.fr       */
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

void print_state(t_philo *philo, const char *str)
{
    long time;

    pthread_mutex_lock(&philo->data->print_mutex);
    if (philo->data->stop_flag == 1)
    {
        pthread_mutex_unlock(&philo->data->print_mutex);
        return ;
    }
    time = current_time(philo->data->start_time);
    printf("%ld ms philo %d %s\n", time, philo->id, str);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

void    pick_forks(t_philo *philo)
{
    if (philo->id % 2 == 0 )
    {
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken left fork");
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken right fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        print_state(philo, "has taken right fork");
        pthread_mutex_lock(philo->left_fork);
        print_state(philo, "has taken left fork");
    }
}

void    *philo_routine(void *arg)
{
    t_philo *philo;
    // long    time;

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
        print_state(philo, "is eating");
    }
    return (NULL);
}

int create_philos_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->args.num_of_philos)
    {
        data->philos[i].data = data;
        if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
        {
            destroy_philo_mutexes(data, i);
            free(data->philos);
            return (0);
        }
        i++;
    }
    return (1);
}

void    join_philos_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->args.num_of_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
}
