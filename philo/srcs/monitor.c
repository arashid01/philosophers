/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amrashid <amrashid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:22:14 by amrashid          #+#    #+#             */
/*   Updated: 2025/07/06 11:58:10 by amrashid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    announce_death(t_philo *runner)
{
    if (runner->data->stop_flag == 0)
    {
        runner->data->stop_flag = 1;
        print_status(runner, "has died");
    }
}

void    *monitor_routine(void *data_struct)
{
    int     i;
    long    last_time;
    t_data  *data;
    t_philo *runner;

    data = (t_data *)data_struct;
    while (1)
    {
        i = 0;
        while (i < data->args.num_of_philos)
        {
            runner = &data->philos[i];
            pthread_mutex_lock(&runner->last_meal_mutex);
            last_time = current_time(data->start_time) - runner->last_meal;
            printf("Last time: %ld\n", last_time);
            pthread_mutex_unlock(&runner->last_meal_mutex);
            if (last_time > data->args.time_to_die)
            {
                pthread_mutex_lock(&data->death_mutex);
                announce_death(runner);
                pthread_mutex_unlock(&data->death_mutex);
                return (NULL);
            }
            i++;
        }
        usleep(500);
    }
}
